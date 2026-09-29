```bash
ip -br addr
```

Linux históricamente usaba nombres simples:

```
eth0    → Ethernet
wlan0   → Wi-Fi
```

En sistemas modernos se usa **Predictable Network Interface Names** para evitar que el nombre cambie dependiendo del orden en que el hardware sea detectado.

Por ejemplo:

```
enp3s0
│ │ └── número de puerto
│ └──── bus PCI
└────── Ethernet
```

`enp3s0` básicamente significa:

> interfaz Ethernet ubicada en PCI bus 3, slot 0.

**para aprender redes te recomiendo acostumbrarte a pensar en tres cosas separadas:**

```
INTERFAZ       IP              FUNCIÓN
────────────────────────────────────────────
lo             127.0.0.1      Tu propia PC
wlan0          192.168.100.6   Tu Wi-Fi
enp3s0         —               Ethernet
docker0        172.17.0.1      Red virtual Docker
```


### Equivalencias

|Linux|Windows|
|---|---|
|`ip addr`|`ipconfig`|
|`ip route`|`route print`|
|`ping 192.168.1.1`|`ping 192.168.1.1`|
|`ip -br addr`|`ipconfig`|
|`ip link`|`getmac` / `ipconfig /all`|

Si quieres **toda la información**, incluyendo MAC, DNS, DHCP, etc.:


