#include <i2cmaster.h>

int freq = 16;  //Set this value to your desired refresh rate
int IRDATA[64];                          // Arreglo con capacidad para 64 ints. Temperatura de cada uno de los 64 pixeles
byte EEPROM_DATA[256];                   // Arreglo con capacidad para 256 bytes. Contenido de los datos de la memoria EEPROM 
byte CFG_LSB, CFG_MSB,TRI_LSB,TRI_MSB, PTAT_LSB, CPIX_LSB, CPIX_MSB, PIX_LSB, PIX_MSB;
int PIX, v_th, CPIX;
float ta, to, emissivity, k_t1, k_t2;
float temperatures[65];
int count=0;
unsigned int PTAT, PTAT_MSB;
int a_cp, b_cp, tgc, b_i_scale;
int a_ij[64];
int b_ij[64];

float alpha_ij[64] = {

  1.77516E-8, 1.93232E-8, 1.85083E-8, 1.63546E-8, 2.03127E-8, 2.18843E-8, 2.08948E-8, 1.83336E-8, 

  2.22918E-8, 2.40380E-8, 2.32231E-8, 1.99052E-8, 2.42126E-8, 2.56096E-8, 2.48529E-8, 2.10694E-8, 

  2.52021E-8, 2.70066E-8, 2.56096E-8, 2.18843E-8, 2.60171E-8, 2.77633E-8, 2.61917E-8, 2.28738E-8, 

  2.73558E-8, 2.89856E-8, 2.73558E-8, 2.36305E-8, 2.85782E-8, 2.99170E-8, 2.79961E-8, 2.38634E-8, 

  2.83454E-8, 2.99170E-8, 2.83454E-8, 2.42126E-8, 2.83454E-8, 2.95677E-8, 2.83454E-8, 2.36305E-8, 

  2.79961E-8, 2.93349E-8, 2.77633E-8, 2.34559E-8, 2.77633E-8, 2.93349E-8, 2.67737E-8, 2.26410E-8, 

  2.67737E-8, 2.77633E-8, 2.64245E-8, 2.22336E-8, 2.52021E-8, 2.64245E-8, 2.46201E-8, 2.04873E-8, 

  2.28738E-8, 2.44454E-8, 2.22918E-8, 1.89157E-8, 2.04873E-8, 2.13022E-8, 2.00799E-8, 1.65292E-8, 

};

///Paso 1. Cargar los datos de calibracion de la memoria EEPROM a la memoria RAM. 
void read_EEPROM_MLX90620(){
   i2c_start_wait(0xA0);                    // Se envia la senal de START, la DIRECCION del dispositivo esclavo (EEPROM) y la direccion de transferencia, siempre que el BUS de comunicacion este disponible, si no es asi, espera a que se libere para iniciar comunicacion. 
   i2c_write(0x00);                         // Se envia el comando Whole EEPROM dump
   i2c_rep_start(0xA1);                     // Envia un Start repetido, envia la DIRECION del dispositivo esclavo (EEPROM) y la direccion de transferencia.  
     for(int i=0;i<256;i++){
       EEPROM_DATA[i]= i2c_readAck();       // Lee un byte del dispositivo esclavo y demanda mas datos de este.
     }
   i2c_stop();                              // Termina con la transferencia de datos y libera el BUS de I2C
   
}


