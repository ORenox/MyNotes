Escribe esto y presiona Enter:

bash

```
echo $SHELL
```

Usa el código con precaución.
![[Pasted image 20260918100752.png]]
- **Qué significa el resultado:** Verás una ruta como `/bin/bash` (indica que usas **Bash**), `/bin/zsh` (indica **Zsh**) o `/usr/bin/fish` (confirma que usas **Fish**).

Las terminales (o más técnicamente, **shells**)  se diferencian principalmente en su **facilidad de uso**, su **velocidad**, las herramientas que traen configuradas por defecto y su **sintaxis de programación**.

Aquí tienes una comparación directa entre las tres más utilizadas:

|Terminal / Shell|Configuración inicial|Autocompletado inteligente|Sintaxis|Ideal para...|
|---|---|---|---|---|
|**Bash**|Viene lista y austera.|Básico (requiere tabulador).|Estándar POSIX.|Servidores, scripts universales y compatibilidad total.|
|**Zsh**|Altamente personalizable.|Avanzado (con plugins).|Compatible con Bash.|Desarrolladores en macOS (es la de por defecto) que aman los temas y plugins.|
|**Fish**|Funciona perfecto desde el día uno.|Ultra inteligente (sugiere mientras escribes).|Diferente (no compatible con Bash).|Desarrolladores que quieren una gran experiencia visual sin perder tiempo configurando.|

---

Detalles clave de cada una

- **Bash (Bourne Again Shell):** Es el **estándar histórico** en el mundo Linux. Prácticamente cualquier script de instalación en internet está escrito para Bash. Su gran ventaja es que funciona en cualquier servidor del mundo, pero visualmente es muy simple y no ayuda mucho al usuario mientras escribe.
- **Zsh (Z Shell):** Es la terminal por defecto en **macOS**. Por sí sola es parecida a Bash, pero se vuelve extremadamente poderosa gracias a frameworks como _Oh My Zsh_. Te permite ver el estado de tu repositorio de Git en la barra de comandos, usar temas de colores y añadir plugins de autocompletado.
- **Fish (Friendly Interactive Shell):** Es la terminal moderna que estás usando actualmente. Su filosofía es **"funcionar bien sin configurar nada"**. Te sugiere comandos en gris claro basados en tu historial antes de que termines de escribir y subraya los comandos en rojo si están mal escritos. Su única desventaja (como descubriste con Django) es que su lenguaje interno es diferente, por lo que comandos complejos pensados para Bash no funcionan en ella.