//Esto codigo es para controlar los motores del robot, tambien se utiliza el led.

#include <DCMotor.h>
#define LED_ROJO 13
DCMotor motor0(M0_EN, M0_D0, M0_D1);
DCMotor motor1(M1_EN, M1_D0, M1_D1);

const int VELOCIDAD_MIN = 20;
const int VELOCIDAD_MAX = 100; // valor máximo teórico, el motor puede saturar antes
const int PASO = 5;        	// cuanto aumenta por paso
const int RETRASO = 50;    	// tiempo entre pasos en ms

void acelerarMotores(int dir0, int dir1) {
  for (int v = VELOCIDAD_MIN; v <= VELOCIDAD_MAX; v += PASO) {
	motor0.setSpeed(dir0 * v);
	motor1.setSpeed(dir1 * v);
	delay(RETRASO);
  }
}

bool estado = false;

void setup()
{
  pinMode(LED_ROJO, OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  if (Serial.available() > 0)
  {
  char letra = Serial.read();
  if (letra == 'F')//acelera
  {
   	acelerarMotores(-1, 1);
  }
  else if (letra == 'B')//rotrocede
  {
   	acelerarMotores(1, -1);
  }
  else if (letra == 'R')//Izquierda
  {
	motor0.setSpeed(70.0);
	motor1.setSpeed(00.0);
  }
  else if (letra == 'L')//Derecha
  {
	motor0.setSpeed(00.0);
	motor1.setSpeed(-70.0);
  }
  else if (letra == 'S')//Prende el led
  {
	estado = !estado;
	digitalWrite(LED_ROJO, estado);
  }
  else if (letra == 'X')//Detiene el robot
  {
	motor0.brake();
	motor1.brake();
  }
  else if (letra == '0')//Deciende la velocidad no es un boton
  {
	motor0.setSpeed(00.0);
	motor1.setSpeed(00.0);
  }
  }
}
