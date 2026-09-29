# 1. IP

IP se encarga principalmente de:

> **¿A qué máquina tengo que enviar estos datos?**

Por ejemplo:

```
192.168.1.30
```

Es una dirección IP.

Cuando haces:

```
ping 192.168.1.30
```

estás utilizando IP para intentar comunicarte con esa máquina.

IPv4 utiliza direcciones como:

```
192.168.1.30
10.0.0.5
8.8.8.8
```

También existe IPv6:

```
2001:db8::1
```

---

# 2. TCP

TCP se encarga de proporcionar una comunicación **confiable y ordenada** entre dos extremos.

Por ejemplo:

```
PC A
 │
 │ TCP
 ↓
PC B
```

TCP se preocupa de cosas como:

- establecer la conexión
- mantenerla
- ordenar los datos
- detectar pérdidas
- retransmitir datos
- controlar el flujo

Por eso cuando utilizas:

```
HTTP
SSH
SMB
PostgreSQL
```

normalmente estás utilizando TCP debajo.

---

# 3. UDP

UDP es mucho más simple.

No establece una conexión como TCP y no garantiza que los paquetes lleguen.

```
PC A
 │
 ├── paquete ──────→ PC B
 ├── paquete ──────→ PC B
 └── paquete ──X
```

El último podría perderse y UDP no necesariamente lo recupera.

¿Por qué utilizarlo?

Porque a veces **la velocidad y baja latencia son más importantes que garantizar cada paquete**.

Por ejemplo:

- streaming
- videojuegos
- VoIP
- DNS
- ciertos protocolos de IoT

---

# 4. HTTP

Este probablemente será uno de los más importantes para ti como desarrollador.

HTTP permite que un cliente se comunique con un servidor.

Por ejemplo:

```
Navegador
    │
    │ GET /usuarios
    ↓
Servidor
    │
    │ respuesta
    ↓
Navegador
```

Una petición podría ser:

```
GET /usuarios HTTP/1.1
Host: ejemplo.com
```

Y el servidor podría responder:

```
HTTP/1.1 200 OK

[
  {"id": 1, "nombre": "Renato"}
]
```

HTTP normalmente utiliza:

```
TCP :80
```

---

# 5. HTTPS

Es HTTP protegido mediante **TLS**.

En vez de:

```
HTTP
 ↓
TCP
```

tienes conceptualmente:

```
HTTP
 ↓
TLS
 ↓
TCP
 ↓
IP
```

Por eso cuando visitas:

```
https://google.com
```

los datos viajan cifrados.

Normalmente:

```
HTTPS → TCP :443
```

---

# 6. SSH

Este ya lo acabamos de utilizar.

SSH permite acceder remotamente a otra máquina de forma segura.

```
Linux
  │
  │ SSH
  │ TCP :22
  ↓
Windows/Linux
```

Puedes hacer:

```
ssh usuario@192.168.1.30
```

Y obtener una terminal remota.

Además SSH sirve como base para:

```
SCP
SFTP
SSH tunneling
```

---

# 7. SMB

Es especialmente importante si trabajas con Windows.

Sirve para compartir:

```
archivos
carpetas
impresoras
```

Por ejemplo:

```
Linux
  │
  │ SMB
  │ TCP 445
  ↓
Windows
  │
  ↓
C:\Compartida
```

Cuando en Windows ves algo como:

```
\\PC-JUAN\Documentos
```

estás entrando en un recurso compartido SMB.

---

# 8. DNS

Este es extremadamente importante.

DNS convierte:

```
google.com
```

en una dirección IP:

```
142.250.x.x
```

Conceptualmente:

```
Tu PC
 │
 │ "¿Cuál es la IP de google.com?"
 ↓
DNS
 │
 │ "Es 142.250.x.x"
 ↓
Tu PC
```

Sin DNS tendríamos que memorizar direcciones IP.

Normalmente utiliza:

```
UDP :53
```

aunque también puede utilizar TCP y otros mecanismos modernos.

---

# 9. DHCP

Cuando conectas tu computadora al Wi-Fi y automáticamente obtiene:

