/*  
 *          Just A Midi Pad 
 * www.github.com/luxarts/JustAMidiPad
 * Module: Input
 * Version: 0.1 
 * 
 * Created by LuxARTS, OG-Jonii & pablonobile99
 *               2016
 */
//dofinishions

#define n0 0;//nota 0x0 //Numero que saca por puerto serie
#define n1 1;//nota 0x1
#define n2 2;//nota 0x2
#define n3 3;//nota 0x3
#define n4 4;//nota 1x0
#define n5 5;//nota 1x1
#define n6 6;//nota 1x2
#define n7 7;//nota 1x3
#define n8 8;//nota 2x0
#define n9 9;//nota 2x1
#define n10 10;//nota 2x2
#define n11 11;//nota 2x3
#define n12 12;//nota 3x0
#define n13 13;//nota 3x1
#define n14 14;//nota 3x2
#define n15 15;//nota 3x3

//Libraries

//Prototypes

int BitRead(int, int);
void notaNF(byte , byte);
void pinMode_init(void);

//Global variables

int boton[2] = {0b11111111,0b11111111};//line 1 y 2 matriz 4x4 //inicialicacion en alta  //line 3 y 4 matriz 4x4
 // {0b11111111},//direccion(4) y mute(4)
 // {0b00000001}//camb.pag. potes

int j=64,i;

void setup(){
  pinMode_init();
  Serial.begin(9600);
}

void loop(){
  
  //Guardado estado botones
  for(i=15;i>=0;i--){ //17-15=2, 17-8=9,
      if(i>=8){
        j=digitalRead(17-i);//*128;
        Serial.write(i);
        Serial.write(digitalRead(17-i));
        Serial.write(". ");
        delay(600);
        if(j==128)boton[1]=j|boton[1];
        //boton[1]=boton[1]|(boton[1]>>i-8);
        boton[1]=boton[1]|(boton[1]>>1);
      }
      if(i<8){
        j=digitalRead(17-i)*128;
        if(j==128)boton[0]=j|boton[0];
        //boton[0]=boton[0]|(boton[0]>>i);
        boton[0]=boton[0]|(boton[0]>>1);
      }
      //Serial.println();
  }
  
  //Prende nota/boton guardad@

  for(byte i=0;i<16;i++)//Comprueba pulsaciones
  {
    delay(500);
    if(i<8)j = BitRead(boton[0],i);//guarda el estado del bit "i" pin "i" en j del primer byte de "boton[]"
    if(i>=8)j = BitRead(boton[1],i-8);//guarda el estado del bit "i" pin "i" en j del segundo byte de "boton[]"
    
    if(j==0)//Se apretó
    {
      switch(i)//envia (numero de boton) mas (1=prendido 0=apagado)
      {
        case 0: notaNF(0,1);
        break;
        case 1: notaNF(1,1);
        break;
        case 2: notaNF(2,1);
        break;
        case 3: notaNF(3,1);
        break;
        case 4: notaNF(4,1);
        break;
        case 5: notaNF(5,1);
        break;
        case 6: notaNF(6,1);
        break;
        case 7: notaNF(7,1);
        break;
        case 8: notaNF(8,1);
        break;
        case 9: notaNF(9,1);
        break;
        case 10: notaNF(10,1);
        break;
        case 11: notaNF(11,1);
        break;
        case 12: notaNF(12,1);
        break;
        case 13: notaNF(13,1);
        break;
        case 14: notaNF(14,1);
        break;
        case 15: notaNF(15,1);
        break;       
      }
    }

    if(j==1)//No se apreto
    {  
      switch(i)
      {
        case 0: notaNF(0,0);
        break;
        case 1: notaNF(1,0);
        break;
        case 2: notaNF(2,0);
        break;
        case 3: notaNF(3,0);
        break;
        case 4: notaNF(4,0);
        break;
        case 5: notaNF(5,0);
        break;
        case 6: notaNF(6,0);
        break;
        case 7: notaNF(7,0);
        break;
        case 8: notaNF(8,0);
        break;
        case 9: notaNF(9,0);
        break;
        case 10: notaNF(10,0);
        break;
        case 11: notaNF(11,0);
        break;
        case 12: notaNF(12,0);
        break;
        case 13: notaNF(13,0);
        break;
        case 14: notaNF(14,0);
        break;
        case 15: notaNF(15,0);
        break;       
      }
    }      
  }
}


//F.declar.

void notaNF(byte nota, byte NF)
{
  switch(nota)//envia nota definida 
  {
    case 0: nota=n0;
    break;
    case 1: nota=n1;
    break;
    case 2: nota=n2;
    break;
    case 3: nota=n3;
    break;
    case 4: nota=n4;
    break;
    case 5: nota=n5;
    break;
    case 6: nota=n6;
    break;
    case 7: nota=n7;
    break;
    case 8: nota=n8;
    break;
    case 9: nota=n9;
    break;
    case 10: nota=n10;
    break;
    case 11: nota=n11;
    break;
    case 12: nota=n12;
    break;
    case 13: nota=n13;
    break;
    case 14: nota=n14;
    break;
    case 15: nota=n15;
    break;
  }
  
  if(NF==1){//pregunta por ON o OFF
    Serial.print(0x90);//NotaON
    Serial.print(" ");
  }
  if(NF==0){
    Serial.print(0x80);//NotaOFF
    Serial.print(" ");
  }
  Serial.print(nota);//Nota
  Serial.print(" ");
  Serial.print(127);//Volumen
  Serial.print(" ");
  Serial.print(NF); 
  Serial.println();
}

int BitRead(int n, int pos){//devuelve un bit de un byte
  n=n>>pos;
  return(n&1);
}

void pinMode_init(void){
  pinMode(2,INPUT_PULLUP);
  //digitalWrite(2,1);
  pinMode(3,INPUT_PULLUP);
  //digitalWrite(3,1);
  pinMode(4,INPUT_PULLUP);
  //digitalWrite(4,1);
  pinMode(5,INPUT_PULLUP);
  //digitalWrite(5,1);
  pinMode(6,INPUT_PULLUP);
  //digitalWrite(6,1);
  pinMode(7,INPUT_PULLUP);
  //digitalWrite(7,1);
  pinMode(8,INPUT_PULLUP);
  //digitalWrite(8,1);
  pinMode(9,INPUT_PULLUP);
  //digitalWrite(9,1);
  pinMode(10,INPUT_PULLUP);
  //digitalWrite(10,1);
  pinMode(11,INPUT_PULLUP);
  //digitalWrite(11,1);
  pinMode(12,INPUT_PULLUP);
  //digitalWrite(12,1);
  pinMode(13,INPUT_PULLUP);
  //digitalWrite(13,1);
  pinMode(14,INPUT_PULLUP);
  //digitalWrite(14,1);
  pinMode(15,INPUT_PULLUP);
  //digitalWrite(15,1);
  pinMode(16,INPUT_PULLUP);
  //digitalWrite(16,1);
  pinMode(17,INPUT_PULLUP);
  //digitalWrite(17,1);
}
