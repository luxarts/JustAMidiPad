/*  
 *          Just A Midi Pad 
 * www.github.com/luxarts/JustAMidiPad
 * Module: Output
 * Version: 0.0
 * 
 * Created by LuxARTS, OG-Jonii & pablonobile99
 *               2016
 */
//Libraries
#define STCP  2 //SR Pin 5: Store Clock Pulse
#define SHCP  3 //SR Pin 2: !Shift Clock Pulse
#define SI    4 //SR Pin 4: Serial Input

//Prototypes

void cargarMatriz(byte,byte,char);
void Shift_init(void);

//Global variables
byte com_red=0b11110000;
byte matriz[4][4]={
  0,0,0,0,
  0,0,0,0,
  0,0,0,0,
  0,0,0,0
}

//Functions
void setup(){
  Serial.begin(9600);
  Shift_init(); //Inicializa el shift register 74F675APC
  
}

void loop(){
  byte recibido=0;
  if(Serial.available()==1){ //Si recibe UN dato
    recibido=Serial.read();

    switch(recibido)
    {
      case '0': cargarMatriz(0,0,'R');
      break;
      case '1': cargarMatriz(1,0,'R');
      break;
      case '2': cargarMatriz(2,0,'R');
      break;
      case '3': cargarMatriz(3,0,'R');
      break;
      case '4': cargarMatriz(0,1,'R');
      break;
      case '5': cargarMatriz(1,1,'R');
      break;  
      case '6': cargarMatriz(2,1,'R');
      break;
      case '7': cargarMatriz(3,1,'R');
      break;
      case '8': cargarMatriz(0,2,'R');
      break;
      case '9': cargarMatriz(1,2,'R');
      break;
      case 10: cargarMatriz(2,2,'R');
      break;
      case 11: cargarMatriz(0,2,'R');
      break;
      case 12: cargarMatriz(1,3,'R');
      break;
      case 13: cargarMatriz(2,3,'R');
      break;
      case 14: cargarMatriz(2,3,'R');
      break;
      case 15: cargarMatriz(3,3,'R');
      break;
    }
  }
  else
  {
    for(byte i=0;i<Serial.available();i++)Serial.read();//Limpia el buffer de entrada
  }
  imprimirMatriz();
}

void Shift_init(void){
  pinMode(STCP,OUTPUT);
  pinMode(SHCP,OUTPUT);
  pinMode(SI,OUTPUT);
  digitalWrite(SI,0);
  digitalWrite(STCP,0);  
  digitalWrite(SHCP,1);

  for(int i=0;i<16;i++)//Limpia los registros
  {
    //Mantiene el registro
    digitalWrite(SI,0);//Envia el dato
    delayMicroseconds(1);
    digitalWrite(SHCP,0);//Corre el registro (bajada)
    delayMicroseconds(1);
    digitalWrite(SHCP,1);//Corre el registro (subida)
    delayMicroseconds(1);   
  }
  digitalWrite(STCP,1);//Carga el puerto
}

void cargarMatriz(byte filas,byte columnas,char color){
  
  
}

