String inputString;

void setup() {
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  Serial.begin(115200);
  digitalWrite(D4, HIGH);
}

void loop() {
  if (Serial.available()){
    char inChar=(char)Serial.read();
    inputString+=inChar;
    if (inChar == '\n'){
      Serial.println("entrou");
      if(inputString.lastIndexOf("init") >= 0){
        digitalWrite(D4, LOW);
        digitalWrite(D3, HIGH);
        carregarDadosAreas();
        delay(1000);
        digitalWrite(D4, HIGH);
        digitalWrite(D3, LOW);
        inputString.remove(0);
        inputString.trim();
      } else if (inputString.lastIndexOf("gravar") >= 0) {
        digitalWrite(D4, LOW);
        digitalWrite(D3, HIGH);
        gravarDadosVoto();
        delay(1000);
        digitalWrite(D4, HIGH);
        digitalWrite(D3, LOW);
        inputString.remove(0);
        inputString.trim();
      }
    }
  }
  delay(100);
}

void carregarDadosAreas(){
  Serial.println("Lendo dados");
}

void gravarDadosVoto(){
  Serial.println("Gravando dados...");
}
