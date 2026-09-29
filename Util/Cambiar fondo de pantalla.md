
### . Actualiza el enlace que usa Omarchy

```
ln -sf ~/Downloads/2.jpg ~/.config/omarchy/current/background
```

Este comando le dice a Omarchy que use esa imagen como fondo.

### 3. Recarga el fondo sin cerrar sesión

```
pkill swaybg

nohup swaybg -i ~/.config/omarchy/current/background -m fill >/dev/null 2>&1 &

```

El fondo cambiará inmediatamente.

---

## Ver qué fondo está usando actualmente

```
ls -l ~/.config/omarchy/current/background
```

Verás algo parecido a:

```
background -> /home/reno/wallpapers/nuevo_fondo.jpg
```

---

## Crear un alias para hacerlo más fácil

Puedes agregar esto a tu configuración de Fish (`~/.config/fish/config.fish`):

debo escribirla en varias lineas:

function wallpaper  
ln -sf $argv[1] ~/.config/omarchy/current/background  
pkill swaybg  
nohup swaybg -i ~/.config/omarchy/current/background -m fill >/dev/null 2>/dev/null &  
end


Luego recarga Fish:

```
source ~/.config/fish/config.fish
```

Y cambiarás el fondo con un solo comando:

```
wallpaper ~/wallpapers/montanas.jpg
```

---

## Lo que aprendimos sobre tu sistema

- Estás usando **Hyprland**.
- Omarchy **no usa `hyprpaper` ni `swww`**.
- El fondo se muestra mediante **`swaybg`**.
- Omarchy controla el fondo mediante el enlace:
    
    ```
    ~/.config/omarchy/current/background
    ```
    
- Cambiar ese enlace cambia el fondo que carga Omarchy.

Con eso ya tienes el método más directo para personalizar los fondos en tu instalación actual.
