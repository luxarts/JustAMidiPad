/*  
 *          Just A Midi Pad 
 * www.github.com/luxarts/JustAMidiPad
 * Module: AD
 * Version: 0.0
 * 
 * Created by LuxARTS, OG-Jonii & pablonobile99
 *               2016
 */
//Libraries

//Prototypes

//Global variables

//Functions
void setup(){

  Serial.begin(9600);
}

void loop(){

  int pote[6],i;
  for(i=0;i<=5;i++)
  {
    pote[i]=analogRead(i);//Lectura del puerto analogico
    Serial.print("POTE");
    Serial.print(i+1);
    Serial.print("= ");
    Serial.print(pote[i]);//Muestro los valores guardados del puerto AD
    Serial.println();
    delayMicroseconds(100);//Delay minimo entre cada lectura de cada pin del AD
  }
}

