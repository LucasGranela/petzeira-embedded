// #ifdef EMBEDDED

#include <Arduino.h>
#include "petzeira.h"
#include "staticconfig.h"

Petzeira* petzeira = nullptr;

void setup() {
  #ifdef SERIAL_ENABLED
    Serial.begin(115200);

    while (!Serial);

    Serial.println("[MAIN - setup] - INFO: setting up");
  #endif

  petzeira = new Petzeira();
  petzeira->setup();
  petzeira->start();

  #ifdef SERIAL_ENABLED
    Serial.println("[MAIN - setup] - INFO: setup finished");
  #endif
}

void loop() {
  petzeira->loop();
}

// #endif

// // #include <Arduino.h>
// // #include <WiFi.h>

// // int mode;
// // bool connected;

// // char* ssidAP = "petzeiraWifi";
// // char* passwordAP = "petzeiraWifi";

// // char* ssid = "dudu";
// // char* password = "duduedudu";

// // // Set web server port number to 80
// // WiFiServer server(80);

// // // Variable to store the HTTP request
// // String header;

// // void connectAsAP()
// // {
// //     WiFi.mode(WIFI_AP);
// //     WiFi.softAP(ssidAP, passwordAP);
// //     Serial.println("[Wifi::connectAsAP] - INFO - Connecting as AP");
// //     Serial.print("[Wifi::connectAsAP] - INFO - SSID: ");
// //     Serial.println(ssidAP);
// //     Serial.print("[Wifi::connectAsAP] - INFO - PASSWORDAP: ");
// //     Serial.println(passwordAP);
// //     Serial.print("[Wifi::connectAsAP] - INFO - IP Gatway: ");
// //     Serial.println(WiFi.softAPIP());
// //     server.begin();
// // }

// // void setup() 
// // {
// //   Serial.begin(115200);

// //   connectAsAP();
// // }

// // void loop()
// // {
// //   WiFiClient client = server.available();   // Listen for incoming clients

// //   if (client) {                             // If a new client connects,
// //     Serial.println("New Client.");          // print a message out in the serial port
// //     String currentLine = "";                // make a String to hold incoming data from the client
// //     while (client.connected()) {            // loop while the client's connected
// //       if (client.available()) {             // if there's bytes to read from the client,
// //         char c = client.read();             // read a byte, then
// //         Serial.write(c);                    // print it out the serial monitor
// //         header += c;
// //         if (c == '\n') {                    // if the byte is a newline character
// //           // if the current line is blank, you got two newline characters in a row.
// //           // that's the end of the client HTTP request, so send a response:
// //           if (currentLine.length() == 0) {
// //             // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
// //             // and a content-type so the client knows what's coming, then a blank line:
// //             client.println("HTTP/1.1 200 OK");
// //             client.println("Content-type:text/html");
// //             client.println("Connection: close");
// //             client.println();
            
// //             // turns the GPIOs on and off
// //             if (header.indexOf("GET /") >= 0) {
// //               Serial.println("HOME");
// //             } 
            
// //             // Display the HTML web page
// //             client.println("<!DOCTYPE html><html>");
// //             client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
// //             client.println("<link rel=\"icon\" href=\"data:,\">");
// //             // CSS to style the on/off buttons 
// //             // Feel free to change the background-color and font-size attributes to fit your preferences
// //             client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
// //             client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
// //             client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
// //             client.println(".button2 {background-color: #555555;}</style></head>");
            
// //             // Web Page Heading
// //             client.println("<body><h1>ESP32 Web Server</h1>");
            
// //             // Display current state, and ON/OFF buttons for GPIO 26  
// //             client.println("<p>GPIO 26 - State ON </p>");
// //             // If the output26State is off, it displays the ON button       
// //             if ("off"=="off") {
// //               client.println("<p><a href=\"/26/on\"><button class=\"button\">ON</button></a></p>");
// //             } else {
// //               client.println("<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>");
// //             } 
               
// //             // Display current state, and ON/OFF buttons for GPIO 27  
// //             client.println("<p>GPIO 27 - State OFF </p>");
// //             // If the output27State is off, it displays the ON button       
// //             if ("on"=="off") {
// //               client.println("<p><a href=\"/27/on\"><button class=\"button\">ON</button></a></p>");
// //             } else {
// //               client.println("<p><a href=\"/27/off\"><button class=\"button button2\">OFF</button></a></p>");
// //             }
// //             client.println("</body></html>");
            
