
/*

* MOSI: Pin 11 / ICSP-4
* MISO: Pin 12 / ICSP-1
* SCK: Pin 13 / ISCP-3
* SS/SDA: Pin 10
* RST: Pin 9
*/

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define PIN 2
int relais = 6;

const int Buzzer = 2;

MFRC522 mfrc522(SS_PIN, RST_PIN);

int counter = 0;



void setup(){
Serial.begin(9600);
SPI.begin();
mfrc522.PCD_Init();


    pinMode(relais, OUTPUT);
pinMode(Buzzer,OUTPUT);
    digitalWrite(relais, HIGH);
   
}

void loop(){
    Serial.println(counter);
 
    if ( ! mfrc522.PICC_IsNewCardPresent())
{
return;
}


if ( ! mfrc522.PICC_ReadCardSerial())
{
return;
}

long code=0; // Als neue Variable fügen wir „code“ hinzu, unter welcher später die UID als zusammenhängende Zahl ausgegeben wird. Statt int benutzen wir jetzt den Zahlenbereich „long“, weil sich dann eine größere Zahl speichern lässt.

for (byte i = 0; i < mfrc522.uid.size; i++)
{
code=((code+mfrc522.uid.uidByte[i])*10); // Nun werden wie auch vorher die vier Blöcke ausgelesen und in jedem Durchlauf wird der Code mit dem Faktor 10 „gestreckt“. (Eigentlich müsste man hier den Wert 1000 verwenden, jedoch würde die Zahl dann zu groß werden.
}

Serial.println(code);
tone(Buzzer,500,100);
delay(101);
tone(Buzzer,1000,100);
   delay(500);


if(code == 2207850) {counter = 1;} 
else if((counter == 1) && (code == 139050)) {counter = 3;}
else {counter = 0;}

if(counter == 3) {
digitalWrite(relais,LOW);
delay(5000);
digitalWrite(relais,HIGH);
counter == 0;}

  else {digitalWrite(relais,HIGH);}
}


//2376050 = gelb lila   1
//139050 = türkis türkis rot 2 5
//1889850 = orange blau 3
//474050 = lila türkis 4
//766650 = gelb orange blau gelb 6
//2207850 = lila rot  7
   
             
    

    
