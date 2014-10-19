Kauil_extras
============

**Archivos**:

-  Archivos de configuración del sistema operativo para la correcta operación del rot.
-  Archivos para el funcionamiento del sensor térmico MLX9060.


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

    

    export ROS_HOSTNAME=local_hostname
    export ROS_MASTER_URI=http://robot.local:11311

Donde local_hostname es el nombre de host de la máquina que se está configurando
en el caso particular de kauil, las computadoras tienen los nombres robot.local y estacion.local.*

#To do

- [ ] Cambiar los scripts y la documentación de .bashrc de los scripts para que se haga la comunicación entre Kauil y la estación remota por medio del puerto 11311
- [ ] Documentar como se realiza ssh a Kauil desde la estación remota 
