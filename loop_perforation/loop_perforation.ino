#include <String.h>

void cleanMatrix();
void mulMatMod();
void mulMatTrunc();
void mulMatNorm();

const int matSize = 50;
float perforationRate = 0.3;

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


  cleanMatrix(dataSend);
  digitalWrite(D4, 1);
  mulMatNorm(data1, data2, dataSend);
  digitalWrite(D4, 0);

  int timeOnMillis = millis();
  Serial.print("\n-------------------------Normal--------------------------\n");
  for (int i = 0; i < matSize; i++) {
    for (int j = 0; j < matSize; j++) {
      matrixSend += dataSend[i][j];
      matrixSend += " ";
    }
    matrixSend += "\n";
  }
  timeOnMillis = millis() - timeOnMillis;
  matrixSend += (String)timeOnMillis + "ms\n";

  timeOnMillis = millis();

  cleanMatrix(dataSend);
  digitalWrite(D4, 1);
  mulMatMod(data1, data2, dataSend);
  digitalWrite(D4, 0);

  Serial.print("--------------------------Modular---------------------------\n");
  for (int i = 0; i < matSize; i++) {
    for (int j = 0; j < matSize; j++) {
      matrixSend += dataSend[i][j];
      matrixSend += " ";
    }
    matrixSend += "\n";
  }

  timeOnMillis = millis() - timeOnMillis;
  matrixSend += (String)timeOnMillis + "ms\n";
  timeOnMillis = millis();

  cleanMatrix(dataSend);
  digitalWrite(D4, 1);
  mulMatTrunc(data1, data2, dataSend);
  digitalWrite(D4, 0);

  Serial.print("-------------------------Truncation---------------------------\n");
  for (int i = 0; i < matSize; i++) {
    for (int j = 0; j < matSize; j++) {
      matrixSend += dataSend[i][j];
      matrixSend += " ";
    }
    matrixSend += "\n";
  }

  timeOnMillis = millis() - timeOnMillis;
  Serial.println();
  matrixSend += (String)timeOnMillis + "ms\n";


}


void loop() {


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

void cleanMatrix(int value[matSize][matSize]) {
  for (int i = 0; i < matSize; i++) {
    for (int j = 0; j < matSize; j++) {
      value[i][j] = 0;
    }
  }
}
