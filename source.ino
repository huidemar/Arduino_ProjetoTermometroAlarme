/*
Projeto - Temômetro LCD com sensor LM35, LED e Alarme 
*/
#include <LiquidCrystal.h>

// Variaveis
int tempPin = 0;       // Declaração do pino de entrada analógica 0 (A0) no Arduino
float mAmostra[8];     // matriz para armazenar oito amostras para o cálculo da temperatura média 
float temperatura = 0;
const int SPEAKER =  7;
const int LED_RED = 6;
const int LED_GREEN = 5;
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
const float TEMP_MAX = 26.00; 

void cabecalho()
{
  lcd.clear();
  lcd.begin(16, 2);        // Inicia e configura o número de linhas e colunas do LCD
  lcd.setCursor(1, 0);     // Seta posição do cursor (coluna, linha) do LCD 
  lcd.print("Projeto LHR");         
  lcd.setCursor(1, 1);     // seta posição do cursor LCD
  lcd.print(" Temp: ");    // imprime no LCD  
  lcd.setCursor(9, 1);     // seta posição do cursor LCD
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);            // inicia comunicação serial
  cabecalho();
  pinMode(SPEAKER, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(SPEAKER, LOW); 
  delay(1000);                   
}

void loop() {
    cabecalho();   
    temperatura = (5 * analogRead(tempPin) * 99.6) / 1023.0;
    lcd.print(temperatura); // imprime a temperatura no LCD
    lcd.print(" C");        // imprime caractere C  
    delay(500); 
    if(temperatura < TEMP_MAX)
    {        
        cabecalho();
        digitalWrite(LED_RED, HIGH);  
        digitalWrite(LED_GREEN, LOW); 
        noTone(SPEAKER);      
        lcd.print(" OK "); // imprime no LCD
    }
    else
    {
        cabecalho();
        digitalWrite(LED_RED, LOW); 
        digitalWrite(LED_GREEN, HIGH); 
        tone(SPEAKER, 1500, 100);  
        lcd.print(" NOK ");   // imprime no LCD
    }     
    delay(500);    
}
