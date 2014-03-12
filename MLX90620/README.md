Sensor térmico
==============

Descripción:
--------------


El sensor MLX90620 de la marca MELEXIS, realiza una imagen termográfica de bajo costo. Este sensor por medio de termopilas integradas puede captar rayos UV que pueden ser traducidos a voltaje para poder ser interpretados como temperatura. El sensor contiene 2 chips dentro de este, una memoria EEPROM y una RAM. La memoria EEPROM guarda valores de calibración que deberán ser cargados a la memoria RAM del MCU que se esté usando para mejor desempeño, que a su vez servirán para que el mismo sensor convierta los voltajes en temperaturas usando la memoria RAM del MLX90620.


+ Se hace uso de un Arduino para realizar la comunicación con el sensor por medio de I2C.

+ Se utiliza una Raspberry Pi para gráficar los 64 pixeles en base a la temperatura registrada.

Archivos:
--------------
+ MLX90620.c - Código para el Arduino

+ GUIMLX90620.py - Código para la Raspberry Pi



