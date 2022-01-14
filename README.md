# Arduino iot 33 telegram chatbot
Repositorio Base de un Chatbot en Telegram con Arduino IOT

Este repositorio es una revisión y adpatación del proyecto de Brian Lough en español, el objetivo es mostrar la disponibilidad de diseño de Chatbots en telegram usando WIFI NINA en las boards Arduino compatibles.

!! Importante agregar el certificado de seguridad en las opciones de la board arduino iot 33 y actualizar el firmware para garantizar el exito del prototipo.

## Hardware necesario

Arduino NANO 33 iot https://store.arduino.cc/products/arduino-nano-33-iot

*Arduino MKR

*Arduino UNO Wifi Rev2

Conectividad mediante WIFI seguridad WPA / WPA2

## Basado en las librerías
Arduino SPI.h

Arduino WifiNINA.h

Arduino ArduinoJson.h

Brian Lough UniversalTelegramBot.h


## Software necesario

Arduino IDE https://www.arduino.cc/en/software

#Pasos necesarios

1. Descarga el IDE de arduino e incluye la board que vas a utilizar
2. Actualiza el firmware de tu Dispositivo

a. Para ello debes cargar el archivo de la libreria WiFiNINA / TOOLS / FIRMWAREUPDATER
b. Una vez cargado ese archivo para la actualizacion ingresa en el Arduino IDE en la opcion: Herramientas / WIFININA firmware updater/ y selecciona la ultima version.

3. Descarga el repositorio de nuestro Bot en telegram o descarga su version original en el repositorio de Brian Lough
4. Incluye las librerias para su correcto funcionamiento usando el Gestor de librerias del IDE de Arduino
5. Reemplaza el nombre de tu red WIFI y PASSWORD
6. Utiliza Botfather para generar tu bot en telegram, asignarle un nombre y conifgurar el mensaje de bienvenida
7. Una vez obtengas tu propio botUSER en telegram genera el BOT_TOKEN y reemplazalo en la linea 40 BOT_TOKEN "0000:0000" conservando este formato
8. Incluye el certificado de telegram SSL en el Arduino IDE en la opcion: Herramientas / WIFININA firmware updater/ 3. Update SSL root certficates < Add a Domain y selecciona la opcion Upload Certificates to WiFi Module
9. Sube tu archivo a tu board arduino y abre el puerto serial para conocer el estado de la conexion.
