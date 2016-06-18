#define MCU_BTN1 1
#define MCU_BTN2 2
#define MCU_POT1 3
#define MCU_POT2 4
#define MCU_LEDS 5
#define MCU_GRAL 6

#include <Wire.h> //Librería I2C

void setup() {
  Wire.begin(MCU_GRAL);	//Inicializa I2C con nombre MCU_GRAL
  Wire.onReceive(receiveEvent); //Interrupción al recibir un dato  
  Serial.begin(9600); //Inicializa el puerto serie
}

void loop() {
  delay(10); //Delay de 10ms para estabilizar
}

void receiveEvent(int howMany) { //Función que se ejecuta en la interrupción
  Serial.print("MCU: "); 
  Serial.print(Wire.read()); //Nombre en el I2C del que envió el dato
  Serial.print("\tBoton: ");
  Serial.print(Wire.read()); //Estado del botón recibido
  Serial.println();
}