// //             // The HTTP response ends with another blank line
// //             client.println();
// //             // Break out of the while loop
// //             break;
// //           } else { // if you got a newline, then clear currentLine
// //             currentLine = "";
// //           }
// //         } else if (c != '\r') {  // if you got anything else but a carriage return character,
// //           currentLine += c;      // add it to the end of the currentLine
// //         }
// //       }
// //     }
// //     // Clear the header variable
// //     header = "";
// //     // Close the connection
// //     client.stop();
// //     Serial.println("Client disconnected.");
// //     Serial.println("");
// //   }
// // }

// // #include <Arduino.h>

// // #include <WiFi.h>
// // extern "C" {
// // 	#include "freertos/FreeRTOS.h"
// // 	#include "freertos/timers.h"
// // }
// // #include <AsyncMqttClient.h>

// // #define WIFI_SSID "AndroidAP4ad9"
// // #define WIFI_PASSWORD "joaoevan410"

// // #define MQTT_HOST IPAddress(34, 168, 1, 10)
// // #define MQTT_PORT 1883

// // AsyncMqttClient mqttClient;
// // TimerHandle_t mqttReconnectTimer;
// // TimerHandle_t wifiReconnectTimer;

// // void connectToWifi() {
// //   Serial.println("Connecting to Wi-Fi...");
// //   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
// // }

// // void connectToMqtt() {
// //   Serial.println("Connecting to MQTT...");
// //   mqttClient.connect();
// // }

// // void WiFiEvent(WiFiEvent_t event) {
// //     Serial.printf("[WiFi-event] event: %d\n", event);
// //     switch(event) {
// //     case SYSTEM_EVENT_STA_GOT_IP:
// //         Serial.println("WiFi connected");
// //         Serial.println("IP address: ");
// //         Serial.println(WiFi.localIP());
// //         connectToMqtt();
// //         break;
// //     case SYSTEM_EVENT_STA_DISCONNECTED:
// //         Serial.println("WiFi lost connection");
// //         xTimerStop(mqttReconnectTimer, 0); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
// //         xTimerStart(wifiReconnectTimer, 0);
// //         break;
// //     }
// // }

// // void onMqttConnect(bool sessionPresent) {
// //   Serial.println("Connected to MQTT.");
// //   Serial.print("Session present: ");
// //   Serial.println(sessionPresent);
// //   uint16_t packetIdSub = mqttClient.subscribe("test/lol", 2);
// //   Serial.print("Subscribing at QoS 2, packetId: ");
// //   Serial.println(packetIdSub);
// //   mqttClient.publish("test/lol", 0, true, "test 1");
// //   Serial.println("Publishing at QoS 0");
// //   uint16_t packetIdPub1 = mqttClient.publish("test/lol", 1, true, "test 2");
// //   Serial.print("Publishing at QoS 1, packetId: ");
// //   Serial.println(packetIdPub1);
// //   uint16_t packetIdPub2 = mqttClient.publish("test/lol", 2, true, "test 3");
// //   Serial.print("Publishing at QoS 2, packetId: ");
// //   Serial.println(packetIdPub2);
// // }

// // void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
// //   Serial.println("Disconnected from MQTT.");

// //   if (WiFi.isConnected()) {
// //     xTimerStart(mqttReconnectTimer, 0);
// //   }
// // }

// // void onMqttSubscribe(uint16_t packetId, uint8_t qos) {
// //   Serial.println("Subscribe acknowledged.");
// //   Serial.print("  packetId: ");
// //   Serial.println(packetId);
// //   Serial.print("  qos: ");
// //   Serial.println(qos);
// // }

// // void onMqttUnsubscribe(uint16_t packetId) {
// //   Serial.println("Unsubscribe acknowledged.");
// //   Serial.print("  packetId: ");
// //   Serial.println(packetId);
// // }

// // void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {
// //   Serial.println("Publish received.");
// //   Serial.print("  topic: ");
// //   Serial.println(topic);
// //   Serial.print("  qos: ");
// //   Serial.println(properties.qos);
// //   Serial.print("  dup: ");
// //   Serial.println(properties.dup);
// //   Serial.print("  retain: ");
// //   Serial.println(properties.retain);
// //   Serial.print("  len: ");
// //   Serial.println(len);
// //   Serial.print("  index: ");
// //   Serial.println(index);
// //   Serial.print("  total: ");
// //   Serial.println(total);
// // }

