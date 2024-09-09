#include <String.h>

void cleanMatrix();
void mulMatMod();

const int matSize = 50;
float perforationRate = 0.3;

String timeSend;

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

  int timeOnMillis = millis();

  cleanMatrix(dataSend);
  //Serial.println("modular");
  for (int cont = 0; cont <= 100; cont++) {
    mulMatMod(data1, data2, dataSend);
  }

  timeOnMillis = millis() - timeOnMillis;
  timeSend += (String)timeOnMillis + "ms\n";
  Serial.println(timeSend);
}
void loop() {
  // put your main code here, to run repeatedly:
}

void mulMatMod(int a[matSize][matSize], int b[matSize][matSize], int c[matSize][matSize]) {
  for (int i = 0; i < matSize; i += 3) {
    for (int j = 0; j < matSize; j += 3) {
      c[i][j] = 0;
      for (int k = 0; k < matSize; k += 3) {
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