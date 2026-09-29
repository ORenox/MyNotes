
Es importante Saber que compositor usa mi sistema operativo, en mi caso
```
echo $XDG_CURRENT_DESKTOP
```
y me sale como resultado 

Hyprland

*Mejor Opcion*
# 🥇 Mejor solución para tu objetivo (pizarra tipo profesor)

Como quieres:

> “tablet como pizarra conectada al PC en vivo”

### Instalar:

```
sudo pacman -S scrcpy android-tool
```

Activar opciones de desarrollador en el dispositivo y depuracion usb

```
adb devices <---- ejecuto esto

adb devices
* daemon not running; starting now at tcp:5037
* daemon started successfully
List of devices attached
R52TB0C974B	device


scrcpy <---- ejecuto esto



scrcpy
scrcpy 4.0 <https://github.com/Genymobile/scrcpy>
INFO: ADB device found:
INFO:     -->   (usb)  R52TB0C974B                     device  SM_P613
/usr/share/scrcpy/scrcpy-server: 1 file pushed, 0 skipped. 500.2 MB/s (732226 bytes in 0.001s)
[server] INFO: Device: [samsung] samsung SM-P613 (Android 14)
INFO: Renderer: opengl
INFO: OpenGL version: 4.6 (Compatibility Profile) Mesa 26.1.1-arch2.1
INFO: Trilinear filtering enabled
WARN: Could not set window icon: wayland: cannot set icon; required xdg_toplevel_icon_v1 protocol not supported
INFO: Texture: 1200x2000
```

# Modo “pizarra fluida” (recomendado)

Para tu uso tipo profesor:

```
scrcpy --max-size 1280 --bit-rate 8M --stay-awake
```

---

# 🧠 6. Opciones útiles (muy importantes)

### 🖊️ Mejor latencia (modo escritura)

```
scrcpy --render-driver=opengl
```

### 🖥️ Pantalla más limpia (sin bordes)

```
scrcpy --borderless
```

### 📺 Fullscreen (modo clase)

```
scrcpy -f
```