#include "control_temperatura.h" 
#include "config.h"
#include <DallasTemperature.h>

void ImprimirDatos(TemperaturaDatos &tempDatos);

void setup() {
  Serial.begin(9600);
  pinMode(STOPBUTTON_PIN, INPUT);
  TemperaturaInicializar();
}

void loop() {
  unsigned long paradaDeEmergencia = digitalRead(STOPBUTTON_PIN);

  if (paradaDeEmergencia == HIGH) {
    TemperaturaParar(); 
  } else {
    TemperaturaControlar(TEMP_OBJETIVO);  
    TemperaturaLeer(tempDatos); 
    ImprimirDatos(tempDatos);
  }


}

void ImprimirDatos(TemperaturaDatos &tempDatos) {
  Serial.print("Temperatura actual: ");
  Serial.print(tempDatos.TemperaturaMedida);
  Serial.print(" °C | Relé: ");
  Serial.println(tempDatos.ActuadorEncendido ? "ENCENDIDO" : "APAGADO");
}
