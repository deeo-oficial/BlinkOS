#include <EEPROM.h>

const int DISK_SIZE = 1024;
String inputString = "";
bool authenticated = false;
const String ADMIN_PASS = "2112"; // Defina sua senha aqui

// Registradores virtuais para o compilador ASM
int RA = 0; 
int RB = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial); 
  delay(500);
  cls();
  login();
}

void login() {
  Serial.println("--- BlinkOS SECURITY SYSTEM ---");
  while(!authenticated) {
    Serial.print("Password: ");
    String pass = readLine();
    if(pass == ADMIN_PASS) {
      authenticated = true;
      cls();
      printHeader();
    } else {
      Serial.println("Access Denied.");
    }
  }
}

// Funcao robusta de leitura com ECHO corrigido
String readLine() {
  String line = "";
  while (true) {
    if (Serial.available() > 0) {
      char c = Serial.read();
      if (c == '\n' || c == '\r') { 
        Serial.println(); 
        break;
      }
      line += c;
      Serial.print(c); // ECHO REAL-TIME
    }
  }
  line.trim();
  return line;
}

void loop() {
  Serial.print("BlinkOS:> ");
  inputString = readLine();
  
  if (inputString.length() > 0) {
    processCommand(inputString);
  }
}

void printHeader() {
  Serial.println("########################################");
  Serial.println("#           BlinkOS v1.0.2             #");
  Serial.println("#              By DEEO                 #");
  Serial.println("########################################");
  Serial.println("Type 'help' for commands.\n");
}

void cls() {
  Serial.print("\033[2J");
  Serial.print("\033[H");
}

void processCommand(String cmd) {
  cmd.toLowerCase();

  if (cmd == "help") {
    Serial.println("Commands: CALC, ASM, EDIT, TYPE, DEL, FREE, CLS, LOGOUT");
  } 
  else if (cmd == "calc") {
    runSmartCalc();
  }
  else if (cmd == "asm") {
    runAsmCompiler();
  }
  else if (cmd == "edit") {
    saveToDisk();
  }
  else if (cmd == "type") {
    readFromDisk();
  }
  else if (cmd == "logout") {
    authenticated = false;
    cls();
    login();
  }
  else if (cmd == "free") {
    showSysInfo();
  }
  else {
    Serial.println("Unknown command.");
  }
}

void runSmartCalc() {
  Serial.println("\n[MATH] Expression (Ex: 15*3):");
  String exp = readLine();

  float n1, n2, res;
  char op = ' ';
  int opPos = -1;
  char operators[] = {'+', '-', '*', '/'};

  for(int i=0; i<4; i++) {
    opPos = exp.indexOf(operators[i]);
    if(opPos != -1) {
      op = operators[i];
      n1 = exp.substring(0, opPos).toFloat();
      n2 = exp.substring(opPos + 1).toFloat();
      break;
    }
  }

  if (op != ' ') {
    if (op == '+') res = n1 + n2;
    else if (op == '-') res = n1 - n2;
    else if (op == '*') res = n1 * n2;
    else if (op == '/') res = (n2 != 0) ? n1 / n2 : 0;
    Serial.print(">> Result: "); Serial.println(res);
  } else {
    Serial.println("Error: Use [N][OP][N]");
  }
}

void runAsmCompiler() {
  Serial.println("\n--- BlinkOS ASM COMPILER v1.0 ---");
  Serial.println("Supported: MOV RA,val | ADD RA,RB | SUB RA,val | SHOW");
  Serial.println("Type 'EXIT' to return.");
  
  while(true) {
    Serial.print("ASM_SRC> ");
    String code = readLine();
    code.toUpperCase();
    
    if(code == "EXIT") break;
    if(code == "SHOW") {
      Serial.print("RA: "); Serial.print(RA); Serial.print(" | RB: "); Serial.println(RB);
      continue;
    }

    // Lógica básica de "compilação" e execução
    if(code.startsWith("MOV RA,")) RA = code.substring(7).toInt();
    else if(code.startsWith("MOV RB,")) RB = code.substring(7).toInt();
    else if(code == "ADD RA,RB") RA = RA + RB;
    else if(code.startsWith("SUB RA,")) RA = RA - code.substring(7).toInt();
    else Serial.println("Syntax Error in ASM.");
  }
}

void saveToDisk() {
  Serial.println("\n[EDITOR] Write note:");
  String text = readLine();
  if (text.length() >= DISK_SIZE) Serial.println("Disk full.");
  else {
    for (int i = 0; i < text.length(); i++) EEPROM.write(i, text[i]);
    EEPROM.write(text.length(), '\0');
    Serial.println("Saved.");
  }
}

void readFromDisk() {
  if (EEPROM.read(0) == '\0') { Serial.println("Empty."); return; }
  Serial.print("Data: ");
  for (int i = 0; i < DISK_SIZE; i++) {
    char c = EEPROM.read(i);
    if (c == '\0') break;
    Serial.print(c);
  }
  Serial.println();
}

void showSysInfo() {
  extern int __heap_start, *__brkval;
  int v;
  int freeRam = (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
  Serial.print("RAM: "); Serial.print(freeRam); Serial.println(" bytes free");
}