// Paso 2. Inicializacion de las variables variables V_th(25), K_t1, k_t2, emissivity, a_cp, b_cp, tgc, b_i_scale. Esto con datos especificos del arreglo EEPROM_DATA 
void varInitialization(byte EEPROM_DATA[]){
  v_th = (EEPROM_DATA[219] <<8) + EEPROM_DATA[218];              // Se calculan las varibles de acuerdo a los valore encontrados en el arreglo EEPROM_DATA 
  k_t1 = ((EEPROM_DATA[221] <<8) + EEPROM_DATA[220])/1024.0;     // Se calculan las varibles de acuerdo a los valore encontrados en el arreglo EEPROM_DATA
  k_t2 =((EEPROM_DATA[223] <<8) + EEPROM_DATA[222])/1048576.0;   // Se calculan las varibles de acuerdo a los valore encontrados en el arreglo EEPROM_DATA
  
  a_cp = EEPROM_DATA[212];            // Compensation pixel individial offset
  if(a_cp > 127){
    a_cp = a_cp - 256;
  }
  b_cp = EEPROM_DATA[213];            // Individual Ta dependence (slope) of the compensation pixel offset
  if(b_cp > 127){
    b_cp = b_cp - 256;
  }
  tgc = EEPROM_DATA[216];             // Thermal Gradien Coefficient
  if(tgc > 127){
    tgc = tgc - 256;
  }

  b_i_scale = EEPROM_DATA[217];      // Scaling coeficient of slope of IR pixels offset

  emissivity = (((unsigned int)EEPROM_DATA[229] << 8) + EEPROM_DATA[228])/32768.0;  //Emissivity coefficient

  for(int i=0;i<=63;i++){          // IR pixels individual offset coefficients
    a_ij[i] = EEPROM_DATA[i];
    if(a_ij[i] > 127){
      a_ij[i] = a_ij[i] - 256;
    }
    b_ij[i] = EEPROM_DATA[64+i];    // Individual Ta dependence (slope) of IR pixels offset
    if(b_ij[i] > 127){
      b_ij[i] = b_ij[i] - 256;
    }
  }
}
// Paso 3. Se escribe el valor de ocilador en el registro 0x93 de la RAM
void write_trimming_value(byte val){        // Funcion que escribe el valor del oscilador. Valor contenido el la EEPROM predeterminado por MELEXIS
   i2c_start_wait(0xC0);                    // Se envia la senal de START, la DIRECCION del dispositivo esclavo (RAM) y la direccion de transferencia, siempre que el BUS de comunicacion este disponible, si no es asi, espera a que se libere para iniciar comunicacion. 
   i2c_write(0x04);                         // Se envia el comando para Escribir el valor.
   i2c_write((byte)val-0xAA);               // Se envia el LSByte check
   i2c_write(val);                          // Se envia el LSByte
   i2c_write(0x56);                         // Se envia el MSByte check
   i2c_write(0x00);                         // Se envia el MSByte
   i2c_stop();                              // Se envia la condicion de paro
}

//Paso 4. Se escriben seleccionan los bits del REGISTRO DE CONFIGURACION. Se le envia como parametro la velocidad de actualizacion.  
void config_MLX90620_Hz(int Hz){            // Aqui se seleccionan el valor del LSByte dependiendo de valor de Hz
  byte Hz_LSB;
  switch(Hz){
    case 0:
      Hz_LSB = B00001111;                   // Si la la velocidad de actualizacion es de 0Hz, el LSByte del registro, tendra la configuracion de HzLSB 
      break;
    case 1:
      Hz_LSB = B00001110;                   // Si la la velocidad de actualizacion es de 1Hz, el LSByte del registro, tendra la configuracion de HzLSB
      break;
    case 2:
      Hz_LSB = B00001101;                   // Si la la velocidad de actualizacion es de 2Hz, el LSByte del registro, tendra la configuracion de HzLSB
      break;
    case 4:
      Hz_LSB = B00001100;                   // Si la la velocidad de actualizacion es de 4Hz, el LSByte del registro, tendra la configuracion de HzLSB
      break;
    case 8:
      Hz_LSB = B00001011;                   // Si la la velocidad de actualizacion es de 8Hz, el LSByte del registro, tendra la configuracion de HzLSB
      break;
    case 16:
      Hz_LSB = B00001010;                   // Si la la velocidad de actualizacion es de 16Hz, el LSByte del registro, tendra la configuracion de HzLSB
      break;
    case 32:
      Hz_LSB = B00001001;                   // Si la la velocidad de actualizacion es de 32Hz, el LSByte del registro, tendra la configuracion de HzLSB
      break;
    default:
      Hz_LSB = B00001110;                   // Si la la velocidad de actualizacion no es ninguna de las anteriores, el LSByte del registro, tendra la configuracion de HzLSB
  }
  i2c_start_wait(0xC0);                     // Se envia la senal de START, la DIRECCION del dispositivo esclavo (RAM) y la direccion de transferencia, siempre que el BUS de comunicacion este disponible, si no es asi, espera a que se libere para iniciar comunicacion.
  i2c_write(0x03);                          // Se envia el comando para Escribir el valor en el REGISTRO DE CONFIGURACION.
  i2c_write((byte)Hz_LSB-0x55);             // Se envia el LSByte check
  i2c_write(Hz_LSB);                        // Se envia el LSByte
  i2c_write(0x1F);                          // Se envia el MSByte check
  i2c_write(0x74);                          // Se envia el MSByte
  i2c_stop();                               // Se envia la condicion de paro
}

