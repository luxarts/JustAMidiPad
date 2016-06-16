/*  
 *          Just A Midi Pad 
 * www.github.com/luxarts/JustAMidiPad
 * Module: Output
 * Version: 1.0
 * 
 * Created by LuxARTS, OG-Jonii & pablonobile99
 *               2016
 */
//Libraries
#define STCP  2 //SR Pin 5: Store Clock Pulse
#define SHCP  3 //SR Pin 2: !Shift Clock Pulse
#define SI    4 //SR Pin 4: Serial Input

//Prototypes

void cargarMatriz(byte,byte,byte);
void Shift_init(void);

//Global variables
//Fil3-Fil0 / R3-R0 / G3-G0 / B3-B0
unsigned int crgb = 0b0000111111111111;//16 bits = Shift register
unsigned int crgb1 = 0b0000111111111111;
byte matriz[4][4]={
  {0,0,0,0},
  {0,0,0,0},
  {0,0,0,0},
  {0,0,0,0}
};

//Functions
void setup(){
  Serial.begin(115200);
  Shift_init(); //Inicializa el shift register 74F675APC
}

void loop(){
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

void cargarMatriz(byte filas,byte columnas,byte color){
  //Color: (0)=OFF=0 , (1;40)=R=1 , (41;80)=G=2 , (81;127)=B=3 
  if(color>0 && color<=40)color=1;  //Rojo
  if(color>40 && color<=80)color=2; //Verde
  if(color>80 && color<=127)color=3;//Azul  
  matriz[filas][columnas]=color;//Carga el espacio con el color
}

void imprimirMatriz(void){
  byte dato;
  
  for(byte fil=0;fil<4;fil++){
    switch(fil){
      case 0: crgb1=0b0001000000000000;//4096
      break;
      case 1: crgb1=0b0010000000000000;//8182
      break;
      case 2: crgb1=0b0100000000000000;//16384
      break;
      case 3: crgb1=0b1000000000000000;//32768
      break;
    }
    for(byte col=0;col<4;col++){
      dato=matriz[fil][col];
      switch(dato){
        case 1: crgb=crgb1|(0x0FFF&~(0b0000000100000000<<col)); //0000 1101 << 1 = 0001 1010 & 0000 1111 = 0000 1010
        break;
        case 2: crgb=crgb1|(0x0FFF&~(0b0000000000010000<<col));
        break;
        case 3: crgb=crgb1|(0x0FFF&~(0b0000000000000001<<col));
        break;
        case 0: crgb=crgb1|(0x0FFF);
      }
      cargarShift();  
      delay(1); 
    }
  }
}

void cargarShift(void){
  byte dato;
  digitalWrite(STCP,0);//Mantiene el registro    
  for(byte i=0;i<16;i++){
    dato=(crgb>>i)&1;
    digitalWrite(SI,dato);//Escribe el bit
    delayMicroseconds(1);
    digitalWrite(SHCP,0);//Manda el pulso de shift
    delayMicroseconds(1);
    digitalWrite(SHCP,1);
    delayMicroseconds(1);
  }
  digitalWrite(STCP,1);//Saca el registro al puerto
}

void serialEvent(){
  unsigned int cantidad;

  while(Serial.available()){ //Si recibe UN dato    

    byte estado=Serial.read(); //Nota ON 0x90+CH - Nota OFF 0x80+CH
    byte nota=Serial.read(); //Nota
    byte velocity=Serial.read(); //Color: (0)=0 , (1;40)=R , (41;80)=G , (81;127)=B 

    if(estado==0x90 || estado==0x80){//Si es Nota ON prende un led según la velocidad y solo deja pasar el canal 0 (0x90+CH0)
      if(estado==0x80)velocity=0; //Si es Nota OFF apaga el led
      switch(nota){
        case 0x00: cargarMatriz(0,0,velocity);//Fila 0
        break;
        case 0x01: cargarMatriz(0,1,velocity);
        break;
        case 0x02: cargarMatriz(0,2,velocity);
        break;
        case 0x03: cargarMatriz(0,3,velocity);
        break;
        case 0x10: cargarMatriz(1,0,velocity);//Fila 1
        break;
        case 0x011: cargarMatriz(1,1,velocity);
        break;  
        case 0x012: cargarMatriz(1,2,velocity);
        break;
        case 0x013: cargarMatriz(1,3,velocity);
        break;
        case 0x20: cargarMatriz(2,0,velocity);//Fila 2
        break;
        case 0x21: cargarMatriz(2,1,velocity);
        break;
        case 0x22: cargarMatriz(2,2,velocity);
        break;
        case 0x23: cargarMatriz(2,3,velocity);
        break;
        case 0x30: cargarMatriz(3,0,velocity);//Fila 3
        break;
        case 0x31: cargarMatriz(3,1,velocity);
        break;
        case 0x32: cargarMatriz(3,2,velocity);
        break;
        case 0x33: cargarMatriz(3,3,velocity);
        break;
      }
    }    
  }
}

