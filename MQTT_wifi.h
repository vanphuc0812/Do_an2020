#define AIO_SERVER       "io.adafruit.com"
#define AIO_SERVERPORT   1883               
#define AIO_USERNAME     "vanphuc2401"       
#define AIO_KEY          "aio_rhzu71ajiwZgVDzPIYgeYtnMbgDo"


#define WLAN_SSID "Van phuc"         
#define WLAN_PASS "0thichcho"  

WiFiClient client;                                                                                  // Tạo một wifi client
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);              // cài đặt MQTT client bằng WiFi client and MQTT server and login details.
Adafruit_MQTT_Subscribe onoffbutton1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/sensor");
Adafruit_MQTT_Subscribe onoffbutton2 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/relay");
Adafruit_MQTT_Subscribe nguong = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/nguong_moi");
Adafruit_MQTT_Publish sensor = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/sensor");
Adafruit_MQTT_Publish relay = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/relay");

void MQTT_connect() 
{
  int8_t ret;
  if (mqtt.connected())     // Stop if already connected.
  {
    return;
  }
  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) 
  { 
       Serial.println(mqtt.connectErrorString(ret));                  // connect will return 0 for connected
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);              // wait 5 seconds
       retries--;
       if (retries == 0) 
       {
         while (1);              // basically die and wait for WDT to reset me
       }

  }
  Serial.println("MQTT Connected!");
}
//-----------------------------------------------------------------------------------
void wifi_connect()
{
  Serial.print("Connecting to ");       
  Serial.println(WLAN_SSID);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());
}