// Paso 5. Leer el valor escrito en el registro para el Oscilador (registro 0x93)
void read_Trimming_Reg_MLX90620(){
  i2c_start_wait(0xC0);                     // Se envia la senal de START, la DIRECCION del dispositivo esclavo (RAM) y la direccion de transferencia, siempre que el BUS de comunicacion este disponible, si no es asi, espera a que se libere para iniciar comunicacion.
  i2c_write(0x02);                          // Se envia el comando para indicar que se quiere accesar a este valor.
  i2c_write(0x93);                          // Se envia la direccion a partir donde se empezara a leer
  i2c_write(0x00);                          // Se envia el numero de Saltos entre cada direccion a leer
  i2c_write(0x01);                          // Se envia el numero de lecturas que se haran. 
  i2c_rep_start(0xC1);                      // Envia un Start repetido, envia la DIRECION del dispositivo esclavo (EEPROM) y la direccion de transferencia.
  TRI_LSB = i2c_readAck();                  // Lee un byte del dispositivo esclavo y demanda mas datos de este.
  TRI_MSB = i2c_readAck();                  // Lee un byte del dispositivo esclavo y demanda mas datos de este.
  i2c_stop();                               // Se envia la condicion de paro
  //Serial.println(TRI_LSB, HEX);
  //Serial.println(TRI_MSB, HEX);
  
}

//Paso 6. Leer el valor escrito en el REGISTRO DE CONFIGURACION
void read_Config_Reg_MLX90620(){
  i2c_start_wait(0xC0);                     // Se envia la senal de START, la DIRECCION del dispositivo esclavo (RAM) y la direccion de transferencia, siempre que el BUS de comunicacion este disponible, si no es asi, espera a que se libere para iniciar comunicacion.
  i2c_write(0x02);                          // Se envia el comando para indicar que se quiere accesar a este valor. 
  i2c_write(0x92);                          // Se envia la direccion a partir donde se empezara a leer
  i2c_write(0x00);                          // Se envia el numero de Saltos entre cada direccion a leer
  i2c_write(0x01);                          // Se envia el numero de lecturas que se haran. 
  i2c_rep_start(0xC1);                      // Envia un Start repetido, envia la DIRECION del dispositivo esclavo (EEPROM) y la direccion de transferencia.
  CFG_LSB = i2c_readAck();                  // Lee un byte del dispositivo esclavo y demanda mas datos de este.
  CFG_MSB = i2c_readAck();                  // Lee un byte del dispositivo esclavo y demanda mas datos de este.
  i2c_stop();                               // Se envia la condicion de paro
  //Serial.println(CFG_LSB, HEX);
  //Serial.println(CFG_MSB, HEX);
  
}
// Paso 7. Leer los datos de temperatura ambiente absoluta (PTAT) de la EEPROM 
void read_PTAT_Reg_MLX90620(){
  i2c_start_wait(0xC0);                     // Se envia la senal de START, la DIRECCION del dispositivo esclavo (RAM) y la direccion de transferencia, siempre que el BUS de comunicacion este disponible, si no es asi, espera a que se libere para iniciar comunicacion.
  i2c_write(0x02);                          // Se envia el comando para indicar que se quiere accesar a este valor. 
  i2c_write(0x90);                          // Se envia la direccion a partir donde se empezara a leer
  i2c_write(0x00);                          // Se envia el numero de Saltos entre cada direccion a leer
  i2c_write(0x01);                          // Se envia el numero de lecturas que se haran. 
  i2c_rep_start(0xC1);                      // Envia un Start repetido, envia la DIRECION del dispositivo esclavo (EEPROM) y la direccion de transferencia.  
  PTAT_LSB = i2c_readAck();                 // Lee un byte del dispositivo esclavo y demanda mas datos de este.
  PTAT_MSB = i2c_readAck();                 // Lee un byte del dispositivo esclavo y demanda mas datos de este.
  i2c_stop();                               // Se envia la condicion de paro
  PTAT = (PTAT_MSB << 8) + PTAT_LSB;        // Se guardan los valores leidos para obtener la temperatura ambiente
  //Serial.println(PTAT, DEC);
}

