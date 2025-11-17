# DuinoBot v2.3 – Instalación, Configuración y Ejemplos

Guía completa para utilizar la placa **DuinoBot v2.3 / Multiplo N6-MAX (ATmega1284)** con el **Arduino IDE**, incluyendo configuración del entorno, pruebas iniciales, uso de motores y control por Bluetooth (HC-06 / JY-MCU).

---

## 📑 Índice

1. [Requisitos](#-requisitos)
2. [Instalación del Arduino IDE](#-instalación-del-arduino-ide)
3. [Agregar soporte DuinoBot al Board Manager](#-agregar-soporte-duinobot-al-board-manager)
4. [Instalación del paquete de placas](#-instalación-del-paquete-de-placas)
5. [Selección de placa y configuración](#-selección-de-placa-y-configuración)
6. [Seleccionar puerto y programador](#-seleccionar-puerto-y-programador)
7. [Probar placa – Blink](#-probar-la-placa--blink)
8. [Problemas comunes](#-problemas-comunes)
9. [Quemar Bootloader](#-quemar-bootloader)
10. [Código: Prueba de motores](#-código-prueba-de-motores)
11. [Control por Bluetooth](#-control-por-bluetooth)
12. [Código: LED y buzzer Bluetooth](#-código-led-y-buzzer-bluetooth)
13. [Código: Control completo del DuinoBot](#-código-control-completo-del-duinobot)
14. [Imágenes](#-imágenes)
15. [Notas finales](#-notas-finales)

---

## 📌 Requisitos

- Arduino IDE (1.8.x o 2.x)
- Placa DuinoBot v2.3 / Multiplo N6-MAX
- Cable USB o adaptador USB–Serial
- Módulo Bluetooth HC-06 / JY-MCU (opcional)
- Librería `DCMotor.h` incluida en el paquete DuinoBot

---

## 🔧 Instalación del Arduino IDE

Descarga el IDE desde:

👉 https://www.arduino.cc/en/software

En Linux, ejecutar desde la carpeta del IDE:

```bash
./arduino
