#include<M5StickC.h> 
#include<Wire.h> 
#include<Arduino.h> 
#include<Bme280.h>
Bme280TwoWire sensor; 

void setup() {
M5.begin();
Wire.begin(0, 26); 
Serial.begin(9600); 
while ( !Serial ) delay(100);
Serial.println("BMP280 selftest started."); 
pinMode(26, OUTPUT); 
sensor.begin(Bme280TwoWireAddress::Primary);
sensor.setSettings(Bme280Settings::indoor());
}
int j = 0; 
void loop() {
j++;
digitalWrite(26, HIGH);   
M5.Lcd.fillScreen(BLACK); 
M5.Lcd.setTextColor(RED, BLACK); 
M5.Lcd.setTextSize(1); 
M5.Lcd.setRotation(3); 
if(j >= 30) { 
  M5.Lcd.setTextColor(random(0xFFFF), BLACK); 
  for (int x = 0; x< 20; x++) {
  auto temperature = String(sensor.getTemperature())+"*C";
  auto pressure = String(sensor.getPressure() / 100.0F) + " hPa";
  String xtemp = "Temperature: \n"+temperature + "/";
  String xpressure = "Pressure:\n"+ pressure + "";
  M5.Lcd.setCursor(1,1);  
  M5.Lcd.setTextSize(2); 
  M5.Lcd.print(xtemp);
  float t = sensor.getTemperature();    
  M5.Lcd.print((int)round(1.8*t+32));
  M5.Lcd.println("*F"); 
  M5.Lcd.println(xpressure);   
  for(int s=0; s<7; s++) {
  digitalWrite(26, LOW); 
  delay(30); 
  digitalWrite(26, HIGH); 
  delay(40); 
  }
  }
  j = 0;  
  M5.Lcd.fillScreen(BLACK); 
  M5.Lcd.setTextSize(1); 
}

if (j >= 1) {  
digitalWrite(26, LOW);   
M5.Lcd.setCursor(1,1); 
M5.Lcd.setTextSize(2); 
byte fahrenheit = (sensor.getTemperature() * 9) / 5 + 32; 
M5.Lcd.println("Temperature:"); 
M5.Lcd.setTextSize(5); 
M5.Lcd.print(fahrenheit, DEC);
M5.Lcd.println("*F");
delay(200); 
}
}
