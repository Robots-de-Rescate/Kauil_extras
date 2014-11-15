#!/bin/bash -e

#Configura el entorno de ROS, como si se ejecutara .bashrc normalmente
#Es importante cuando se esta corriendo este script automaticamente desde rc.local

source /opt/ros/fuerte/setup.bash
export ROS_PACKAGE_PATH=~/fuerte_workspace:$ROS_PACKAGE_PATH
export ROS_WORKSPACE=~/fuerte_workspace
export ROS_HOSTNAME=robot.local
export ROS_MASTER_URI=http://robot.local:11311

#Crea variables globales que le indican a roslaunch la ubicación en /dev
#del arduino y la interfaz I2C

#Variable set for STM32 board 
export STM32_PORT=`find /dev | grep "STM32"`
#Variable set for Hokuyoexport HOKUYO_PORT= `find /dev | grep "usb-Hokuyo"`
export HOKUYO_PORT=`find /dev | grep "Hokuyo"`
exec roslaunch ~/fuerte_workspace/rosLaunch/robotKauil.launch
