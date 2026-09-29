### Comandos útiles

**Modo automático (recomendado para uso diario)**

```
sudo nbfc set -a
```

**Velocidad fija al 50%**

```
sudo nbfc set -s 50
```

**Velocidad máxima**

```
sudo nbfc set -s 100
```

**Ver estado**

```
sudo nbfc status
```

### Monitorear temperatura y ventilador en tiempo real

Instala `watch` (normalmente ya viene) y usa:

```
watch -n 1 'sensors && echo && sudo nbfc status'
```

## Resumen de lo que hicimos

Tu objetivo inicial era que **CoolerControl no detectaba los ventiladores** en tu Acer Aspire A515-44 con Arch Linux (Omarchy/CachyOS).

Durante el proceso descubrimos que el problema no era la ausencia de sensores térmicos, sino que Linux no tenía una interfaz estándar (`hwmon`) para controlar el ventilador.

### Embedded Controller (EC)
[[Que es el EC]]

Luego verificamos el EC:

```
sudo modprobe ec_sys write_support=1
```

y encontramos:

```
sudo ls /sys/kernel/debug/ec
```

Resultado:

```
ec0
```

Esto confirmó que:

✅ Tu portátil posee un Embedded Controller accesible desde Linux.

# Qué instalamos

Instalamos:

```
yay -S nbfc-linux
```

Lo que también instaló:

```
acpi_callacpica
```

---

### ¿Qué es NBFC?

NBFC significa:

> Notebook Fan Control

Es un software que controla ventiladores escribiendo directamente en registros del EC.

# Qué descubrimos sobre tu laptop

Modelo:

```
sudo dmidecode -s system-product-name
```

Resultado:

```
Aspire A515-44
```

---

Buscamos perfiles:

```
find /usr/share/nbfc/configs -iname "*acer*"
```

Y encontramos:

```
Acer Aspire A515-48M.json
```

# Lo más importante

Configuramos el perfil:

```
sudo nbfc config --set "Acer Aspire A515-48M"
```

Activamos el servicio:

```
sudo systemctl enable --now nbfc_service
```

Y verificamos:

```
sudo nbfc status
```

Resultado:

```
Selected Config Name : Acer Aspire A515-48M
```

# Prueba definitiva

Ejecutaste:

```
sudo nbfc set -s 100
```

y luego:

```
sudo nbfc status
```

Mostró:

```
Target Fan Speed : 100Current Fan Speed: 26.97
```

Y además escuchaste los ventiladores.

Eso demuestra que:

✅ NBFC logró escribir en el EC.

✅ El EC respondió.

✅ El ventilador físico cambió de velocidad.

Por lo tanto:

> El perfil Acer Aspire A515-48M es compatible con tu Acer Aspire A515-44.

# Lo que aprendimos técnicamente

Hay varias capas:

## Nivel 1

Aplicaciones

```
CoolerControlNBFCfancontrol
```

---

## Nivel 2

Interfaces Linux

```
hwmonACPIEC
```

---

## Nivel 3

Hardware real

```
CPUGPUEmbedded ControllerVentilador
```

---

En tu caso:

```
CoolerControl      ↓   hwmon      ↓   (vacío)
```

Por eso no veía ventiladores.

Mientras que:

```
NBFC   ↓ Embedded Controller   ↓ Ventilador
```

Sí funcionó.


# Qué te recomiendo aprender

## ACPI

Fundamental para laptops.

Herramientas:

```
acpidumpiaslacpi_call
```

Permiten:

- leer tablas ACPI
- llamar métodos internos
- descubrir funciones ocultas

---

## Embedded Controllers (EC)

Aprender:

- registros
- offsets
- lectura/escritura

Herramientas:

```
ec_probexxdhexdump
```

---

## SMBus / I²C

Muchos sensores usan:

```
SMBusI²C
```

Herramientas:

```
i2cdetecti2cdumpi2cget
```

Paquete:

```
sudo pacman -S i2c-tools
```

## Kernel hwmon

Aprender cómo Linux expone sensores:

```
/sys/class/hwmon/
```

Muy útil para:

- ventiladores
- VRM
- GPU
- temperatura

---

## ACPI DSDT Reverse Engineering

Nivel avanzado.

Herramientas:

```
acpidumpiasl
```

Permite descubrir:

- métodos ocultos
- registros EC
- control térmico

Es una de las técnicas usadas para crear perfiles NBFC nuevos.

# Próximos experimentos interesantes

### Monitorizar cambios del EC

```
sudo ec_probe monitor
```

Muestra registros que cambian en tiempo real.

---

### Leer un registro específico

```
sudo ec_probe read 100
```

---

### Escribir un registro

```
sudo ec_probe write 100 255
```

⚠️ Solo cuando sepas exactamente qué hace el registro.

---

### Comparar dumps del EC

Repositorio típico para ingeniería inversa:

```
sudo ec_probe dump > idle.txt
```

Luego:

```
sudo nbfc set -s 100sudo ec_probe dump > fan100.txt
```

Comparar:

```
diff idle.txt fan100.txt
```

Así se descubren los registros de control de ventilador.

---

# Conclusión

Lograste algo bastante interesante:

- Verificaste que tu laptop expone un Embedded Controller.
- Aprendiste a acceder al EC desde Linux.
- Instalaste y configuraste NBFC.
- Encontraste un perfil compatible aunque no fuera exactamente tu modelo.
- Confirmaste control manual real del ventilador.
- Entendiste la diferencia entre sensores `hwmon` y control directo por EC.

Si quieres profundizar en hardware y sistemas embebidos, el siguiente paso natural sería aprender **ACPI, EC reverse engineering, SMBus/I²C y lectura de tablas DSDT**, porque son las tecnologías que utilizan Linux, Windows y los fabricantes para controlar prácticamente todo el hardware de una laptop moderna.