// // void onMqttPublish(uint16_t packetId) {
// //   Serial.println("Publish acknowledged.");
// //   Serial.print("  packetId: ");
// //   Serial.println(packetId);
// // }

// // void setup() {
// //   Serial.begin(115200);
// //   Serial.println();
// //   Serial.println();

// //   mqttReconnectTimer = xTimerCreate("mqttTimer", pdMS_TO_TICKS(2000), pdFALSE, (void*)0, reinterpret_cast<TimerCallbackFunction_t>(connectToMqtt));
// //   wifiReconnectTimer = xTimerCreate("wifiTimer", pdMS_TO_TICKS(2000), pdFALSE, (void*)0, reinterpret_cast<TimerCallbackFunction_t>(connectToWifi));

// //   WiFi.onEvent(WiFiEvent);

// //   mqttClient.onConnect(onMqttConnect);
// //   mqttClient.onDisconnect(onMqttDisconnect);
// //   mqttClient.onSubscribe(onMqttSubscribe);
// //   mqttClient.onUnsubscribe(onMqttUnsubscribe);
// //   mqttClient.onMessage(onMqttMessage);
// //   mqttClient.onPublish(onMqttPublish);
// //   mqttClient.setServer(MQTT_HOST, MQTT_PORT);

// //   connectToWifi();
// // }

// // void loop() {
  
// // }

// /*********
//   Rui Santos
//   Complete project details at https://randomnerdtutorials.com  
// *********/

// // #include <WiFi.h>
// // #include <PubSubClient.h>
// // #include <esp_mac.h>
// // #include <Wire.h>

// // // Replace the next variables with your SSID/Password combination
// // const char* ssid = "AndroidAP4ad9";
// // const char* password = "joaoevan410";

// // // Add your MQTT Broker IP address, example:
// // const char* mqtt_server = "34.234.225.102";
// // //const char* mqtt_server = "YOUR_MQTT_BROKER_IP_ADDRESS";

// // WiFiClient espClient;
// // PubSubClient client(espClient);
// // long lastMsg = 0;

// // uint8_t* mac_address;

// // void setup_wifi() {
// //   delay(10);
// //   // We start by connecting to a WiFi network
// //   Serial.println();
// //   Serial.print("Connecting to ");
// //   Serial.println(ssid);

// //   WiFi.begin(ssid, password);

// //   while (WiFi.status() != WL_CONNECTED) {
// //     delay(500);
// //     Serial.print(".");
// //   }

// //   Serial.println("");
// //   Serial.println("WiFi connected");
// //   Serial.println("IP address: ");
// //   Serial.println(WiFi.localIP());
// // }

// // void callback(char* topic, byte* message, unsigned int length) {
// //   Serial.print("Message arrived on topic: ");
// //   Serial.print(topic);
// //   Serial.print(". Message: ");
// //   String messageTemp;
  
// //   for (int i = 0; i < length; i++) {
// //     Serial.print((char)message[i]);
// //     messageTemp += (char)message[i];
// //   }
// //   Serial.println();

// //   // Feel free to add more if statements to control more GPIOs with MQTT

// //   // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
// //   // Changes the output state according to the message
// //   if (String(topic) == "esp32/output") {
// //     Serial.print("Changing output to ");
// //     if(messageTemp == "on"){
// //       Serial.println("on");
// //     }
// //     else if(messageTemp == "off"){
// //       Serial.println("off");
// //     }
// //   }
// // }

// // void reconnect() {
// //   // Loop until we're reconnected
// //   while (!client.connected()) {
// //     Serial.print("Attempting MQTT connection...");
// //     // Attempt to connect
// //     if (client.connect((char *)mac_address)) {
// //       Serial.println("connected");
// //       // Subscribe
// //       String cliente = "client/serial/client";
// //       client.subscribe(cliente.c_str());
// //       client.subscribe("agua/");
// //       client.subscribe("esp32/output");

// //     } else {
// //       Serial.print("failed, rc=");
// //       Serial.print(client.state());
// //       Serial.println(" try again in 5 seconds");
// //       // Wait 5 seconds before retrying
// //       delay(5000);
// //     }
// //   }
// // }

