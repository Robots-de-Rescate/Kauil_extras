//
//  MLX90620S.h
//  
//
//  Created by Andres Tosca Ramírez on 3/28/14.
//
//

#ifndef _MLX90620S_h
#define _MLX90620S_h

void read_EEPROM_MLX90620();
void varInitialization(unsigned char EEPROM_DATA[]);
void write_trimming_value(unsigned char val);
void config_MLX90620_Hz(int Hz);
void read_Trimming_Reg_MLX90620();
void read_Config_Reg_MLX90620();
void read_PTAT_Reg_MLX90620();
void read_IR_ALL_MLX90620();
void calculate_TA();
void read_CPIX_Reg_MLX90620();
void calculate_TO();
void check_Config_Reg_MLX90620();
void Temperatures_Serial_Transmit();
void setupSensor();
float* getTemperatureArray();
void sensorTARefresh();
void readSensor();


#endif
