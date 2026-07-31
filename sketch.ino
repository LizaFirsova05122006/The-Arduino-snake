#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define width 128
#define height 64
#define oled_addr 0x3C
#define joy_x 33
#define joy_y 32
#define joy_btn 15
Adafruit_SSD1306 display(width, height, &Wire);

// БУКВЫ и ЗНАКИ
const uint8_t letter_1[8] PROGMEM = {8, 24, 8, 8, 8, 8, 28, 0}; // 1
const uint8_t letter_2[8] PROGMEM = {28, 34, 2, 4, 8, 16, 62, 0}; // 2
const uint8_t letter_3[8] PROGMEM = {60, 66, 2, 28, 2, 66, 60, 0}; // 3
const uint8_t letter_4[8] PROGMEM = {12, 20, 36, 126, 4, 4, 4, 0}; // 4
const uint8_t letter_5[8] PROGMEM = {126, 64, 124, 2, 2, 66, 60, 0}; // 5
const uint8_t letter_6[8] PROGMEM = {60, 66, 64, 124, 66, 66, 60, 0}; // 6
const uint8_t letter_7[8] PROGMEM = {126, 2, 4, 8, 8, 8, 8, 0}; // 7
const uint8_t letter_8[8] PROGMEM = {60, 66, 66, 60, 66, 66, 60, 0}; // 8
const uint8_t letter_9[8] PROGMEM = {60, 66, 66, 62, 2, 66, 60, 0}; // 9
const uint8_t letter_0[8] PROGMEM = {60, 66, 66, 66, 66, 66, 60, 0}; // 0
const uint8_t letter_DV[8] PROGMEM = {0, 24, 24, 0, 24, 24, 0, 0}; // :
const uint8_t letter_VO[8] PROGMEM = {24, 24, 24, 24, 0, 24, 24, 0}; // !
const uint8_t letter_A[8] PROGMEM = {24, 36, 66, 126, 66, 66, 66, 0}; // A
const uint8_t letter_B[8] PROGMEM = {126, 64, 64, 124, 66, 66, 124, 0}; // Б
const uint8_t letter_V[8] PROGMEM = {124, 66, 66, 124, 66, 66, 124, 0}; // B
const uint8_t letter_G[8] PROGMEM = {126, 64, 64, 64, 64, 64, 64, 0}; // Г
const uint8_t letter_D[8] PROGMEM = {28, 36, 68, 68, 68, 126, 66, 0}; // Д
const uint8_t letter_E[8] PROGMEM = {126, 64, 64, 126, 64, 64, 126, 0}; // E
const uint8_t letter_Zh[8] PROGMEM = {90, 90, 60, 24, 60, 90, 90, 0}; // Ж
const uint8_t letter_Z[8] PROGMEM = {60, 66, 2, 4, 2, 66, 60, 0}; // З
const uint8_t letter_I[8] PROGMEM = {64, 70, 70, 74, 82, 98, 98, 0}; // И
const uint8_t letter_II[8] PROGMEM = {36, 24, 70, 74, 82, 98, 66, 0}; // Й
const uint8_t letter_K[8] PROGMEM = {66, 68, 72, 112, 72, 68, 66, 0}; // K
const uint8_t letter_L[8] PROGMEM = {30, 34, 66, 66, 66, 66, 66, 0}; // Л
const uint8_t letter_M[8] PROGMEM = {66, 102, 90, 90, 66, 66, 66, 0}; // М
const uint8_t letter_N[8] PROGMEM = {66, 66, 66, 126, 66, 66, 66, 0}; // Н
const uint8_t letter_O[8] PROGMEM = {60, 66, 66, 66, 66, 66, 60, 0}; // O
const uint8_t letter_P[8] PROGMEM = {126, 66, 66, 66, 66, 66, 66, 0}; // П
const uint8_t letter_R[8] PROGMEM = {124, 66, 66, 124, 64, 64, 64, 0}; // Р
const uint8_t letter_S[8] PROGMEM = {62, 64, 64, 64, 64, 64, 62, 0}; // C
const uint8_t letter_T[8] PROGMEM = {126, 126, 24, 24, 24, 24, 24, 0}; // T
const uint8_t letter_F[8] PROGMEM = {60, 90, 90, 90, 90, 60, 24, 0}; // Ф
const uint8_t letter_Ch[8] PROGMEM = {66, 66, 66, 124, 2, 2, 2, 0}; // Ч
const uint8_t letter_Sh[8] PROGMEM = {66, 66, 66, 90, 90, 90, 124, 0}; // Ш
const uint8_t letter_VV[8] PROGMEM = {66, 66, 66, 66, 114, 74, 114, 0}; // Ы
const uint8_t letter_U[8] PROGMEM = {76, 82, 82, 114, 82, 82, 76, 0}; // Ю

