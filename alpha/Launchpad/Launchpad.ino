byte boton[7]={1,1,1,1,1,1,1};
byte boton_b[7]={0,0,0,0,0,0,0};
int pot[2];
byte pot_b[2]={0,0};
int actual[2][2],control[2];

void setup()
{
  for(byte i=40;i<46;i++)
  {
    pinMode(i,INPUT);//Botones
    digitalWrite(i,HIGH);//Pullup
  }
  Serial.begin(31250);   
}

void loop()
{
  for(byte i=0;i<6;i++)//Comprueba pulsaciones
  {
    boton[i]=digitalRead(i+40);
    delay(1);//Anti-rebote
    if(boton[i]!=digitalRead(i+40))digitalRead(i+40);
    
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
  
  for(byte y=0;y<6;y++)//Apaga banderas
  {
    boton[y]=digitalRead(y+40);
    delay(1);//Anti-rebote
    if(boton[y]!=digitalRead(y+40))digitalRead(y+40);
    
    if(boton[y]==1 && boton_b[y]==1)//Se soltó y estaba apretado
    {
      switch(y)
      {
        case 0: notaOff(11);
        break;
        case 1: notaOff(12);
        break;
        case 2: notaOff(21);
        break;
        case 3: notaOff(22);
        break;
        case 4: notaOff(31);
        break;
        case 5: notaOff(32);
        break;     
      }
      boton_b[y]=0;//Se soltó
    }
  }
  
  pote(0); //Manda estado de los potes
  pote(1); 
}

void notaOn(byte nota)
{
  switch(nota)
  {
    case 11: nota=0;//C0
    break;
    case 12: nota=1;//C#0
    break;
    case 21: nota=12;//C1
    break;
    case 22: nota=13;//C#1
    break;
    case 31: nota=24;//C2
    break;
    case 32: nota=25;//C#2
    break;
  }
  Serial.write(0x90);//NotaON
  Serial.write(nota);//Nota
  Serial.write(127);//Volumen
  
}
void notaOff(byte nota)
{
  switch(nota)
  {
    case 11: nota=0;//C0
    break;
    case 12: nota=1;//C#0
    break;
    case 21: nota=12;//D0
    break;
    case 22: nota=13;//C1
    break;
    case 31: nota=24;//C#1
    break;
    case 32: nota=25;//D1
    break;
  }
  Serial.write(0x80);//NotaOFF
  Serial.write(nota);//Nota
  Serial.write(127);//Volumen
}

void pote(byte num)
{
  pot[num]=analogRead(num);
  control[num]=map(pot[num],0,1023,0,127);//Lectura fin
  
  if(pot_b[num]==0 && actual[num][1]!=control[num])
  {
    Serial.write(0xB0);//Control Change
    Serial.write(num);//Número de control
    Serial.write(control[num]);//Valor de pote
    //Debug
  //  Serial.println(control[num]);//Valor de pote
    
    pot_b[num]=1;
    actual[num][0]=pot[num];//Guarda el valor leido del pote
    //actual[num][1]=control[num];//Guarda el valor calculado de control
  }  
  if(pot[num]>actual[num][0]+1 || pot[num]<actual[num][0]-1)pot_b[num]=0; //Hasta que no salga del rango de valores
}

