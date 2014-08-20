#!/bin/bash -e

#Configura el entorno de ROS, como si se ejecutara .bashrc normalmente

source /opt/ros/fuerte/setup.bash
export ROS_PACKAGE_PATH=~/fuerte_workspace:$ROS_PACKAGE_PATH
export ROS_WORKSPACE=~/fuerte_workspace
export ROS_HOSTNAME=robot.local
export ROS_MASTER_URI=http://robot.local:40876

#Crea variables globales que le indican a roslaunch la ubicación en /dev
#del arduino y la interfaz I2C

export ARDUINO_PORT=`find /dev | grep "arduino"`
#Variable set for ARM I2C Interface
export ISS_PORT_ARM=`find /dev | grep "ISS._00001973"`
#Variable set for Kauil motors I2C Interface
export ISS_PORT_Kauil=`find /dev | grep "ISS._00001974"`

exec roslaunch -p 40876 ~/fuerte_workspace/rosLaunch/robotKauilARM.launch


