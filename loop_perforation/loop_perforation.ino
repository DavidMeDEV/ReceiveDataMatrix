#include <String.h>

void cleanMatrix();
void mulMatMod();
void mulMatTrunc();
void mulMatNorm();

const int matSize = 50;
int perforationRate = (0.3) * 10;
;

String matrixSend;

int data1[matSize][matSize];
int data2[matSize][matSize];
int dataSend[matSize][matSize];

void setup() {

  pinMode(D4, OUTPUT);
  digitalWrite(D4, 1);
  Serial.begin(9600);
  randomSeed(30);

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
}


void loop() {
  int timeOnMillis = millis();

  cleanMatrix(dataSend);
  mulMatNorm(data1, data2, dataSend);

  Serial.print("inicio");
  Serial.println();
  Serial.print("\n-------------------------Normal--------------------------\n");
  Serial.println();
  for (int i = 0; i < matSize; i++) {
    for (int j = 0; j < matSize; j++) {
      Serial.print(dataSend[i][j]);
      Serial.print(";");
    }
    Serial.println();
  }


  timeOnMillis = millis() - timeOnMillis;
  matrixSend += (String)timeOnMillis + "ms\n";

  timeOnMillis = millis();

  Serial.println();
  cleanMatrix(dataSend);
  mulMatMod(data1, data2, dataSend);
  Serial.println();
  Serial.print("--------------------------Modular---------------------------\n");
  Serial.println();
  for (int i = 0; i < matSize; i++) {
    for (int j = 0; j < matSize; j++) {
      Serial.print(dataSend[i][j]);
      Serial.print(";");
    }
    Serial.println();
  }

  timeOnMillis = millis() - timeOnMillis;
  matrixSend += (String)timeOnMillis + "ms\n";
  timeOnMillis = millis();

  cleanMatrix(dataSend);
  mulMatTrunc(data1, data2, dataSend);

  // Serial.print("inicio");
  Serial.println();
  Serial.println();
  Serial.print("-------------------------Truncation---------------------------\n");
  Serial.println();
  for (int i = 0; i < matSize; i++) {
    for (int j = 0; j < matSize; j++) {
      Serial.print(dataSend[i][j]);
      Serial.print(";");
    }
    Serial.println();
  }

  Serial.print("fim");

  timeOnMillis = millis() - timeOnMillis;
  Serial.println();
  matrixSend += (String)timeOnMillis + "ms\n";

  delay(2000);
}

void mulMatMod(int a[matSize][matSize], int b[matSize][matSize], int c[matSize][matSize]) {
  for (int i = 0; i < matSize; i++) {
    for (int j = 0; j < matSize; j += perforationRate) {
      c[i][j] = 0;
      for (int k = 0; k < matSize; k++) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
}

void mulMatTrunc(int a[matSize][matSize], int b[matSize][matSize], int c[matSize][matSize]) {
  for (int i = 0; i < matSize - perforationRate; i++) {
    for (int j = 0; j < matSize - perforationRate; j++) {
      c[i][j] = 0;
      for (int k = 0; k < matSize; k++) {
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

void cleanMatrix(int value[matSize][matSize]) {
  for (int i = 0; i < matSize; i++) {
    for (int j = 0; j < matSize; j++) {
      value[i][j] = 0;
    }
  }
}
