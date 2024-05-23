#include <String.h>

void cleanMatrix();
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
  Serial.println("normal");
  digitalWrite(D4, 1);
  for (int cont = 0; cont <= 100; cont++) {
    mulMatNorm(data1, data2, dataSend);
  }
  digitalWrite(D4, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
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
