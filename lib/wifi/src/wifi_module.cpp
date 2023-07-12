#include "wifi_module.h"

#include <WiFi.h>       // standard library
#include <WebServer.h>  // standard library
#include <HTTPClient.h> // standard library
#include <ArduinoJson.h>
#include <esp_mac.h>
#include <PubSubClient.h>
#include "index_for_wifi_connection.h"   // .h file that stores your html page code
#include "index_for_login.h" // .cpp file that stores your html page code


// once  you are read to go live these settings are what you client will connect to
#define AP_SSID "petzeira_wifi"
#define AP_PASS "petzeira123"
#define SSID_NAME "Jao"
#define PASS_NAME "12345678"

Wifi_Module* object;

IPAddress local_IP(192, 168, 1, 184);
IPAddress wifi_IP(192, 168, 1, 185);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional


String local_ssid;
String local_pass;
String username;
String password;
String user_token;

volatile bool change_type_wifi = false;
volatile bool change_type_login = false;
volatile bool login_successful = false;

String cookie;
uint8_t* mac_address;
char XML[2048];
char buf[32];

Application* application;

// gotta create a server
WebServer server(80);
CookieJar cookieJar;
String serverName = "http://api.pedroribasserras.space:3333/";

#define MQTT_PORT 1883
const char* mqtt_server = "api.pedroribasserras.space";

String mac_address_string;
String mqtt_token;

String mqtt_message_ping;
String mqtt_client_topic;
String mqtt_server_topic;
String mqtt_date_topic = "date";

WiFiClient espClient;
PubSubClient mqtt_client(espClient);

void update_wifi_name_and_password() {
  String update = server.arg("VALUE");
  local_ssid = update.substring(0, update.indexOf(","));
  local_pass = update.substring(update.indexOf(",") + 1);

  Serial.println("[update_user_name] - INFO - ");
  Serial.print("user_name: "); Serial.println(local_ssid);
  Serial.print("password: "); Serial.println(local_pass);

  change_type_wifi = true;

  server.send(200, "text/plain", ""); //Send web page
}

void update_login() {
  String update = server.arg("VALUE");
  username = update.substring(0, update.indexOf(","));
  password = update.substring(update.indexOf(",") + 1);

  Serial.println("[update_login] - INFO - ");
  Serial.print("user_name: "); Serial.println(username);
  Serial.print("password: "); Serial.println(password);

  change_type_login = true;

  server.send(200, "text/plain", ""); //Send web page
}

void send_web_page_for_get_wifi_connections() {
  Serial.println("sending web page");
  server.send(200, "text/html", PAGE_MAIN_FOR_WIFI_CONNECTION);
}

void send_web_page_for_login() {
  Serial.println("sending web page");
  server.send(200, "text/html", PAGE_FOR_LOGIN);
}

void SendXML() {
  server.send(200, "text/xml", XML);
}

void printWifiStatus() {

  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("Open http://");
  Serial.println(WiFi.localIP());
}

void connect_wifi_network() 
{
  //server.close();
  //WiFi.disconnect();
  WiFi.mode(WIFI_STA);

  Serial.print("Connecting to ");
  //Serial.println(local_ssid.c_str());

  //WiFi.begin(local_ssid.c_str(), local_pass.c_str());

  WiFi.begin(SSID_NAME, PASS_NAME);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/login", send_web_page_for_login);
  server.on("/SEND_NAME_PASSWORD", update_login);

  server.begin();

  change_type_wifi = false;
}

void connect_to_server() 
{
  if(WiFi.status()== WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;

    String http_path_login = serverName + "auth/login";

    const char * headerkeys[] = {"Set-Cookie"};
    size_t headerkeyssize = sizeof(headerkeys)/sizeof(char*);
    
    http.collectHeaders(headerkeys,headerkeyssize);

    http.begin(client, http_path_login);

    http.addHeader("Content-Type", "application/json");

    Serial.print("HTTP path: ");
    Serial.println(http_path_login);

    int httpResponseCode = http.POST("{\"email\":\""+ username +"\",\"password\":\""+password+"\"}");

    String payload = http.getString();

    StaticJsonDocument<200> doc;

    DeserializationError error = deserializeJson(doc, payload);

    // Test if parsing succeeds.
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    } 

    Serial.print("message: ");
    Serial.println(doc["message"].as<String>());

    if(doc["message"].as<String>() == "Login successful") {
      cookie = http.header("Set-Cookie");
      Serial.print("Set-Cookie: ");
      Serial.println(cookie);

      cookie = cookie.substring(0, cookie.indexOf(';'));

      login_successful = true;
    }

    http.end();

    change_type_login = false;
  }
}

