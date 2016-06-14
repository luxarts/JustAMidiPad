/*  
 *          Just A Midi Pad 
 * www.github.com/luxarts/JustAMidiPad
 * Module: Input
 * Version: 1.0 
 * 
 * Created by LuxARTS, OG-Jonii & pablonobile99
 *               2016
 */
//Definitions

#define n0   0;//nota 0x0 //Numero que saca por puerto serie
#define n1   1;//nota 0x1
#define n2   2;//nota 0x2
#define n3   3;//nota 0x3
#define n4   4;//nota 1x0
#define n5   5;//nota 1x1
#define n6   6;//nota 1x2
#define n7   7;//nota 1x3
#define n8   8;//nota 2x0
#define n9   9;//nota 2x1
#define n10 10;//nota 2x2
#define n11 11;//nota 2x3
#define n12 12;//nota 3x0
#define n13 13;//nota 3x1
#define n14 14;//nota 3x2
#define n15 15;//nota 3x3

//Libraries

//Prototypes

byte BitRead(unsigned int, byte);
void BitWrite(byte, byte);
void pinMode_init(void);
void notaOn(byte);
void notaOff(byte);

//Global variables
unsigned int estado_anterior = 0b1111111111111111;//matriz 4x4 c/ pullup

void setup(){
  pinMode_init(); //PIN 13 NO TIENE PULLUP INTERNO, OJO
  Serial.begin(9600);
}

void loop(){  
  //Guardado estado botones
  byte estado;
  
  for(byte i=0;i<12;i++){ //16 botones de matriz
    if(i==12)estado=digitalRead(A0);
    if(i==13)estado=digitalRead(A1);
    if(i==14)estado=digitalRead(A2);
    if(i==15){
      estado=digitalRead(A3);
    }
    else{
      estado = digitalRead(i+2); //Guarda el estado del botón
      delay(1);
      if(estado!=digitalRead(i+2))estado=digitalRead(i+2); //Anti-rebote
    }
    
    if(estado==0 && BitRead(i)==1){
      BitWrite(i,0);                        //  EJ: i=0 -> estado_anterior=1111 1111 1111 1111 &~(1<<15)
                                            //                             1111 1111 1111 1111 & 0111 1111 1111 1111
      notaOn(i);//Se presionò una tecla     //             estado_anterior=0111 1111 1111 1111   
    }                                       //  EJ: i=9 -> estado_anterior=0111 1111 1111 1111 &~(1<<6)
    if(estado==1 && BitRead(i)==0){         //                             0111 1111 1111 1111 & 1111 1111 1011 1111
      BitWrite(i,1);                        //             estado_anterior=0111 1111 1011 1111
      notaOff(i);//Se soltó una tecla
    } 
  }
}

void notaOn (byte i){
  byte boton;
  
  switch(i){
    case 0:  boton=n0;
    break;
    case 1:  boton=n1;
    break;
    case 2:  boton=n2;
    break;
    case 3:  boton=n3;
    break;
    case 4:  boton=n4;
    break;
    case 5:  boton=n5;
    break; 
    case 6:  boton=n6;
    break;
    case 7:  boton=n7;
    break;
    case 8:  boton=n8;
    break;
    case 9:  boton=n9;
    break;
    case 10: boton=n10;
    break;
    case 11: boton=n11;
    break;
    case 12: boton=n12;
    break;
    case 13: boton=n13;
    break;
    case 14: boton=n14;
    break;
    case 15: boton=n15;
    break;
  }
  //Serial.write(0x90);
  //Serial.write(boton);
  //Serial.write(127);
  Serial.print("Nota ON: ");
  Serial.print(boton);
  Serial.println();
}

void notaOff (byte i){
  byte boton;
  
  switch(i){
    case 0:  boton=n0;
    break;
    case 1:  boton=n1;
    break;
    case 2:  boton=n2;
    break;
    case 3:  boton=n3;
    break;
    case 4:  boton=n4;
    break;
    case 5:  boton=n5;
    break; 
    case 6:  boton=n6;
    break;
    case 7:  boton=n7;
    break;
    case 8:  boton=n8;
    break;
    case 9:  boton=n9;
    break;
    case 10: boton=n10;
    break;
    case 11: boton=n11;
    break;
    case 12: boton=n12;
    break;
    case 13: boton=n13;
    break;
    case 14: boton=n14;
    break;
    case 15: boton=n15;
    break;
  }
  //Serial.write(0x80);
  //Serial.write(boton);
  //Serial.write(0);
 Serial.print("Nota OFF: ");
  Serial.print(boton);
  Serial.println();
}

byte BitRead(byte pos){//Devuelve un bit de un int
  unsigned int n;
  n=estado_anterior<<pos;
  return((n&0x8000)>>15); //0x8000 = 0b1000 0000 0000 0000, corre 15 para devolver el bit 0  
}

void BitWrite(byte pos, byte estado){ //Escribe un bit en una posicion                           
  if(estado==1)estado_anterior = estado_anterior | (1<<15-pos); //0000 0000 -> 0000 0010: 0000 0000 |  1<<2                          //SET
  if(estado==0)estado_anterior = estado_anterior & ~(1<<15-pos);//1111 1111 -> 1111 1101: 1111 1111 & ~1<<2 -> 1111 1111 & 1111 1101 //CLEAR
}

void pinMode_init(void){
  for(byte i=2;i<13;i++){
    pinMode(i,INPUT_PULLUP);
  }
  pinMode(13,INPUT);//Tiene un led, NO TIENE PULLUP INTERNO
  pinMode(A0,INPUT_PULLUP);
  pinMode(A1,INPUT_PULLUP);
  pinMode(A2,INPUT_PULLUP);
  pinMode(A3,INPUT_PULLUP);
}
