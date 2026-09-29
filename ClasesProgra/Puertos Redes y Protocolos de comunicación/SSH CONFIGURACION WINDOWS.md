### ¿Cómo saber cuál es el `usuario_windows`?

En la PowerShell de tu computadora Windows, ejecuta este comando para ver exactamente tu nombre de usuario:

powershell

```
[System.Environment]::UserName
```

Para saber si el servidor SSH ya está activo y funcionando,
powershell

```
Get-Service sshd
```


```
Add-WindowsCapability -Online -Name OpenSSH.Server~~~~0.0.1.0
```

🔍 ¿Cómo comprobar si ya está instalado?

Antes de lanzarlo, puedes verificar si tu sistema ya lo tiene disponible o instalado con este comando:
powershell

```
Get-WindowsCapability -Online | Where-Object Name -like 'OpenSSH*'
```

Usa el código con precaución.

- Si en **State** dice `NotPresent`, debes ejecutar el primer comando de instalación.
- Si dice `Installed`, ya está listo y puedes proceder a usarlo. 

---

1. Configurar en modo manual (Solo se hace una vez)

Este comando cambia el comportamiento del servicio para que no arranque solo al encender la computadora:

powershell

```
Set-Service -Name sshd -StartupType 'Manual'
```

2. Comando para encenderlo (Cuando lo vayas a usar)

Cada vez que necesites usar el servidor SSH, ejecuta este comando:

powershell

```
Start-Service sshd
```

Usa el código con precaución.

3. Comando para apagarlo (Al terminar)

Cuando termines de usarlo y quieras cerrarlo por seguridad, ejecuta:

powershell

```
Stop-Service sshd
```

Usa el código con precaución.

---

Si quieres verificar en cualquier momento si el servidor está encendido o apagado, puedes usar este comando de control:

powershell

```
Get-Service sshd
```

