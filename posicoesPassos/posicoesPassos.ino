#include <Servo.h>

Servo servoBase;  //Servo base
Servo servoX;     //Servo frente e tras
Servo servoY;     //Servo sobe e desce
Servo servoGarra; //Servo garra (abre e fecha)

#define zeroBase       90
#define zeroX          20
#define zeroYAlta     150
#define zeroYBaixa    130
#define garraFechada  165
#define garraAberta   140

int svBase, svX, svY, svGarra;
int etapa = -1;
int ciclo = 0;

int posicoesBase[] = { 118, 107, 98, 86, 76, 65, 54, 45 };
int posicoesX[] =     { 36,  23, 19, 21, 20, 25, 33, 40 };

void setup() {
  Serial.begin(115200);
  servoBase.attach(3);
  servoX.attach(5);
  servoY.attach(9);
  servoGarra.attach(6);
}

void loop() {

  if ( etapa == -1 )
  {
    svBase = zeroBase;
    svX = zeroX;
    svGarra = garraAberta;
    svY = zeroYAlta;
    etapa = 0;
  }
  else
  {
    if (etapa == 0 && ciclo == 0) {
      delay(2000);
    }

    ciclo ++;
    if (ciclo == 1)
    {
      // vai para a posição com a garra aberta
      svBase = posicoesBase[etapa];
      svX = posicoesX[etapa];
      svGarra = garraAberta;
    }
    else if (ciclo == 2)
    {
      svY = zeroYBaixa;
    }
    else if (ciclo == 3)
    {
      svGarra = garraFechada;
    }
    else if (ciclo == 4)
    {
      svY = zeroYAlta;
    }
    else if (ciclo == 5)
    {
      svBase = posicoesBase[etapa + 1];
      svX = posicoesX[etapa + 1];
    }
    else if (ciclo == 6)
    {
      svY = zeroYBaixa;
    }
    else if (ciclo == 7)
    {
      svGarra = garraAberta;
    }
    else if (ciclo == 8)
    {
      svY = zeroYAlta;
    }
    else
    {
      etapa ++;
      ciclo = 0;
      if (etapa >= (sizeof(posicoesX) / sizeof(int)) - 1)
      {
        etapa = -1;
      }
    }
  }

  // Posição atual
  servoBase.write(svBase);
  servoX.write(svX);
  servoY.write(svY);
  servoGarra.write(svGarra);

  Serial.print(etapa);
  Serial.print(" Base: ");
  Serial.print(svBase);
  Serial.print(" X: ");
  Serial.print(svX);
  Serial.print(" Y: ");
  Serial.print(svY);
  Serial.println();

  delay (200);

}
