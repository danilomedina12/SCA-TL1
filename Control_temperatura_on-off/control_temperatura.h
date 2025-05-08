// Acá van las declaraciones necesarias para que el módulo principal funcione

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

extern TemperaturaDatos tempDatos;

// Declaración de funciones
void TemperaturaInicializar();
void TemperaturaControlar(float temperaturaDeseada);
void TemperaturaLeer(TemperaturaDatos &datos);
void TemperaturaParar();

#endif