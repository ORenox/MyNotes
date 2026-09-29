```docker
version: '3.8' 
services: 
	pihole: 
		container_name: pihole 
		image: pihole/pihole:latest 
		ports: 
		- "53:53/tcp" 
		- "53:53/udp" 
		- "8081:80" 
		environment: 
		- TZ=America/Mexico_City 
		- WEBPASSWORD=dockerdemo 
		- DNS1=1.1.1.1 
		- DNS2=8.8.8.8 
		- DNSMASQ_LISTENING=all 
		restart: unless-stopped
```

es lo mismo que esta en esta imagen

- **`docker run -d --name pihole`**: Descarga e inicia el contenedor en segundo plano (modo _detached_ o `-d`) y le asigna el nombre "pihole" para que puedas identificarlo fácilmente.
- - **`-e TZ=America/Mexico_City`**: Configura la variable de entorno de la zona horaria para que los registros y las estadísticas de Pi-hole muestren la hora correcta de la Ciudad de México.
- - **`-e WEBPASSWORD=dockerdemo`**: Establece "dockerdemo" como la contraseña para iniciar sesión en el panel de administración web de Pi-hole.
- **`-e DNS1=1.1.1.1 -e DNS2=8.8.8.8`**: Define los servidores DNS ascendentes a los que Pi-hole consultará cuando una página no esté bloqueada (en este caso, Cloudflare y Google).
- - **`-e DNSMASQ_LISTENING=all`**: Configura Pi-hole para que escuche y responda a las consultas DNS que provengan de cualquier interfaz de red del contenedor.
- **`-p 8081:80`**: Mapea el puerto 80 del contenedor (su interfaz web) al puerto 8081 de tu computadora local. Podrás acceder al panel entrando a `http://localhost:8081/admin`.
- **`-p 53:53/tcp -p 53:53/udp`**: Abre los puertos DNS estándar (53) tanto en protocolo TCP como UDP para que los dispositivos de tu red puedan enviar sus solicitudes de navegación a Pi-hole.
- - **`--restart unless-stopped`**: Configura una política de reinicio automático. Si tu computadora se apaga o Docker se reinicia, el contenedor volverá a encenderse solo, a menos que lo detengas manualmente.
- - **`pihole/pihole`**: Especifica la imagen oficial de Pi-hole que se va a descargar desde Docker Hub para crear el contenedor.
-


password: Pihole@#!


````

 ip -brief -4 address show

lo               UNKNOWN        127.0.0.1/8
wlan0            UP             192.168.100.6/24
br-8f43f6eb1849  UP             172.18.0.1/16
docker0          DOWN           172.17.0.1/16
br-e8d4e248feeb  DOWN           172.19.0.1/16

para saber la ip de mi máquina
```