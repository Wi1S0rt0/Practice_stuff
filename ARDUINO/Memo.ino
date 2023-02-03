/* 
Librerias a instalar:
Adafruit SH110X
Adafruit MQTT Library
DHT sensor library by Adafruit
*/
#include "DHT.h"
#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <SPI.h>
#include <Wire.h>
#include <WiFiUdp.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <ESP32Servo.h>
#include <analogWrite.h>
#include <RTClib.h>
#include <ESP32Tone.h>
#include <ESP32PWM.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <NTPClient.h>


//wifi
const char* ssid = "The name of your WiFi";
const char* password = "The password of your WiFi";

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define IO_USERNAME  "Your Adafruit user"
#define IO_KEY       "Your key from Adafruit"

/********************************NTP SETUP**************************************/
#define UTC_OFFSET_IN_SECONDS -21600  

WiFiClient client;
WiFiClientSecure Client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, IO_USERNAME, IO_KEY);

Adafruit_MQTT_Publish indicator_publisher = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/luz");
Adafruit_MQTT_Subscribe encendercompuertasus = Adafruit_MQTT_Subscribe(&mqtt, IO_USERNAME "/feeds/encendercompuerta");


/************************* TelegramBot Setup *********************************/
/*for this, use a bot in telegram called BotFather, just type the name of your bot*/
#define BOTtoken "Telegram Bot Token" 
/*for this, use the bot "get id bot"*/
#define CHAT_ID "Your chat ID"

String chat_id;
UniversalTelegramBot bot(BOTtoken, Client);
//variable a enviar a adafruit 
int feedingSignal = 0;
//variable para manejar el tiempo proporcionado por pool ntp
float tiempo = 0;
//alarmas
String comida[] = {" ", " ", " "};
int hora;
int minuto; 
String arregloHora;
String opcion = "";
int repeticiones = 0;
//variables para HC-SR04
const int trigPin = 5;
const int echoPin = 18;                                                                    
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701
long duration;
float distanceCm;

//SERVO
// create four servo objects 
Servo servo1;
Servo servo2;
// Published values for SG90 servos; adjust if needed
int minUs = 1000;
int maxUs = 2000;

// These are all GPIO pins on the ESP32
// Recommended pins include 2,4,12-19,21-23,25-27,32-33
// for the ESP32-S2 the GPIO pins are 1-21,26,33-42
int servo1Pin = 15;
int servo2Pin = 12;

int pos = 0;      // position in degrees
ESP32PWM pwm;

// Variables for pir sensor
const int PIN_TO_SENSOR = 14; // GIOP14 pin connected to OUTPUT pin of sensor
int pinStateCurrent   = LOW;  // current state of pin
int pinStatePrevious  = LOW;  // previous state of pin

//for button
void onoffcallback(char *data, uint16_t len) {
  Serial.print("Hey we're in a onoff callback, the button value is: ");
  Serial.println(data);
  String message = String(data);
      message.trim();
      if (message == "ON") {
        feedingSignal = 1;
        Serial.println("Abriendo compuerta");
         servo1.write(180);
      indicator_publisher.publish(feedingSignal);
      delay(3000);
      feedingSignal = 0;
      indicator_publisher.publish(feedingSignal);
      Serial.println("apagado");
       servo1.write(0);
        }
      if (message == "OFF") {Serial.print("cerrando compuerta");
      servo1.attach(servo1Pin, minUs, maxUs);}
}

