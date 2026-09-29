[[SSH CONFIGURACION WINDOWS]]
[[Linux Cliente SSH]]

Sí. Si ambas PCs son tuyas y están en la misma red, el ejercicio perfecto es montar **SSH + transferencia de archivos**. En Linux, una opción muy buena es **SFTP sobre SSH**.

La idea será:

```
PC A                         PC B
tu PC                        otra PC
192.168.1.20                 192.168.1.30
   │                             │
   │────── SSH / SFTP :22 ──────│
   │                             │
   └──── acceder a archivos ─────┘
```

## 1. En la otra PC instala un servidor SSH

En la **otra PC**, si es Arch/CachyOS:

```
sudo pacman -S openssh
```

Comprueba que está instalado:

```
ssh -V
```

---

## 2. Activa el servidor SSH

En la otra PC:

```
sudo systemctl enable --now sshd

```

Comprueba:

```
systemctl status sshd
```

Deberías ver:

```
Active: active (running)
```

Ahora esa PC está escuchando normalmente en:

```
TCP :22
```

Puedes comprobarlo:

```
ss -ltnp | grep :22
```

---

## 3. Averigua la IP de la otra PC

En la otra PC:

```
hostname -I
```

Supongamos:

```
192.168.1.30
```

Y tu PC es:

```
192.168.1.20
```

---


# 4. Desde tu PC conéctate

En **tu PC**:

```
ssh usuario@192.168.1.30

o

ssh -v usuario@192.168.1.30
```

Por ejemplo, si el usuario de la otra PC es `juan`:

```
ssh juan@192.168.1.30
```

La primera vez probablemente aparecerá algo como:

```
The authenticity of host '192.168.1.30' can't be established.
Are you sure you want to continue connecting?
```

Escribe:

```
yes
```

Después introduce la contraseña del usuario de **la otra PC**.

Si funciona, pasarás a tener una terminal de la otra máquina:

```
juan@otra-pc:~$
```

🎉 Ya tienes acceso remoto.

---

# 5. ¿Y cómo accedo a sus archivos?

Ahora estás dentro de la otra PC:

```
pwd
```

Podrías obtener:

```
/home/juan
```

Puedes hacer:

```
ls
```

y ver:

```
Documents
Downloads
Pictures
Projects
...
```

Por ejemplo:

```
cd Projects
ls
```

Estás trabajando directamente con el sistema de archivos de la otra máquina.

# 6. Pero hay una diferencia importante

SSH te da una **terminal remota**.

Si quieres transferir archivos, puedes utilizar:

### `scp`

Desde tu PC:

```
scp archivo.txt juan@192.168.1.30:/home/juan/
```

Esto copia:

```
TU PC
archivo.txt
    │
    │ SSH
    ↓
OTRA PC
/home/juan/archivo.txt
```

---

## 7. Copiar una carpeta completa

Puedes hacer:

```
scp -r proyecto/ juan@192.168.1.30:/home/juan/
```

El `-r` significa **recursivo**, necesario para copiar directorios.

---

# 8. También puedes traer archivos hacia tu PC

Por ejemplo:

```
scp juan@192.168.1.30:/home/juan/archivo.txt .
```

El `.` significa:

```
directorio actual
```

Entonces:

```
OTRA PC
/home/juan/archivo.txt
        │
        │ SCP
        ↓
TU PC
./archivo.txt
```

---

# 9. Una opción todavía más interesante: SFTP

Puedes abrir una sesión SFTP:

```
sftp juan@192.168.1.30
```

Y tendrás comandos como:

```
ls
cd
pwd
```

pero además:

```
get archivo.txt
```

para descargarlo.

Y:

```
put archivo.txt
```

para subirlo.

Por ejemplo:

```
sftp> ls
Documents
Projects
archivo.txt

sftp> get archivo.txt
```

Ahora tienes el archivo en tu PC.

---

# 10. Puedes montar la otra PC como si fuera una carpeta

Esta parte te va a resultar especialmente interesante.

Con SSHFS puedes hacer que un directorio de la otra PC aparezca **montado dentro de tu sistema de archivos**.

Por ejemplo:

```
Tu PC

/mnt/otra-pc/
├── Documents/
├── Downloads/
├── Projects/
└── Pictures/
```

Pero esos archivos realmente están físicamente en:

```
Otra PC
/home/juan/
```

La conexión sería:

```
Tu PC                         Otra PC
                             
/mnt/otra-pc/ ─── SSH ───→   /home/juan/
```

En Arch puedes instalar SSHFS:

```
sudo pacman -S sshfs
```

Crear el punto de montaje:

```
mkdir ~/otra-pc
```

Y montar:

```
sshfs juan@192.168.1.30:/home/juan ~/otra-pc
```

Ahora:

```
cd ~/otra-pc
ls
```

y estarás viendo los archivos de la otra computadora.

---

## 11. Lo bonito de este ejercicio

Ahora puedes relacionar todo lo que acabamos de aprender:

```
                 OTRA PC
                    │
                    │
              ┌─────▼─────┐
              │   sshd    │
              │   :22     │
              └─────┬─────┘
                    │
                    │ TCP
                    │
              ┌─────▼─────┐
              │ FIREWALL  │
              └─────┬─────┘
                    │
                    │
              ┌─────▼─────┐
              │ filesystem│
              │ /home/... │
              └───────────┘
```

Y desde tu PC:

```
ssh usuario@192.168.1.30
        │
        └──→ puerto 22
```

SSH proporciona **la conexión segura**, mientras que SFTP/SCP aprovechan esa conexión para trabajar con archivos.

### Para tu práctica

Yo haría los ejercicios en este orden:

```
1. SSH
   └── entrar remotamente

2. SCP
   └── copiar archivos

3. SFTP
   └── administrar archivos remotamente

4. SSHFS
   └── montar la otra PC como un directorio

5. tcpdump
   └── observar qué está pasando por la red
```

El último es especialmente interesante porque podrías ver la diferencia entre una conexión **SSH cifrada** y un servidor HTTP simple como el que acabas de levantar con Python.

# Copiar archivos de Windows a linux por SSH


```bash
scp -r usuario@192.168.100.12:/C:/Users/Usuario/Desktop/STV .
```