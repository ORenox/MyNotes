Administrar PCs/servidores remotamente mediante SSH, equivalencias entre **Linux/Bash, PowerShell y CMD**.

> Nota: PowerShell y Bash son mucho más potentes que CMD. En Windows moderno, **PowerShell es el equivalente que más conviene.

### 🖥️ Comandos básicos

|Acción|Linux / Bash|PowerShell|CMD|
|---|---|---|---|
|Ver archivos|`ls`|`Get-ChildItem` / `ls`|`dir`|
|Cambiar directorio|`cd`|`Set-Location` / `cd`|`cd`|
|Directorio actual|`pwd`|`Get-Location` / `pwd`|`cd`|
|Ir al directorio padre|`cd ..`|`cd ..`|`cd ..`|
|Crear directorio|`mkdir`|`New-Item -ItemType Directory` / `mkdir`|`mkdir`|
|Crear archivo|`touch archivo.txt`|`New-Item archivo.txt`|`type nul > archivo.txt`|
|Copiar|`cp`|`Copy-Item` / `cp`|`copy`|
|Mover|`mv`|`Move-Item` / `mv`|`move`|
|Renombrar|`mv`|`Rename-Item`|`ren`|
|Eliminar archivo|`rm`|`Remove-Item` / `rm`|`del`|
|Eliminar directorio|`rm -r`|`Remove-Item -Recurse`|`rmdir /s`|
|Limpiar terminal|`clear`|`Clear-Host` / `clear`|`cls`|
|Mostrar archivo|`cat`|`Get-Content` / `cat`|`type`|
|Buscar texto|`grep`|`Select-String`|`findstr`|

### 📂 Archivos y directorios

|Acción|Linux|PowerShell|CMD|
|---|---|---|---|
|Listar detalles|`ls -l`|`Get-ChildItem`|`dir`|
|Archivos ocultos|`ls -la`|`Get-ChildItem -Force`|`dir /a`|
|Tamaño de archivos|`du -h`|`Get-ChildItem` + propiedades|`dir`|
|Buscar archivo|`find`|`Get-ChildItem -Recurse`|`dir /s`|
|Ver estructura|`tree`|`tree`|`tree`|
|Copiar directorio|`cp -r`|`Copy-Item -Recurse`|`xcopy /E`|
|Comparar archivos|`diff`|`Compare-Object`|`fc`|

### 🌐 Red

Esta parte es **especialmente importante para lo que estás aprendiendo de SSH**:

|Acción|Linux|PowerShell|CMD|
|---|---|---|---|
|Ver IP|`ip addr`|`Get-NetIPAddress`|`ipconfig`|
|Configuración de red|`ip addr`|`Get-NetIPConfiguration`|`ipconfig /all`|
|Probar conexión|`ping IP`|`Test-Connection IP`|`ping IP`|
|Ver conexiones|`ss`|`Get-NetTCPConnection`|`netstat`|
|Ver puertos|`ss -tuln`|`Get-NetTCPConnection -State Listen`|`netstat -ano`|
|Ver tabla ARP|`ip neigh`|`Get-NetNeighbor`|`arp -a`|
|DNS|`dig` / `nslookup`|`Resolve-DnsName`|`nslookup`|
|Ruta hacia host|`traceroute`|`Test-NetConnection`|`tracert`|
|Probar puerto TCP|`nc -zv IP PUERTO`|`Test-NetConnection IP -Port PUERTO`|`PowerShell Test-NetConnection`|

Por ejemplo, en Windows puedes comprobar tu SSH:

```
Test-NetConnection 192.168.100.12 -Port 22
```

Y ver si el puerto está escuchando:

```
Get-NetTCPConnection -State Listen
```

---

### ⚙️ Procesos

|Acción|Linux|PowerShell|CMD|
|---|---|---|---|
|Ver procesos|`ps`|`Get-Process`|`tasklist`|
|Buscar proceso|`ps aux \| grep nginx`|`Get-Process nginx`|`tasklist \| findstr nginx`|
|Terminar proceso|`kill PID`|`Stop-Process -Id PID`|`taskkill /PID PID`|
|Forzar terminación|`kill -9 PID`|`Stop-Process -Id PID -Force`|`taskkill /F /PID PID`|

---

### 🔧 Servicios

Muy importante cuando administras servidores:

