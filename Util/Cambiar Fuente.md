
En caso de que venga la fuente comprimida, primero debo descomprimir y encontrar los archivos ttf y otp
7z x archivo.dmg  
unzip fuente.zip

##  Ubicar los archivos de fuente

Busca extensiones:

```
find . -name "*.otf"
find . -name "*.ttf"
```
## Instalarla en tu usuario (recomendado)

creo una carpeta denstro de local/share/fonts  con el nombre de la fuente
despues copio el contenido de la carpeta donde esten las fuentes en mi nueva carpeta.
El fc-cache reinicia el cache para que se aplique la fuente.

```
mkdir -p ~/.local/share/fonts/NOMBRE_FUENTE
cp *.otf ~/.local/share/fonts/NOMBRE_FUENTE/
fc-cache -fv
```

✔ Esto es suficiente en el 90% de casos  
✔ No necesitas root

## Verificar que se instaló

```
fc-list | grep -i "nombre"
```

