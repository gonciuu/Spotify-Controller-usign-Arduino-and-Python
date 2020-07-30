
#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>
#include <IRremote.h>


LiquidCrystal_PCF8574 lcd(0x27); // set the LCD address to 0x27 for a 16 chars and 2 line display

     
String allStr="";

const int led_green = 10;  
const int led_red = 9;  

const int RECV_PIN = 4;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;



void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); 
  lcd.clear();
  lcd.setBacklight(255);
  irrecv.enableIRIn();
  pinMode(led_green, OUTPUT);
  pinMode(led_red, OUTPUT);
  irrecv.blink13(true);
}

void loop() {

    
    lcd.clear();
    while (Serial.available() > 0) {  
        allStr = allStr + char(Serial.read());
    }
    int border = allStr.indexOf('^');
    String song = allStr.substring(0,border);
    String artist = allStr.substring(border+1,allStr.length());
    lcd.print(song);
    lcd.setCursor(0,1);
    lcd.print(artist);
    allStr = "";
    delay(400);
    lcd.setCursor(0,0);
    lcd.clear();
    if (irrecv.decode(&results)){
 
        if (results.value == 0XFFFFFFFF)
          results.value = key_value;

        switch(results.value){
          case 0xFFA25D:
          Serial.println("CH-");
          break;
          case 0xFF22DD:
          Serial.println("|<<");
          break;
          case 0xFF02FD:
          Serial.println(">>|");
          break ;  
          case 0xFFC23D:
          Serial.println(">|");
          break ;               
          case 0xFFE01F:
          Serial.println("-");
          break ;  
          case 0xFFA857:
          Serial.println("+");
          break ;  
          case 0xFF906F:
          Serial.println("EQ");
          break ;  
        }
        key_value = results.value;
        irrecv.resume(); 
  }
    
  
}
