#include <KnightRoboticsLibs_Iroh.h>
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>
#include <Servo.h>
#include <Wire.h>

int IRD, IRI, LI, LC, LD, US;
int umbral = 300;
int vel = 140;
int t = 375;
int cont = 0; // contador intersecciones
int cont_us = 0; // contador objetos captados por ultrasonido
int dist1 = 15;
int dist2 = 5;

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
  LI = leerSensorLineaIzquierdo();
  LC = leerSensorLineaCentral();
  LD = leerSensorLineaDerecho();
  if (LI <= umbral && LC <= umbral && LD <= umbral){
    detenerse();
    inicializarCabeza();
    
    moverServoYaw(15);
    pausa(t);
    US = leerDistanciaSonar();
    if (US < dist1 && US > dist2){
      cont_us++;
    }
    
    moverServoYaw(165);
    pausa(t);
    US = leerDistanciaSonar();
    if (US < dist1 && US > dist2){
      cont_us++;
    }
    apagarCabeza();
    while (LI <= umbral && LC <= umbral && LD <= umbral){
      avanzar(vel);
      LI = leerSensorLineaIzquierdo();
      LC = leerSensorLineaCentral();
      LD = leerSensorLineaDerecho();
    }
  }
  seguirLinea(umbral,vel);
}

void seguirLinea(int umbral, int vel) {
  if (LI <= umbral && LC > umbral && LD <= umbral) {
    avanzar(vel);
  }
  else if (LI > umbral && LC <= umbral && LD <= umbral) {
    avanzar(0, vel);
  }
  else if (LI <= umbral && LC <= umbral && LD > umbral) {
    avanzar(vel, 0);
  }
}
