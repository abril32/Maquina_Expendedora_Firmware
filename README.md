# Maquina_Expendedora_Firmware
Actividad Integradora - Proyecto de Máquina Expendedora con implementación de Página web.
Alumna: Abril Iara Mosquera 
Año y curso: 6ºD

Explicación del proyecto
Este proyecto tiene como objetivo el desarrollo de una máquina expendedora de snacks conectada a una página web, permitiendo realizar compras digitales de forma rápida y sencilla. A través de una página web, los clientes pueden seleccionar sus productos, pagar  mediante una plataforma de pago y agarrar su pedido en la expendedora.
Diagrama de bloques 



Leyenda:
	→mandar datos a la máquina
	— recibir datos de la máquina 
— datos
— energía
Elección del motor y el por qué
Se utiliza el motor paso a paso de 6 cables porque es un motor que tiene la escuela lo que evita pagar por un motor nuevo. También sirve para controlar la cantidad de vueltas que da el resorte con los pasos por revolución, se puede controlar la velocidad de las vueltas (rpm), por lo que sirve para controlar qué tan rápido cae y las vueltas tiene que dar el “dispenser” para dar la comida.

¿Cómo se mueve el motor?
El cliente entra a la página web de la máquina expendedora, que está guardada en un servidor, y selecciona el pedido que quiere comer, al apretar el botón “pagar” la pagina le manda una señal al broker MQTT mediante el servicio de mosquito, con esta señal, la máquina expendedora acciona su motor y este da cierta cantidad de vueltas hasta que tira la comida.

Tabla de actividades

Act.Descripción Responsable Estado

A Descripción/definición del problema a resolver abril terminado
B Elección/justificación del sensor y accesorios a utilizar abril terminado
C Mosquitto: instalación y puesta en marcha del servicio abril terminado
D SQL: Instalación y puesta en marcha de servicio abril terminado
E SQL: Creación de base de datos (modelo relacional) abril terminado
F ESP32: obtención del dato provisto por el sensor abril terminado
G ESP32: conexión a broker MQTT abril terminado
H ESP32: publicación del dato a través de MQTT abril terminado
I Servidor: suscripción a broker MQTT abril terminado
J Servidor: guardar página web abril terminado
K Servidor: instalación de las dependenciasabril terminado
L Servidor: instalación de la base de datos abril terminado
M Servidor: puesta de marcha del servicio abril terminado


¿Por qué no se hizo con el NODE-RED ni el grafana?
No se hizo con el NODE-RED porque mi proyecto cuenta con un servidor en donde se guardan todos los datos, es decir, la base de datos, el código de la página web y el servicio mosquitto mqtt para poder conectarse al broker mediante el servidor. 
No se pudo hacer el grafana por falta de tiempo.


Bibliotecas a instalar
Stepper
Se necesita de esta biblioteca para poder configurar el motor paso a paso.

PubSubClient
Se necesita de esta biblioteca para poder suscribirse y publicarse al broker.

Wifi
Se necesita de esta biblioteca para poder conectarse a la red y así mandar los mensajes a través del broker, viene incluida con el esp32s.

Cableado

Para la tira de leds
![Circuito de los leds](/conexion_leds.jpg)

Para el motor
![Circuito del motor](/conexion_motor.jpg)

Video del funcionamientro
[Ver video](/maquina.mp4)

Explicación detallada del proyecto

Vista del cliente
Un cliente ingresa a la página web, este selecciona los productos que quiere pagar y los pone para pagar, cuando aprieta el botón la máquina tira los productos.

Funcionamiento interno
La página web está almacenada en un servidor, cuando alguien paga en la página, el servidor envía, mediante mqtt, un mosquitto un mosquitto_pub al broker con la palabra “comprar”, cuando esta palabra le llega a la ESP32, esta gira el dispensador a un número determinado de vueltas para tirar el producto.

Para comprobar que el motor funciona
mosquitto_pub -h 10.56.2.73 -p 1883 -t maquina/estado -m "comprar"

Para comprobar que los leds funcionen
mosquitto_pub -h 10.56.2.73 -p 1883 -t maquina/estado -m "ON"
mosquitto_pub -h 10.56.2.73 -p 1883 -t maquina/estado -m "OFF"

Para ver si se manda los mensajes
mosquitto_sub -h 10.56.2.73 -p 1883 -t maquina/estado

Aclaraciones

El motor mueve el “dispensador” con la página más la tira de leds se tiene que cambiar el color manualmente.
Para que la tira de leds funcione hay que poner en el broker un mensaje de “ON” si está conectado y un mensaje de “OFF” si está desconectado.

Referencias 

https://motorba.com.ar/wp-content/uploads/como-controlar-la-velocidad-de-un-motor-con-puente-h-1.webp

http://www.kio4.com/arduino/29motorpasoapaso.htm

https://dronebotworkshop.com/stepper-motors-with-arduino/

https://motorba.com.ar/puente-h-motor-a-pasos/

https://neonledstrip.com/es/guia-completa-para-el-cableado-de-tiras-led-rgb/#Basic_Wiring_Diagram_for_RGB_LED_Strips

Japan Servo Co. KH42JM2B160 Servo Motor //tipo de motor