int dtX = 64;
int dtY = 32;
enum GameState {
  SPLASH,
  MENU,
  PLAY,
  PLAY_EASY,
  PLAY_NORMAL,
  PLAY_HARD,
  OVER
};
GameState state = SPLASH;
int select_level = 0;
int current_level = -1;
unsigned long last_menu = 0;
const int meny_delay = 200;
// ИГРОВЫЕ ПЕРЕМЕННЫЕ
const int size = 4;
const int grid_w = 32;
const int grid_h = 13;
const int total = grid_w * grid_h;
int snakeX[416], snakeY[416];
int snake_len = 3;
int food_x, food_y;
int dX = 1, dY = 0;
unsigned long last_move = 0;
int score = 0;
int easy_pobeda = 25; // 100
bool smert = false;
int normal_pobeda = 100;
int hard_pobeda = 200;
const int speed_hard = 300;
struct Fruit {
  int x, y;
  int type;
  bool bad;
};
Fruit fruits[4];
int f_count = 0;
int bf_count = 0;
int spawn_count = 0;

void setup() {
  //Serial.begin(115200);
  pinMode(joy_btn, INPUT_PULLUP);
  if (!display.begin(SSD1306_SWITCHCAPVCC, oled_addr)) {
    return;
    //Serial.println("Ошибка дисплея!");
  }
  //Serial.println("Все готово!");
  drawSplash();
}

void loop() {
  switch (state) {
    case SPLASH:
      handleSplash();
      break;
    case MENU:
      handleMenu();
      break;
    case PLAY:
      handlePlay();
      break;
    case PLAY_EASY:
      handlePlayEasy();
      break;
    case PLAY_NORMAL:
      handlePlayNormal();
      break;
    case PLAY_HARD:
      handlePlayHard();
      break;
    case OVER:
      handleOver();
      break;
  }
  delay(10);
}

