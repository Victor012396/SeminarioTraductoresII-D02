# IoT-NODEMCU8266-Led

El presente repositorio contiene los archivos utilizados para el desarrollo e implementación del Proyecto del Internet de las cosas que conecta una placa NODEMCU8266 con un broker, utilizando las tecnologías de Docker, K8s, K3S, K3D y Rancher. En el archivo 'Proyecto-IoT' se puede observar más información acerca del mismo, y en el archivo 'Proyecto-avances' se pueden observar los avances previamente implementados.


## Despliegue del Proyecto

### Instalaciones para el despliegue

Para el despliegue del proyecto se debe de tener como herramientas:
* Una placa NODEMUC8266
* Cable usb con puerto Micro-B
* Para observar mejor el funcionamiento del módulo de internet, se recomienda una PowerRank

Y previamente instalado:
* Arduino IDE
* Docker
Además de algunas otras las cuales se mencionan sus comandos de instalación en el documento 'Proyecto-IoT' como:
* Chocolatey
* K3S, K3D, Rancher

### Desarrollo del Despliegue

Una vez que instaladas y obtenidas las anteriores herramientas, primeramente se tiene que abrir el IDE de Arduino para cargar el archivo 'NODEMCU2'. En este caso, arduino solicitará hacer la creación de una carpeta, a lo cuál le daremos permiso. Una vez con el código dentro de Arduino, se debe de instalar la libreria que permite el uso de la placa NODEMCU8366, para lo cuál, se sugieren los siguientes pasos:

1. Primeramente ir al repositorio oficial del ESP8266: https://github.com/esp8266/arduino 
2. Ahi se encuentra el link oficial que le dice a Arduino qué descargar para el uso de NODEMCU8366: https://arduino.esp8266.com/stable/package_esp8266com_index.json
3. En el IDE de Arduino, abrir 'Archivo>Preferencias' y pegar el link en 'Gestor de URLs Adicionales de Tarjetas: '
4. Dar click en Ok

Ya con la libreria descargada, conectamos la NODEMCU8266 a uno de los puertos de nuestra máquina, conectando nuestra placa con el IDE de la siguiente forma:
5. Ir a 'Herramientas>Placa:Arduino/Genuino Uno>Gestor de tarjetas'
6. En el campo de busqueda poner 'esp8266' y al encontrarlo, instalar dicha librería
7. Cerrar el Gestor de tarjetas y abrirlo nuevamente
8. Podemos observar ahora la placa NODEMCU8266, de manera que ahora se debe de dar click en 'Generic ESP8266 Module' (Es la 01) para seleccionarla
Pd. También existe la ESP8285 (Es la 12)
9. En herramientas checar los siguientes atributos:
   Flash Size: Se debe de observar si es 01 o 12, como se mencionó anteriormente
    Upload Speed: Es el nivel de carga del programa, esto depende del valor y carga del puerto y del usb
10. En caso de no poder, orientarse mediante el siguiente url de Youtube, link video: https://www.youtube.com/watch?v=0g7sazWXfEI

De esta manera, una vez seleccionada la placa, procedemos a, dentro del código, poner nuestra red de internet a la cuál nos conectaremos, junto con su contraseña. Así, ya podemos compilar el programa para cargarlo a la placa, de esta forma, comenzará a buscar la señal del internet previamente configurado, y en la pantalla de salida del IDE, esperaremos hasta observar el mensaje de que 'Se ha conectado al internet'. 
El siguiente paso es opcional, el cuál consiste en decidir si dejar la placa conectada a la computadora o conectar la placa a un PowerRank (cuando se conecta a este último, se demuestra que la placa puede seguir utilizando el programa aún cuando ya no esta conectado a nuestro equipo, utilizando su modulo ESP8266 que contiene el dispositivo WiFi.

Después, el siguiente paso es dirigirnos al Broker EMQX de la siguiente manera:

1. Entrar a la página emqx.com/en
2. Dirigirse al apartado gratis y publico, con este link:
https://www.emqx.com/en/mqtt/public-mqtt5-broker o buscar la opción 'Publick mqtt5 broker'
3. Ir y dar click al botón de 'Learn more...' en el apartado de Online MQTT Client
4. Dar click en el botón de 'Visit MQTT WebSocket Toolkit'
5. Click en New conection
6. Crear un client

7. En el apartado de 'Tools' dar click en 'Websocket' y hacer las siguientes configuraciones:
   1. Name: ESP8266
   2. Client ID: esp8266-client
   3. Username: admin
   4. Password: public
8. Dar click en el botón 'Connect' y observar que la placa marque como Connected

9. Por último, en 'Messsages', configurar:
   1. Topic: esp8266/test
   2. Messages: 1 (para encender) o 0 (para apagar)
   3. Dar click en botón para enviar y vemos si se envió el mensaje

De esta manera, si el mensaje ha sido enviado correctamente, el led de la placa NODEMCU8266 prenderá o se apagará, según reciba el mensaje.


