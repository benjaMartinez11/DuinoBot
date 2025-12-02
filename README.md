# 🚗 Vehículo controlado a distancia
# Robot Múltiplo N6 — DuinoBot v2.3  
**Controlado por Bluetooth / MQTT — Documentación completa**

---

## 👥 Integrantes
- Adan Coronel  
- Benjamín Martinez

---

## 📸 Foto del robot

<img src="imagenes/1000117783.jpg" width="400">

---

# 🛠️ Pasos (Windows / macOS / Linux)

1.Instalar Arduino IDE

  Baja e instala la versión oficial (IDE 1.8.x o IDE 2.x funcionan). Página oficial de descargas. arduino.cc

2.Agregar el soporte del DuinoBot al Board Manager

  Abre Arduino IDE → File (Archivo) → Preferences (Ajustes).

  En Additional Boards Manager URLs pega esta URL:

      https://raw.githubusercontent.com/Robots-Linti/Multiplo/master/package_SoporteLihuen_DuinobotAVRBoards_index.json

Guarda. (Puedes añadir varias URLs separadas por comas o en el diálogo si usás IDE 2.x). GitHub+1

3.Instalar el paquete de placas

  Arduino IDE → Tools (Herramientas) → Board (Placa) → Boards Manager…

  Busca Duinobot AVR Boards y click en Install. Reinicia el IDE si no aparece inmediatamente. GitHub

4.Seleccionar la placa y la configuración

  Tools → Board → seleccioná la entrada Duinobot v2.3 / Multiplo N6-MAX (ATmega1284) o la opción equivalente dentro del paquete.

  Tools → CPU / Variant → elegí ATmega1284 (si hay sub-opciones).

  Tools → Clock / Frequency → por defecto 16 MHz (el paquete documenta soporte a 20/16/8/1 MHz — confirmá cuál tiene tu placa). GitHub

5.Seleccionar puerto y programador

  Conectá el DuinoBot por USB (o el adaptador USB-Serial que venga). Tools → Port → seleccioná el puerto COM/tty asignado.

  En la mayoría de los casos para cargar sketches por USB no necesitás cambiar el "Programmer". Si necesitás grabar el bootloader (ver abajo) entonces usarás Arduino as ISP u otro programador compatible. GitHub
    

 6.Subir un sketch de prueba (Blink)

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

 7.Si falla la carga por serial (problemas comunes)

  Confirmá puerto y drivers (ej. chips CH340/FTDI).

  Si la placa no tiene bootloader compatible o nunca se le grabó el bootloader del paquete, puede ser necesario grabar el bootloader usando otra placa Arduino como programador (ArduinoISP) — el repo oficial del paquete explica cómo hacerlo (conexiones y pasos). GitHub+1

  8.Quemar bootloader (solo si indica el paquete / la placa lo requiere)

    Programá un UNO/Nano con el sketch ArduinoISP (Arduino → Examples → 11.ArduinoISP → ArduinoISP). Conectá ISP (MOSI/MISO/SCK/GND/Reset) según las tablas del repositorio.

    En el IDE seleccioná la placa Duinobot v1.2 / v2.3 apropiada en Tools, el puerto de la placa programadora, y Tools → Burn Bootloader. GitHub




---

## **Conexiones del JY-MCU**

<img src="imagenes/Captura de pantalla_2025-12-01_19-18-29.png" width="400">


## **Codigo del ESP-32**

      #include <WiFi.h>
      #include <PubSubClient.h>


      const char* ssid = "PEINE-3";
      const char* password = "etecPeine3";
      const char* mqtt_server = "10.56.2.74"; // Ej: "192.168.0.10"


      WiFiClient espClient;
      PubSubClient client(espClient);


      void callback(char* topic, byte* message, unsigned int length) {


      Serial.print("Mensaje MQTT -> ");
      String msg;


      for (int i = 0; i < length; i++) {
        msg += (char)message[i];
      }


      Serial.println(msg);


      // Reenviar al Duinobot por Serial2
      Serial2.print(msg);
      }


      void reconnect() {
      while (!client.connected()) {
        if (client.connect("ESP32Cliente")) {
          client.subscribe("/robot/movimiento");
        } else {
          delay(2000);
        }
      }
      }


      void setup() {
      Serial.begin(115200);


      // Comunicación serial hacia Duinobot
      Serial2.begin(9600, SERIAL_8N1, 16, 17); // RX=16, TX=17


      // Conectar WiFi
      WiFi.begin(ssid, password);
      while (WiFi.status() != WL_CONNECTED) delay(500);


      // Configurar MQTT
      client.setServer(mqtt_server, 1883);
      client.setCallback(callback);
      }
      void loop() {
      if (!client.connected()) reconnect();
      client.loop();
      }

## **Codigo del DuinoBot**

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
      motor1.setSpeed(00.0);
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
