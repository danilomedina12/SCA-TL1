#include "control_temperatura.h" 
#include "config.h"
//#include <DallasTemperature.h>

TemperaturaDatos DatosLeidos = {};  // Estructura de datos que leeremos

void ImprimirDatos();

void setup() {
  Serial.begin(9600);
  pinMode(STOPBUTTON_PIN, INPUT);
  TemperaturaInicializar();
  // imprimir encabezado de datos
}

void loop() {
  unsigned long paradaDeEmergencia = digitalRead(STOPBUTTON_PIN);

  if (paradaDeEmergencia == HIGH) {
    // llamar a otra función definida en este módulo
    TemperaturaParar(); 
  } else {
    // esto debe hacerse cada un tiempo determinado
    TemperaturaMedir();
    TemperaturaControlar(TEMP_OBJETIVO); // mide, controla, y gurda datos
    TemperaturaLeer(&DatosLeidos);          // lee datos guardados
    ImprimirDatos();
  }
}

void ImprimirDatos() {
  // sólo imprimir dalos separados por tabulación...
  // Queremos mostras: tiempo de muetreo / temp ambiente / temp medida / accion de control
  Serial.print("Temperatura actual: ");
  Serial.print(DatosLeidos.TemperaturaMedida);
  Serial.print(" °C | Relé: ");
  Serial.println(DatosLeidos.ActuadorEncendido ? "ENCENDIDO" : "APAGADO");
}