// ЗАСТАВКА
void drawSplash() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  //display.setCursor(0, 0);
  display.drawBitmap(20, 0, letter_I, 8, 8, SSD1306_WHITE);
  display.drawBitmap(28, 0, letter_G, 8, 8, SSD1306_WHITE);
  display.drawBitmap(36, 0, letter_R, 8, 8, SSD1306_WHITE);
  display.drawBitmap(44, 0, letter_A, 8, 8, SSD1306_WHITE);
  display.drawBitmap(60, 0, letter_Z, 8, 8, SSD1306_WHITE);
  display.drawBitmap(68, 0, letter_M, 8, 8, SSD1306_WHITE);
  display.drawBitmap(76, 0, letter_E, 8, 8, SSD1306_WHITE);
  display.drawBitmap(84, 0, letter_II, 8, 8, SSD1306_WHITE);
  display.drawBitmap(92, 0, letter_K, 8, 8, SSD1306_WHITE);
  display.drawBitmap(100, 0, letter_A, 8, 8, SSD1306_WHITE);
  display.drawBitmap(40, 16, letter_A, 8, 8, SSD1306_WHITE);
  display.drawBitmap(48, 16, letter_V, 8, 8, SSD1306_WHITE);
  display.drawBitmap(56, 16, letter_T, 8, 8, SSD1306_WHITE);
  display.drawBitmap(64, 16, letter_O, 8, 8, SSD1306_WHITE);
  display.drawBitmap(72, 16, letter_R, 8, 8, SSD1306_WHITE);
  display.drawBitmap(80, 16, letter_DV, 8, 8, SSD1306_WHITE);
  display.drawBitmap(36, 32, letter_F, 8, 8, SSD1306_WHITE);
  display.drawBitmap(44, 32, letter_I, 8, 8, SSD1306_WHITE);
  display.drawBitmap(52, 32, letter_R, 8, 8, SSD1306_WHITE);
  display.drawBitmap(60, 32, letter_S, 8, 8, SSD1306_WHITE);
  display.drawBitmap(68, 32, letter_O, 8, 8, SSD1306_WHITE);
  display.drawBitmap(76, 32, letter_V, 8, 8, SSD1306_WHITE);
  display.drawBitmap(84, 32, letter_A, 8, 8, SSD1306_WHITE);
  display.drawBitmap(28, 40, letter_E, 8, 8, SSD1306_WHITE);
  display.drawBitmap(36, 40, letter_L, 8, 8, SSD1306_WHITE);
  display.drawBitmap(44, 40, letter_I, 8, 8, SSD1306_WHITE);
  display.drawBitmap(52, 40, letter_Z, 8, 8, SSD1306_WHITE);
  display.drawBitmap(60, 40, letter_A, 8, 8, SSD1306_WHITE);
  display.drawBitmap(68, 40, letter_V, 8, 8, SSD1306_WHITE);
  display.drawBitmap(76, 40, letter_E, 8, 8, SSD1306_WHITE);
  display.drawBitmap(84, 40, letter_T, 8, 8, SSD1306_WHITE);
  display.drawBitmap(92, 40, letter_A, 8, 8, SSD1306_WHITE);
  display.drawBitmap(24, 48, letter_D, 8, 8, SSD1306_WHITE);
  display.drawBitmap(32, 48, letter_M, 8, 8, SSD1306_WHITE);
  display.drawBitmap(40, 48, letter_I, 8, 8, SSD1306_WHITE);
  display.drawBitmap(48, 48, letter_T, 8, 8, SSD1306_WHITE);
  display.drawBitmap(56, 48, letter_R, 8, 8, SSD1306_WHITE);
  display.drawBitmap(64, 48, letter_I, 8, 8, SSD1306_WHITE);
  display.drawBitmap(72, 48, letter_E, 8, 8, SSD1306_WHITE);
  display.drawBitmap(80, 48, letter_V, 8, 8, SSD1306_WHITE);
  display.drawBitmap(88, 48, letter_N, 8, 8, SSD1306_WHITE);
  display.drawBitmap(96, 48, letter_A, 8, 8, SSD1306_WHITE);
  //display.println("Игра Змейка");
  display.display();
}

void handleSplash() {
  if (digitalRead(joy_btn) == LOW) {
    delay(200);                   
    last_menu = millis();         
    state = MENU;
    drawMenu();
  }
}

// МЕНЮ
void handleMenu() {
  int y = analogRead(joy_y);
  bool btn = digitalRead(joy_btn);
  if (millis() - last_menu > meny_delay) {
    if (y < 1200 && select_level < 2) {   
      select_level++;
      last_menu = millis();
      drawMenu();
    }
    else if (y > 2800 && select_level > 0) { 
      select_level--;
      last_menu = millis();
      drawMenu();
    }
  }
  
  if (btn == LOW) {
    delay(200);
    current_level = select_level;
    state = PLAY;
  }
}

