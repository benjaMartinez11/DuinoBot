Pasos (Windows / macOS / Linux)
Instalar Arduino IDE


Baja e instala la versión oficial (IDE 1.8.x o IDE 2.x funcionan). Página oficial de descargas. arduino.cc
Abrir la terminal en la carpeta de el IDE 1.8.19 con el siguiente comando:
./arduino


Agregar el soporte del DuinoBot al Board Manager


Abre Arduino IDE → File (Archivo) → Preferences (Ajustes).


En Additional Boards Manager URLs pega esta URL:


https://raw.githubusercontent.com/Robots-Linti/Multiplo/master/package_SoporteLihuen_DuinobotAVRBoards_index.json

Guarda. (Puedes añadir varias URLs separadas por comas o en el diálogo si usás IDE 2.x). GitHub+1


Instalar el paquete de placas


Arduino IDE → Tools (Herramientas) → Board (Placa) → Boards Manager…


Busca Duinobot AVR Boards y click en Install. Reinicia el IDE si no aparece inmediatamente. GitHub


Seleccionar la placa y la configuración


Tools → Board → seleccioná la entrada Duinobot v2.3 / Multiplo N6-MAX (ATmega1284) o la opción equivalente dentro del paquete.


Tools → CPU / Variant → elegí ATmega1284 (si hay sub-opciones).


Tools → Clock / Frequency → por defecto 16 MHz (el paquete documenta soporte a 20/16/8/1 MHz — confirmá cuál tiene tu placa). GitHub


Seleccionar puerto y programador


Conectá el DuinoBot por USB (o el adaptador USB-Serial que venga). Tools → Port → seleccioná el puerto COM/tty asignado.


En la mayoría de los casos para cargar sketches por USB no necesitás cambiar el "Programmer". Si necesitás grabar el bootloader (ver abajo) entonces usarás Arduino as ISP u otro programador compatible. GitHub


Subir un sketch de prueba (Blink)


Abre el ejemplo File → Examples → 01.Basics → Blink.


Uso recomendado: reemplazar LED_BUILTIN por el pin que indique el pinout si el LED integrado no responde; pero probá primero con LED_BUILTIN.


Click Upload (flecha). Si todo está bien, compila y sube.


Ejemplo (idéntico al ejemplo Arduino):
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}







Ejemplo de Luz de prueba (Blink)

Si falla la carga por serial (problemas comunes)


Confirmá puerto y drivers (ej. chips CH340/FTDI).


Si la placa no tiene bootloader compatible o nunca se le grabó el bootloader del paquete, puede ser necesario grabar el bootloader usando otra placa Arduino como programador (ArduinoISP) — el repo oficial del paquete explica cómo hacerlo (conexiones y pasos). GitHub+1


Quemar bootloader (solo si indica el paquete / la placa lo requiere)


Programá un UNO/Nano con el sketch ArduinoISP (Arduino → Examples → 11.ArduinoISP → ArduinoISP). Conectá ISP (MOSI/MISO/SCK/GND/Reset) según las tablas del repositorio.


En el IDE seleccioná la placa Duinobot v1.2 / v2.3 apropiada en Tools, el puerto de la placa programadora, y Tools → Burn Bootloader. GitHub


Subir código para probar los Servo motores
 Código de Ejemplo para poder probar los servo motores:
#include <DCMotor.h>

DCMotor motor0(M0_EN, M0_D0, M0_D1);
DCMotor motor1(M1_EN, M1_D0, M1_D1);

void setup()
{
  motor0.setClockwise(false);
  motor0.setSpeed(50.0);
  motor1.setSpeed(100.0);
  delay(5000);

  motor0.brake();
  motor1.brake();
}

void loop()
{ }

Aplicación para controlar el DuinoBot a partir de una aplicación bluetooth
Descargar Aplicación Arduino Bluetooth Controller:
https://play.google.com/store/apps/details?id=com.giristudio.hc05.bluetooth.arduino.control 
Abrir la aplicación y Seleccionar la sección “Gamepad”:

Conectar tu celular al módulo bluetooth hc-06
Paso a Paso de como poder usar y conectar el JY-MCU al múltiplo n6

Conectar el JY-MCU a la placa DuinoBot v2.3

Conexiones

PIN Placa DuinoBot
Módulo bluetooth: HC-06
TX(pin:01)
RX
RX(pin:0)
TX
GND
GND
5V
VCC


 Tenemos que poner el tx en el rx(0) y el rx en el tx(1), recuerda que también tienes que conectar el gnd y 5v. 

Para conectarnos al JY-MCU tenemos que descargar la aplicación oficial de arduino llamada “Arduino bluetooth”, para conectarse es de forma bluetooth.

Foto de ejemplo de conexiones:


Código:
#define LED_ROJO 13
#define BuzzLightyear 9

void setup()
{
  pinMode(LED_ROJO, OUTPUT);
  pinMode(BuzzLightyear, OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  if(Serial.available()>0)
  {
  char letra = Serial.read();
  if(letra == 'p')
  {
	digitalWrite(LED_ROJO,HIGH);
  }
  if(letra == 'a')
  {
	digitalWrite(LED_ROJO,LOW);
  }
  if(letra == 'c')
  {
	if (digitalRead(LED_ROJO)== LOW)
	{
  	digitalWrite(LED_ROJO,HIGH);
	}
	else
	{
  	digitalWrite(LED_ROJO,LOW);
	}
	if(letra == 'z')
	{
  	tone(BuzzLightyear, 660, 2000);
	}
	else
	{
  	noTone(BuzzLightyear);
	}
  }
  }
}


Foto:


Recordatorio:
al momento de cargar el código desconecte el 5v del bluetooth

codigo para poder controlar el DuinoBot:


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
  if (letra == 'F')
  {
   	acelerarMotores(-1, 1);
  }
  else if (letra == 'B')
  {
   	acelerarMotores(1, -1);
  }
  else if (letra == 'R')
  {
	motor0.setSpeed(70.0);
	moor1.setSpeed(00.0);
  }
  else if (letra == 'L')
  {
	motor0.setSpeed(00.0);
	motor1.setSpeed(-70.0);
  }
  else if (letra == 'S') {
	estado = !estado;
	digitalWrite(LED_ROJO, estado);
  }
  else if (letra == 'X')
  {
	motor0.brake();
	motor1.brake();
  }
  else if (letra == '0')
  {
	motor0.setSpeed(00.0);
	motor1.setSpeed(00.0);
  }
  }
}