// Paso 8. Lectura de los datos IR de la RAM
void read_IR_ALL_MLX90620(){
  i2c_start_wait(0xC0);                     // Se envia la senal de START, la DIRECCION del dispositivo esclavo (RAM) y la direccion de transferencia, siempre que el BUS de comunicacion este disponible, si no es asi, espera a que se libere para iniciar comunicacion.
  i2c_write(0x02);                          // Se envia el comando para indicar que se quiere accesar a este valor.
  i2c_write(0x00);                          // Se envia la direccion a partir donde se empezara a leer
  i2c_write(0x01);                          // Se envia el numero de Saltos entre cada direccion a leer
  i2c_write(0x40);                          // Se envia el numero de lecturas que se haran. 
  i2c_rep_start(0xC1);                      // Envia un Start repetido, envia la DIRECION del dispositivo esclavo (EEPROM) y la direccion de transferencia.
  for(int i=0;i<64;i++){                    // Ciclo for para repetirse 64 veces y poder leer los 64 pixeles
    PIX_LSB = i2c_readAck();                // Lee un byte del dispositivo esclavo y demanda mas datos de este.
    PIX_MSB = i2c_readAck();                // Lee un byte del dispositivo esclavo y demanda mas datos de este. 
    IRDATA[i] = (PIX_MSB << 8) + PIX_LSB;   // Se guarda el el arreglo IRDATA los valores de cada pixel 
  }
  i2c_stop();                               // Se envia la condicion de paro
}


//. Paso 9. Se calcula la TEMPERATURA ABSOLUTA DEL CHIP Ta (sensor de temperatura)
void calculate_TA(){ 
  ta = (-k_t1 + sqrt(square(k_t1) - (4 * k_t2 * (v_th - (float)PTAT))))/(2*k_t2) + 25; 	//Se calcula de acuerdo a la formula de el DATASHEET DEL MLX90620 de una manera sencilla
  Serial.println(ta);
}