void drawMenu() {
  display.clearDisplay();
  display.drawBitmap(48, 0, letter_M, 8, 8, SSD1306_WHITE);
  display.drawBitmap(56, 0, letter_E, 8, 8, SSD1306_WHITE);
  display.drawBitmap(64, 0, letter_N, 8, 8, SSD1306_WHITE);
  display.drawBitmap(72, 0, letter_U, 8, 8, SSD1306_WHITE);
  if (select_level == 0) display.drawRect(0, 10, 128, 18, SSD1306_WHITE);
  else if (select_level == 1) display.drawRect(0, 28, 128, 18, SSD1306_WHITE);
  else if (select_level == 2) display.drawRect(0, 46, 128, 18, SSD1306_WHITE);
  // Легкий
  display.drawBitmap(40, 12, letter_L, 8, 8, SSD1306_WHITE);
  display.drawBitmap(48, 12, letter_E, 8, 8, SSD1306_WHITE);
  display.drawBitmap(56, 12, letter_G, 8, 8, SSD1306_WHITE);
  display.drawBitmap(64, 12, letter_K, 8, 8, SSD1306_WHITE);
  display.drawBitmap(72, 12, letter_I, 8, 8, SSD1306_WHITE);
  display.drawBitmap(80, 12, letter_II, 8, 8, SSD1306_WHITE);
  // Средний
  display.drawBitmap(36, 30, letter_S, 8, 8, SSD1306_WHITE);
  display.drawBitmap(44, 30, letter_R, 8, 8, SSD1306_WHITE);
  display.drawBitmap(52, 30, letter_E, 8, 8, SSD1306_WHITE);
  display.drawBitmap(60, 30, letter_D, 8, 8, SSD1306_WHITE);
  display.drawBitmap(68, 30, letter_N, 8, 8, SSD1306_WHITE);
  display.drawBitmap(76, 30, letter_I, 8, 8, SSD1306_WHITE);
  display.drawBitmap(84, 30, letter_II, 8, 8, SSD1306_WHITE);
  // Сложный
  display.drawBitmap(36, 48, letter_S, 8, 8, SSD1306_WHITE);
  display.drawBitmap(44, 48, letter_L, 8, 8, SSD1306_WHITE);
  display.drawBitmap(52, 48, letter_O, 8, 8, SSD1306_WHITE);
  display.drawBitmap(60, 48, letter_Zh, 8, 8, SSD1306_WHITE);
  display.drawBitmap(68, 48, letter_N, 8, 8, SSD1306_WHITE);
  display.drawBitmap(76, 48, letter_VV, 8, 8, SSD1306_WHITE);
  display.drawBitmap(84, 48, letter_II, 8, 8, SSD1306_WHITE);
  display.display();
}

// ИГРА
void handlePlay() {
  if (current_level == 0) {
    state = PLAY_EASY;
    startLevelEasy();
  }
  else if (current_level == 1) {
    state = PLAY_NORMAL;
    startLevelNormal();
  }
  else if (current_level == 2) {
    state = PLAY_HARD;
    startLevelHard();
  }
}

// ЛЕГКИЙ УРОВЕНЬ
void startLevelEasy() {
  snake_len = 3;
  score = 0;
  dX = 1;
  dY = 0;
  
  for (int i = 0; i < snake_len; i++) {
    snakeX[i] = grid_w / 2 - i;
    snakeY[i] = grid_h / 2;
  }
  
  spawnFood();
  last_move = millis();
  drawGame();
}

void handlePlayEasy() {
  int x = analogRead(joy_x);
  int y = analogRead(joy_y);
  int newX = 0, newY = 0;
  if (x < 1200)      { newX = 1; newY = 0; }  // ВЛЕВО
  else if (x > 2800) { newX = -1;  newY = 0; }  // ВПРАВО
  else if (y < 1200) { newX = 0;  newY = 1; } // ВВЕРХ
  else if (y > 2800) { newX = 0;  newY = -1; }  // ВНИЗ
  else return; 
  if (newX == -dX && newY == -dY) return;
  dX = newX;
  dY = newY;
  for (int i = snake_len; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }
  snakeX[0] += dX;
  snakeY[0] += dY;
  if (snakeX[0] < 0)        snakeX[0] = grid_w - 1;
  else if (snakeX[0] >= grid_w) snakeX[0] = 0;
  if (snakeY[0] < 0)        snakeY[0] = grid_h - 1;
  else if (snakeY[0] >= grid_h) snakeY[0] = 0;
  if (snakeX[0] == food_x && snakeY[0] == food_y) {
    snake_len++;
    score += 5;
    if (score >= easy_pobeda) {
      state = OVER;
      return;
    }
    spawnFood();
  }
  
  drawGame();
  delay(150);
  while (analogRead(joy_x) < 1200 || analogRead(joy_x) > 2800 ||
         analogRead(joy_y) < 1200 || analogRead(joy_y) > 2800) {
    delay(10);
  }
  delay(50);
}

void spawnFood() {
  bool onSnake;
  do {
    onSnake = false;
    food_x = random(0, grid_w);
    food_y = random(0, grid_h);
    for (int i = 0; i < snake_len; i++) {
      if (snakeX[i] == food_x && snakeY[i] == food_y) {
        onSnake = true;
        break;
      }
    }
  } while (onSnake);
}

