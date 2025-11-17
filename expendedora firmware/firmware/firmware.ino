#include <WiFi.h>
#include <PubSubClient.h>
#include <Stepper.h>

const int stepsPerRevolution = 200;  // ajusta según tu motor
const int PASOS_A_PROBAR = -500;
Stepper myStepper(stepsPerRevolution, 16, 17, 5, 18);

const char* SSID = "PEINE-3";
const char* contrasenna = "etecPeine3";

// crea objetos para gestionar la conexión
const char* mqtt_server = "10.56.2.73";  // O usa la IP de tu propio servidor MQTT
const int mqtt_port = 1883;
const char* mqtt_topic = "maquina/estado";  // suscribirse a un topic
const char* mqtt_topic_test = "maquina/probar-motor";

// Pin de control de la luz (LED o relé)
const int luzPin = 2;  // GPIO2 (integrado como LED en muchos ESP32);

//
WiFiClient espClient;
PubSubClient clienteMQTT(espClient);

// Función para manejar mensajes entrantes
void callback(char* topic, byte* payload, unsigned int length) {
  String mensaje;
  for (int i = 0; i < length; i++) {
    mensaje += (char)payload[i];
  }

  // encender y apagar la luz dependiendo del mensaje recibido por el broker
  mensaje.trim();
  Serial.print("Mensaje recibido: ");
  Serial.println(mensaje);

  //si el topic es test
  if (strcmp(topic, mqtt_topic_test) == 0) {
    Serial.println("✅ Mensaje para el motor recibido correctamente");

    float pasos = mensaje.toFloat();
    Serial.print("Valor convertido a número: ");
    Serial.println(pasos);


    Serial.println("→ Ejecutando myStepper.step()");
    myStepper.step(pasos);
    Serial.println("✅ Movimiento terminado");
  }
  //si el topic no es test
  else if (String(topic) == mqtt_topic) {
    if (mensaje == "ON") {
      digitalWrite(luzPin, HIGH);
      Serial.println("Luz encendida");
    } else if (mensaje == "OFF") {
      digitalWrite(luzPin, LOW);
      Serial.println("Luz apagada");
    } else if (mensaje == "comprar") {
      Serial.println("Girando sentido horario");
      myStepper.step(PASOS_A_PROBAR);  // una vuelta completa
    }
  }
}


void callback_test(char* topic, byte* payload, unsigned int length) {
  String mensaje;
  for (int i = 0; i < length; i++) mensaje += (char)payload[i];
}


// configurar y establecer conexión al broker MQTT
void conectarMQTT() {
  while (!clienteMQTT.connected()) {
    if (clienteMQTT.connect("ClienteESP32")) {
      Serial.println("Conectado al broker MQTT");  // mostrar mensaje de prueba para conectar al broker
      clienteMQTT.subscribe(mqtt_topic);
      clienteMQTT.subscribe(mqtt_topic_test);
    } else {
      Serial.print("Error de conexión: ");
      Serial.print(clienteMQTT.state());
      Serial.println(" - Reintentando en 5 segundos...");
      delay(5000);
    }
  }
}


void setup() {
  // iniciar puerto serie
  Serial.begin(115200);
  myStepper.setSpeed(60);  // velocidad en RPM (aumenta si es muy lento)
  // conectarse a la red
  WiFi.begin(SSID, contrasenna);
  Serial.println("Intentando Conectarse a la Red");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }


  Serial.println("Conectado a WiFi: ");
  Serial.println(WiFi.localIP());
  pinMode(luzPin, OUTPUT);
  clienteMQTT.setServer(mqtt_server, mqtt_port);
  clienteMQTT.setCallback(callback);
}


void loop() {
  if (!clienteMQTT.connected()) {
    conectarMQTT();
  }
  clienteMQTT.loop();
}
