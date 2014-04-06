#include "MLX90620S.h"
#include <Arduino.h>
#include <i2cmaster.h>
#include <ros.h>
#include <std_msgs/Int16MultiArray.h>

ros::NodeHandle  nh;

//Object of type Int32MultiArray
std_msgs::Int16MultiArray arr_temp1;


//Object of type Int32MultiArray
//std_msgs::Int16MultiArray arr_temp2;


ros::Publisher chatter("chatter", &arr_temp1);
//ros::Publisher chat("chat", &arr_temp2);

int count = 0;
float* temperatureSensor;

char temp[8];

void setup(){
  i2c_init();
  delay(5);
  arr_temp1.data = (int *)malloc(sizeof(int)*8);
  arr_temp1.data_length = 64;
 // arr_temp2.data_length = 32;
  
  setupSensor();
  nh.initNode();
  nh.advertise(chatter);
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
    
    temperatureSensor = getTemperatureArray();
    for(int i=0;i<64;i++){
        
        arr_temp1.data[i] = (int)temperatureSensor[i];
      
    }
    
    for(int i=32;i<65;i++){
   
       // arr_temp2.data[i-32] = (int)temperatureSensor[i]; 
        
    }
    
    chatter.publish( &arr_temp1 );
    //chatter.publish( &arr_temp2 );
    nh.spinOnce();
    delay(500);
}
