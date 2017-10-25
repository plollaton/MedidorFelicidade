#include <LCD5110_Basic.h>

 /*Cria objeto da classe LCD5110
 CLK – Pino 9
 DIN – Pino 8
 DC – Pino 7
 RST – Pino 5
 CE – Pino 6        
 */
LCD5110 tela(9,8,7,5,6);

//Obtendo as fontes
extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];
int area = 0;
int numAreas=8;
int AREACIMA = 2;
int AREABAIXO = 3;
int BTN_VOTE_1 = A1;
int BTN_VOTE_2 = A2;
int BTN_VOTE_3 = A3;
int BTN_VOTE_4 = A4;
int BTN_VOTE_5 = A5;
bool should_write = true;



char *areas[] = {"Anymarket", "Consignet", "Holding", "IT Services", "TechGov", "Edig", "Gestao Emp.", "Gileade"};
 
void setup() {
  tela.InitLCD();
  tela.setFont(SmallFont);
  pinMode(AREACIMA, INPUT_PULLUP);
  pinMode(AREABAIXO, INPUT_PULLUP);
  pinMode(BTN_VOTE_1, INPUT_PULLUP);
  pinMode(BTN_VOTE_2, INPUT_PULLUP);
  pinMode(BTN_VOTE_3, INPUT_PULLUP);
  pinMode(BTN_VOTE_4, INPUT_PULLUP);
  pinMode(BTN_VOTE_5, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  montarMenu();
  handleUp();
  handleDown();
/*  handleVoteButton(BTN_VOTE_1, 1);
  handleVoteButton(BTN_VOTE_2, 2);
  handleVoteButton(BTN_VOTE_3, 3);
  handleVoteButton(BTN_VOTE_4, 4);
  handleVoteButton(BTN_VOTE_5, 5);*/
}

void handleVoteButton(int btn, int value) {
  if (digitalRead(btn) == LOW) {
    Serial.print("Area = ");
    Serial.println(areas[area]);
    Serial.print("Voto = ");
    Serial.println(value);
    Serial.println("***DEBUG***");
    Serial.print("idArea: ");
    Serial.println(area);

    int nLinha = area + 1;
    if(nLinha >= 6){
      nLinha = 5;
    }
    tela.clrRow(nLinha);
    Serial.print("nLinha: ");
    Serial.println(nLinha);
    Serial.println("***END DEBUG***");
    Serial.println("");
    area = 0;

    delay(5000);
  }
}

void handleUp() {
  if(!digitalRead(AREACIMA)){
    area++;
    while(digitalRead(AREACIMA) == LOW){
    }
    tela.clrRow(area);
    if(area > 6){
      tela.clrRow(5);
      area = 0;
    }
    should_write = true;
  }
}

void handleDown() {
  if(!digitalRead(AREABAIXO)){
    area--;
    while(digitalRead(AREABAIXO) == LOW){
    }
    if(area < 0){
       tela.clrRow(area - 1);
       area = 6;
    } else {
      tela.clrRow(area+ 2);
    }
    should_write = true;
  }
}

void montarMenu(){
  if (!should_write) {
    return;
  }
  
  tela.clrScr();
  tela.print("Selecione:", 0, 0);  

  int pos = 9;
  for(int i=0; i<numAreas; i++){
    
    if((area-i) > 4){
      continue;
    }
    
    if(i==area){
      tela.print("<", 0, pos);
      tela.print(areas[i], 7,pos);
      tela.print(">", 7 + (6 * strlen(areas[i])), pos);
    } else {
      tela.print(areas[i], 0, pos);
    }
    pos = pos + 9;
  }
  should_write = false;
}     
