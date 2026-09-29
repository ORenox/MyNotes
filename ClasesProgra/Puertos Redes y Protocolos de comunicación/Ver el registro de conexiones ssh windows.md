Desde el servidor (Windows): Ver el registro de conexiones recibidas

Por defecto, el servidor OpenSSH de Windows guarda los registros e intentos de inicio de sesión directamente en el **Visor de Eventos de Windows**. 

Puedes consultar estos mensajes directamente desde **PowerShell (como Administrador)** ejecutando el siguiente comando:

powershell

```
Get-WinEvent -LogName "OpenSSH/Operational" -MaxEvents 20 | Select-TimeCreated, Message | Format-Table -Wrap
```

Usa el código con precaución.