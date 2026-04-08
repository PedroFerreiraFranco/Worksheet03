#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = ""; 
const char* password = ""; 

const char* mqtt_server = "";
const int mqtt_port = ;
const char* topic_control = ""; 

const int ONBOARD_LED = 2;

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("Mensagem recebida [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(message);

  if (message == "OPEN") {
    digitalWrite(ONBOARD_LED, LOW);
    Serial.println(">>> JANELA ABERTA");
  } 
  else if (message == "CLOSE") {
    digitalWrite(ONBOARD_LED, HIGH);
    Serial.println(">>> JANELA FECHADA");
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando MQTT...");
    
    String clientId = "ESP8266-Pedro-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println("conectado!");
      client.subscribe(topic_control); 
      Serial.print("Inscrito no topico: ");
      Serial.println(topic_control);
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando em 5s");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(9600);
  
  pinMode(ONBOARD_LED, OUTPUT);
  digitalWrite(ONBOARD_LED, HIGH);

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
