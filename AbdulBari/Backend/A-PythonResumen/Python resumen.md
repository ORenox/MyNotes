## 🖥️ Comandos de Terminal

| Comando                   | Descripción                         |
| ------------------------- | ----------------------------------- |
| `python archivo.py`       | Ejecuta un script                   |
| `python -i archivo.py`    | Ejecuta y entra en modo interactivo |
| `python -m modulo`        | Ejecuta un módulo                   |
| `pip install paquete`     | Instala un paquete                  |
| `pip list`                | Lista paquetes instalados           |
| `pip freeze > req.txt`    | Guarda dependencias                 |
| `pip install -r req.txt`  | Instala desde archivo               |
| `python -m venv env`      | Crea entorno virtual                |
| `source env/bin/activate` | Activa venv (Linux/Mac)             |
| `env\Scripts\activate`    | Activa venv (Windows)               |

## 🖨️ Entrada/Salida

```python

print("Hola")                          # Imprime
print("Hola", end="")                  # Sin salto de línea
print(f"Edad: {edad}")                 # f-string (recomendado)
print("Hola %s" % nombre)              # Formato antiguo
print("Valor: {}".format(x))           # .format()
nombre = input("Tu nombre: ")          # Leer texto
num = int(input("Número: "))           # Convertir a int`
```

## 🔤 Strings (Métodos Comunes)

```python

s = "Hola Mundo"
len(s)                  # Longitud
s.upper()               # MAYÚSCULAS
s.lower()               # minúsculas
s.strip()               # Quitar espacios
s.split(" ")            # Dividir → lista
"-".join(["a","b"])     # Unir → "a-b"
s.replace("a","b")      # Reemplazar
s.startswith("Ho")      # ¿Empieza con?
s.endswith("do")        # ¿Termina con?
s.find("M")             # Posición (-1 si no está)
s[0:4]                  # Slicing → "Hola"
s[::-1]                 # Invertir
```


## 🔀 Estructuras de Control

```python

# Condicional
if x > 0:
    pass
elif x < 0:
    pass
else:
    pass
# Bucle for
for i in range(10):        # 0..9
    pass
for item in lista:
    pass
for i, v in enumerate(lista):
    pass
# Bucle while
while condicion:
    pass
# Comprensión de listas
cuadrados = [x**2 for x in range(10)]
pares = [x for x in range(10) if x % 2 == 0]
# break / continue
break       # Sale del bucle
continue    # Siguiente iteración
```

## 📚 Colecciones

```python

# Lista (mutable, ordenada)
lista = [1, 2, 3]
lista.append(4)         # Añadir al final
lista.insert(0, 0)      # Insertar en índice
lista.remove(2)         # Quitar por valor
lista.pop()             # Quitar último
lista.sort()            # Ordenar
lista.reverse()         # Invertir
lista.index(3)          # Posición
lista.count(1)          # Contar
# Tupla (inmutable)
t = (1, 2, 3)
a, b, c = t             # Desempaquetar
# Diccionario
d = {"a": 1, "b": 2}
d["c"] = 3              # Añadir
d.get("x", 0)           # Valor o default
d.keys()                # Claves
d.values()              # Valores
d.items()               # Pares
d.pop("a")              # Eliminar
"a" in d                # ¿Existe clave?
# Set
s = {1, 2, 3}
s.add(4)
s.remove(1)
s | s2                  # Unión
s & s2                  # Intersección
s - s2                  # Diferencia`
```

## 🎯 Funciones

```python

def suma(a, b=0):       # Con valor por defecto
    return a + b
def args_dinamicos(*args, **kwargs):
    print(args)         # Tupla de posicionales
    print(kwargs)       # Dict de nombrados
# Lambda (función anónima)
doble = lambda x: x * 2
# Funciones útiles
map(lambda x: x*2, lista)
filter(lambda x: x > 0, lista)
sorted(lista, key=lambda x: -x)
zip(lista1, lista2)
sum(lista), min(lista), max(lista)`
```


## 🏛️ Programación Orientada a Objetos

```python

class Persona:
    def __init__(self, nombre, edad):   # Constructor
        self.nombre = nombre            # Atributo
        self.edad = edad
    
    def saludar(self):                  # Método
        return f"Hola, soy {self.nombre}"
    
    def __str__(self):                  # Como string
        return self.nombre
    
    def __repr__(self):                 # Representación
        return f"Persona({self.nombre})"
# Herencia
class Estudiante(Persona):
    def __init__(self, nombre, edad, carrera):
        super().__init__(nombre, edad)
        self.carrera = carrera
# Uso
p = Persona("Ana", 25)
print(p.saludar())`

```

## ⚠️ Manejo de Excepciones

```python

try:
    resultado = 10 / 0
except ZeroDivisionError as e:
    print(f"Error: {e}")
except (ValueError, TypeError):
    pass
else:
    print("Sin errores")     # Solo si no hubo excepción
finally:
    print("Siempre se ejecuta")
# Lanzar excepción
raise ValueError("Mensaje")
# Excepciones comunes
ValueError, TypeError, KeyError, IndexError
FileNotFoundError, ZeroDivisionError
AttributeError, ImportError`

```


## 📁 Archivos

```python

# Leer
with open("archivo.txt", "r", encoding="utf-8") as f:
    contenido = f.read()          # Todo
    # lineas = f.readlines()      # Lista de líneas
    # for linea in f: pass        # Iterar
# Escribir
with open("archivo.txt", "w") as f:
    f.write("Hola\n")
# Añadir
with open("archivo.txt", "a") as f:
    f.write("Más texto\n")
# Modos: r (leer), w (escribir), a (añadir), rb/wb (binario)
```

## 📦 Módulos e Imports

```python

import os
import sys
from math import sqrt, pi
from datetime import datetime
import numpy as np                # Con alias
# Módulos útiles de la stdlib
os, sys, math, random, datetime, json, re
collections, itertools, functools, pathlib`
```


## 🧵 Concurrencia (Básico)

```python

import threading
t = threading.Thread(target=funcion)
t.start()
t.join()
# Asíncrono
import asyncio
async def tarea():
    await asyncio.sleep(1)
asyncio.run(tarea())`
```

## 📄 JSON (JavaScript Object Notation)

### Importar y conceptos básicos

```python

import json
```


| Función             | Descripción          |
| ------------------- | -------------------- |
| `json.dumps(obj)`   | Python → String JSON |
| `json.loads(str)`   | String JSON → Python |
| `json.dump(obj, f)` | Python → Archivo     |
| `json.load(f)`      | Archivo → Python     |



## ⚡ Concurrencia


Python ofrece **3 modelos** principales:

|Modelo|Módulo|Ideal para|
|---|---|---|
|**Threading**|`threading`|I/O intensivo (red, archivos)|
|**Multiprocessing**|`multiprocessing`|CPU intensivo (cálculos)|
|**Asyncio**|`asyncio`|Muchas conexiones I/O concurrentes|

## 🎯 ¿Cuándo usar cada uno?

|Escenario|Herramienta|
|---|---|
|Muchas peticiones HTTP, websockets|**asyncio**|
|Leer/escribir muchos archivos|**threading**|
|Cálculos pesados (CPU)|**multiprocessing**|
|Tareas simples en paralelo|**ThreadPoolExecutor**|
|Procesamiento de datos numéricos|**multiprocessing** + NumPy|


