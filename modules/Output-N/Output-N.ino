/*  
 *          Just A Midi Pad 
 * www.github.com/luxarts/JustAMidiPad
 * Module: Output
 * Version: 0.7
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
//Fil3-Fil0 / R3-R0 / G3-G0 / B3-B0
int crgb = 0b1111000000000000;//16 bits = Shift register
int matriz[4][4]={
  {0,0,0,0},
  {0,0,0,0},
  {0,0,0,0},
  {0,0,0,0}
};

//Functions
void setup(){
  Serial.begin(9600);
  Shift_init(); //Inicializa el shift register 74F675APC
  
}

void loop(){
  byte recibido=0;
  if(Serial.available()==1){ //Si recibe UN dato
    recibido=Serial.read();

    switch(recibido){
      case '1': cargarMatriz(0,0,'R');
      break;
      case '2': cargarMatriz(1,0,'R');
      break;
      case '3': cargarMatriz(2,0,'R');
      break;
      case '4': cargarMatriz(3,0,'R');
      break;
      case 'q': cargarMatriz(0,1,'R');
      break;
      case 'w': cargarMatriz(1,1,'R');
      break;  
      case 'e': cargarMatriz(2,1,'R');
      break;
      case 'r': cargarMatriz(3,1,'R');
      break;
      case 'a': cargarMatriz(0,2,'R');
      break;
      case 's': cargarMatriz(1,2,'R');
      break;
      case 'd': cargarMatriz(2,2,'R');
      break;
      case 'f': cargarMatriz(3,2,'R');
      break;
      case 'z': cargarMatriz(0,3,'R');
      break;
      case 'x': cargarMatriz(1,3,'R');
      break;
      case 'c': cargarMatriz(2,3,'R');
      break;
      case 'v': cargarMatriz(3,3,'R');
      break;
    }
  }
  else{
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

void cargarMatriz(byte columnas,byte filas,char color){
  
  switch(color){
    case 'R': color=1;
    break;
    case 'G': color=2;
    break;
    case 'B': color=3;
    break;
    case 0: color=0;
    break;   
  }
  matriz[filas][columnas]=color;//Carga el espacio con el color, si es 0 apaga el led
}

void imprimirMatriz(void){
  byte dato;
  
  for(byte fil=0;fil<4;fil++){
    switch(fil){
      case 0: crgb=0b1110000000000000;
      break;
      case 1: crgb=0b1101000000000000;
      break;
      case 2: crgb=0b1011000000000000;
      break;
      case 3: crgb=0b0110000000000000;
      break;
    }
    for(byte col=0;col<4;col++){
      dato=matriz[fil][col];
      switch(dato){
        case 1: crgb=crgb|(0b0000100000000000>>col);
        break;
        case 2: crgb=crgb|(0b0000000010000000>>col);
        break;
        case 3: crgb=crgb|(0b0000000000001000>>col);
        break;
      }
    }
    
  }
}

void cargarShift(void){
  byte dato;
  
  for(byte i=0;i<16;i++){
    dato=(crgb>>i)&1;
    
    digitalWrite(STCP,0);//Mantiene el registro    
      
    digitalWrite(SI,dato);//Escribe el bit
    delayMicroseconds(1);
    digitalWrite(SHCP,0);//Manda el pulso de shift
    delayMicroseconds(1);
    digitalWrite(SHCP,1);
    delayMicroseconds(1);
    
    digitalWrite(STCP,1);//Saca el registro al puerto
  }
}

