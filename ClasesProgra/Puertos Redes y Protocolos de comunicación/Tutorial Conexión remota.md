## 1. En tu PC principal: averigua su IP

En Linux:

```
ip addr
```

Busca la interfaz de Wi-Fi/Ethernet y una dirección como:

```
192.168.1.20
```

También puedes usar:

```
hostname -I
```

Supongamos que obtienes:

```
192.168.1.20
```

## 2. Levanta un servidor sencillo

Como tienes Python, esta es probablemente la forma más fácil.

En tu PC principal crea una carpeta:

```
mkdir ~/servidor-prueba
cd ~/servidor-prueba
```

Pon algo dentro:

```
echo "Hola desde mi PC" > mensaje.txt
```

Ahora ejecuta:

```
python3 -m http.server 8080 --bind 0.0.0.0
```

Desglosemos:

| Parte            | Qué hace                                              |
| ---------------- | ----------------------------------------------------- |
| `python3`        | Ejecuta Python 3                                      |
| `-m http.server` | Ejecuta el módulo de servidor HTTP incluido en Python |
| `8080`           | Usa el **puerto 8080**                                |
| `--bind 0.0.0.0` | Escucha conexiones en **todas las interfaces de red** |

Deberías ver algo parecido a:

```
Serving HTTP on 0.0.0.0 port 8080
```

Acabas de hacer algo muy importante:

```
PC principal
192.168.1.20
      │
      └── puerto 8080
              │
              ↓
       Python HTTP server
```

## 3. Pruébalo desde la misma PC

Abre otra terminal:

```
curl http://localhost:8080
```

Deberías recibir algo como:

```
<!DOCTYPE HTML>
<html>
...
```

También puedes abrir:

```
http://localhost:8080
```

en el navegador.

## 4. Ahora viene el ejercicio interesante

Desde **tu otra PC**, conectada a la misma red, ejecuta:

```
curl http://192.168.1.20:8080
```

Sustituye `192.168.1.20` por la IP real de tu PC principal.

Si todo está correctamente configurado, deberías obtener la página del servidor Python.

La comunicación sería:

```
OTRA PC
192.168.1.30
     │
     │ HTTP
     │
     ↓
192.168.1.20:8080
     │
     ↓
Python
```

🎉 Acabas de establecer una conexión entre dos computadoras mediante un puerto.

---

# 5. Si NO funciona: aquí empieza el aprendizaje real

Primero comprueba que el servidor realmente está escuchando:

```
ss -ltnp | grep 8080
```

Deberías ver algo parecido a:

```
LISTEN 0 5 0.0.0.0:8080
```

Eso significa:

```
0.0.0.0
   ↓
todas las interfaces

8080
   ↓
puerto donde escucha Python
```

---

## 6. Comprueba el firewall

Si tienes `ufw`:

```
sudo ufw status
```

Si está activo y bloquea la conexión, puedes permitir **solamente el puerto 8080**:

```
sudo ufw allow 8080/tcp
```

Luego:

```
sudo ufw status
```

Y desde la otra PC:

```
curl http://192.168.1.20:8080
```

### No desactives todo el firewall

Para este ejercicio es mejor aprender a abrir **un puerto específico**:

```
Firewall
   │
   ├── 8080/tcp → ✅ permitir
   │
   └── demás    → reglas existentes
```

# 7. Puedes observar la conexión en tiempo real

Mientras Python está ejecutándose, en tu PC principal:

```
ss -tn
```

Cuando la otra PC se conecte, podrás ver una conexión relacionada con:

```
192.168.1.30:xxxxx → 192.168.1.20:8080
```

El puerto de la otra PC puede ser algo como:

```
53142
```

Eso es interesante porque ahora puedes distinguir:

```
192.168.1.30:53142
       │
       │ cliente
       ↓
192.168.1.20:8080
       │
       │ servidor
       ↓
     Python
```

El `53142` es un **puerto efímero** que el sistema operativo eligió para la conexión del cliente.

---

# 8. Después podemos hacer un ejercicio todavía mejor

Una vez que esto funcione, podemos hacerlo sin Python y construirlo paso a paso con:

```
PC A
 │
 ├── IP
 ├── puerto
 ├── servidor TCP
 └── firewall
        │
        ↓
PC B
 │
 ├── cliente TCP
 └── conexión
```

Y usar herramientas como:

```
nc
ss
ip
tcpdump
```

Ahí vas a poder **ver literalmente los paquetes viajando entre las dos PCs** y entender qué hacen IP, TCP, puertos, `LISTEN`, `ESTABLISHED`, firewall y NAT. Ese sería un ejercicio muy bueno para aprender redes desde cero.