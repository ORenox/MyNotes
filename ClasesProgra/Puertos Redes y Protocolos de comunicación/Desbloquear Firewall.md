```
sudo ufw status
```
antes de desbloquear el firewall puedo [[Permitir acceso a un puerto temporalmente]]]


Para que mi PC funcione como servidor, además de levantar el servicio, debo permitir que otros dispositivos puedan establecer conexiones con ella. Para ello, puedo desactivar temporalmente el firewall, aunque **no es recomendable**, o, de forma más segura, crear reglas en el firewall que permitan las conexiones entrantes al puerto que utiliza el servidor. Las conexiones salientes normalmente ya están permitidas, dependiendo de la configuración del firewall.

### La idea clave

Cuando ejecutas, por ejemplo:

```
python3 -m http.server 8080 --bind 0.0.0.0
```

tienes dos cosas diferentes:

1. **El servidor está escuchando** en el puerto `8080`.
2. **El firewall debe permitir** que otros dispositivos lleguen a ese puerto.

Puedes imaginarlo así:

```
Otro PC
   │
   │  conexión TCP → puerto 8080
   ▼
┌───────────────┐


└───────┬───────┘
        │
        ▼
┌────────────────┐
│ Servidor Python│ ← escucha en 0.0.0.0:8080
└────────────────┘
```

Por eso, **desactivar el firewall no es un requisito para ser servidor**. Lo correcto en una red de prueba es mantenerlo activo y permitir únicamente el puerto/servicio que necesitas.