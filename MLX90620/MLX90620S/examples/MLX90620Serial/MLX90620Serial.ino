#include "MLX90620S.h"
#include <Arduino.h>
#include <i2cmaster.h>
int count = 0;
float* temperatureSensor;

void setup(){
  Serial.begin(9600);
  i2c_init();
  delay(5);
  
  setupSensor();
}

void loop(){  
  if(count == 0){		//TA refresh is slower than the pixel readings, I'll read the values and computate them not every loop. 
        sensorTARefresh();
    }
    count++;
    if(count >=16){
        count = 0;
    }
    
    readSensor();
    
    //Temperatures_Serial_Transmit();
    
    temperatureSensor = getTemperatureArray();
    for(int i=0;i<65;i++){
        //Serial.print(i);
        Serial.println(temperatureSensor[i]);
        delay(15);
    }
}
