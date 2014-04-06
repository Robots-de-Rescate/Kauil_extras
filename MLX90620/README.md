Sensor térmico
==============

Descripción:
--------------


El sensor MLX90620 de la marca MELEXIS, realiza una imagen termográfica de bajo costo. Este sensor por medio de termopilas integradas puede captar rayos UV que pueden ser traducidos a voltaje para poder ser interpretados como temperatura. El sensor contiene 2 chips dentro de este, una memoria EEPROM y una RAM. La memoria EEPROM guarda valores de calibración que deberán ser cargados a la memoria RAM del MCU que se esté usando para mejor desempeño, que a su vez servirán para que el mismo sensor convierta los voltajes en temperaturas usando la memoria RAM del MLX90620.


+ Se hace uso de un Arduino para realizar la comunicación con el sensor por medio de I2C.

+ Se utiliza Python con la librería tk  para gráficar los 64 pixeles en base a la temperatura registrada.

Carpetas y archivos:
--------------
+ Carpeta MLX90620S - Contiene la librería para la comunicació con el sensor por medio del bus de comunicación  I2C.
	Es importante copiar la carpeta de la librería al lugar correspondiente del [IDE del Arduino.] (http://arduino.cc/en/Guide/Libraries)
	
	<pre><code> cp MLX90620S ~/sketchbook/libraries </code></pre>


	La misma librería contiene los siguientes códigos de ejemplo:
		MLX90620Serial - Código para el funcionamiento directamente con python.
		MLX90620ROS_String - Código para el funcionamiento con ROS por medio de Strings.
		MLX90620ROS_Int16Array - Código para el funcionamuento con ROS por medio de un Arreglo.

+ GUIMLX90620.py - Código para correrlo directamente con Python

La interfaz gráfica para el funcionamiento con ROS se encuentra en el paquete "MLX9062" ubicado en el reposotorio Kauil_ROS.



