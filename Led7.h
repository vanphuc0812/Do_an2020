int latchPin = D7; //load
//chân SH_CP của 74HC595
int clockPin = D6;//sclk
//Chân DS của 74HC595
int dataPin = D5;//sdi
int LED_value =30;
 
// Ta sẽ xây dựng mảng hằng số với các giá trị cho trước
// Các bit được đánh số thứ tự (0-7) từ phải qua trái (tương ứng với A-F,DP)
// Vì ta dùng LED 7 đoạn chung cực dương nên với các bit 0
// thì các đoạn của LED 7 đoạn sẽ sáng
// với các bit 1 thì đoạn ấy sẽ tắt
 
//mảng có 10 số (từ 0-9) và 
const byte Seg[10] = {
  0b11000000,//0 - các thanh từ a-f sáng
  0b11111001,//1 - chỉ có 2 thanh b,c sáng
  0b10100100,//2
  0b10110000,//3
  0b10011001,//4
  0b10010010,//5
  0b10000010,//6
  0b11111000,//7
  0b10000000,//8
  0b10010000,//9
};
 void Led7Init() {
  //Bạn BUỘC PHẢI pinMode các chân này là OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  Serial.println("led 7 connected");
}
void HienThiLED7doan(unsigned long Giatri, byte SoLed = 2) {
  
  byte *array= new byte[SoLed];
  for (byte i = 0; i < SoLed; i++) {
    //Lấy các chữ số từ phải quá trái
    array[i] = (byte)(Giatri % 10UL);
    Giatri = (unsigned long)(Giatri /10UL);
  }
  digitalWrite(latchPin, LOW);
  for (int i = 0; i < SoLed; i++)
    shiftOut(dataPin, clockPin, MSBFIRST, Seg[array[i]]); 
  
  digitalWrite(latchPin, HIGH);
  free(array);
}
