
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
const int rs = A0, en = A1, d4 = A2, d5 = A3, d6 = A4, d7 = A5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const byte Filas = 4;
const byte Cols = 4;
byte Pins_Filas[] = {13, 12, 11, 10};
byte Pins_Cols[] = {9, 8, 7, 6};
char Teclas [Filas][Cols] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}

};
char codigoSecreto[4] = {'2', '2', '5', '5'};
int posicion = 0;
int cursor = 5;
int clave = 0;
int luz = 0;
int tiempo = 0;
int ledVerde = 2;
int ledRojo = 3;
int buzzer = 4;
Keypad Teclado1 = Keypad(makeKeymap(Teclas), Pins_Filas, Pins_Cols, Filas, Cols);


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  //lcd.noBacklight();
  pinMode (ledVerde, OUTPUT);
  pinMode (ledRojo, OUTPUT);
  pinMode (buzzer, OUTPUT);
  digitalWrite(ledVerde, HIGH);
  lcd.setCursor(0, 0);
  lcd.print("Introduzca la clave");
  lcd.setCursor(cursor, 1);
}
void loop()
{ char pulsacion = Teclado1.getKey();
  if (pulsacion != 0)
  {
    if (pulsacion != '#' && pulsacion != '*' && clave == 0)
    { lcd.print(pulsacion);
      cursor++;
      tone(buzzer, 350);
      delay(200);
      if (pulsacion == codigoSecreto[posicion])
          posicion++;
      if (posicion == 4) {
        digitalWrite(3, HIGH);
          lcd.setCursor(0, 0);
          lcd.print("Clave correcta");
          delay(200);
          tone(buzzer, 500);
          delay(100);
          noTone(buzzer);
          tone(buzzer, 600);
          delay(100);
          noTone(buzzer);
          lcd.setCursor(5, 1);
          clave = 1;
          digitalWrite(ledRojo, LOW);
          digitalWrite(ledVerde, HIGH);
        }
        if(cursor>8)
        { cursor=5;
          posicion=0;
          lcd.setCursor(5,1);
          lcd.print(" ");
          lcd.setCursor(5,1);
          if(clave=0)
          { tone(buzzer,70,500);
            delay(250);
            noTone(buzzer);
            
          }
        }
    }
        }
      if (pulsacion =='#' && luz==0) {
//      lcd.noBacklight();
        luz = 1;
        pulsacion=0;
      }
      if(pulsacion =='#' && luz==1){
//        lcd.noBacklight();
        luz=0;
      }
      if (pulsacion == '*') {
      posicion = 0;
      cursor = 5;
      clave = 0;
      posicion = 0;
      lcd.setCursor(0,0);
        lcd.print("introduzca clave");
        lcd.setCursor(5, 1);
        lcd.print(" ");
        lcd.setCursor(5, 1);
        digitalWrite(ledRojo, HIGH);
        digitalWrite(ledVerde, LOW);
      }


    }
