#/bin/bash -e

roslaunch_PID=(`ps -A | grep roslaunch`)

kill `echo ${roslaunch_PID[0]}`
