#include "Arduino.h"
#include "control_temperatura.h" 
#include "config.h"
#include <DallasTemperature.h>    
#include <OneWire.h>              


// Inicializa el objeto de sensor
OneWire oneWire(SENSOR_TEMP_PIN);              // Pasamos por parámetro el pin donde se realiza la comunicación 1-Wire.
DallasTemperature sensorDS18B20(&oneWire);     // Pasamos la posición de memoria donde está almacenado 1-Wire.

TemperaturaDatos tempDatos = {};  // Estructura de datos inicializada (sin desplegar)


void TemperaturaInicializar() {
  sensorDS18B20.begin();

  pinMode(RELAY_PIN, OUTPUT);  // Usamos RELAY_PIN de config.h
  digitalWrite(RELAY_PIN, LOW);  // Apaga el relé al inicio

}

void TemperaturaLeer(TemperaturaDatos &datos) {
  sensorDS18B20.requestTemperatures();
  datos.TemperaturaMedida = sensorDS18B20.getTempCByIndex(0);
  datos.TemperaturaAmbiente = sensorDS18B20.getTempCByIndex(1);
  datos.TiempoMedicion = millis();
  datos.HuboMedicion = true;
}

void TemperaturaControlar(float temperaturaDeseada) {
/*  sensorDS18B20.requestTemperatures();  // Solicita nuevamente la temperatura
 
  float tempActual = sensorDS18B20.getTempCByIndex(0);  // Obtiene la temperatura actual
  float tempAmbiente = sensorDS18B20.getTempCByIndex(1);*/

  // Compara la temperatura medida actual con la deseada y controla el relé
  if (tempDatos.TemperaturaMedida < temperaturaDeseada - TEMP_HISTERESIS) {
    digitalWrite(RELAY_PIN, HIGH);  // Enciende el relé
    tempDatos.ActuadorEncendido = true;
  } else if (tempDatos.TemperaturaMedida >= temperaturaDeseada + TEMP_HISTERESIS) {
    digitalWrite(RELAY_PIN, LOW);  // Apaga el relé
    tempDatos.ActuadorEncendido = false;
  }

  // Actualiza los datos de la estructura
/*  tempDatos.TemperaturaMedida = tempActual;
  tempDatos.TemperaturaAmbiente = tempAmbiente;
  tempDatos.TiempoMedicion = millis();
  tempDatos.HuboMedicion = true;*/
}

void TemperaturaParar() {
  digitalWrite(RELAY_PIN, LOW);  // Apaga el relé
  tempDatos.ActuadorEncendido = false;
  Serial.println("¡PARADA DE EMERGENCIA ACTIVADA!");
}
