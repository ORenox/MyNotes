**VPS**= Un **VPS (Virtual Private Server o Servidor Privado Virtual)** es un entorno virtual aislado dentro de un servidor físico compartido que funciona como una solución híbrida entre el hosting compartido y un servidor dedicado.

Cloud debo poder:
 * **Seleccinar servicios o recursos bajo demanda:** Si necesito más máquinas, el proveedor debe darmelas automáticamente(automatizar bajo demanda).
 * **infraestructura global**: podría tener mis servidores en local, en mi edificio, pero me pierdo la infraestructura gobal...
 aws tiene 39 regiones, osea, tengo acceso a una estructura de servidores global en practicamente todo el mundo
 **AZ** : availability zone, es un datacenter, usualmente tengo 3 AZ por región
 ![[Pasted image 20260915132623.png]]
 ![[Pasted image 20260915132703.png]]
 * **Responsabilidad compartida**: si se cae una región entera, aws tiene la responsabilidad y podría darme un a compensación. AWS es responzable de la seguridad del cloud.[[Responsabilidad compartida esquema]]
 **Como Usuario, soy responsable de la seguridad en el cloud**: si me levanto un servidor y levanto ubuntu, dejo servidores abiertos, abro puertos, etc, me hackea, es mi responsabilidad


### AWS
--- 
## conjunto de computo
Servicios para ejecutar código

--- 
## conjunto de datos o información
Almacenar información
**S3**: servicio en la nube es como un almacenamiento infinito, **S**imple **S**torage **S**ervice. Es el mejor para guardar el css, html y javaScript en la nube.
Se organiza en buckets (cubos o baldes)
no pueden haber dos buckets en el mundo con el mismo nombre, tambien se puede poner un nombre regional
![[Pasted image 20260915141008.png|600]]
en el 99% de los casos deberé bloquear el acceso público

El único que puede tener acceso al s3 es el **cloud front**
el frente de nubes, permite el acceso al s3, controla accesos, por paises, por origen, por boots, etc. el cloud front tiene firewall, se puede configurar limites de consumo, etc.

--- 
## Conjunto de comunicación
Transmitir información


--- 
# CDN
![[Pasted image 20260915142256.png|416]]
Va a existir mucha latencia, entre un continente y otro, por eso se usa la CDN, una red de servidores repartidos en el mundo, que guardan información de la web, y eso ayuda a que la experiencia tenga menos retraso entre paises.
Servidores que replican información, para que los usuarios no tengan que ir al origen, para que los usuarios puedan tener la info desde la copia regional.
![[Pasted image 20260915142016.png]]

# DNS
Domain Name System
![[Pasted image 20260915142043.png]]