/*
  *Voltage reading based on
  * blog.Udemy.com/arduino-voltmeter/
  * Amps Pulled * Hours ran 
  * hours = secs/3600
  */
 
 float vPow = 4.7;
 float r1 = 100000;
 float r2 = 10000;
 float vmin = 0
 float hour = 0
 int sec = 0
 int plus1 = 12
 int pluspoint1 = 11
 int minus1 = 10
 int minuspoint1 = 9
 int mosfet = 8 
 
 void setup() {
   Serial.begin(9600);
   pinMode(plus1, INPUT);
   pinMode(pluspoint1, INPUT);
   pinMode(minus1, INPUT);
   pinMode(minuspoint1, INPUT);
   pinMode(Mosfet, OUTPUT);
   
   // Send ANSI terminal codes
   Serial.print("\x1B");
   Serial.print("[2J");
   Serial.print("\x1B");
   Serial.println("[H");
   // End ANSI terminal codes
   
   Serial.println("--------------------");
   Serial.println("BATTERY TESTER by T.Cowles");
   Serial.print("Maximum readable Battery Voltage: ");
   Serial.print((int)(vPow / (r2 / (r1 + r2))));
   Serial.println("V");
   Serial.println("--------------------");
   Serial.println("");
   
   delay(2000);
 }
 
 void loop() {
   float v = (analogRead(0) * vPow) / 1024.0;
   float v2 = v / (r2 / (r1 + r2));
   
   // Send ANSI terminal codes
   Serial.print("\x1B");
   Serial.print("[1A");
   // End ANSI terminal codes
   Serial.println(v2);
   if ()
 }
