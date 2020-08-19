#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <max6675.h>

int ktcSO = 8;
int ktcCS = 9;
int ktcCLK = 13;


int set;

MAX6675 thermocouple(ktcCLK, ktcCS, ktcSO);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for(;;);
  }
  delay(500);
  pinMode(6,OUTPUT);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.println("DIY JBC MK.2 v1.1");
  display.display(); 
  delay(1500);
}

void dp(int cr, int se){
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  if(cr == 0){
    display.println("Insert tip");
  }
  else{
    display.println(String(cr)+" C");
  }
  display.drawLine(0, 30, 128, 30, WHITE);
  display.setCursor(0, 36);
  display.println("Set: "+String(se));
  display.display(); 
}

void loop() {


  digitalWrite(6,LOW);
  delay(200);
  int temp = thermocouple.readCelsius();
  temp = 1.406*temp;
  int pot = map(analogRead(A6) ,0 ,1023 ,0 ,400);
  dp(temp,pot);
  set = pot-temp;
  if(set < 0) {set = 0;}
  set =map(set, 0, 30, 0, 500);
  if(set> 500) {set = 500;}
  if(temp < pot) {digitalWrite(6,HIGH);}
  if(temp > pot) {digitalWrite(6,LOW);}
  delay(set);

}