// // void setup() {
// //   Serial.begin(115200);
// //   esp_efuse_mac_get_default(mac_address);
// //   setup_wifi();
// //   client.setServer(mqtt_server, 1883);
// //   client.setCallback(callback);
// // }

// // void loop() {
// //   if (!client.connected()) {
// //     reconnect();
// //   }
// //   client.loop();

// //   long now = millis();
// //   if (now - lastMsg > 5000) {
// //     lastMsg = now;
    
// //     // Temperature in Celsius
// //     //temperature = bme.readTemperature();   
// //     // Uncomment the next line to set temperature in Fahrenheit 
// //     // (and comment the previous temperature line)
// //     //temperature = 1.8 * bme.readTemperature() + 32; // Temperature in Fahrenheit
    
// //     // Convert the value to a char array
// //     char tempString[8];
// //     //dtostrf(temperature, 1, 2, tempString);
// //     Serial.print("Temperature: ");
// //     Serial.println(tempString);
// //     client.publish("esp32/temperature", tempString);

// //     //humidity = bme.readHumidity();
    
// //     // Convert the value to a char array
// //     char humString[8];
// //     //dtostrf(humidity, 1, 2, humString);
// //     Serial.print("Humidity: ");
// //     Serial.println(humString);
// //     client.publish("esp32/humidity", humString);
// //   }
// // }

// // #include <WiFi.h>

// // const char* apSSID = "PetzeiraWifi";
// // const char* apPassword = "petzeira";

// // const int configTimeout = 30;  // Timeout for configuration in seconds

// // WiFiServer server(80);

// // void connectWiFiSTA(const String& ssid, const String& password) {
// //   WiFi.disconnect();
// //   WiFi.mode(WIFI_STA);

// //   Serial.print("Connecting to ");
// //   Serial.println(ssid);

// //   WiFi.begin(ssid.c_str(), password.c_str());

// //   while (WiFi.status() != WL_CONNECTED) {
// //     delay(1000);
// //     Serial.print(".");
// //   }

// //   Serial.println("");
// //   Serial.println("Wi-Fi connected");
// //   Serial.print("IP address: ");
// //   Serial.println(WiFi.localIP());
// // }

// // void waitForConfiguration(WiFiClient& client) {
// //   while (client.connected()) {
// //     if (client.available()) {
// //       String request = client.readStringUntil('\r');
// //       if (request.indexOf("POST /configure?ssid=") != -1) {
// //         // Extract the SSID and password from the request
// //         String ssid = request.substring(request.indexOf("ssid=") + 5, request.indexOf("&"));
// //         String password = request.substring(request.indexOf("password=") + 9, request.indexOf(" HTTP/"));
        
// //         Serial.print("ssid: ");
// //         Serial.println(ssid.c_str());
// //         Serial.print("password: ");
// //         Serial.println(password.c_str());
        
// //         // Connect the ESP32 as a station to the specified Wi-Fi network
// //         connectWiFiSTA(ssid, password);

// //         // Send a success response to the client
// //         client.println("HTTP/1.1 200 OK");
// //         client.println("Content-Type: text/html");
// //         client.println("");
// //         client.println("<html><body>");
// //         client.println("<h1>Configuration Successful</h1>");
// //         client.println("The ESP32 has been configured to connect to the specified Wi-Fi network.");
// //         client.println("</body></html>");

// //         // Close the connection
// //         client.stop();
// //         delay(2000);

// //         // Restart the ESP32
// //         ESP.restart();
// //       }
// //     }
// //   }
// // }

// // void configureWiFiSTA() {
// //   Serial.println("Waiting for configuration...");

// //   int timeout = 0;
// //   while (timeout < configTimeout) {
// //     if (WiFi.softAPgetStationNum() > 0) {
// //       // Client connected
// //       Serial.println("Configuration started.");
// //       break;
// //     }

// //     delay(1000);
// //     timeout++;
// //   }

// //   if (timeout >= configTimeout) {
// //     // Configuration timeout reached
// //     Serial.println("Configuration timeout. Restarting...");
// //     ESP.restart();
// //   }

// //   // Serve the configuration page to the connected client
// // }

// // void setup() {
// //   Serial.begin(115200);

// //   // Start in AP mode
// //   WiFi.mode(WIFI_AP);
  
// //   // Create an open network with a specified SSID and password
// //   WiFi.softAP(apSSID, apPassword);
  
// //   Serial.print("AP IP address: ");
// //   Serial.println(WiFi.softAPIP());
// //   server.begin();
  
