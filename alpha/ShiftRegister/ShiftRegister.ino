#define STCP  2
#define SHCP  3
#define SI    4

void escribe (byte,byte);

void setup()
{
  
  
  pinMode(STCP,OUTPUT);
  pinMode(SHCP,OUTPUT);
  pinMode(SI,OUTPUT);
  digitalWrite(SI,0);
  digitalWrite(STCP,0);  
  digitalWrite(SHCP,1);
  
  digitalWrite(STCP,0);
  
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

void loop()
{
  for(int i=0;i<256;i++)
  {
    escribe(i,0);
    delay(500);
  }
}

void escribe (byte MSB,byte LSB)//Most significant byte,Less significant byte
{
  byte data[16]={0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0};

  for(int i=0;i<8;i++)
  {
    data[i]=MSB&0b00000001;//Máscara
    MSB=MSB>>1;
  }
  for(int i=8;i<16;i++)
  {
    data[i]=LSB&0b00000001;//Máscara
    LSB=LSB>>1;
  }
  
  digitalWrite(STCP,0);//Mantiene el registro  
  for(int i=0;i<16;i++)
  {      
    digitalWrite(SI,data[i]);//Escribe el bit
    delayMicroseconds(1);
    digitalWrite(SHCP,0);//Manda el pulso de shift
    delayMicroseconds(1);
    digitalWrite(SHCP,1);
    delayMicroseconds(1);
  }
  digitalWrite(STCP,1);//Saca el registro al puerto
  
}

