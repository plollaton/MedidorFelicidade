#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

String inputString;
const char* ssid = "GVT9865";
const char* password = "12345678";
const int LED_BLOQUEADO = 0;
const int LED_LIBERADO = 2;
HTTPClient http;
int areaSelecionada = -1;
int votoSelecionado = -1;
bool bBloqueado;

void bloquearMedidor(boolean pbBloquear){
  digitalWrite(LED_BLOQUEADO, pbBloquear);
  digitalWrite(LED_LIBERADO, !pbBloquear);
  String b;
  b+='B';
  b+=pbBloquear;
  b+='\n';
  Serial.write(b.c_str());
  bBloqueado = pbBloquear;
}

void limparVariaveis(){
  inputString.remove(0);
  inputString.trim();
}

void setup() {
  pinMode(LED_BLOQUEADO, OUTPUT);
  pinMode(LED_LIBERADO, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  bloquearMedidor(true);
  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
  }
  bloquearMedidor(false); 
}

void loop() {
  if (Serial.available()){
    digitalWrite(LED_BLOQUEADO, HIGH);
    char inChar=(char)Serial.read();
    inputString+=inChar;
    Serial.println(inputString);
    if (inChar == '$'){
      if (inputString.lastIndexOf("A") >= 0) {
        areaSelecionada = inputString.substring(1,2).toInt();
      } else if (inputString.lastIndexOf("V") >= 0) {
        votoSelecionado = inputString.substring(1,2).toInt();
      } else if (inputString.lastIndexOf("S")>=0){
        retornarStatusConexaoWiFi();
      } 
      else {
        digitalWrite(LED_BLOQUEADO, HIGH);
      }
      limparVariaveis();      
    }
  } 
  else{
    limparVariaveis(); 
  }
  if((areaSelecionada >=0) && (votoSelecionado > 0)){
        gravarDadosVoto();
        areaSelecionada = -1;
        votoSelecionado = -1;   
  }
  delay(100);
}

void retornarStatusConexaoWiFi(){
  Serial.write(WiFi.status());
  Serial.println(WiFi.status());
}

void gravarDadosVoto(){
  bloquearMedidor(true);

 
 
   http.begin("http://demo8844204.mockable.io/voto");      //Specify request destination
   http.addHeader("Content-Type", "app/json");  //Specify content-type header
 
   int httpCode = http.POST("{"area":1,"voto":2}");   //Send the request
   String payload = http.getString();                  //Get the response payload
 
   Serial.println(httpCode);   //Print HTTP return code
   Serial.println(payload);    //Print request response payload
 
   http.end();
   
  
  Serial.println("Gravando dados...");
  bloquearMedidor(false);
}
