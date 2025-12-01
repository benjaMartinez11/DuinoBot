# 🚗 Robot Múltiplo N6 — DuinoBot v2.3  
**Controlado por Bluetooth / MQTT — Documentación completa**

---

## 👥 Integrantes
- Adan Coronel  
- Benjamín Martinez

---

## 📸 Foto del robot

<img src="imagenes/1000117783.jpg" width="400">

---

# 🛠️ Avances por fecha

## Pasos (Windows / macOS / Linux)

    Instalar Arduino IDE

        Baja e instala la versión oficial (IDE 1.8.x o IDE 2.x funcionan). Página oficial de descargas. arduino.cc

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


---

## **10/20 — Instalación de Arduino IDE**
- Instalación de **Arduino IDE 1.8.19** desde la página oficial.
- Inicialización con el comando:

🔵 Bluetooth — Módulo JY-MCU / HC-06
Conexiones
JY-MCU	DuinoBot
TX	RX (0)
RX	TX (1)
GND	GND
VCC	5V
📌 Recordatorio
Antes de subir el código → Desconectar el cable 5V del Bluetooth.