void handleNewMessages(int numNewMessages) {

  Serial.println(numNewMessages);
  for (int i=0; i<numNewMessages; i++) {

    // Chat id of the requester
    chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID){
      bot.sendMessage(chat_id, "Usuario no autorizado", "");
      continue;
    }

    String text = bot.messages[i].text;

    if (text == "/comida") {
      bot.sendMessage(chat_id, "Alimentando", "");
      feedingSignal = 1;
      
      Serial.println("encendido");
      servo1.write(180);
      indicator_publisher.publish(feedingSignal);
      delay(3000);
      feedingSignal = 0;

      indicator_publisher.publish(feedingSignal);
      Serial.println("apagado");
       servo1.write(0);
                 
    } else if (text == "/manual"){
      opcion = "manual";
       for(int k = 0; k < 3 ; k++){
         String messageNumber;
         messageNumber += k+1;
         String message = "Establecer horario #" + messageNumber + ": ";
          bot.sendMessage(chat_id, message, "");
          delay(1000);
         int prueba = bot.getUpdates(bot.last_message_received + 1);
         Serial.println(prueba);

       while(prueba) {
        
        comida[k] = bot.messages[i].text;
        prueba = bot.getUpdates(bot.last_message_received + 1);
          }
           delay(2000);
       }
       bot.sendMessage(chat_id, "opciones guardadas", "");

    } else if (text == "/auto"){
        opcion = "auto";
       for(int k = 0; k < 3 ; k++){
         String messageNumber;
         messageNumber += k+1;
         String message = "Establecer horario #" + messageNumber + ": ";
          bot.sendMessage(chat_id, message, "");
          delay(1000);
         int prueba = bot.getUpdates(bot.last_message_received + 1);
         Serial.println(prueba);

       while(prueba) {
        
        comida[k] = bot.messages[i].text;
        prueba = bot.getUpdates(bot.last_message_received + 1);
          }
           delay(2000);
       }
       bot.sendMessage(chat_id, "opciones guardadas", "");
    }else if (text == "/reiniciar"){
      bot.sendMessage(chat_id, "Se esta reiniciando su configuracion", "");
      opcion = "";
       for(int k = 0; k < 3 ; k++){
        comida[k] = "";
          }
       bot.sendMessage(chat_id, "Se ha reiniciando su configuracion", "");
       } else if (text == "/horario"){
        Serial.println("comidas");
        bot.sendMessage(CHAT_ID, "Tu horario guardado es: ", "");
          for(int j = 0; j < 3; j++){
            String hora = comida[j];
            bot.sendMessage(chat_id, hora, "");
            Serial.println(comida[j]);
          }
        bot.sendMessage(CHAT_ID, "Fin de lo guardado", "");  
    } 
    else {
      bot.sendMessage(chat_id, "Comando no implementado", "");
    }
    

  }
}
void ultrasonicSensor(){
  //configuracion del HC-SR04
   // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;

  //el limite es de 23cm
  Serial.println(distanceCm);
  if(distanceCm >= 23){
    bot.sendMessage(CHAT_ID, "Tu recipiente esta casi vacio, recuerda llenarlo", "");
  }

}


WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", UTC_OFFSET_IN_SECONDS);

void setup() {
  //for button sus
  encendercompuertasus.setCallback(onoffcallback);

  mqtt.subscribe(&encendercompuertasus);

  // Allow allocation of all timers, THIS IS FOR SERVO 
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
  Serial.begin(115200); // Starts the serial communication
  //Configuracion de servo 
  servo1.setPeriodHertz(50);      // Standard 50hz servo
	servo2.setPeriodHertz(50);      // Standard 50hz servo
  //wifi
  initWiFi();

  //setup for pir sensor
  pinMode(PIN_TO_SENSOR, INPUT); // set ESP32 pin to input mode to read value from OUTPUT pin of sensor

  //configuracion bot de telegram
  Client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  bot.sendMessage(CHAT_ID, "Memo-bot iniciado", "");
  bot.sendMessage(CHAT_ID,  "¡Hola!✌️ Soy Memo-bot, tengo la función de darte recordatorios para alimentar a tu mascosta cada cierto tiempo 🐶😺\nAlgunas recomendaciones:\n1- cuando coloques la hora en tu horario, evita colocar ceros (0) innecesarios, por ejemplo si tu reloj indica\n12:08, coloca 12:8 pero si tu reloj indica una hora como las 7:00, coloca en su lugar 7:0\n 2- coloca tu hora en formato 24 horas \nComandos disponibles:\n1- /comida: abre compuerta para alimentar a tu mascota 🍗🐶😺\n2- /manual: te permite guardar los horarios en los que quieres recibir tus recordatorios 📅\n3- /auto: te permite decirle al bot la hora en la que quieres que se le de comida a tu mascota🤖📅\n4- /reiniciar: reinicia tus configuraciones por si algo no te ha gustado✅🔧\n 5- /horario: te envia los horarios que se han guardado✅📅", "");
  //configuracionHC-SR04
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  //reloj integrado al ESP
  timeClient.begin();
  servo1.attach(servo1Pin, minUs, maxUs);
	servo2.attach(servo2Pin, minUs, maxUs);
}