void drawGame() {
  display.clearDisplay();
  display.drawBitmap(0, 0, letter_O, 8, 8, SSD1306_WHITE);
  display.drawBitmap(8, 0, letter_Ch, 8, 8, SSD1306_WHITE);
  display.drawBitmap(16, 0, letter_K, 8, 8, SSD1306_WHITE);
  display.drawBitmap(24, 0, letter_I, 8, 8, SSD1306_WHITE);
  display.drawBitmap(32, 0, letter_DV, 8, 8, SSD1306_WHITE);
  drawNumber(40, 0, score);
  display.drawLine(0, 9, 128, 9, SSD1306_WHITE);
  
  display.fillRect(food_x * size, food_y * size + 10, size, size, SSD1306_WHITE);
  for (int i = 0; i < snake_len; i++) {
    display.fillRect(snakeX[i] * size, snakeY[i] * size + 10, size, size, SSD1306_WHITE);
  }
  
  display.display();
}

// СРЕДНИЙ УРОВЕНЬ
void startLevelNormal() {
  snake_len = 3;
  score = 0;
  dX = 1;
  dY = 0;
  smert = false;
  for (int i = 0; i < snake_len; i++) {
    snakeX[i] = grid_w / 2 - i;
    snakeY[i] = grid_h / 2;
  }
  spawnFood();
  last_move = millis();
  drawGame();
}

void handlePlayNormal() {
  int x = analogRead(joy_x);
  int y = analogRead(joy_y);
  int nX = 0, nY = 0;
  if (x < 1200) {nX = 1; nY = 0;}
  else if (x > 2800) {nX = -1; nY = 0;}
  else if (y < 1200) { nX = 0; nY = 1;}
  else if (y > 2800) { nX = 0; nY = -1;}
  else return;
  if (nX == -dX && nY == -dY) return;
  dX = nX;
  dY = nY;
  for (int i = snake_len; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }
  snakeX[0] += dX;
  snakeY[0] += dY;
  if (snakeX[0] < 0 || snakeX[0] >= grid_w ||
      snakeY[0] < 0 || snakeY[0] >= grid_h) {
    state = OVER;
    smert = true;
    return;
  }
  if (snakeX[0] == food_x && snakeY[0] == food_y) {
    snake_len++;
    score += 10;
    if (score >= normal_pobeda) {
      state = OVER;
      return;
    }
    spawnFood();
  }
  for (int i = 1; i < snake_len; i++) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      state = OVER;
      smert = true;
      return;
    }
  }
  drawGame();
  delay(150);
  while (analogRead(joy_x) < 1200 || analogRead(joy_x) > 2800 ||
         analogRead(joy_y) < 1200 || analogRead(joy_y) > 2800) {
    delay(10);
  }
  delay(50);
}

// СЛОЖНЫЙ УРОВЕНЬ
void spawnFruits() {
  f_count = 0;
  bf_count = 0;
  spawn_count++;
  
  int good = random(1, 4);
  for (int i = 0; i < good; i++) {
    bool onSnake;
    int fx, fy;
    do {
      onSnake = false;
      fx = random(0, grid_w);
      fy = random(0, grid_h);
      for (int j = 0; j < snake_len; j++) {
        if (snakeX[j] == fx && snakeY[j] == fy) {
          onSnake = true;
          break;
        }
      }
      for (int j = 0; j < f_count; j++) {
        if (fruits[j].x == fx && fruits[j].y == fy) {
          onSnake = true;
          break;
        }
      }
    } while (onSnake);
    fruits[f_count].x = fx;
    fruits[f_count].y = fy;
    fruits[f_count].type = random(0, 3);
    fruits[f_count].bad = false;
    f_count++;
  }
  
  if (spawn_count % 3 == 0) {
    bool onSnake;
    int fx, fy;
    do {
      onSnake = false;
      fx = random(0, grid_w);
      fy = random(0, grid_h);
      for (int j = 0; j < snake_len; j++) {
        if (snakeX[j] == fx && snakeY[j] == fy) {
          onSnake = true;
          break;
        }
      }
      for (int j = 0; j < f_count; j++) {
        if (fruits[j].x == fx && fruits[j].y == fy) {
          onSnake = true;
          break;
        }
      }
    } while (onSnake);
    fruits[f_count].x = fx;
    fruits[f_count].y = fy;
    fruits[f_count].type = random(3, 5);
    fruits[f_count].bad = true;
    f_count++;
    bf_count = 1;
  }
}

