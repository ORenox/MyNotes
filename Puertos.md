```bash
sudo ss -tulpn | grep :53

[sudo] password for reno:
udp   UNCONN 0      0                                0.0.0.0:5353       0.0.0.0:*    users:(("avahi-daemon",pid=665,fd=12))
udp   UNCONN 0      0                                0.0.0.0:5355       0.0.0.0:*    users:(("systemd-resolve",pid=484,fd=13))
udp   UNCONN 0      0                             172.17.0.1:53         0.0.0.0:*    users:(("systemd-resolve",pid=484,fd=24))
udp   UNCONN 0      0                             127.0.0.54:53         0.0.0.0:*    users:(("systemd-resolve",pid=484,fd=22))
udp   UNCONN 0      0                          127.0.0.53%lo:53         0.0.0.0:*    users:(("systemd-resolve",pid=484,fd=20))
udp   UNCONN 0      0                                   [::]:5353          [::]:*    users:(("avahi-daemon",pid=665,fd=13))
udp   UNCONN 0      0                                   [::]:5355          [::]:*    users:(("systemd-resolve",pid=484,fd=15))
tcp   LISTEN 0      4096                             0.0.0.0:5355       0.0.0.0:*    users:(("systemd-resolve",pid=484,fd=14))
tcp   LISTEN 0      4096                          172.17.0.1:53         0.0.0.0:*    users:(("systemd-resolve",pid=484,fd=25))
tcp   LISTEN 0      4096                          127.0.0.54:53         0.0.0.0:*    users:(("systemd-resolve",pid=484,fd=23))
tcp   LISTEN 0      4096                       127.0.0.53%lo:53         0.0.0.0:*    users:(("systemd-resolve",pid=484,fd=21))
tcp   LISTEN 0      4096                                [::]:5355          [::]:*    users:(("systemd-resolve",pid=484,fd=16))
```


¡Perfecto! El misterio está completamente resuelto. El culpable absoluto es **`systemd-resolved`** (identificado en tu salida como `systemd-resolve` con el PID 484).

Está escuchando en el puerto 53 de múltiples interfaces (incluyendo la IP interna de Docker `172.17.0.1`), lo que bloquea por completo el arranque de Pi-hole.

Para liberar el puerto en CachyOS de forma definitiva y limpia sin romper el internet de tu computadora, ejecuta esta secuencia de comandos en tu terminal:

Paso 1: Desactivar el resolvedor intruso

Vamos a detener el servicio y a decirle al sistema que no vuelva a encenderlo automáticamente cuando reinicies la PC:

zsh

```
sudo systemctl stop systemd-resolved
sudo systemctl disable systemd-resolved
```

Usa el código con precaución.

---

Paso 2: Ajustar el archivo de configuración DNS del sistema

Cuando apagas `systemd-resolved`, el enlace simbólico del archivo que gestiona tu internet (`/etc/resolv.conf`) puede quedar roto o apuntando a la nada. Vamos a asegurarnos de que tu computadora siga teniendo internet temporalmente usando los DNS de Cloudflare antes de prender Pi-hole.

1. Borra el enlace viejo:
    
    zsh
    
    ```
    sudo rm /etc/resolv.conf
    ```
    
    Usa el código con precaución.
    
2. Crea un archivo nuevo y limpio:
    
    zsh
    
    ```
    sudo nano /etc/resolv.conf
    ```
    
    Usa el código con precaución.
    
3. Pega estas dos líneas adentro:
    
    text
    
    ```
    nameserver 1.1.1.1
    nameserver 8.8.8.8
    ```
    
    Usa el código con precaución.
    
4. Guarda y sal (`Ctrl + O`, `Enter`, `Ctrl + X`).

---

Paso 3: Lanzar Pi-hole en Docker

Ahora que el puerto 53 está 100% libre, ejecuta los comandos para limpiar el viejo intento de Docker y levantar el servicio con éxito:

zsh

```
docker compose down
docker compose up -d
```

Usa el código con precaución.

---

Paso 4: Comprobación final

Para confirmar que todo funcionó de maravilla, revisa el estado del contenedor:

zsh

```
docker ps
```

Usa el código con precaución.

Si todo salió bien, verás que la columna `STATUS` dice **`Up (healthy)`**. A partir de ese momento, abre tu navegador web e ingresa a la interfaz usando el puerto alternativo que configuramos en el paso anterior:

text

```
http://192.168.100.6:8080
```


#Importante

sudo nano /etc/systemd/resolved.conf
comentar
DNSStubListener=no



2. Cambiar el enlace del resolvedor de DNS

Por defecto, Linux crea un enlace simbólico que apunta a su propio resolvedor interno. Debes redirigirlo para que no pierdas conexión a internet en la máquina mientras levantas Docker: [[1](https://blog.steveyi.net/en/posts/ubuntu-53-port-already-in-use/)]

bash

```
sudo ln -sf /run/systemd/resolve/resolv.conf /etc/resolv.conf
```

Usa el código con precaución.

3. Reiniciar el servicio del sistema

Aplica la nueva configuración reiniciando el servicio encargado de la red: [[1](https://discourse.pi-hole.net/t/update-what-to-do-if-port-53-is-already-in-use/52033), [2](https://discourse.pi-hole.net/t/docker-unable-to-bind-to-port-53/45082)]

bash

```
sudo systemctl restart systemd-resolved
```