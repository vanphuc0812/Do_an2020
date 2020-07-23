#define ledPIN  D3
#include  "Led7.h"
#include "MQTT_wifi.h"
#include <Ticker.h>
Ticker    timer;
#define relayPin D0
void  autoPum()
{
  if(sensor_value>LED_value)  {digitalWrite(ledPIN,0);}
  if(sensor_value>70)         
  {
    digitalWrite(relayPin,0);
    relay.publish(0);
  }
  if(sensor_value<LED_value)  
  {
    digitalWrite(ledPIN,1);
    digitalWrite(relayPin,HIGH);
    relay.publish(1);
  }
}

void timer_task()
{
  read_sensorvalue();
  HienThiLED7doan(sensor_value,2);
  autoPum();
}

void timer_interrupt_init()
{
  pinMode(ledPIN, OUTPUT);
  timer.attach(10,timer_task);
}
  