void handlePlayHard() {
  int x = analogRead(joy_x);
  int y = analogRead(joy_y);
  if (x < 1200 && dX != -1) {dX = 1; dY = 0;}
  else if (x > 2800 && dX != 1) {dX = -1; dY = 0;}
  else if (y < 1200 && dY != -1) {dX = 0; dY = 1;}
  else if (y > 2800 && dY != 1) {dX = 0; dY = -1;}
  if (millis() - last_move > speed_hard) {
    last_move = millis();
    for (int i = snake_len; i > 0; i--) {
      snakeX[i] = snakeX[i - 1];
      snakeY[i] = snakeY[i - 1];
    }
    snakeX[0] += dX;
    snakeY[0] += dY;
    if (snakeX[0] < 0 || snakeX[0] >= grid_w ||
        snakeY[0] < 0 || snakeY[0] >= grid_h) {
      state = OVER;
      smert = true;
      return;
    }
    for (int i = 0; i < f_count; i++) {
      if (snakeX[0] == fruits[i].x && snakeY[0] == fruits[i].y) {
        if (fruits[i].bad) {
          // Плохой фрукт
          score -= 5;
          if (score < 0) {
            state = OVER;
            smert = true;
            return;
          }
        } else {
          // Хороший фрукт
          snake_len++;
          score += 15;
          if (score >= hard_pobeda) {
            state = OVER;
            return;
          }
        }
        for (int j = i; j < f_count - 1; j++) {
          fruits[j] = fruits[j + 1];
        }
        f_count--;
        i--;
      }
    }
    if (f_count == 0) {
      spawnFruits();
    }
    for (int i = 1; i < snake_len; i++) {
      if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
        state = OVER;
        smert = true;
        return;
      }
    }
    drawGameHard();
  }
}

void drawFruit(int x, int y, bool bad) {
  int px = x * size;
  int py = y * size + 10;
  
  if (bad) {
    display.drawRect(px, py, size, size, SSD1306_WHITE);
  } else {
    display.fillRect(px, py, size, size, SSD1306_WHITE);
  }
}

void drawGameHard() {
  display.clearDisplay();
  display.drawBitmap(0, 0, letter_O, 8, 8, SSD1306_WHITE);
  display.drawBitmap(8, 0, letter_Ch, 8, 8, SSD1306_WHITE);
  display.drawBitmap(16, 0, letter_K, 8, 8, SSD1306_WHITE);
  display.drawBitmap(24, 0, letter_I, 8, 8, SSD1306_WHITE);
  display.drawBitmap(32, 0, letter_DV, 8, 8, SSD1306_WHITE);
  drawNumber(40, 0, score);
  display.drawLine(0, 9, 128, 9, SSD1306_WHITE);
  for (int i = 0; i < f_count; i++) {
    drawFruit(fruits[i].x, fruits[i].y, fruits[i].bad);
  }
  
  for (int i = 0; i < snake_len; i++) {
    display.fillRect(snakeX[i] * size, snakeY[i] * size + 10, size, size, SSD1306_WHITE);
  }
  
  display.display();
}

void startLevelHard() {
  snake_len = 3;
  score = 0;
  dX = 1;
  dY = 0;
  smert = false;
  f_count = 0;
  bf_count = 0;
  spawn_count = 0;
  
  for (int i = 0; i < snake_len; i++) {
    snakeX[i] = grid_w / 2 - i;
    snakeY[i] = grid_h / 2;
  }
  
  spawnFruits();
  last_move = millis();
  drawGameHard();
}

