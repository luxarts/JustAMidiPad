/*  
 *          Just A Midi Pad 
 * www.github.com/luxarts/JustAMidiPad
 * Module: AD
 * Version: 1.2
 * 
 * Created by LuxARTS, OG-Jonii & pablonobile99
 *               2016
 */
//Libraries

//Prototypes

//Global variables

int pote_anterior[6];

//Functions
void setup(){

  Serial.begin(9600);
  for(byte i=0;i<6;i++)pote_anterior[i]=analogRead(i);//Leo los pines analogicos y guardo lo que lee
}

void loop(){

  int pote[6];
  byte mapeo;
  
  for(byte i=0;i<6;i++)
  {
    pote[i]=analogRead(i);//Lectura del puerto analogico
    mapeo=map(pote[i],0,1023,0,127);//Mapeo entre 0 y 1023 a 0 y 127

    if(pote[i]>pote_anterior[i]+2 || pote[i]<pote_anterior[i]-2)//Comparo 1er lectura con 2da lectura
    {
        Serial.write(0xB0);//Control Change
        Serial.write(i);//Número de control, en 2do micro se reemplaza la i por i+6 debido a que son 12 potes
        Serial.write(mapeo);//Valor de pote
        /*
        Serial.print("POTE");
        Serial.print(i+1);
        Serial.print("= ");
        Serial.print(mapeo);//Imprimo el mapeo hecho en la 2da lectura de los pines Analogicos
        Serial.println();
        pote_anterior[i]=pote[i];//Igualo para luego comparar con el sig
        */
    }
  }
}

