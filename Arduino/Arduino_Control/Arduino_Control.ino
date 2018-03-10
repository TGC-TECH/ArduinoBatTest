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
 float r1 = 100000;
 float r2 = 10000;
 float vmin = 0;
 float hour = 0;
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
  display.clearDisplay();
  display.display();
   
   // Send ANSI terminal codes
   Serial.print("\x1B");
   Serial.print("[2J");
   Serial.print("\x1B");
   Serial.println("[H");
   // End ANSI terminal codes
   
  
   Serial.println("BATTERY TESTER by T.Cowles");
   Serial.print("Max readable Voltage: ");
   Serial.print((int)(vPow / (r2 / (r1 + r2))));
   
   
   delay(2000);
 }
 
 void loop() {
  plus1State = digitalRead(plus1);
  pluspoint1State = digitalRead(pluspoint1);
  minus1State = digitalRead(minus1);
 minuspoint1State = digitalRead(minuspoint1);
   float v = (analogRead(0) * vPow) / 1024.0;
   float v2 = v / (r2 / (r1 + r2));
   
   // Send ANSI terminal codes
   Serial.print("\x1B");
   Serial.print("[1A");
   // End ANSI terminal codes
   Serial.println(v2);
   if (v2 >= vmin);
   {
    Serial.print("Cut Off Voltage = ");
    Serial.println(vmin);
    sec = sec + 1; 
    delay (1000);
    digitalWrite(mosfet, HIGH);
     Serial.print("Time in sec = ");
     Serial.println(sec);
      display.clearDisplay();
       display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(27,0);
  display.print("Time in sec =");
  display.setCursor(27, 40);
  display.print(sec);


   }
   if (v2 < vmin);
   {
    digitalWrite(mosfet, LOW);
    hour = sec / 3600;
    Serial.println("DONE! Time in hours =");
    Serial.println(hour);
    display.clearDisplay();
   display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(27,0);
  display.print("DONE! Time in hours =");
  display.setCursor(27, 40);
  display.print(hour);

  // update display with all of the above graphics
  display.display();
    if (plus1State == HIGH);
    {
      vmin = vmin + 1;
      delay (50);
      display.clearDisplay();
       display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(27,0);
  display.print("Cut off voltage =");
  display.setCursor(27, 40);
  display.print(vmin);

  // update display with all of the above graphics
  display.display();
    }
    if (pluspoint1State == HIGH);
    {
      vmin = vmin + .1;
      delay (50);
      display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(27,0);
  display.print("Cut off voltage =");
  display.setCursor(27, 40);
  display.print(vmin);

  // update display with all of the above graphics
  display.display();
    }
    if (minus1State == HIGH);
   {
    vmin = vmin - 1;
    delay (50);
    display.clearDisplay();
     display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(27,0);
  display.print("Cut off voltage =");
  display.setCursor(27, 40);
  display.print(vmin);

  // update display with all of the above graphics
  display.display();
   }
   if (minuspoint1State == HIGH);
   {
    vmin = vmin - .1;
    delay (50);
    display.clearDisplay();
     display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(27,0);
  display.print("Cut off voltage =");
  display.setCursor(27, 40);
  display.print(vmin);

  // update display with all of the above graphics
  display.display();
   }
   }
 }
