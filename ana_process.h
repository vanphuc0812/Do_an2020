#define anaPIN  A0
int sensor_value=0;

void  read_sensorvalue() {
  for(int i=0;i<10;i++)
  { 
    int analog=analogRead(anaPIN);
    sensor_value+=analog;
  }
  sensor_value=sensor_value/10;
  sensor_value=map(sensor_value,1024,0,0,100);
}