void mqtt_message_callback(char* topic, byte* message, unsigned int length) 
{
  String messageTemp;
  String messageTopic(topic);
  
  for (int i = 0; i < length; i++) {
    messageTemp += (char)message[i];
  }

  if(messageTemp.substring(0, messageTemp.indexOf('\n')).compareTo("eDeLagrima2005") != 0) {
    return;
  }

  messageTemp.remove(0, messageTemp.indexOf('\n') + 1);
  
  int index = messageTemp.indexOf('\n');

  String command = messageTemp.substring(0, index);
  String data = messageTemp.substring(index + 1);

  if(messageTopic.compareTo(mqtt_server_topic) == 0) {
    if(command.compareTo("ping") == 0) {
      return;
    }


    Serial.println("Server topic: ");
    Serial.print("command: ");
    Serial.println(command);
    Serial.print("data: ");
    Serial.println(data);

    if(command.compareTo("act") == 0) {
      
      StaticJsonDocument<200> doc;
      deserializeJson(doc, data);
      String type_act = doc["type"].as<String>();

      application->act_module(type_act);

      String return_message = mqtt_token + "\nact\n{\"message\":\"ok\",\"moduleType\":\""+ type_act +"\"}\n";
      mqtt_client.publish(mqtt_client_topic.c_str(), return_message.c_str());
      return;
    }

    if(command.compareTo("read") == 0) {
      
      StaticJsonDocument<200> doc;
      deserializeJson(doc, data);
      String type_read = doc["type"].as<String>();

      String return_message = mqtt_token + "\nread\n{\"value\":\""+application->read_module(type_read)+"\",\"moduleType\":\""+ type_read +"\"}\n";
      mqtt_client.publish(mqtt_client_topic.c_str(), return_message.c_str());
      return;
    }

    if(command.compareTo("sendSchedule") == 0) {
      
      StaticJsonDocument<200> doc;
      deserializeJson(doc, data);

      JsonArray documentRoot = doc.as<JsonArray>();

      String type_schedule;
      int time;
      struct timeval time_now;

      for (JsonObject keyValue : documentRoot) {
        type_schedule = keyValue["moduleType"].as<String>();
        time = keyValue["time"].as<String>().toInt();
      }

      time_now.tv_sec = time;
      time_now.tv_usec = time * 1000000;
      application->add_schedule(time_now, type_schedule);

      String return_message = mqtt_token + "\nsendSchedule\n{\"message\":\"ok\",\"moduleType\":\""+ type_schedule +"\"}\n";
      mqtt_client.publish(mqtt_client_topic.c_str(), return_message.c_str());
      return;
    }

    if(command.compareTo("calibre") == 0) {
      application->calibre_module();

      String return_message = mqtt_token + "\ncalibre\n{\"message\":\"ok\",\"moduleType\":\"food\",\"calibreWeight\":\"1000\"}\n";
      mqtt_client.publish(mqtt_client_topic.c_str(), return_message.c_str());
      return;
    }

    if(command.compareTo("schedule") == 0) {
      
      StaticJsonDocument<200> doc;
      deserializeJson(doc, data);
	
      JsonArray documentRoot = doc.as<JsonArray>();

      String type_schedule;
      int time;
      struct timeval time_now;

      for (JsonObject keyValue : documentRoot) {
        type_schedule = keyValue["moduleType"].as<String>();
        time = keyValue["time"].as<String>().toInt();
        time_now.tv_sec = time;
        time_now.tv_usec = time * 1000000;
        application->add_schedule(time_now, type_schedule);
      }
      return;
    }
  }

  if(messageTopic.compareTo(mqtt_date_topic) == 0) {
    struct timeval time_now;
    time_now.tv_sec = command.toInt();
    time_now.tv_usec = command.toInt() * 1000000;
    settimeofday(&time_now, nullptr);
  }
}

void get_mqtt_token()
{
  Serial.println("Connecting to mqtt token...");

  WiFiClient client;
  HTTPClient http;

  String http_path_subscribe_water = serverName + "module/mqtt-token";

  http.begin(client, http_path_subscribe_water);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Cookie", cookie);

  http.POST("{\"serial\":\""+ mac_address_string+ "\"}");

  StaticJsonDocument<200> doc;
  String payload = http.getString();

  deserializeJson(doc, payload);

  http.end();

  Serial.print("module/mqtt_token/ result: ");
  serializeJsonPretty(doc, Serial);
  Serial.println();

  mqtt_token = doc["mqttToken"].as<String>();
}

void subscribe_modules(String modules_payload)
{
  Serial.println("Connecting to subscribe modules...");

  WiFiClient client;
  HTTPClient http;

  String http_path_subscribe_water = serverName + "module/subscribe";

  http.begin(client, http_path_subscribe_water);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Cookie", cookie);

  StaticJsonDocument<400> doc;

  String payload = "";

  deserializeJson(doc, modules_payload);

  if(doc["type"].as<String>().compareTo("water") != 0) {
      http.POST("{\"serial\":\""+ mac_address_string +"\",\"moduleType\":\"water\",\"name\":\"water\"}");
      payload += http.getString();
  }

  if(doc["type"].as<String>().compareTo("food") != 0) {
    http.POST("{\"serial\":\""+ mac_address_string +"\",\"moduleType\":\"food\",\"name\":\"food\"}");
    payload += http.getString();
  }

  mqtt_client.subscribe(mqtt_server_topic.c_str(),1);
  mqtt_client.subscribe(mqtt_date_topic.c_str(),1);
  Serial.println("mqtt client subscribe");

  Serial.print("module/subscribe/ result: ");
  Serial.println(payload);

  http.end();
}