// //   // Wait for a client to connect and configure the ESP32
// //   configureWiFiSTA();
// // }

// // void loop() {
// //   // Your code goes here
// //   WiFiClient client = server.available();

// //   if (client) {
// //     Serial.println("Client connected. Serving configuration page.");

// //     // Send the HTML configuration page to the client
// //     client.println("HTTP/1.1 200 OK");
// //     client.println("Content-Type: text/html");
// //     client.println("");

// //     client.println("<html><body>");
// //     client.println("<h1>ESP32 Configuration</h1>");
// //     client.println("<form method=\"post\" action=\"configure\">");
// //     client.println("SSID: <input type=\"text\" name=\"ssid\"><br>");
// //     client.println("Password: <input type=\"password\" name=\"password\"><br>");
// //     client.println("<input type=\"submit\" value=\"Submit\">");
// //     client.println("</form>");
// //     client.println("</body></html>");

// //     // Wait for the client to submit the configuration form
// //     waitForConfiguration(client);
// //   }
// // }

// // const char * [] = {
// //     "HTTP/1.1 200 OK");
// //     client.println("Content-Type: text/html");
// //     client.println("");

// //     client.println("<html><body>");
// //     client.println("<h1>ESP32 Configuration</h1>");
// //     client.println("<form method=\"post\" action=\"configure\">");
// //     client.println("SSID: <input type=\"text\" name=\"ssid\"><br>");
// //     client.println("Password: <input type=\"password\" name=\"password\"><br>");
// //     client.println("<input type=\"submit\" value=\"Submit\">");
// //     client.println("</form>");
// //     client.println("</body></html>");
// // }

// // const char index_html[] PROGMEM = 
// // R"rawliteral(
// // <!DOCTYPE HTML>
// // <html>
// //   <head>
// //     <title>ESP Input Form</title>
// //     <meta name="viewport" content="width=device-width, initial-scale=1">
// //   </head>
// //   <body>
// //     <form action="/get"> SSID: 
// //       <input type="text" name="ssid">
// //       <input type="submit" value="Submit">
// //     </form>
// //     <br>
// //     <form action="/get"> password: 
// //       <input type="text" name="password">
// //       <input type="submit" value="Submit">
// //     </form>
// //     <br>
// //   </body>
// // </html>
// // )rawliteral";

// /*


//   this example will show
//   1. how to use and ESP 32 for reading pins
//   2. building a web page for a client (web browser, smartphone, smartTV) to connect to
//   3. sending data from the ESP to the client to update JUST changed data
//   4. sending data from the web page (like a slider or button press) to the ESP to tell the ESP to do something

//   If you are not familiar with HTML, CSS page styling, and javascript, be patient, these code platforms are
//   not intuitive and syntax is very inconsitent between platforms

//   I know of 4 ways to update a web page
//   1. send the whole page--very slow updates, causes ugly page redraws and is what you see in most examples
//   2. send XML data to the web page that will update just the changed data--fast updates but older method
//   3. JSON strings which are similar to XML but newer method
//   4. web sockets very very fast updates, but not sure all the library support is available for ESP's

//   I use XML here...

//   compile options
//   1. esp32 dev module
//   2. upload speed 921600
//   3. cpu speed 240 mhz
//   flash speed 80 mhz
//   flash mode qio
//   flash size 4mb
//   partition scheme default


//   NOTE if your ESP fails to program press the BOOT button during programm when the IDE is "looking for the ESP"

//   The MIT License (MIT)

//   code writen by Kris Kasprzak
  
//   Permission is hereby granted, free of charge, to any person obtaining a copy of
//   this software and associated documentation files (the "Software"), to deal in
//   the Software without restriction, including without limitation the rights to
//   use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
//   the Software, and to permit persons to whom the Software is furnished to do so,
//   subject to the following conditions:
//   The above copyright notice and this permission notice shall be included in all
//   copies or substantial portions of the Software.
//   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
//   FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
//   COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
//   IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
//   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

//   On a personal note, if you develop an application or product using this code 
//   and make millions of dollars, I'm happy for you!

// */

// #include <WiFi.h>       // standard library
// #include <WebServer.h>  // standard library
// #include <HTTPClient.h> // standard library
// #include <ArduinoJson.h>
// #include <esp_mac.h>

