# 🌡️ Sistema de Controle de Janela IoT 
### Mestrado em Informática - IPB | Worksheet 3 - Exercício 9

Este projeto implementa uma solução de automação inteligente para o controlo de uma janela (simulada pelo LED interno de um ESP8266). O sistema monitoriza a temperatura média ambiente da última hora e executa uma ação de abertura ou fecho baseada num limite (threshold) definido pelo utilizador.

---

## 👥 Autores
* **Pedro Ferreira Franco**
* **André Luiz de Lima**
* **Deyvison Nogueira de Oliveira**

---

## 🚀 Funcionamento do Sistema

O fluxo de dados segue a seguinte lógica:
1. **Recolha de Dados:** O sistema consulta o **InfluxDB** para obter a média de temperatura dos últimos 60 minutos.
2. **Interface do Utilizador:** Através de um Dashboard no **Node-RED**, o utilizador define a temperatura desejada.
3. **Processamento:** O Node-RED compara os valores:
   - Se `Média > Limite` ➡️ Envia comando `OPEN`.
   - Se `Média <= Limite` ➡️ Envia comando `CLOSE`.
4. **Atuação:** O **ESP8266** recebe o comando via protocolo **MQTT** e altera o estado do LED onboard.

---

## 🛠️ Stack Tecnológica

- **Hardware:** ESP8266 (NodeMCU / Wemos D1 Mini).
- **Firmware:** Linguagem C++ (Arduino IDE).
- **Middleware:** Node-RED para orquestração e lógica de negócio.
- **Base de Dados:** InfluxDB (Time Series Database).
- **Protocolo de Comunicação:** MQTT (Broker Público HiveMQ).

---

## 🔧 Configuração e Instalação

### 1. Firmware (ESP8266)
No ficheiro `.ino`, é necessário configurar as seguintes constantes com os teus dados locais:
- `STASSID`: Nome da tua rede Wi-Fi.
- `STAPSK`: Senha da rede Wi-Fi.
- `MQTT_BROKER`: Endereço do broker (ex: `broker.mqtt-dashboard.com`).
- `MQTT_TOPIC`: Tópico subscrito (deve ser o mesmo configurado no Node-RED).

### 2. Fluxo Node-RED
- Importar o ficheiro JSON do fluxo.
- Configurar o nó **InfluxDB Query** com a URL, Token e Organização da tua instância.
- Configurar o nó **MQTT Out** com o broker e tópico correspondentes.

---

## 📝 Notas de Implementação
- **Baud Rate:** A comunicação serial está configurada para **9600 baud** para compatibilidade com o Serial Monitor.
- **Lógica do LED:** Foi utilizada a lógica *Active Low*, padrão no LED interno do ESP8266 (GPIO 2).
- **Segurança:** O projeto utiliza um Broker público para fins académicos; para ambientes de produção, recomenda-se o uso de autenticação TLS/SSL.

---
*Projeto desenvolvido para a unidade curricular de Internet das Coisas (IoT) - IPB 2026.*