void connectToMqtt() 
{
  Serial.println("Connecting to MQTT...");

  mqtt_client.setServer(mqtt_server, MQTT_PORT);

  mqtt_client.setCallback(mqtt_message_callback);

  while (!mqtt_client.connected()) {
    Serial.print(".");
  
    if (mqtt_client.connect(mac_address_string.c_str())) {
      mqtt_client.setKeepAlive(600);
      mqtt_client.setSocketTimeout(600);
      Serial.println("connected");  
      break;
    } 

    delay(2000);
  }
}

void get_subscribed_modules() 
{
  
    connectToMqtt();

    WiFiClient client;
    HTTPClient http;

    String http_path_modules = serverName + "module";

    http.begin(client, http_path_modules);

    http.addHeader("Content-Type", "application/json");
    http.addHeader("Cookie", cookie);

    Serial.print("HTTP path: ");
    Serial.println(http_path_modules);

    int httpResponseCode = http.GET();

    String payload = http.getString();

    http.end();

    Serial.print("module/(result: ");
    Serial.println(payload);

    subscribe_modules(payload);

    get_mqtt_token();

    mqtt_message_ping = mqtt_token + "\n" + "ping\n";

    mqtt_client.publish(mqtt_client_topic.c_str(), mqtt_message_ping.c_str());
}

Wifi_Module::Wifi_Module(Application* app)
{
  _mac_address = nullptr;
  application = app;
}

Wifi_Module::~Wifi_Module()
{
    delete _mac_address;
}

void Wifi_MQTT_Task(void *pvParameters) 
{
    connect_wifi_network();

    // WiFi.softAP(AP_SSID, AP_PASS);
    // delay(100);
    // WiFi.softAPConfig(local_IP, gateway, subnet);
    // delay(100);
    // Serial.print("IP address: "); Serial.println(WiFi.softAPIP());

    // server.on("/", send_web_page_for_get_wifi_connections);
    // server.on("/xml", SendXML);
    // server.on("/SEND_WIFI_NAME_PASSWORD", update_wifi_name_and_password);

    // finally begin the server
    // server.begin();

    // while (true) {
    //     if (WiFi.softAPgetStationNum() > 0) {
    //     // Client connected
    //     Serial.println("Configuration started.");
    //         break;
    //     }

    //     delay(1000);
    // }

    while (true)
    { 
        server.handleClient();

        // if(change_type_wifi) {
        //   connect_wifi_network();
        // }

        if(change_type_login) {
          connect_to_server();
        }

        if(login_successful) {
          get_subscribed_modules();
          break;
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }

    //start schedule
    String get_schedule_water = mqtt_token + "\nschedule\n{\"moduleType\":\"water\"}\n";
    String get_schedule_food = mqtt_token + "\nschedule\n{\"moduleType\":\"food\"}\n";
    
    mqtt_client.publish(mqtt_client_topic.c_str(), get_schedule_water.c_str());
    vTaskDelay(200 / portTICK_PERIOD_MS);
    mqtt_client.publish(mqtt_client_topic.c_str(), get_schedule_food.c_str());

    int i = -1;
    std::pair<bool, String> some_executed;
    while (true)
    {
      i++;
      vTaskDelay(10 / portTICK_PERIOD_MS);
      mqtt_client.loop();

      if(i == 200) {
        Serial.println("Ping");
        mqtt_client.publish(mqtt_client_topic.c_str(), mqtt_message_ping.c_str());
        i = -1;
      }

      some_executed = application->check_some_executed();

      if(some_executed.first) {
        Serial.println("Some executed");
        String return_message = mqtt_token + "\nfed\n{\"moduleType\":\""+ some_executed.second +"\"}\n";
        mqtt_client.publish(mqtt_client_topic.c_str(), return_message.c_str());
      }
    }

    vTaskDelete(nullptr);
}

void Wifi_Module::setup()
{
    Serial.println("[Wifi_Module::setup] - INFO - wifi setup");

    if(esp_efuse_mac_get_default(mac_address) != ESP_OK) {
      mac_address = nullptr;
      mac_address_string= "0000001321";
    } else {
      for(int i=0; i < 6; i++) {
        mac_address_string += (int)mac_address[i];
      }
    }

    mqtt_client_topic = "client/" + mac_address_string;
    mqtt_server_topic = "server/" + mac_address_string;

   
}

void Wifi_Module::start()
{
  Serial.println("Wifi_Module::start");
  xTaskCreate(Wifi_MQTT_Task, "WifiMQTT_Task", 40 * 1024, this, 3, nullptr);
}

void Wifi_Module::loop()
{
  
}

void Wifi_Module::exec_action()
{

}

String Wifi_Module::name()
{
    return "wifi_module";
}

float Wifi_Module::read_value()
{
  return 0.0;
}

bool Wifi_Module::action_executed()
{
  return false;
}