|Acción|Linux|PowerShell|CMD|
|---|---|---|---|
|Ver servicios|`systemctl`|`Get-Service`|`sc query`|
|Estado servicio|`systemctl status ssh`|`Get-Service sshd`|`sc query sshd`|
|Iniciar|`sudo systemctl start ssh`|`Start-Service sshd`|`net start sshd`|
|Detener|`sudo systemctl stop ssh`|`Stop-Service sshd`|`net stop sshd`|
|Reiniciar|`sudo systemctl restart ssh`|`Restart-Service sshd`|`net stop sshd && net start sshd`|
|Habilitar al inicio|`systemctl enable ssh`|`Set-Service sshd -StartupType Automatic`|`sc config sshd start=auto`|

---

### 🔐 Permisos

Aquí Linux y Windows son bastante diferentes:

|Acción|Linux|PowerShell|CMD|
|---|---|---|---|
|Permisos|`ls -l`|`Get-Acl`|`icacls`|
|Cambiar permisos|`chmod`|`Set-Acl`|`icacls`|
|Cambiar propietario|`chown`|`Set-Acl`|`icacls`|
|Ejecutar como admin|`sudo`|Ejecutar PowerShell como Admin / `Start-Process -Verb RunAs`|Ejecutar CMD como Admin|

Por ejemplo, Linux:

```
chmod 755 script.sh
```

Windows:

```
icacls archivo.txt
```

---

### 💾 Sistema

|Acción|Linux|PowerShell|CMD|
|---|---|---|---|
|Información del sistema|`uname -a`|`Get-ComputerInfo`|`systeminfo`|
|Espacio disco|`df -h`|`Get-PSDrive`|`wmic logicaldisk`|
|Uso memoria|`free -h`|`Get-CimInstance Win32_OperatingSystem`|`systeminfo`|
|Variables entorno|`env`|`Get-ChildItem Env:`|`set`|
|Ver variable|`echo $PATH`|`$env:PATH`|`echo %PATH%`|
|Hostname|`hostname`|`$env:COMPUTERNAME`|`hostname`|
|Usuario actual|`whoami`|`whoami`|`whoami`|
|Fecha/hora|`date`|`Get-Date`|`date /t`|

---

### 🔎 Buscar y filtrar

Esta categoría es **muy importante en Linux**, especialmente porque estás aprendiendo pipes.

|Acción|Linux|PowerShell|CMD|
|---|---|---|---|
|Buscar texto|`grep`|`Select-String`|`findstr`|
|Filtrar salida|`grep`|`Where-Object`|`findstr`|
|Ordenar|`sort`|`Sort-Object`|`sort`|
|Contar|`wc`|`Measure-Object`|`find /c`|
|Primeras líneas|`head`|`Select-Object -First`|`more`|
|Últimas líneas|`tail`|`Select-Object -Last`|—|

Ejemplo Linux:

```
ps aux | grep python
```

PowerShell:

```
Get-Process | Where-Object {$_.ProcessName -like "*python*"}
```

CMD:

```
tasklist | findstr python
```

Aquí puedes ver que **los pipes existen en los tres**, pero funcionan de manera diferente.

---

## ⭐ Los que yo priorizaría

No necesitas memorizar toda la tabla. Para administración remota, empezaría por estos:

### Linux

```
ls
cd
pwd
cp
mv
rm
mkdir
cat
grep
find
chmod
ps
kill
systemctl
ip
ss
ping
scp
ssh
```

### PowerShell

```
Get-ChildItem
Set-Location
Get-Location
Copy-Item
Move-Item
Remove-Item
New-Item
Get-Content
Select-String
Get-Process
Stop-Process
Get-Service
Start-Service
Stop-Service
Get-NetIPAddress
Get-NetTCPConnection
Test-Connection
Test-NetConnection
```

### CMD

```
dir
cd
copy
move
del
mkdir
rmdir
type
findstr
tasklist
taskkill
ipconfig
ping
netstat
tracert
```

Y para tu objetivo concreto de aprender **redes + SSH**, hay una relación que conviene tener muy clara:

```
             RED
              │
      ┌───────┴────────┐
      │                │
    Linux            Windows
      │                │
     ssh              ssh
      │                │
   Bash/Fish        PowerShell/CMD
      │                │
   comandos          comandos
```

**SSH es el transporte; Bash/PowerShell/CMD es el entorno donde ejecutas los comandos.** Esa distinción te va a evitar mucha confusión cuando empieces a administrar servidores Linux y Windows.