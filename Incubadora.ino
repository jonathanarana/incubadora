#include <DHT.h>
#include <DHT_U.h>

#include <LiquidCrystal.h>

LiquidCrystal lcd(8,9,10,11,12,13); // (0x3f,16,2) || (0x27,16,2)  ||(0x20,16,2) 

DHT dht(2, DHT11);

float Objetivo = 38;  // Temperatura Objetivo
float Margen = 1;     // Variación Máxima
float at = -0.5;      // Ajuste Temperatura
float ah = 0;         // Ajuste Humedad
boolean Alerta=false; // Variable para activar el Buzer

int Buzer = 3;        // Pin Buzer (Alarma Auditiva)
int Calentador = 4;   // Pin Lampara Incandecente o Resistencia
  
void setup() {
  // lcd
  lcd.begin(16,2);
  // sensor
  dht.begin();
  // Relay
  pinMode(Buzer, OUTPUT);
  pinMode(Calentador, OUTPUT);
  digitalWrite(Calentador, HIGH);   // Apagamos el Calentador por Defecto (Si, Funciona a la Inversa)
}

void loop() {
  // Reset
  lcd.clear();
  analogWrite(Buzer, 0);

  
  lcd.setCursor(2,0);         // X,Y Columna,Fila Espacio,Renglón
  lcd.print("PrimerMaster"); 
  lcd.setCursor (2,1);
  lcd.print("Consultoria");
  delay(2000);

  
  // Lectura y Ajuste de Valores del Sensor
  float Humedad = dht.readHumidity() + ah;
  float Temperatura = dht.readTemperature() + at;

  if (isnan(Humedad) || isnan(Temperatura) ) {
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("Error de"); 
    lcd.setCursor (4,1);
    lcd.print("Lectura");
    analogWrite(Buzer, 150);
    delay(5000);
    return;
  }


  // Mostramos Temperatura y Humedad
  String line;
  line = "Temp: " + String(Temperatura) + " C";
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(line);
  line = "Hum:  " + String(Humedad) + " %";
  lcd.setCursor(0,1);
  lcd.print(line);


  // Validamos Temperatura
  if(Temperatura <= (Objetivo - Margen) ) {
    digitalWrite(Calentador, LOW); // Encendemos el Calentador (Si, Funciona a la Inversa)
    if(Temperatura < (Objetivo - 2*Margen)) {
      Alerta = true;
    }
  }
  else if (Temperatura > Objetivo) {
    digitalWrite(Calentador, HIGH); // Apagamos el Calentador (Si, Funciona a la Inversa)
    if(Temperatura > (Objetivo + Margen) ) {
      Alerta = true;
    }
  }

  // Validamos la Temperatura
  if(Humedad < 50 or Humedad > 70){
    Alerta = true;  
  }

  // Activamos el Buzer
  if(Alerta){
    analogWrite(Buzer, 150);
  }
  

  delay(5000);
  
}
