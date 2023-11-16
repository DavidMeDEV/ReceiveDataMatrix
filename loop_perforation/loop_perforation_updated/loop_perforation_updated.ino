// import de libs
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsClient.h>
#include <Hash.h>
#include <String.h>

//Funções
void mulMatMod();
void mulMatTrunc();
void mulMatNorm();

//Variáveis

const int matSize = 50;
float perforationRate = 0.3;
char validator = '0';

String matrixSend;

int data1[matSize][matSize];
int data2[matSize][matSize];
int dataSend[matSize][matSize];

ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;


void webSocketEvent(WStype_t type, uint8_t* payload, size_t length) {

  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[WSc] Disconnected!\n");
      break;
    case WStype_CONNECTED:
      {
        Serial.printf("[WSc] Connected to url: %s\n", payload);

        // send message to server when Connected
        webSocket.sendTXT("Connected");
      }
      break;
    case WStype_TEXT:
      Serial.printf("[WSc] get text: %s\n", payload);

      break;
    case WStype_BIN:
      Serial.printf("[WSc] get binary length: %u\n", length);
      hexdump(payload, length);
      break;
    case WStype_PING:
      // pong will be send automatically
      Serial.printf("[WSc] get ping\n");
      break;
    case WStype_PONG:
      // answer to a ping we send
      Serial.printf("[WSc] get pong\n");
      break;
  }
}

void setup() {
  Serial.begin(115200);
  randomSeed(30);

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] BOOT WAIT %d...\n", t);
    delay(1000);
  }

  WiFiMulti.addAP("Josi", "SOUSAcruz");

  //WiFi.disconnect();
  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.println("conectando...");
    delay(100);
  }
  Serial.println("conectado!");
  // server address, port and URL
  webSocket.begin("192.168.2.177", 8080, "/");

  // event handler
  webSocket.onEvent(webSocketEvent);

  webSocket.setReconnectInterval(5000);

  webSocket.enableHeartbeat(15000, 3000, 2);

  for (int i = 0; i < matSize; i++) {
    for (int j = 0; j < matSize; j++) {
      data1[i][j] = random(300);
    }
  }

  for (int i = 0; i < matSize; i++) {
    for (int j = 0; j < matSize; j++) {
      data2[i][j] = random(300);
    }
  }

  validator = '1';
}

void loop() {
  webSocket.loop();

  // Rotina de envio dos dados

  if (validator != '0' && webSocket.isConnected()) {

    mulMatNorm(data1, data2, dataSend);

    int timeOnMillis = millis();
    Serial.print("\n-------------------------Normal--------------------------\n");

    for (int i = 0; i < matSize; i++) {
      for (int j = 0; j < matSize; j++) {
        matrixSend += dataSend[i][j];
        matrixSend += " ";
      }

      matrixSend += "\n";

      if (i == (matSize / 2) - 1) {
        webSocket.sendTXT(matrixSend);
        matrixSend = "";
      }
    }

    timeOnMillis = millis() - timeOnMillis;
    matrixSend += "\n" + (String)timeOnMillis + "ms\n";
    webSocket.sendTXT(matrixSend);
    matrixSend = "";

    for (int i = 0; i < matSize; i++) {
      for (int j = 0; j < matSize; j++) {
        dataSend[i][j]=0;
      }
    }

    timeOnMillis = millis();
    mulMatMod(data1, data2, dataSend);

    Serial.print("--------------------------Modular---------------------------\n");
    for (int i = 0; i < matSize; i++) {
      for (int j = 0; j < matSize; j++) {
        matrixSend += dataSend[i][j];
        matrixSend += " ";
      }

      matrixSend += "\n";

      if (i == (matSize / 2) - 1) {
        webSocket.sendTXT(matrixSend);
        matrixSend = "";
      }
    }

    timeOnMillis = millis() - timeOnMillis;
    matrixSend += "\n" + (String)timeOnMillis + "ms\n";
    webSocket.sendTXT(matrixSend);
    matrixSend = "";

    for (int i = 0; i < matSize; i++) {
      for (int j = 0; j < matSize; j++) {
        dataSend[i][j]=0;
      }
    }


    timeOnMillis = millis();
    mulMatTrunc(data1, data2, dataSend);

    Serial.print("-------------------------Truncation---------------------------\n");
    for (int i = 0; i < matSize; i++) {
      for (int j = 0; j < matSize; j++) {
        matrixSend += dataSend[i][j];
        matrixSend += " ";
      }

      matrixSend += "\n";

      if (i == (matSize / 2) - 1) {
        webSocket.sendTXT(matrixSend);
        matrixSend = "";
      }
    }

    timeOnMillis = millis() - timeOnMillis;
    matrixSend += "\n" + (String)timeOnMillis + "ms\n";
    webSocket.sendTXT(matrixSend);
    matrixSend = "";

    validator = '0';

  } else if (Serial.available()) {
    validator = Serial.read();
  } else {
    validator = '0';
  }
}

void mulMatMod(int a[matSize][matSize], int b[matSize][matSize], int c[matSize][matSize]) {
  for (int i = 0; i < matSize; i += (perforationRate * 10)) {
    for (int j = 0; j < matSize; j += (perforationRate * 10)) {
      c[i][j] = 0;
      for (int k = 0; k < matSize; k += (perforationRate * 10)) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
}

void mulMatTrunc(int a[matSize][matSize], int b[matSize][matSize], int c[matSize][matSize]) {
  for (int i = 0; i < matSize - (10 * perforationRate); i++) {
    for (int j = 0; j < matSize - (10 * perforationRate); j++) {
      c[i][j] = 0;
      for (int k = 0; k < matSize - (10 * perforationRate); k++) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
}

void mulMatNorm(int a[matSize][matSize], int b[matSize][matSize], int c[matSize][matSize]) {
  for (int i = 0; i < matSize; i++) {
    for (int j = 0; j < matSize; j++) {
      c[i][j] = 0;
      for (int k = 0; k < matSize; k++) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
}

void matResult(int matReference[matSize][matSize], int matAprox[matSize][matSize], int matReturn[matSize][matSize]) {
  for (int i = 0; i < matSize; i++) {
    for (int j = 0; j < matSize; j++) {
      matReturn[i][j] = matReference[i][j] - matAprox[i][j];
    }
  }
}
