void mulMatMod();
void mulMatTrunc();
void mulMatNorm();
const int matSize=30;
float perforationRate = 0.3;

int data1[matSize][matSize];
int data2[matSize][matSize];
int dataNorm[matSize][matSize], somaNorm;
int dataMod[matSize][matSize], somaMod;
int dataTrunc[matSize][matSize], somaTrunc;

void setup() {
  Serial.begin(9600);
  randomSeed(30);

  

  for(int i=0;i<matSize;i++){
    for(int j=0;j<matSize;j++){
      data1[i][j]=random(300);
    }
  }

  for(int i=0;i<matSize;i++){
    for(int j=0;j<matSize;j++){
      data2[i][j]=random(300);
    }
  }

  mulMatNorm(data1, data2, dataNorm);
  mulMatMod(data1, data2, dataMod);
  mulMatTrunc(data1, data2, dataTrunc);
 
  Serial.println("Teste de Loop Perforation");
  int timeOnMillis=millis();
  Serial.print("\n-------------------------Normal--------------------------\n");
  for (int i = 0; i < matSize; i++) {
    for (int j = 0; j < matSize; j++) {
      somaNorm+=dataNorm[i][j];
      Serial.print(dataNorm[i][j]);
      Serial.print(" ");
    }
    Serial.println("");
  }
  timeOnMillis=millis()-timeOnMillis;
  Serial.println();
  Serial.print("Tempo usado para calcular Matriz: "+(String)timeOnMillis+"ms\n");
  Serial.println();

  timeOnMillis=millis();
  
  Serial.print("--------------------------Modular---------------------------\n");
  for (int i = 0; i < matSize; i++) {
    for (int j = 0; j < matSize; j++) {
        somaMod+=dataMod[i][j];
      Serial.print(dataMod[i][j]);
      Serial.print(" ");
    }
    Serial.println("");
  }

  timeOnMillis=millis()-timeOnMillis;
  Serial.println();
  Serial.print("Tempo usado para calcular Matriz: "+(String)timeOnMillis+"ms\n");
  Serial.println();
  timeOnMillis=millis();
  Serial.print("-------------------------Truncation---------------------------\n");
  for (int i = 0; i < matSize; i++) {
    for (int j = 0; j < matSize; j++) {
      somaTrunc+=dataTrunc[i][j];
      Serial.print(dataTrunc[i][j]);
      Serial.print(" ");
    }
    Serial.println("");
  }

  timeOnMillis=millis()-timeOnMillis;
  Serial.println();
  Serial.print("Tempo usado para calcular Matriz: "+(String)timeOnMillis+"ms\n");
  //Serial.println();
  /*
  Serial.print("\nSoma do normal: "+(String)somaNorm+"\n");
  Serial.print("Soma do Modular: "+(String)somaMod+"\n");
  Serial.print("Soma do Truncation: "+(String)somaTrunc+"\n");

  */
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

void matResult(int matReference[matSize][matSize], int matAprox[matSize][matSize], int matReturn[matSize][matSize]){
    for (int i = 0; i < matSize; i++) {
      for (int j = 0; j < matSize; j++) {
        //c[i][j] = 0;
        matReturn[i][j]=matReference[i][j]-matAprox[i][j];
    }
  }
}
