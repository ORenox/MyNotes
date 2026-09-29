Ejecuta este comando para instalar todos los paquetes necesarios:

```bash
sudo pacman -S qemu-full virt-manager virt-viewer dnsmasq vde2 openbsd-netcat libvirt iptables-nft
```

en caso de salirme un error 404:

![[Pasted image 20260929170950.png]]

Ese error **404** significa que los servidores (espejos) desde donde tu sistema intenta descargar los paquetes están un poco desactualizados con respecto a los archivos más nuevos que salieron para Arch. 

En Arch Linux y CachyOS, esto se soluciona obligando a pacman a sincronizar y actualizar las bases de datos de los repositorios antes de descargar cualquier cosa.

```bash
sudo pacman -Syu qemu-full virt-manager virt-viewer dnsmasq vde2 openbsd-netcat libvirt iptables-nft
``` 
![[Pasted image 20260929171210.png]]

Te explico rápidamente qué está pasando de forma sencilla: tu sistema quiere actualizar la librería principal `pcre2` a la versión `10.48`, pero la versión de 32 bits (`lib32-pcre2`) en tu computadora aún exige exactamente la versión `10.47`. Como `pacman` protege tu sistema para que nada deje de funcionar, prefiere detenerse antes de romper esa dependencia.

Dado que `lib32-pcre2`
suele ser requerida temporalmente por aplicaciones de 32 bits (como Steam o Wine), podemos forzar a `pacman` a remover esa restricción, actualizar todo el sistema y completar nuestra instalación de golpe.

1. Remueve el paquete conflictivo de 32 bits (sin romper sus dependencias asociadas):

```bash
	sudo pacman -Rdd lib32-pcre2
	(El comando -Rdd le dice a pacman: "Sé lo que hago, elimina este paquete específico e ignora temporalmente qué otros programas lo necesitan").
```
2. **Lanza la actualización completa e instala las herramientas de virtualización:**  

Ahora que la traba no existe, refrescaremos todo el sistema e instalaremos el entorno para tu máquina virtual ejecutando:

```bash
sudo pacman -Syu qemu-full virt-manager virt-viewer dnsmasq vde2 openbsd-netcat libvirt iptables-nft
```

3. (Opcional) Regresa el paquete a su lugar:

Una vez que termine la instalación del paso anterior, el sistema ya tendrá la versión de `pcre2` al día. Puedes volver a instalar la versión correcta de 32 bits sin ningún error corriendo:

```bash
sudo pacman -S lib32-pcre2
```

# configuración

```bash
Ahora, activa y arranca los servicios del sistema para que se ejecuten automáticamente:

sudo systemctl enable --now libvirtd

Para poder gestionar tus máquinas virtuales sin que te pida contraseña de administrador (`sudo`) a cada rato, añade tu usuario al grupo de virtualización:

sudo usermod -aG libvirt $(whoami)



```