// ОКОНЧАНИЕ ИГРЫ
void handleOver() {
  display.clearDisplay();
  if ((current_level == 0 && score >= easy_pobeda) || 
      (current_level == 1 && !smert && score >= normal_pobeda) ||
      (current_level == 2 && !smert && score >= hard_pobeda)) {
    display.drawBitmap(36, 20, letter_P, 8, 8, SSD1306_WHITE);
    display.drawBitmap(44, 20, letter_O, 8, 8, SSD1306_WHITE);
    display.drawBitmap(52, 20, letter_B, 8, 8, SSD1306_WHITE);
    display.drawBitmap(60, 20, letter_E, 8, 8, SSD1306_WHITE);
    display.drawBitmap(68, 20, letter_D, 8, 8, SSD1306_WHITE);
    display.drawBitmap(76, 20, letter_A, 8, 8, SSD1306_WHITE);
    display.drawBitmap(84, 20, letter_VO, 8, 8, SSD1306_WHITE);
  }
  else {
    display.drawBitmap(32, 20, letter_P, 8, 8, SSD1306_WHITE);
    display.drawBitmap(40, 20, letter_R, 8, 8, SSD1306_WHITE);
    display.drawBitmap(48, 20, letter_O, 8, 8, SSD1306_WHITE);
    display.drawBitmap(56, 20, letter_I, 8, 8, SSD1306_WHITE);
    display.drawBitmap(64, 20, letter_G, 8, 8, SSD1306_WHITE);
    display.drawBitmap(72, 20, letter_R, 8, 8, SSD1306_WHITE);
    display.drawBitmap(80, 20, letter_VV, 8, 8, SSD1306_WHITE);
    display.drawBitmap(88, 20, letter_Sh, 8, 8, SSD1306_WHITE);
  }
  drawScoreCenter(36);
  display.display(); 
  delay(30);
  while (digitalRead(joy_btn) == HIGH) {
    delay(10);
  }
  delay(30);
  while (digitalRead(joy_btn) == LOW) {
    delay(10);
  }
  smert = false;
  state = MENU;
  drawMenu();
}

void drawNumber(int x, int y, int num) {
  if (num == 0) {
    display.drawBitmap(x, y, letter_0, 8, 8, SSD1306_WHITE);
    return;
  }
  int digits[5];
  int count = 0;
  while (num > 0) {
    digits[count] = num % 10;
    num /= 10;
    count++;
  }
  for (int i = count - 1; i >= 0; i--) {
    switch (digits[i]) {
      case 0: display.drawBitmap(x, y, letter_0, 8, 8, SSD1306_WHITE); break;
      case 1: display.drawBitmap(x, y, letter_1, 8, 8, SSD1306_WHITE); break;
      case 2: display.drawBitmap(x, y, letter_2, 8, 8, SSD1306_WHITE); break;
      case 3: display.drawBitmap(x, y, letter_3, 8, 8, SSD1306_WHITE); break;
      case 4: display.drawBitmap(x, y, letter_4, 8, 8, SSD1306_WHITE); break;
      case 5: display.drawBitmap(x, y, letter_5, 8, 8, SSD1306_WHITE); break;
      case 6: display.drawBitmap(x, y, letter_6, 8, 8, SSD1306_WHITE); break;
      case 7: display.drawBitmap(x, y, letter_7, 8, 8, SSD1306_WHITE); break;
      case 8: display.drawBitmap(x, y, letter_8, 8, 8, SSD1306_WHITE); break;
      case 9: display.drawBitmap(x, y, letter_9, 8, 8, SSD1306_WHITE); break;
    }
    x += 8;
  }
}

void drawScoreCenter(int y) {
  int count = 0;
  int tmp = score;
  if (tmp == 0) count = 1;
  else {
    while (tmp > 0) {
      count++;
      tmp /= 10;
    }
  }
  int fix_h = 40;
  int digits_w = count * 8;
  int total = fix_h + digits_w;
  int startX = (128 - total) / 2;
  display.drawBitmap(startX, y, letter_O, 8, 8, SSD1306_WHITE);
  startX += 8;
  display.drawBitmap(startX, y, letter_Ch, 8, 8, SSD1306_WHITE);
  startX += 8;
  display.drawBitmap(startX, y, letter_K, 8, 8, SSD1306_WHITE);
  startX += 8;
  display.drawBitmap(startX, y, letter_I, 8, 8, SSD1306_WHITE);
  startX += 8;
  display.drawBitmap(startX, y, letter_DV, 8, 8, SSD1306_WHITE);
  startX += 8;
  drawNumber(startX, y, score);
}
