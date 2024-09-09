#include <String.h>

void cleanMatrix();
void mulMatMod();
void mulMatTrunc();
void mulMatNorm();

const int matSize = 50;
int perforationRate = (0.3) * 10;


String matrixSend;

int data1[matSize][matSize];
int data2[matSize][matSize];
int dataSend[matSize][matSize];

void setup() {

  pinMode(D4, OUTPUT);
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
//normal
  cleanMatrix(dataSend);
  digitalWrite(D4, 1);
  mulMatNorm(data1, data2, dataSend);
   digitalWrite(D4, 0);
   delay(200);
//normal

//mod
  cleanMatrix(dataSend);
  digitalWrite(D4, 1);
  mulMatMod(data1, data2, dataSend);
  digitalWrite(D4, 0);
  delay(200);
//mod

//trunc
  cleanMatrix(dataSend);
  digitalWrite(D4, 1);
  mulMatTrunc(data1, data2, dataSend);
  digitalWrite(D4, 0);
  delay(200);
//trunc
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
