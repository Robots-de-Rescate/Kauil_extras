#include "MLX90620S.h"
#include <Arduino.h>
#include <i2cmaster.h>
#include <ros.h>
#include <std_msgs/String.h>

ros::NodeHandle  nh;

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

int count = 0;
float* temperatureSensor;

char temp[8];

void setup(){
  i2c_init();
  delay(5);
  
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
    for(int i=0;i<65;i++){
        dtostrf(temperatureSensor[i], 5, 4, temp);
        str_msg.data = temp;
        chatter.publish( &str_msg );
        nh.spinOnce();
        delay(15);
    }
}
