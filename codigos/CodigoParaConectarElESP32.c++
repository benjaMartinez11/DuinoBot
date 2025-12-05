#include <WiFi.h>

#include <PubSubClient.h>

const char *ssid = "PEINE-3";
const char *password = "etecPeine3";
const char *mqtt_server = "10.56.13.25";

WiFiClient espClient;
PubSubClient client(espClient);

// LED interno del ESP32 (GPIO 2)
#define LED_MQTT 2

void callback(char *topic, byte *message, unsigned int length)
{

    Serial.print("Mensaje MQTT ");

    String msg = "";

    for (int i = 0; i < length; i++)
    {
        msg += (char)message[i];
    }

    Serial.println(msg);

    // Reenviar al Duinobot por Serial2

    Serial2.print(msg);
}

void reconnect()
{

    while (!client.connected())
    {

        Serial.println("Conectando al servidor MQTT...");

        // LED apagado mientras intenta conectarse

        digitalWrite(LED_MQTT, LOW);

        if (client.connect("ESP32Cliente"))
        {

            Serial.println("Conectado al servidor MQTT");

            client.subscribe("/robot/movimiento");

            // LED encendido cuando se conecta correctamente

            digitalWrite(LED_MQTT, HIGH);
        }
    }
}

void setup()
{

    Serial.begin(115200);

    // Comunicación con el Duinobot

    Serial2.begin(9600, SERIAL_8N1, 16, 17);

    // LED interno

    pinMode(LED_MQTT, OUTPUT);

    digitalWrite(LED_MQTT, LOW);

    // Conexión WiFi (sin mensajes)

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
        delay(500);

    // Config MQTT

    client.setServer(mqtt_server, 1883);

    client.setCallback(callback);
}

void loop()
{

    if (!client.connected())
        reconnect();

    client.loop();
}
