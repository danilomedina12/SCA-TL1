// control_temperatura.cpp
#include "Arduino.h"
#include "control_temperatura.h" 
#include "config.h"
#include <DallasTemperature.h>    
#include <OneWire.h>              


// Inicializa el objeto de sensor
OneWire oneWire(SENSOR_TEMP_PIN);              // Pasamos por parámetro el pin donde se realiza la comunicación 1-Wire.
DallasTemperature sensorDS18B20(&oneWire);     // Pasamos la posición de memoria donde está almacenado 1-Wire.

TemperaturaDatos tempDatos = {};  // Estructura de datos inicializada (sin desplegar)

/****************************************************************
* Inicializa el objeto CONTROL DE TEMPERATURA
*****************************************************************/
void TemperaturaInicializar() {
  sensorDS18B20.begin();
  pinMode(RELAY_PIN, OUTPUT);  // Usamos RELAY_PIN de config.h
  digitalWrite(RELAY_PIN, LOW);  // Apaga el relé al inicio
}
/*****************************************************************/

void TemperaturaMedir() {
  sensorDS18B20.requestTemperatures();
  tempDatos.TemperaturaMedida = sensorDS18B20.getTempCByIndex(0);
  tempDatos.TemperaturaAmbiente = sensorDS18B20.getTempCByIndex(1);
  tempDatos.TiempoMedicion = millis();
  tempDatos.HuboMedicion = true;
}

void TemperaturaControlar(float temperaturaDeseada) {

  // Compara la temperatura medida actual con la deseada y controla el relé
  if (tempDatos.TemperaturaMedida < temperaturaDeseada - TEMP_HISTERESIS) {
    digitalWrite(RELAY_PIN, HIGH);  // Enciende el relé
    tempDatos.ActuadorEncendido = true;
  } else if (tempDatos.TemperaturaMedida > temperaturaDeseada + TEMP_HISTERESIS) {
    digitalWrite(RELAY_PIN, LOW);  // Apaga el relé
    tempDatos.ActuadorEncendido = false;
  }

}

void TemperaturaLeer(TemperaturaDatos * DATOS)
{
  DATOS->TemperaturaMedida   = tempDatos.TemperaturaMedida; 
  DATOS->TemperaturaAmbiente = tempDatos.TemperaturaAmbiente;
  DATOS->TiempoMedicion      = tempDatos.TiempoMedicion;
  DATOS->HuboMedicion        = tempDatos.HuboMedicion;
}

void TemperaturaParar() {
  digitalWrite(RELAY_PIN, LOW);  // Apaga el relé
  tempDatos.ActuadorEncendido = false;
  Serial.println("¡PARADA DE EMERGENCIA ACTIVADA!");
}