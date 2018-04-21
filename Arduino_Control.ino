/*
  *Voltage reading based on
  * blog.Udemy.com/arduino-voltmeter/
  * Capcity in amp hours=Amps Pulled from constent current source * Hours ran 
  * hours = secs/3600
  * Program released under GPL v3 
  */

 #include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C //Change this value to match your i2c address 

Adafruit_SSD1306 display(-1);

 
 float vPow = 4.7;
 float r1 = 0;
 float r2 = 0;
 float vmin = 2;
 float hour = 0;
 float v = 0;
 int sec = 0;
 int plus1State = 0;
 int pluspoint1State = 0;
 int minus1State = 0;
 int minuspoint1State = 0;
 const int plus1 = 12;
 const int pluspoint1 = 11;
 const int minus1 = 10;
 const int minuspoint1 = 9;
 const int mosfet = 8;

 
 void setup() {
   Serial.begin(9600);
   pinMode(plus1, INPUT);
   pinMode(pluspoint1, INPUT);
   pinMode(minus1, INPUT);
   pinMode(minuspoint1, INPUT);
   pinMode(mosfet, OUTPUT);
   display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
   
   // Send ANSI terminal codes
   Serial.print("\x1B");
   Serial.print("[2J");
   Serial.print("\x1B");
   Serial.println("[H");
   // End ANSI terminal codes
   
  
   Serial.println("BATTERY TESTER by T.Cowles");
   
   
   
   
   delay(2000);
 }
 
 void loop() {
  plus1State = digitalRead(plus1);
  pluspoint1State = digitalRead(pluspoint1);
  minus1State = digitalRead(minus1);
 minuspoint1State = digitalRead(minuspoint1);
   v = (analogRead(0) * vPow) / 1024.0;
   float v2 = v;
   
   // Send ANSI terminal codes
   Serial.print("\x1B");
   Serial.print("[1A");
   // End ANSI terminal codes
   Serial.println(v2);
   if (v >= vmin) {
    sec = sec + 1; 
    delay (1000);
    digitalWrite(mosfet, HIGH);
     Serial.print("Time in sec = ");
     Serial.println(sec);
    display.clearDisplay();
   display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(27,0);
  display.print("Running ");
  display.print(sec);
  display.setCursor(27,20);
  display.print("input= ");
  display.print(v);
  display.setCursor(27,40);
  display.print("V Min= ");
  display.print(vmin);
 display.display();
    Serial.print(v);
    v = (analogRead(0) * vPow) / 1024.0;
    delay (10);  }


     if (v < vmin) {
    digitalWrite(mosfet, LOW);
    hour = sec / 3600.0;
    Serial.print("Time in hours = ");
    Serial.println(hour);
    display.clearDisplay();
   display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Done! Time in Hours = ");
  display.print(hour);
  display.display(); 
  delay (1000); }
  
    if (plus1State == HIGH)
    {
      vmin = vmin + 1;
      delay (50); 


  // update display with all of the above graphics
  display.display();
    }
    if (pluspoint1State == HIGH)
    {
      vmin = vmin + .1;
      delay (50);
      display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(27,0);
  display.print("Cut off voltage =");
  display.setCursor(27, 40);
  display.print(vmin);

  // update display with all of the above graphics
  display.display();
    }
    if (minus1State == HIGH)
   {
    vmin = vmin - 1;
    delay (50);
    display.clearDisplay();
     display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(27,0);
  display.print("Cut off voltage =");
  display.setCursor(27, 40);
  display.print(vmin);

  // update display with all of the above graphics
  display.display();
   }
if (minuspoint1State == HIGH)
   {
    vmin = vmin - .1;
    delay (50);
    display.clearDisplay();
     display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(27,0);
  display.print("Cut off voltage =");
  display.setCursor(27, 40);
  display.print(vmin);

  // update display with all of the above graphics
  display.display();
   }
   //}
 }
