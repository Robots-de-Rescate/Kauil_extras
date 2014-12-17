Kauil_extras
============

**Archivos**:

-  Archivos de configuración del sistema operativo para la correcta operación del robot.
-  Archivos para el funcionamiento del sensor térmico MLX9060.
-  La carpeta  TEW-684UB contiene el driver de la interfase de WiFi del CPU Intel Atom en el robot. 


Para iniciar los ambientes de ROS correctamente es necesario copiar las
siguientes líneas de código en el archivo ~/.bashrc pues este siempre se
ejecuta antes de iniciar una terminal y puede definir las variables de
entorno necesarias para usar los comandos de ROS.

La configuración básica de una máquina requiere haber creado una carpeta
llamada ~/fuerte_workspace donde estará todo el código del repositorio
kauil_ROS, y copiar las siguientes líneas a ~/.bashrc:

        source /opt/ros/fuerte/setup.bash
        export ROS_PACKAGE_PATH=~/fuerte_workspace:$ROS_PACKAGE_PATH
        export ROS_WORKSPACE=~/fuerte_workspace

Además de estas líneas para la configuración de la red de las maquinas se
deben añadir las siguientes líneas:

    

    export ROS_HOSTNAME=`hostname`.local
    export ROS_MASTER_URI=http://robot.local:11311

Esto hace que ROS_HOSTNAME tome el nombre de host de la maquina que se está onfigurando y ROS_MASTER_URI es el nombre de host de la computadora que está sobre kauil. En nuestro caso particular, las computadoras tienen los nombres robot.local y estacion.local.

#To do

- [ ] Documentar como se realiza ssh a Kauil desde la estación remota 
