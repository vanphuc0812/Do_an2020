#include <Adafruit_MQTT.h>            
#include <Adafruit_MQTT_Client.h>     
#include <ThingSpeak.h>
#include <ESP8266WiFi.h>              
#include "ana_process.h"
#include "timer_interrupt.h"

//--------------------------------------------------------------------                 
const char *server = "api.thingspeak.com";
unsigned long myChannelNumber = 1009263;
const char * myWriteAPIKey = "OG5WGCF1OTLO6AGI";
//--------------------------------------------------------------------   
void setup() 
{ 
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  Serial.begin(9600);
  delay(10);
/*---------------------------------kết nối wifi-----------------------------------------*/
  wifi_connect();
/*--------------------------------cài đặt ngắt và timer----------------------------------*/
  timer_interrupt_init();
/*--------------------------------Cài đặt MQTT-------------------------------------------*/
  mqtt.subscribe(&onoffbutton1);        
  mqtt.subscribe(&onoffbutton2);
  mqtt.subscribe(&nguong);

/*--------------------------------khởi tạo thingspeak------------------------------------*/
  ThingSpeak.begin(client);
/*--------------------------------Khởi tạo hiển thị led 7 đoạn---------------------------*/
 Led7Init() ;
 read_sensorvalue();
 HienThiLED7doan(LED_value,2);
 MQTT_connect();
 digitalWrite(relayPin, LOW);
 relay.publish(0);
}
 
void loop() 
{ MQTT_connect();
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) 
  {
    if (subscription == &nguong) {
      Serial.print("Channel 3: Got: ");
      Serial.println((char *)nguong.lastread);
      String response = (char*)nguong.lastread;
      LED_value = response.toInt();
      HienThiLED7doan(LED_value,2);
      }
    if (subscription == &onoffbutton1) {
      Serial.print("Channel 1: Got: ");
      Serial.println((char *)onoffbutton1.lastread);
      String response = (char*)onoffbutton1.lastread;
      if (response == "1")
      {
       read_sensorvalue();
       Serial.print("Sensor value is:");
       Serial.println(sensor_value);
       sensor.publish(0);
       ThingSpeak.writeField(myChannelNumber, 1, sensor_value, myWriteAPIKey);
      }
      }
    if (subscription == &onoffbutton2) 
    {
      Serial.print("Channel 2 Got: ");
      Serial.println((char *)onoffbutton2.lastread);
      String response = (char*)onoffbutton2.lastread;
      if (response == "1")
            { 
            digitalWrite(relayPin, HIGH);
            }
      else  {
            digitalWrite(relayPin, LOW);
            }
    }
  }
}
