/*  
 *          Just A Midi Pad 
 * www.github.com/luxarts/JustAMidiPad
 * Module: Input
 * Version: 0.0 
 * 
 * Created by LuxARTS, OG-Jonii & pablonobile99
 *               2016
 */
//Libraries

//Prototypes

//Global variables

byte boton[2]=
{
  {0b11111111},//line 1 y 2 matriz 4x4
  {0b11111111},//line 3 y 4 matriz 4x4
 // {0b11111111},//direccion(4) y mute(4)
 // {0b00000001}//camb.pag. potes
};

byte mask;

byte n0=0;//nota 0x0 
byte n1=1;//nota 0x1
byte n2=2;//nota 0x2
byte n3=3;//nota 0x3
byte n4=4;//nota 1x0
byte n5=5;//nota 1x1
byte n6=6;//nota 1x2
byte n7=7;//nota 1x3
byte n8=8;//nota 2x0
byte n9=9;//nota 2x1
byte n10=10;//nota 2x2
byte n11=11;//nota 2x3
byte n12=12;//nota 3x0
byte n13=13;//nota 3x1
byte n14=14;//nota 3x2
byte n15=15;//nota 3x3

//Functions


void setup(){
  
}

void loop(){
  //Guardado estado botones
  
  for(i=1;i<3;i++){
    for(j=0;0<8;i++){
      mask==digitalRead(i)*64;//mando el estado del boton al bit 8
      boton[i]=mask&boton[i];
      boton[i]=boton[i]>>1;
    }
  }
  
  //Prende nota/boton guardad@

  for(byte i=0;i<6;i++)//Comprueba pulsaciones
  {
  if(boton[i]==0 && boton_b[i]==0)//Se apretó y no estaba apretado
    {
      switch(i)
      {
        case 0: notaOn(11);
        break;
        case 1: notaOn(12);
        break;
        case 2: notaOn(21);
        break;
        case 3: notaOn(22);
        break;
        case 4: notaOn(31);
        break;
        case 5: notaOn(32);
        break;       
      }
      boton_b[i]=1;//Se apretó
    }
  }
  
  //Apaga nota/boton guardad@
}


//F.declar.

void notaOut(byte nota, byte NF)
{
  switch(nota)
  {
    case : nota=n0;
    break;
    case : nota=n1;
    break;
    case : nota=n2;
    break;
    case : nota=n3;
    break;
    case : nota=n4;
    break;
    case : nota=n5;
    break;
    case : nota=n6;
    break;
    case : nota=n7;
    break;
    case : nota=n8;
    break;
    case : nota=n9;
    break;
    case : nota=n10;
    break;
    case : nota=n11;
    break;
    case : nota=n12;
    break;
    case : nota=n13;
    break;
    case : nota=n14;
    break;
    case : nota=n15;
    break;
  }
  
  if(NF==1){
    Serial.write(0x90);//NotaON
  }
  else{
    Serial.write(0x80);//NotaOFF
  }
  Serial.write(nota);//Nota
  Serial.write(127);//Volumen 
}
