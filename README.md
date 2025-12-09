# 🚗 Vehículo controlado a distancia
# Robot Múltiplo N6 — DuinoBot v2.3  
**Controlado por MQTT — Documentación completa**

---

## 👥 Integrantes
- Adan Coronel  
- Benjamín Martinez

---

## 📸 Foto del robot

<img src="imagenes/1000117783.jpg" width="400">

## 📸 Foto del circuito del robot

<img src="imagenes/IMG_20251201_191544856_HDR.jpg" width="400">

---

# 🛠️ Pasos (Windows / macOS / Linux)

1.Instalar Arduino IDE

  Baja e instala la versión oficial (IDE 1.8.x o IDE 2.x funcionan). Página oficial de descargas. arduino.cc

  Nota: El IDE 1.8.X es usada para el duinobot.
  El IDE 2.X fue usada para el NodeMCU-32.

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

## **Conexiones del NodeMCU-32**

<img src="imagenes/Captura de pantalla_2025-12-05_10-54-16.png" width="400">


## **Foto del ESP-32**

<img src="imagenes/esp32-devkitc-v4-esp32-wifi-micro-usb.jpg" width="400">



## **Foto dela Placa duinobot v2.3**
<img src="imagenes/IMG_20251113_110920156_HDR.jpg" width="400">

## **Diagrama de Bloques de conexion**
<img src="imagenes/Captura de pantalla_2025-12-05_11-07-12.png" width="400">

## **Diagrama de Bloques de comunicacion**
<img src="imagenes/Captura de pantalla_2025-12-05_11-08-22.png" width="400">

## **Diagrama Flujo**
<img src="imagenes/Captura de pantalla_2025-12-02_14-35-26.png" width="400">
