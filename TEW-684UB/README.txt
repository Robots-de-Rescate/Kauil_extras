Para la instalación del adaptador WiFi TEW-684UB es necesario seguir los 
siguientes pasos:

1. bajar el driver de la página http://wikidevi.com/wiki/TRENDnet_TEW-684UB o
descomprimir el otro archivo en esta carpeta.

2. Revisar que el código fuente del kernel esté instalado en la maquina
ejecutando los siguientes comandos:

	sudo apt-get install build-essential
	sudo apt-get install build-essential linux-headers-`uname -r`

3. revisar que el archivo os/linux/config.mk tenga las líneas como se muestran
a continuación

	...
	# Support Wpa_Supplicant
	HAS_WPA_SUPPLICANT=y
	# Support Native WpaSupplicant for Network Manger
	HAS_NATIVE_WPA_SUPPLICANT_SUPPORT=y
	...

4. Desde una terminal en la carpeta extraida ejecutar los siguientes comandos
para compilar el driver:

	# sudo su
	# make clean
	# make
	# make install

5. Añadir la línea rt3573sta al archivo /etc/modules

6. Cargar el módulo del driver al kernel y re iniciar las conexiones de red:

	# sudo modprobe rt3573sta	
	# sudo /etc/init.d/networking restart
