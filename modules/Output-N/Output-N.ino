/*  
 *          Just A Midi Pad 
 * www.github.com/luxarts/JustAMidiPad
 * Module: Output
 * Version: 1.0
 * 
 * Created by LuxARTS, OG-Jonii & pablonobile99
 *               2016
 */
 /* Conections
 * Q0-Q3:   Fil3-Fil0
 * Q4-Q7:   R3-R0
 * Q8-Q11:  G3-G0
 * Q12-Q15: B3-B0
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
  Serial.begin(9600);
  Shift_init(); //Inicializa el shift register 74F675APC
  pinMode(13,OUTPUT);

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

void cargarMatriz(byte filas,byte columnas,char color){
  
  switch(color){
    case 'R': color=1;  //Rojo
    break;
    case 'G': color=2;  //Verde
    break;
    case 'B': color=3;  //Azul
    break;
    case 0: color=0;  //Apagado
    break;   
  }
  matriz[filas][columnas]=color;//Carga el espacio con el color, si es 0 apaga el led
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

   byte estado=Serial.read(); //Nota ON 0x80+CH - Nota OFF 0x90+CH
   char nota=Serial.read(); //Nota
   byte velocity=Serial.read(); //Color: (0)=0 , (1;40)=R , (41;80)=G , (81;127)=B 
    
    switch(nota){
      //Prende
      case '1': cargarMatriz(0,0,'R');
      break;
      case '2': cargarMatriz(0,1,'R');
      break;
      case '3': cargarMatriz(0,2,'R');
      break;
      case '4': cargarMatriz(0,3,'R');
      break;
      case 'q': cargarMatriz(1,0,'G');
      break;
      case 'w': cargarMatriz(1,1,'G');
      break;  
      case 'e': cargarMatriz(1,2,'G');
      break;
      case 'r': cargarMatriz(1,3,'G');
      break;
      case 'a': cargarMatriz(2,0,'B');
      break;
      case 's': cargarMatriz(2,1,'B');
      break;
      case 'd': cargarMatriz(2,2,'B');
      break;
      case 'f': cargarMatriz(2,3,'B');
      break;
      case 'z': cargarMatriz(3,0,'R');
      break;
      case 'x': cargarMatriz(3,1,'G');
      break;
      case 'c': cargarMatriz(3,2,'B');
      break;
      case 'v': cargarMatriz(3,3,'G');
      break;
      //Apaga
      case '5': cargarMatriz(0,0,0);
      break;
      case '6': cargarMatriz(0,1,0);
      break;
      case '7': cargarMatriz(0,2,0);
      break;
      case '8': cargarMatriz(0,3,0);
      break;
      case 't': cargarMatriz(1,0,0);
      break;
      case 'y': cargarMatriz(1,1,0);
      break;  
      case 'u': cargarMatriz(1,2,0);
      break;
      case 'i': cargarMatriz(1,3,0);
      break;
      case 'g': cargarMatriz(2,0,0);
      break;
      case 'h': cargarMatriz(2,1,0);
      break;
      case 'j': cargarMatriz(2,2,0);
      break;
      case 'k': cargarMatriz(2,3,0);
      break;
      case 'b': cargarMatriz(3,0,0);
      break;
      case 'n': cargarMatriz(3,1,0);
      break;
      case 'm': cargarMatriz(3,2,0);
      break;
    }
  }
}

