#include <KnightRoboticsLibs_Iroh.h>
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>
#include <Servo.h>
#include <Wire.h>

int IRD, IRI, LI, LC, LD, US;
int umbral = 300;
int vel1 = 140;
int vel2 = 110;
int t = 375;
int cont = 0;

void setup() {
  inicializarSensores();
  inicializarCabeza();
  inicializarMovimiento();
  inicializarPantalla();
  inicializarGolpe();
  botonInicio();
  moverServoYaw(90);
  moverServoPitch(45);
  apagarPantalla();
  apagarCabeza();
  moverServoGolpe(-1);
}

void loop() {
  if (cont == 0) {
    avanzar(vel1);
    pausa(t);
    cont++;
  }
  else if (cont != 0) {
    LI = leerSensorLineaIzquierdo();
    LC = leerSensorLineaCentral();
    LD = leerSensorLineaDerecho();
    US = leerDistanciaSonar();

    if (US > 8 && US < 12) {
      seguirLinea(umbral, vel2);
    }
    else if (US <= 8 && US >= 5) {
      detenerse();
      pausa(500);
      moverServoGolpe(1);
      pausa(t);
      moverServoGolpe(-1);
      pausa(t);
    }
    else {
      seguirLinea(umbral, vel1);
    }
  }
}
void seguirLinea(int umbral, int vel) {
  while (LI > umbral && LC > umbral && LD > umbral) {
    borrarPantalla();
    escribirPantalla(0,0, "aiudaa");
    if (leerSensorObstaculoDerecho() == 0) {
      while (leerSensorObstaculoDerecho() == 0);
      girarDerecha(vel1);
      pausa(4 * t);
    }

    else if (leerSensorObstaculoIzquierdo() == 0) {
      while (leerSensorObstaculoIzquierdo() == 0);
      girarIzquierda(vel1);
      pausa(4 * t);
    }
    LI = leerSensorLineaIzquierdo();
    LC = leerSensorLineaCentral();
    LD = leerSensorLineaDerecho();
  }
  if (LI <= umbral && LC > umbral && LD <= umbral) {
    avanzar(vel);
  }
  else if (LI > umbral && LC <= umbral && LD <= umbral) {
    avanzar(0, vel);
  }
  else if (LI <= umbral && LC <= umbral && LD > umbral) {
    avanzar(vel, 0);
  }
  else if (LI <= umbral && LC <= umbral && LD <= umbral) {
    avanzar(vel);
  }
}
