/*******************************************************************
    Ejemplo de Bot en telegram para Arduino con Wifi NINA.
    Dispositivos:
    Arduino Nano 33 IOT
    Basado en el el proyecto y libreria de Brian Lough
 *******************************************************************/
#include "arduino_secrets.h"
// ----------------------------
// Incluimos las librerias estandar para comunicacion SPI
// ----------------------------
#include <SPI.h>
// ----------------------------
// Incluimos la libreria de WIFININA para manejar la conectividad del proyecto
// ----------------------------
#include <WiFiNINA.h>
// Library for using network deatures of the official Arudino
// Wifi Boards (MKR WiFi 1010, Nano 33 IOT etc)

// Las librerias se pueden descargar directamente en el IDE de arduino para tener la ultima version, esta es la documentacion incial
// https://github.com/arduino-libraries/WiFiNINA
// https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot/blob/master/examples/WifiNINA/EchoBot/EchoBot.ino
// https://core.telegram.org/bots/api - esta documentacion es solo de refencia realmente vamos a usar Universal Arduino

// Libreria para conectar con telegram
#include <UniversalTelegramBot.h>

// Documentacion oficial - https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot * Tiene limitantes segun los comentarios

#include <ArduinoJson.h>
// Libreria recomendada para uso de JSON en Arduino

// https://github.com/bblanchon/ArduinoJson

// Credenciales de la red wifi
char ssid[] = SSID_network;         // Nombre de la red WIFI
char password[] = SSID_password; // PASSWORD de la red WiFI

// Es necesario crear un TOKEN para el bot desde telegram usando el servicio de (Botfather) elimine los // del comentario e incluya su token

// #define BOT_TOKEN "***:***"

//Asigna el token de acceso de Botfather ideal agregarlo desdel el archivo arduino_secrets adjunto aun que ahora hay que dejarlo directamente aqui en el main.ino***

// IMPORTANTE es la seccion de certificados del Arduino IOT
// Agregar telegram.com como una ruta con certificado de seguridad HTTPS de lo contrario no hay conectividad para los protocolos

const unsigned long BOT_MTBS = 1000; // Tiempo entre mensajes escaneados

int status = WL_IDLE_STATUS;

WiFiSSLClient client;
UniversalTelegramBot bot(BOT_TOKEN, client);
unsigned long bot_lasttime; // Ultima vez que se realizo el escaneo de mensajes

void handleNewMessages(int numNewMessages) {
  Serial.println("Nuevos mensajes"); // Para ver el estado en el puerto seriañ
  Serial.println(String(numNewMessages));  // Para ver el estado en el puerto serie
  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;
    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "Guest";
    //————
    //Aquí debes incluir o añadir más comandos para tu controlar el bot o modificar los actuales
    //————

    if (text == "/start") {
      //Mensaje de bienvenida del bot presentando los comandos basicos del chatbot
  String welcome = from_name + ", Bienvenido a un bot de datos en Telegram.\n";
  welcome += "Puede usar los siguientes comandos, para solicitar información:\n\n";
  welcome += "/Dato1 : Te muestra el primer dato sobre tu consulta\n";
  welcome += "/Dato2 : Te muestra la segunda captura de datos disponible\n";
  welcome += "/Dato3 : Te muestra la segunda captura de datos disponible\n";
  welcome += "/ConsultaJson : Realizamos una consulta por Json\n";
  bot.sendMessage(chat_id, welcome, "");
}

    if (text == "/Dato1") {
      // Incluye un mensaje y una foto en el formato que lo solicita la libreria de telegram & arduino
      bot.sendMessage(chat_id, "Respondemos a la primera consulta", "");
      bot.sendPhoto(chat_id, "https://s3-us-west-2.amazonaws.com/melingoimages/Images/14337.jpg","Caption*");
    }
    if (text == "/Dato2") {
      // Incluye un mensaje y vinculos con sendMessageWithInlineKeyboard les da apariencia de opciones dentro de la conversacion
      bot.sendMessage(chat_id, "Respondemos a la segunda consulta", "");
      String keyboardJson = "[[{ \"text\" : \"Go to Google\", \"url\" : \"https://www.google.com\" }],[{ \"text\" : \"Send\", \"callback_data\" : \"This was sent by inline\" }]]";
        bot.sendMessageWithInlineKeyboard(chat_id, "Choose from one of the following options", "", keyboardJson);
    }
    if (text == "/Dato3") {
      // Incluye un mensaje como respuesta y tiene un comando que resalta al final
      bot.sendMessage(chat_id, "Respondemos a la tercera consulta. \n\n /Dato2", "");

    }
    if (text == "/ConsultaJson") {
      // Incluye un mensaje y envio de mensajes con sendMessageWithReplyKeyboard estas opciones quedan disponibles todo el tiempo en la navegacion del chat
        bot.sendMessage(chat_id, "Realizamos una consulta de Json", "");
        String keyboardJson = "[[\"/Dato1\", \"/Dato2\"],[\"/Dato3\"],[\"/ConsultaJson\"]]";
      bot.sendMessageWithReplyKeyboard(chat_id, "Choose from one of the following options", "", keyboardJson, true);
    }

  }
}


void printWiFiStatus() {
  // Imprimimos en el puerto serial la red WIFI a la que nos queremos conectar
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // Imprimimos la direccion IP de la tarjeta
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // Imprimimos la intensidad de la señal recibida
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void setup()
{
    //incializamos la comunicacion serial y esperamos la apertura del puerto
  Serial.begin(9600);
  while (!Serial) {
    ; // Esperamos se conecte el puerto serial. Solo es util para puertos USB nativos
  }

  // Revisamos el status de la comunicacion WiFI
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < "1.0.0") {
    Serial.println("Please upgrade the firmware");
  }

  // Espera para realizar la conexion WIFI
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Conectando a WIFI con una red de seguridad WPA/WPA2. Cambia esta linea si usas una red WEP:
    status = WiFi.begin(ssid, password);
    // esperamos 10 segundos para la conexion
    delay(10000);
  }
  Serial.println("Connected to wifi");
  printWiFiStatus();
}

void loop()
{
  if (millis() - bot_lasttime > BOT_MTBS)
  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages)
    {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    bot_lasttime = millis();
  }
}