void loop() {
  MQTT_connect();
  mqtt.processPackets(10000);
  if (!mqtt.ping()) {
    mqtt.disconnect();
  }

  // //we call function for pir sensor
  // pirSensor();

    pinStatePrevious = pinStateCurrent; // store old state
  pinStateCurrent = digitalRead(PIN_TO_SENSOR);   // read new state

  if (pinStatePrevious == LOW && pinStateCurrent == HIGH) {   // pin state change: LOW -> HIGH
    Serial.println("Motion detected!");
    servo2.write(180);
    delay(10000);
    servo2.write(30);
  } else if (pinStatePrevious == HIGH && pinStateCurrent == LOW) {   // pin state change: HIGH -> LOW
    Serial.println("Motion stopped!");
    // TODO: turn off alarm, light or deactivate a device ... here
  }

  // Primero se valida la cantidad de alimento en el recipiente
  ultrasonicSensor();
  
  String stHora;
  String stMinuto;

  timeClient.update();
  hora = timeClient.getHours();
  minuto = timeClient.getMinutes();
  
  stHora += hora;
  stMinuto += minuto;

  arregloHora = stHora + ":" + stMinuto;
  Serial.println(arregloHora);

  // Mandando mensajes de recordatorios
  if(opcion == "auto" && arregloHora == comida[0] ) {
    //funcion del servo
      feedingSignal = 1;
      Serial.println("encendido");
      servo1.write(180);
      indicator_publisher.publish(feedingSignal);
      delay(3000);
      feedingSignal = 0;
      indicator_publisher.publish(feedingSignal);
      Serial.println("apagado");
       servo1.write(0);
    //mensaje de confirmacion de alimento             
    bot.sendMessage(CHAT_ID, "Mensaje de confirmacion de desayuno", "");
    delay(60000);
  } else if(opcion == "manual" && arregloHora == comida[0]){
    bot.sendMessage(CHAT_ID, "Mensaje de recordatorio para desayuno", "");
  } else if(opcion == "auto" && arregloHora == comida[1]){
      //funcion del servo
      feedingSignal = 1;
      Serial.println("encendido");
      servo1.write(180);
      indicator_publisher.publish(feedingSignal);
      delay(3000);
      feedingSignal = 0;
      indicator_publisher.publish(feedingSignal);
      Serial.println("apagado");
      servo1.write(0);
      //mensaje de confirmacion de alimento             
    bot.sendMessage(CHAT_ID, "Mensaje de confirmacion de almuerzo", "");
    delay(60000);
  } else if(opcion == "manual" && arregloHora == comida[1]){
    bot.sendMessage(CHAT_ID, "Mensaje de recordatorio para almuerzo", "");
  }else if(opcion == "auto" && arregloHora == comida[2]){
      //funcion del servo
      feedingSignal = 1;
      Serial.println("encendido");
      servo1.write(180);
      indicator_publisher.publish(feedingSignal);
      delay(3000);
      feedingSignal = 0;
      indicator_publisher.publish(feedingSignal);
      Serial.println("apagado");
      servo1.write(0);
      //mensaje de confirmacion de alimento             
    bot.sendMessage(CHAT_ID, "Mensaje de confirmacion de cena", "");
    delay(60000);
  } else if(opcion == "manual" && arregloHora == comida[2]){
    bot.sendMessage(CHAT_ID, "Mensaje de recordatorio para cena", "");
  }
  int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
  while(numNewMessages) {
    handleNewMessages(numNewMessages);
    numNewMessages = bot.getUpdates(bot.last_message_received + 1);
  }
  
}




void MQTT_connect() {
  int8_t ret;
  // Stop if already connected.
  if (mqtt.connected()) {
    return;}
  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 10 seconds...");
       mqtt.disconnect();
       delay(10000);  // wait 10 seconds
       retries--;
       if (retries == 0) {       // basically die and wait for WDT to reset me
         while (1);}}
  Serial.println("MQTT Connected!");
}

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.println(WiFi.localIP());
}