#include <ESP8266HTTPClient.h>

#include <ESP8266WiFi.h>

String inputString;
const char* ssid = "FAST3184-567C";
const char* password = "LCNTJVJV1WHQ";
const int LED_BLOQUEADO = 0;
const int LED_LIBERADO = 2;
HTTPClient http;
int areaSelecionada = -1;
int votoSelecionado = -1;

void bloquearMedidor(boolean pbBloquear){
  digitalWrite(LED_BLOQUEADO, pbBloquear);
  digitalWrite(LED_LIBERADO, !pbBloquear);
}

void limparVariaveis(){
  inputString.remove(0);
  inputString.trim();
}

void setup() {
  pinMode(LED_BLOQUEADO, OUTPUT);
  pinMode(LED_LIBERADO, OUTPUT);
  Serial.begin(115200);
  bloquearMedidor(true);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println("Conectando...");
  }
  bloquearMedidor(false);
}

void loop() {
  if (Serial.available()){
    char inChar=(char)Serial.read();
    inputString+=inChar;
    if (inChar == '&'){
      if(inputString.lastIndexOf("I") >= 0){
        carregarDadosAreas();
        delay(1000);
        limparVariaveis();
      } else if (inputString.lastIndexOf("A") >= 0) {
        areaSelecionada = inputString.substring(1).toInt();
        limparVariaveis();
      } else if (inputString.lastIndexOf("V") >= 0) {
        votoSelecionado = inputString.substring(1).toInt();
        limparVariaveis();
      }
    }
  }
  if((areaSelecionada >=0) && (votoSelecionado > 0)){
        gravarDadosVoto();
        areaSelecionada = -1;
        votoSelecionado = -1;   
  }
  delay(100);
}

void carregarDadosAreas(){
  bloquearMedidor(true);
  http.begin("http://jsonplaceholder.typicode.com/users/1");
  int httpCode = http.GET();
  String payload = http.getString();
  Serial.println(payload);
  bloquearMedidor(false);
}

void gravarDadosVoto(){
  bloquearMedidor(true);
  Serial.println("Gravando dados...");
  bloquearMedidor(false);
}
