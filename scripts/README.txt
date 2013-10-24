Esta carpeta contiene scripts que ayudan a iniciar y detener la ejecucion de
los nodos de ROS.

launchKauil.sh:	Define las variables de entorno necesarias para levantar los
		nodos locales en la computadora del robot.

killKauil.sh: 	Busca y mata el proceso local de roslaunch, y por ende todos 
		los nodos que se lanzaron por el mismo.

launchKauil.sh fue pensado para que se ejecute automáticamente en el robot al
momento de encenderse, por esto es necesario que se llame desde el archivo
/etc/rc.local , para esto se debe editar el archivo añadiendo la siguiente 
línea:

	exec su kauil_intel -c "source ~/launchKauil.sh &>~/ROS_start_up.log"

Esta iniciará sesión como kauil_intel y ejecutará el script siempre y cuando
se encuentre en home, además de enviar la salida de la ejecución al archivo
~/ROS_start_up.log para poder detectar errores al momento de cargar todo.