// #include "index_for_wifi_connection.h"   // .h file that stores your html page code
// #include "index_for_login.h" // .cpp file that stores your html page code

// // once  you are read to go live these settings are what you client will connect to
// #define AP_SSID "petzeira_wifi"
// #define AP_PASS "petzeira123"

// String local_ssid;
// String local_pass;
// String username;
// String password;
// String user_token;

// volatile bool change_type_wifi = false;

// volatile bool change_type_login = false;

// volatile bool login_successful = false;

// String cookie;

// uint8_t* mac_address;

// // the XML array size needs to be bigger that your maximum expected size. 2048 is way too big for this example
// char XML[2048];

// // just some buffer holder for char operations
// char buf[32];

// // variable for the IP reported when you connect to your homes intranet (during debug mode)
// IPAddress Actual_IP;

// // definitions of your desired intranet created by the ESP32
// IPAddress PageIP(192, 168, 1, 1);
// IPAddress gateway(192, 168, 1, 1);
// IPAddress subnet(255, 255, 255, 0);
// IPAddress ip;

// // gotta create a server
// WebServer server(80);

// CookieJar cookieJar;

// String serverName = "http://34.234.225.102:3333/";

// void update_wifi_name_and_password() {

//   // many I hate strings, but wifi lib uses them...
//   String update = server.arg("VALUE");
//   local_ssid = update.substring(0, update.indexOf(","));
//   local_pass = update.substring(update.indexOf(",") + 1);

//   Serial.println("[update_user_name] - INFO - ");
//   Serial.print("user_name: "); Serial.println(local_ssid);
//   Serial.print("password: "); Serial.println(local_pass);

//   change_type_wifi = true;

//   server.send(200, "text/plain", ""); //Send web page
// }

// void update_login() {

//   // many I hate strings, but wifi lib uses them...
//   String update = server.arg("VALUE");
//   username = update.substring(0, update.indexOf(","));
//   password = update.substring(update.indexOf(",") + 1);

//   Serial.println("[update_login] - INFO - ");
//   Serial.print("user_name: "); Serial.println(username);
//   Serial.print("password: "); Serial.println(password);

//   change_type_login = true;

//   server.send(200, "text/plain", ""); //Send web page
// }

// // code to send the main web page
// // PAGE_MAIN is a large char defined in SuperMon.h
// void send_web_page_for_get_wifi_connections() {
//   Serial.println("sending web page");
//   // you may have to play with this value, big pages need more porcessing time, and hence
//   // a longer timeout that 200 ms
//   server.send(200, "text/html", PAGE_MAIN_FOR_WIFI_CONNECTION);
// }

// void send_web_page_for_login() {
//   Serial.println("sending web page");
//   // you may have to play with this value, big pages need more porcessing time, and hence
//   // a longer timeout that 200 ms
//   server.send(200, "text/html", PAGE_FOR_LOGIN);
// }

// // code to send the main web page
// // I avoid string data types at all cost hence all the char mainipulation code
// void SendXML() {
//   // you may have to play with this value, big pages need more porcessing time, and hence
//   // a longer timeout that 200 ms
//   server.send(200, "text/xml", XML);
// }

// // I think I got this code from the wifi example
// void printWifiStatus() {

//   // print the SSID of the network you're attached to:
//   Serial.print("SSID: ");
//   Serial.println(WiFi.SSID());

//   // print your WiFi shield's IP address:
//   ip = WiFi.localIP();
//   Serial.print("IP Address: ");
//   Serial.println(ip);

//   // print the received signal strength:
//   long rssi = WiFi.RSSI();
//   Serial.print("signal strength (RSSI):");
//   Serial.print(rssi);
//   Serial.println(" dBm");
//   // print where to go in a browser:
//   Serial.print("Open http://");
//   Serial.println(ip);
// }

// void connect_wifi_network() 
// {
//   server.close();
//   WiFi.disconnect();
//   WiFi.mode(WIFI_STA);

//   Serial.print("Connecting to ");
//   Serial.println(local_ssid.c_str());

//   WiFi.begin(local_ssid.c_str(), local_pass.c_str());

//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.print(".");
//   }

//   Serial.println("");
//   Serial.println("Wi-Fi connected");
//   Serial.print("IP address: ");
//   Serial.println(WiFi.localIP());

//   server.on("/login", send_web_page_for_login);
//   server.on("/SEND_NAME_PASSWORD", update_login);

//   server.begin();

