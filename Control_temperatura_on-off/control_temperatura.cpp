#include "Arduino.h"
#include "control_temperatura.h" 
#include "config.h"
#include <DallasTemperature.h>    
#include <OneWire.h>              


// Inicializa el objeto de sensor
OneWire oneWire(SENSOR_TEMP_PIN);              // Pasamos por parámetro el pin donde se realiza la comunicación 1-Wire.
DallasTemperature sensorDS18B20(&oneWire);     // Pasamos la posición de memoria donde está almacenado 1-Wire.

TemperaturaDatos tempDatos = {};  // Estructura de datos inicializada (sin desplegar)

DeviceAddress sensorControlado;
DeviceAddress sensorAmbiente;

void TemperaturaInicializar() {
  sensorDS18B20.begin();

  sensorDS18B20.getAddress(sensorControlado, 0);
  sensorDS18B20.getAddress(sensorAmbiente, 1);

  pinMode(RELAY_PIN, OUTPUT);  // Usamos RELAY_PIN de config.h
  digitalWrite(RELAY_PIN, LOW);  // Apaga el relé al inicio

}

void TemperaturaLeer(TemperaturaDatos &datos) {
  sensorDS18B20.requestTemperatures();
  datos.TemperaturaMedida = sensorDS18B20.getTempC(sensorControlado);
  datos.TemperaturaAmbiente = sensorDS18B20.getTempC(sensorAmbiente);
  datos.TiempoMedicion = millis();
  datos.HuboMedicion = true;
}

void TemperaturaControlar(float temperaturaDeseada) {
  sensorDS18B20.requestTemperatures();  // Solicita nuevamente la temperatura
 
  float tempActual = sensorDS18B20.getTempC(sensorControlado);  // Obtiene la temperatura actual
  float tempAmbiente = sensorDS18B20.getTempC(sensorAmbiente);

  // Compara la temperatura actual con la deseada y controla el relé
  if (tempActual < temperaturaDeseada - TEMP_HISTERESIS) {
    digitalWrite(RELAY_PIN, HIGH);  // Enciende el relé
    tempDatos.ActuadorEncendido = true;
  } else if (tempActual >= temperaturaDeseada + TEMP_HISTERESIS) {
    digitalWrite(RELAY_PIN, LOW);  // Apaga el relé
    tempDatos.ActuadorEncendido = false;
  }

  // Actualiza los datos de la estructura
  tempDatos.TemperaturaMedida = tempActual;
  tempDatos.TemperaturaAmbiente = tempAmbiente;
  tempDatos.TiempoMedicion = millis();
  tempDatos.HuboMedicion = true;
}

void TemperaturaParar() {
  digitalWrite(RELAY_PIN, LOW);  // Apaga el relé
  tempDatos.ActuadorEncendido = false;
  Serial.println("¡PARADA DE EMERGENCIA ACTIVADA!");
}
