#define MCU_BTN1 1
#define MCU_BTN2 2
#define MCU_POT1 3
#define MCU_POT2 4
#define MCU_LEDS 5
#define MCU_GRAL 6

#include <Wire.h> //Librería I2C

void setup() {
  Wire.begin(MCU_BTN1); //Inicializa I2C con nombre MCU_BTN1
  pinMode(12,INPUT_PULLUP); //Boton en el pin 12 con pullup interno
}
int btn_b=1;

void loop() {
  if(digitalRead(12)==0 && btn_b==1){ //Si se presionó y estaba suelto
    Wire.beginTransmission(MCU_GRAL); //Inicia la transmisión al esclavo MCU_GRAL
    Wire.write(MCU_BTN1); //Envía el nombre en el I2C       
    Wire.write(1); //Boton presionado
    Wire.endTransmission(); //Termina la transmisión
    btn_b=0; //El botón se presionó
  }
	//Idem a lo anterior pero cuando se suelta el botón
  if(digitalRead(12)==1 && btn_b==0){
    Wire.beginTransmission(MCU_GRAL);
    Wire.write(MCU_BTN2);
    Wire.write(0);
    Wire.endTransmission();
    btn_b=1;
  }
}
