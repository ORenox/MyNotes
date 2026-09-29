Imagina que tu computadora tiene una dirección:

```
192.168.1.20
```

Esa dirección identifica **tu computadora dentro de la red**.

Pero puede estar ejecutando muchos programas al mismo tiempo:

```
        Computadora
     192.168.1.20
           │
     ┌─────┼─────┬─────┐
     ↓     ↓     ↓     ↓
  Web    SSH    DB   Otro
```

¿Cómo sabe la computadora **a qué programa** debe entregar los datos?

Ahí aparecen los **puertos**.

Un puerto es como una "puerta" o "canal" asociado a un servicio.

Por ejemplo:

```
192.168.1.20:80
             ↑
           puerto
```

Significa:

> Conéctate a la computadora `192.168.1.20`, específicamente al servicio que está escuchando en el puerto `80`.

