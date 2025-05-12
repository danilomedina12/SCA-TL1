#include "control_temperatura.h" 
#include "config.h"

TemperaturaDatos DatosLeidos = {};  // Estructura de datos que leeremos
unsigned long tiempoActual = 0;
unsigned long tiempoUltimaMedicion = 0;

void MostrarEncabezado();
void ImprimirDatos();
void ApagarTodo();

void setup() {
  Serial.begin(9600);
  pinMode(STOPBUTTON_PIN, INPUT);
  TemperaturaInicializar();
  MostrarEncabezado();  // imprimir encabezado de datos
}

void loop() {
  unsigned long paradaDeEmergencia = digitalRead(STOPBUTTON_PIN);
  tiempoActual = millis(); // actualiza el tiempo actual

  if (paradaDeEmergencia == HIGH) {
    TemperaturaParar(); 
    ApagarTodo();// llamar a otra función definida en este módulo

  } else {
    // esto debe hacerse cada un tiempo determinado
    if(tiempoActual - tiempoUltimaMedicion >= TIEMPO_MUESTREO){
      tiempoUltimaMedicion = tiempoActual;

      TemperaturaMedir();
      TemperaturaControlar(TEMP_OBJETIVO); // mide, controla, y gurda datos
      TemperaturaLeer(&DatosLeidos);          // lee datos guardados
      ImprimirDatos();
    }
  }
}

void MostrarEncabezado() {
  Serial.println("============================================");
  Serial.println("CONTROL DE TEMPERATURA DE LA PAVA ELECTRICA");
  Serial.println("============================================");
  Serial.println("Datos: ");
  Serial.print("   Temperatura referencia:  ");
  Serial.print(TEMP_OBJETIVO);  // Usa macro de config.h
  Serial.println(" ºC");
  Serial.print("   Intervalo de histéresis: ±");
  Serial.print(TEMP_HISTERESIS);
  Serial.println(" ºC");
  Serial.println("--------------------------------------------");
  Serial.println(" ");
  Serial.println("Tiempo\tTempAmb\tTempMed\tEstado");
  Serial.println("[s]\t[°C]\t[°C]\t[Si/No]");
}

void ImprimirDatos() {
  // sólo imprimir dalos separados por tabulación...
  // Queremos mostrar: tiempo de muestreo / temp ambiente / temp medida / accion de control

  unsigned long tiempoEnSegundos = DatosLeidos.TiempoMedicion / 1000;

  Serial.print(tiempoEnSegundos);
  Serial.print("\t");
  Serial.print(DatosLeidos.TemperaturaAmbiente, 2);
  Serial.print("\t");
  Serial.print(DatosLeidos.TemperaturaMedida, 2);
  Serial.print("\t");
  Serial.println(DatosLeidos.ActuadorEncendido ? "SI" : "NO");
}

void ApagarTodo() {
  Serial.println("SISTEMA APAGADO. REINICIAR PARA CONTINUAR.");
  TemperaturaParar();
  while (true) {
    // loop infinito controlado para que el sistema quede apagado
  }
}