//   change_type_wifi = false;
// }

// void connect_to_server() 
// {
//   if(WiFi.status()== WL_CONNECTED){
//     WiFiClient client;
//     HTTPClient http;

//     String http_path_login = serverName + "auth/login";

//     const char * headerkeys[] = {"Set-Cookie"};
//     size_t headerkeyssize = sizeof(headerkeys)/sizeof(char*);
    
//     http.collectHeaders(headerkeys,headerkeyssize);

//     http.begin(client, http_path_login);

//     http.addHeader("Content-Type", "application/json");

//     Serial.print("HTTP path: ");
//     Serial.println(http_path_login);

//     StaticJsonDocument<200> post;

//     DeserializationError error1 = deserializeJson(post, "{\"email\":\""+ username +"\",\"password\":\""+password+"\"}");
//     serializeJsonPretty(post, Serial);

//     int httpResponseCode = http.POST("{\"email\":\""+ username +"\",\"password\":\""+password+"\"}");

//     String payload = http.getString();
         
//     Serial.print("HTTP Response code: ");
//     Serial.println(httpResponseCode);

//     Serial.print("HTTP Response payload: ");
//     Serial.println(payload);

//     StaticJsonDocument<200> doc;

//     DeserializationError error = deserializeJson(doc, payload);

//     // Test if parsing succeeds.
//     if (error) {
//       Serial.print(F("deserializeJson() failed: "));
//       Serial.println(error.f_str());
//       return;
//     } 


//     Serial.print("message: ");
//     Serial.println(doc["message"].as<String>());

//     if(doc["message"].as<String>() == "Login successful") {
//       cookie = http.header("Set-Cookie");
//       login_successful = true;

//       Serial.print("cookie: ");
//       Serial.println(cookie);
//     }

//     // Print the result
//     serializeJsonPretty(doc, Serial);

//     Serial.println();

//       // Free resources
//     http.end();

//     change_type_login = false;
//   }
// }


// void get_subscribed_modules() 
// {
//   if(WiFi.status()== WL_CONNECTED){
//     WiFiClient client;
//     HTTPClient http;

//     String http_path_modules = serverName + "modulo";

//     http.begin(client, http_path_modules);

//     http.addHeader("Content-Type", "application/json");
//     http.addHeader("Cookie", cookie);

//     Serial.print("HTTP path: ");
//     Serial.println(http_path_modules);

//     int httpResponseCode = http.GET();

//     String payload = http.getString();
         
//     Serial.print("HTTP Response code: ");
//     Serial.println(httpResponseCode);

//     Serial.print("HTTP Response payload: ");
//     Serial.println(payload);

//     StaticJsonDocument<200> doc;

//     DeserializationError error = deserializeJson(doc, payload);

//     // Test if parsing succeeds.
//     if (error) {
//       Serial.print(F("deserializeJson() failed: "));
//       Serial.println(error.f_str());
//       return;
//     } 

//     // Print the result
//     serializeJsonPretty(doc, Serial);

//     Serial.println();

//     // Free resources
//     http.end();
//   }

//   get_subscribed_modules();
// }

// void setup() {

//   // standard stuff here
//   Serial.begin(115200);

//   esp_efuse_mac_get_default(mac_address);

//   // just an update to progress
//   Serial.println("starting server");

//   WiFi.softAP(AP_SSID, AP_PASS);
//   delay(100);
//   WiFi.softAPConfig(PageIP, gateway, subnet);
//   delay(100);
//   Actual_IP = WiFi.softAPIP();
//   Serial.print("IP address: "); Serial.println(Actual_IP);

//   printWifiStatus();

//   server.on("/", send_web_page_for_get_wifi_connections);
//   server.on("/xml", SendXML);
//   server.on("/SEND_WIFI_NAME_PASSWORD", update_wifi_name_and_password);

//   // finally begin the server
//   server.begin();

//   while (true) {
//     if (WiFi.softAPgetStationNum() > 0) {
//       // Client connected
//       Serial.println("Configuration started.");
//       break;
//     }

//     delay(1000);
//   }

//   while (true)
//   { 
    
//     server.handleClient();

//     if(change_type_wifi) {
//       connect_wifi_network();
//     }

//     if(change_type_login) {
//       connect_to_server();
//     }

//     if(login_successful) {
//       break;
//     }

//   }
  
// }

// void loop() 
// {

// }

// // end of code