```
IP:      192.168.1.30
Gateway: 192.168.1.1
DNS:     192.168.1.1
```

normalmente interviene DHCP.

Conceptualmente:

```
PC
 │
 │ "Necesito una IP"
 ↓
Router / DHCP Server
 │
 │ "Toma 192.168.1.30"
 ↓
PC
```

---

# 10. WebSocket

Este es muy interesante si haces aplicaciones web.

HTTP normalmente funciona como:

```
Cliente ──→ servidor
Cliente ←── servidor
```

Pero WebSocket permite mantener una conexión persistente y que **ambos lados puedan enviar datos**.

```
Cliente
   ↕
   ↕ conexión persistente
   ↕
Servidor
```

Por eso es útil para:

- chats
- notificaciones
- dashboards
- datos en tiempo real
- juegos

Por ejemplo, podrías tener:

```
ESP32 → Spring Boot → WebSocket → React
```

y actualizar una interfaz en tiempo real.

---

# 11. MQTT

Este te interesa especialmente por tu experiencia con **IoT**.

MQTT está diseñado para comunicación mediante mensajes, utilizando el modelo:

```
Publisher
    │
    │ mensaje
    ↓
 MQTT Broker
    │
    ├────────→ Subscriber
    │
    └────────→ Subscriber
```

Por ejemplo:

```
ESP32
 │
 │ temperatura = 25.4
 ↓
MQTT Broker
 │
 ├──→ Dashboard
 ├──→ Backend
 └──→ Otro ESP32
```

Puertos típicos:

```
1883  → MQTT
8883  → MQTT sobre TLS
```

---

# 12. FTP

FTP se utiliza para transferencia de archivos:

```
Cliente
  │
  │ FTP
  ↓
Servidor
```

Pero actualmente, para muchas situaciones, se prefieren alternativas como:

```
SFTP
HTTPS
```

porque FTP tradicional no cifra las credenciales ni los datos de la misma manera.

---

# 13. PostgreSQL también utiliza un protocolo

Esto es algo que a veces se pasa por alto.

Cuando tu aplicación Spring Boot hace:

```
jdbc:postgresql://localhost:5432/empresa
```

estás teniendo:

```
Spring Boot
     │
     │ PostgreSQL protocol
     │ TCP :5432
     ↓
PostgreSQL
```

No estás utilizando HTTP para hablar con PostgreSQL.

PostgreSQL tiene su propio **protocolo de comunicación cliente-servidor**.

---

# 14. La imagen completa

Esta es la idea que te recomiendo guardar:

```
                 APLICACIONES
                      │
       ┌──────────────┼──────────────┐
       ↓              ↓              ↓
     HTTP            SSH            SMB
       │              │              │
       └──────────────┼──────────────┘
                      ↓
                   TCP/UDP
                      ↓
                      IP
                      ↓
              Ethernet / Wi-Fi
```

Por ejemplo, cuando haces:

```
https://google.com
```

hay muchas cosas sucediendo:

```
HTTP
 ↓
TLS
 ↓
TCP
 ↓
IP
 ↓
Wi-Fi/Ethernet
```

Y cuando haces:

```
ssh usuario@192.168.1.30
```

tienes aproximadamente:

```
SSH
 ↓
TCP
 ↓
IP
 ↓
Wi-Fi/Ethernet
```

Mientras que cuando accedes a una carpeta Windows:

```
SMB
 ↓
TCP
 ↓
IP
 ↓
Wi-Fi/Ethernet
```

---

## Si estás aprendiendo programación y redes

Yo priorizaría estos en este orden:

```
1. IP
2. TCP
3. UDP
4. DNS
5. HTTP
6. HTTPS / TLS
7. SSH
8. DHCP
9. SMB
10. WebSocket
11. MQTT
```

Y después aprendería **puertos, sockets, NAT, routing y firewalls**.

Cuando entiendas **TCP + IP + puertos + sockets**, empieza a cambiar mucho tu forma de ver cosas como Spring Boot, Docker, PostgreSQL, SSH y APIs. Ya no son herramientas aisladas: empiezas a ver que todas están construidas sobre las mismas piezas de comunicación.