// Paso 10. Se calcula la constante V_cp que se guardara en CPIX 
void read_CPIX_Reg_MLX90620(){
  i2c_start_wait(0xC0);                     // Se envia la senal de START, la DIRECCION del dispositivo esclavo (RAM) y la direccion de transferencia, siempre que el BUS de comunicacion este disponible, si no es asi, espera a que se libere para iniciar comunicacion.
  i2c_write(0x02);                          // Se envia el comando para indicar que se quiere accesar a este valor.
  i2c_write(0x91);                          // Se envia la direccion a partir donde se empezara a leer
  i2c_write(0x00);                          // Se envia el numero de Saltos entre cada direccion a leer
  i2c_write(0x01);                          // Se envia el numero de lecturas que se haran.
  i2c_rep_start(0xC1);                      // Envia un Start repetido, envia la DIRECION del dispositivo esclavo (EEPROM) y la direccion de transferencia.
  CPIX_LSB = i2c_readAck();                 // Lee un byte del dispositivo esclavo y demanda mas datos de este.
  CPIX_MSB = i2c_readAck();                 // Lee un byte del dispositivo esclavo y demanda mas datos de este.
  i2c_stop();                               // Se envia la condicion de paro
  CPIX = (CPIX_MSB << 8) + CPIX_LSB;        // Se guardan los valores leidos para obtener la temperatura ambiente
}

// Paso 11. Se calcula la temperatura especifica a cada pixel en la matriz
void calculate_TO(){
  float v_ir_tgc_comp[64];
  float v_cp_off_comp = (float) CPIX - (a_cp + (b_cp/pow(2, b_i_scale)) * (ta - 25)); //this is needed only during the to calculation, so I declare it here.
  
  for (int i=0; i<64; i++){
    v_ir_tgc_comp[i] = IRDATA[i] - (a_ij[i] + (float)(b_ij[i]/pow(2, b_i_scale)) * (ta - 25)) - (((float)tgc/32)*v_cp_off_comp);
    //v_ir_comp[i]= v_ir_tgc_comp[i] / emissivity;									

//removed to save SRAM, since emissivity in my case is equal to 1. 
    //temperatures[i] = sqrt(sqrt((v_ir_comp[i]/alpha_ij[i]) + pow((ta + 273.15),4))) - 273.15;
    temperatures[i] = sqrt(sqrt((v_ir_tgc_comp[i]/alpha_ij[i]) + pow((ta + 273.15),4))) - 273.15;	//edited to work with v_ir_tgc_comp instead of v_ir_comp
  }
}

// Paso 12.
void check_Config_Reg_MLX90620(){
  read_Config_Reg_MLX90620();
  if ((!CFG_MSB & 0x04) == 0x04){
    config_MLX90620_Hz(freq);
  }
}

void Temperatures_Serial_Transmit(){
  temperatures[64]= 500.00;
  for(int i=0;i<65;i++){
    //Serial.print(i);
    Serial.println(temperatures[i]);  
    delay(15);
  }
}
/*
void setup(){
i2c_init();
Serial.begin(9600);
read_EEPROM_MLX90620();                    //Paso1
varInitialization(EEPROM_DATA);            //Paso2
write_trimming_value(EEPROM_DATA[247]);    //Paso3
config_MLX90620_Hz(freq);                  //Paso4
read_Trimming_Reg_MLX90620();              //Paso5
read_Config_Reg_MLX90620();                //Paso6
read_PTAT_Reg_MLX90620();                  //Paso7
read_IR_ALL_MLX90620();                    //Paso8
calculate_TA();                            //Paso9 
}

void loop (){
  
}
*/

void setup(){
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  i2c_init(); 
  delay(5);
  read_EEPROM_MLX90620();
  varInitialization(EEPROM_DATA);            //Paso2
  write_trimming_value(EEPROM_DATA[247]);    //Paso3
  config_MLX90620_Hz(freq);
}

void loop(){
  if(count ==0){		//TA refresh is slower than the pixel readings, I'll read the values and computate them not every loop. 
    read_PTAT_Reg_MLX90620();
    calculate_TA();
    check_Config_Reg_MLX90620();
  }
  count++;
  if(count >=16){
    count = 0;
  }
  read_IR_ALL_MLX90620();
  read_CPIX_Reg_MLX90620();
  calculate_TO();
  Temperatures_Serial_Transmit();
  
}MLX90620MLX90620MLX90620MLX90620
