// control_temperatura.h

#ifndef CONTROL_TEMPERATURA_H
#define CONTROL_TEMPERATURA_H


// Definimos la estructura para almacenar los datos de temperatura.
struct TemperaturaDatos {
  float         TemperaturaMedida;
  float         TemperaturaAmbiente;
  unsigned long TiempoMedicion;
  bool          HuboMedicion;
  bool          ActuadorEncendido;
};

//extern TemperaturaDatos tempDatos;

// Declaración de funciones
void TemperaturaInicializar();
void TemperaturaMedir();
void TemperaturaControlar(float temperaturaDeseada);
void TemperaturaLeer(TemperaturaDatos * datos);
void TemperaturaParar();

#endif