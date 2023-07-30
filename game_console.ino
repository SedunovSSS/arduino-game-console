#include "U8glib.h"

const uint8_t width = 128;
const uint8_t height = 64;

const uint8_t buttonUp = 4;
const uint8_t buttonDown = 2;
const uint8_t buttonRight = 3;
const uint8_t buttonLeft = 5;
const uint8_t buttonBack2Menu = 6;

const char* _version = "1.0.5";

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0);

// snake variables

uint8_t length_ = 1;
const uint8_t max_length = 40;

const uint8_t sizeCube = 8;

uint8_t x = 64;
uint8_t y = 32;
int dx = 0;
int dy = 0;

uint8_t score = 0;

const uint8_t xPos[] = {8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112};
const uint8_t yPos[] = {8, 16, 24, 32, 40, 48};

uint8_t xFruit = xPos[random(0, sizeof(xPos))];
uint8_t yFruit = yPos[random(0, sizeof(yPos))];

uint8_t tailX[max_length], tailY[max_length];

String score_string;

// pong variables

const uint8_t p_width = 8;
const uint8_t p_height = 16;
const uint8_t ball_size = 3;

const uint8_t step_ = 1;
const uint8_t ball_step = step_ * 4;

int ball_x = width / 2 - ball_size;
int ball_y = height / 2 - ball_size;

int dxS[] = { -1, 1};
int dyS[] = { -1, 1};

int ball_dx = dxS[random(0, 2)];
int ball_dy = dyS[random(0, 2)];

const uint8_t f_x = 0;
uint8_t f_y = height - p_height * 2.5;
const uint8_t s_x = width - p_width;
uint8_t s_y = height - p_height * 2.5;

uint8_t f_score = 0;
uint8_t s_score = 0;

String f_score_string, s_score_string;

// ray casting variables

const uint8_t map_width = 32;
const uint8_t map_height = 16;

const float pi = 3.14;
float angle = 0;

float player_x = 2;
float player_y = 2;

const uint8_t block_size = width / map_width;
const uint8_t num_rays = 32;
const float fov = pi / 3;
const float half_fov = fov / 2;
const float delta_angle = fov / num_rays;
const uint8_t max_depth = 32;
const float dist = num_rays / (2 * tan(half_fov));
const float coeff = 6 * dist * block_size;
const float scale = width / num_rays;
const float player_speed = 0.5;

const uint8_t _map[map_width][map_height] {
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1},
  {1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

// menu variables

uint8_t menu_state = 0;
int8_t menu_select = 0;
const uint8_t menu_length = 4;
const char *menu_objects[menu_length] = {"SNAKE", "PING PONG", "RAY CAST", "GOOGLE DINO"};
const uint8_t menu_offset = 15;

// load screen variables

const uint8_t piggis[] U8G_PROGMEM = { 
    0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x63, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x40, 0x80, 0x00, 0x00, 
    0x00, 0x38, 0x00, 0x9c, 0xc0, 0x00, 0x00, 
    0x00, 0xec, 0x00, 0x9c, 0x80, 0x00, 0x00, 
    0x01, 0x82, 0x00, 0x9e, 0xc0, 0x00, 0x00, 
    0x01, 0x01, 0x1f, 0x9c, 0x80, 0x00, 0x00, 
    0x03, 0x3d, 0xf4, 0x81, 0x80, 0x00, 0x00, 
    0x02, 0x3d, 0x80, 0x03, 0x80, 0x00, 0x00, 
    0x01, 0x3c, 0x00, 0x00, 0x70, 0x00, 0x00, 
    0x01, 0xc0, 0x00, 0x00, 0x1c, 0x00, 0x00, 
    0x00, 0xe0, 0x00, 0x00, 0x06, 0x00, 0x00, 
    0x00, 0xc0, 0x00, 0x00, 0x01, 0x80, 0x00, 
    0x01, 0x80, 0x00, 0x00, 0x00, 0xc0, 0x00, 
    0x03, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 
    0x06, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 
    0x07, 0xc0, 0x00, 0x00, 0x00, 0xd0, 0x00, 
    0x0e, 0x00, 0x00, 0x00, 0x01, 0xe8, 0x00, 
    0x18, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 
    0x10, 0x00, 0x1f, 0xe0, 0x00, 0x06, 0x00, 
    0x31, 0x40, 0x60, 0x1c, 0x00, 0x02, 0x00, 
    0x27, 0xe0, 0x80, 0x03, 0x03, 0xe3, 0x00, 
    0x2c, 0x13, 0x00, 0x01, 0x06, 0x11, 0x00, 
    0x70, 0x0a, 0x00, 0x00, 0x88, 0x09, 0x80, 
    0x50, 0x04, 0x00, 0x00, 0x58, 0x05, 0x80, 
    0x60, 0x0c, 0x00, 0x00, 0x50, 0x04, 0x80, 
    0xc0, 0x28, 0x70, 0x30, 0x72, 0x04, 0x80, 
    0xe0, 0x38, 0x78, 0x78, 0x23, 0x02, 0x80, 
    0x80, 0x38, 0x78, 0x78, 0x33, 0x04, 0x80, 
    0xd0, 0x08, 0xf8, 0x7c, 0x30, 0x04, 0x80, 
    0x90, 0x08, 0x78, 0x78, 0x20, 0x04, 0x80, 
    0xc8, 0x18, 0x78, 0x38, 0x28, 0x08, 0x80, 
    0xc6, 0x68, 0x10, 0x00, 0x64, 0x10, 0x80, 
    0x41, 0x08, 0x00, 0x00, 0x43, 0xe0, 0x80, 
    0x40, 0xb4, 0x00, 0x00, 0x41, 0x00, 0x80, 
    0x61, 0x06, 0x00, 0x00, 0xf1, 0x00, 0x80, 
    0x60, 0x6f, 0x00, 0x03, 0xf6, 0x61, 0x80, 
    0x20, 0x27, 0xe8, 0x1d, 0xe0, 0x01, 0x80, 
    0x30, 0x01, 0x8f, 0xe0, 0xc0, 0x01, 0x00, 
    0x18, 0x00, 0x84, 0x31, 0x80, 0x03, 0x00, 
    0x08, 0x00, 0x5c, 0x3a, 0x00, 0x06, 0x00, 
    0x0c, 0x00, 0x22, 0x44, 0x00, 0x0c, 0x00, 
    0x07, 0x00, 0x01, 0x80, 0x00, 0x18, 0x00, 
    0x03, 0x80, 0x00, 0x00, 0x00, 0x30, 0x00, 
    0x00, 0xc0, 0x00, 0x00, 0x00, 0xe0, 0x00, 
    0x00, 0x70, 0x00, 0x00, 0x03, 0xc0, 0x00, 
    0x00, 0x1e, 0x00, 0x00, 0x1f, 0x00, 0x00, 
    0x00, 0x07, 0xc0, 0x01, 0x7c, 0x00, 0x00, 
    0x00, 0x00, 0xff, 0xff, 0xe0, 0x00, 0x00, 
    0x00, 0x00, 0x0f, 0xfa, 0x00, 0x00, 0x00       
};

const uint8_t piggis_w = 7;
const uint8_t piggis_h = sizeof(piggis)/piggis_w;

// dino variables


const uint8_t dino_run_1[] U8G_PROGMEM = { 
    0x00, 0x00, 0x00, 
    0x00, 0x1f, 0xe0, 
    0x00, 0x17, 0xf0, 
    0x00, 0x1f, 0xf0, 
    0x00, 0x3f, 0xf0, 
    0x00, 0x1f, 0xf0, 
    0x00, 0x1e, 0x00, 
    0x00, 0x7f, 0xc0, 
    0x40, 0xfc, 0x00, 
    0x61, 0xff, 0x00, 
    0x73, 0xfe, 0x00, 
    0x7f, 0xfe, 0x00, 
    0x7f, 0xfe, 0x00, 
    0x3f, 0xf8, 0x00, 
    0x1f, 0xf0, 0x00, 
    0x0f, 0xf0, 0x00, 
    0x07, 0xc0, 0x00, 
    0x03, 0x30, 0x00, 
    0x02, 0x18, 0x00, 
    0x03, 0x00, 0x00
};

const uint8_t dino_run_2[] U8G_PROGMEM = { 
    0x00, 0x00, 0x00, 
    0x00, 0x1f, 0xe0, 
    0x00, 0x17, 0xf0, 
    0x00, 0x1f, 0xf0, 
    0x00, 0x3f, 0xf0, 
    0x00, 0x1f, 0xf0, 
    0x00, 0x1e, 0x00, 
    0x00, 0x7f, 0xc0, 
    0x40, 0xfc, 0x00, 
    0x61, 0xff, 0x00, 
    0x73, 0xfe, 0x00, 
    0x7f, 0xfe, 0x00, 
    0x7f, 0xfe, 0x00, 
    0x3f, 0xf8, 0x00, 
    0x1f, 0xf8, 0x00, 
    0x0f, 0xf0, 0x00, 
    0x06, 0x60, 0x00, 
    0x03, 0x20, 0x00, 
    0x03, 0x10, 0x00, 
    0x00, 0x18, 0x00
};

const uint8_t cactus_big[] U8G_PROGMEM = { 
    0x08, 0x00, 0x00, 0x83, 
    0x0c, 0x0c, 0x01, 0xc3, 
    0x1e, 0x0c, 0x01, 0xc3, 
    0x0c, 0x0c, 0x0d, 0xc3, 
    0x1c, 0x0d, 0x8d, 0xc3, 
    0x4d, 0x8d, 0x0c, 0xdb, 
    0xdc, 0x8c, 0x8d, 0xdb, 
    0x4d, 0xaf, 0x0d, 0xdb, 
    0xed, 0xad, 0x4f, 0xdb, 
    0x5d, 0xac, 0x67, 0xdb, 
    0xcc, 0xbc, 0xa9, 0xcb, 
    0x7f, 0xad, 0x51, 0xf3, 
    0x7e, 0x3d, 0x79, 0xc3, 
    0x1c, 0x0d, 0x51, 0xc3, 
    0x0c, 0x0c, 0xf1, 0xc3, 
    0x0e, 0x0c, 0x40, 0xc3, 
    0x1c, 0x0c, 0x61, 0xc3, 
    0x0c, 0x0c, 0x41, 0xc3, 
    0x1c, 0x0c, 0x61, 0xc3, 
    0x00, 0x00, 0x00, 0x03
};

const uint8_t cactus_small[] U8G_PROGMEM = { 
    0x03, 0x80, 
    0x07, 0x80, 
    0x67, 0x80, 
    0xf7, 0x80, 
    0xe7, 0x90, 
    0xf7, 0x90, 
    0xf7, 0xb0, 
    0xe7, 0x10, 
    0xf7, 0xf0, 
    0xf7, 0xf0, 
    0xe7, 0xe0, 
    0xf7, 0x80, 
    0x7f, 0x80, 
    0x7f, 0x80, 
    0x1f, 0x80, 
    0x07, 0x80, 
    0x07, 0x00, 
    0x07, 0x80, 
    0x07, 0x80, 
    0x07, 0x80
};

const uint8_t dino_w = 3;
const uint8_t dino_h = sizeof(dino_run_1)/dino_w;

const uint8_t cactus_big_w = 4;
const uint8_t cactus_big_h = sizeof(cactus_big)/cactus_big_w;

const uint8_t cactus_small_w = 2;
const uint8_t cactus_small_h = sizeof(cactus_small)/cactus_small_w;

const uint8_t dino_x = 20;
int8_t dino_y = height - dino_h - 10;

bool isDino1 = true;
bool isJump = false;
int jumpCount = 20;
const uint8_t dino_speed = 10;
uint8_t dino_score = 0;

int cactus_x = width / 2;
int cactus_y = 55;

bool cactusIsBig = false;

int cactus_w;
int cactus_h;
uint8_t *cactus;

void snake_logic(void) {
  uint8_t prevX = tailX[0];
  uint8_t prevY = tailY[0];
  uint8_t prev2X, prev2Y;

  x += dx;
  y += dy;

  tailX[0] = x;
  tailY[0] = y;

  for (int i = 1; i < length_; i++) {
    prev2X = tailX[i];
    prev2Y = tailY[i];
    tailX[i] = prevX;
    tailY[i] = prevY;
    prevX = prev2X;
    prevY = prev2Y;
  }

  if (length_ >= 3) {
    for (int i = 1; i < length_; i++) {
      if (x == tailX[i] && y == tailY[i]) {
        delay(500);
        dx = 0;
        dy = 0;
        score = 0;
        length_ = 1;
        x = 64;
        y = 32;
        xFruit = xPos[random(sizeof(xPos))];
        yFruit = yPos[random(sizeof(yPos))];
        for (int k = 0; k < max_length; k++) {
          tailX[k] = 0;
          tailY[k] = 0;
        }
      }
    }
  }
}

void snake(void) {
  for (int i = 0; i < length_; i++) {
    if (i == 0) {
      u8g.drawFrame(tailX[i], tailY[i], sizeCube, sizeCube);
    }
    else {
      u8g.drawRBox(tailX[i], tailY[i], sizeCube, sizeCube, 0);
    }
  }
  u8g.drawRBox(xFruit, yFruit, sizeCube, sizeCube, 0);
  score_string = String(score);
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr(10, 10, score_string.c_str());

  if (digitalRead(buttonUp) == 0) {
    dy = -sizeCube;
    dx = 0;
  }
  if (digitalRead(buttonDown) == 0) {
    dy = sizeCube;
    dx = 0;
  }
  if (digitalRead(buttonRight) == 0) {
    dx = sizeCube;
    dy = 0;
  }
  if (digitalRead(buttonLeft) == 0) {
    dx = -sizeCube;
    dy = 0;
  }
  if (dx == sizeCube && x >= width - sizeCube) {
    x = 0;
  }
  if (dx == -sizeCube && x <= 0) {
    x = width - sizeCube;
  }
  if (dy == sizeCube && y >= height - sizeCube) {
    y = 0;
  }
  if (dy == -sizeCube && y <= 0) {
    y = height - sizeCube;
  }
  if (x == xFruit && y == yFruit) {
    xFruit = xPos[random(sizeof(xPos))];
    yFruit = yPos[random(sizeof(yPos))];
    score++;
    length_++;
  }
}

void run_snake(void) {
  snake_logic();
  u8g.firstPage();
  do {
    snake();
  } while ( u8g.nextPage() );

  delay(100);
}

void pong_logic(void) {
  ball_x += ball_dx * ball_step;
  ball_y += ball_dy * ball_step;
}

void pong(void) {
  u8g.drawRBox(f_x, f_y, p_width, p_height, 0);
  u8g.drawRBox(s_x, s_y, p_width, p_height, 0);
  u8g. drawFilledEllipse (ball_x, ball_y, ball_size, ball_size, U8G_DRAW_ALL);
  u8g.drawVLine(width / 2, 0, height);
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr(10, 10, f_score_string.c_str());
  u8g.drawStr(width - 20, 10, s_score_string.c_str());

  if (digitalRead(buttonUp) == 0 && f_y > 0) {
    f_y -= step_;
  }
  if (digitalRead(buttonDown) == 0 && s_y < height - p_height) {
    s_y += step_;
  }
  if (digitalRead(buttonRight) == 0 && s_y > 0) {
    s_y -= step_;
  }
  if (digitalRead(buttonLeft) == 0 && f_y < height - p_height) {
    f_y += step_;
  }
  if (ball_y >= height - ball_size) {
    ball_dy = -1;
  }
  if (ball_y <= 0) {
    ball_dy = 1;
  }
  if (ball_x >= width - ball_size - p_width && s_y <= ball_y && ball_y <= s_y + p_height) {
    ball_dx = -1;
  }
  if (ball_x <= p_width && f_y <= ball_y && ball_y <= f_y + p_height) {
    ball_dx = 1;
  }
  if ((ball_x >= width) && !(s_y <= ball_y && ball_y <= s_y + p_height)) {
    f_score++;
    ball_x = width / 2 - ball_size;
    ball_y = height / 2 - ball_size;
    ball_dx = dxS[random(0, 2)];
    ball_dy = dyS[random(0, 2)];
  }
  if ((ball_x <= 0) && !(f_y <= ball_y && ball_y <= f_y + p_height)) {
    s_score++;
    ball_x = width / 2 - ball_size;
    ball_y = height / 2 - ball_size;
    ball_dx = dxS[random(0, 2)];
    ball_dy = dyS[random(0, 2)];
  }
  f_score_string = String(f_score);
  s_score_string = String(s_score);
}

void run_pong(void) {
  pong_logic();
  u8g.firstPage();
  do {
    pong();
  } while ( u8g.nextPage() );

  delay(20);
}

void run_ray_cast(void) {
  u8g.firstPage();
  do {
    float sin_a = sin(angle);
    float cos_a = cos(angle);
    float cur_angle = angle - half_fov;
    for (int i = 0; i < num_rays; i++) {
      float sin_ca = sin(cur_angle);
      float cos_ca = cos(cur_angle);
      for (int d = 0; d < max_depth; d++) {
        float x_ = player_x * block_size + d * block_size * cos_ca;
        float y_ = player_y * block_size + d * block_size * sin_ca;
        int x_index = (int)(x_ / block_size);
        int y_index = (int)(y_ / block_size);
        if (_map[x_index][y_index] == 1) {
          float proj_height = coeff / (d * block_size);
          float half_proj_height = proj_height / 2;
          u8g.drawRBox(scale * i, height / 2 - half_proj_height, scale, proj_height, 0);
          break;
        }
      }
      cur_angle += delta_angle;
    }
    if (digitalRead(buttonUp) == 0) {
      player_x += player_speed * cos_a;
      player_y += player_speed * sin_a;
    }
    if (digitalRead(buttonDown) == 0) {
      player_x -= player_speed * cos_a;
      player_y -= player_speed * sin_a;
    }
    if (digitalRead(buttonRight) == 0) {
      angle += 0.1;
    }
    if (digitalRead(buttonLeft) == 0) {
      angle -= 0.1;
    }
    for (int i = 0; i < width; i++) {
      for (int j = 0; j < height / 2; j++) {
        if (i % 8 == 0 && j % 8 == 0) {
          u8g.drawPixel(i, j);
        }
        if (i % 4 == 0 && j % 4 == 0) {
          u8g.drawPixel(i, height / 2 + j);
        }
      }
    }
  } while ( u8g.nextPage() );
}

void dino_logic(void){
  if (!cactusIsBig){
    cactus = cactus_small ;
    cactus_w = cactus_small_w;
    cactus_h = cactus_small_h;
  }
  else{
    cactus = cactus_big ;
    cactus_w = cactus_big_w;
    cactus_h = cactus_big_h;
  }
  isDino1 = !isDino1;
  cactus_x -= dino_speed;
  if (cactus_x < -cactus_w){
    if (random(0, 2) == 0){
    cactusIsBig = false;
  }
  else{
    cactusIsBig = true;
  }
  cactus_x = width - cactus_w;
  dino_score++;
  }
  if (dino_y == height - dino_h - 10 && cactus_x < dino_x + cactus_w){
    delay(1000);
    dino_y = height - dino_h - 10;
    
    isDino1 = true;
    isJump = false;
    jumpCount = 20;
    dino_score = 0;
    
    cactus_x = width - cactus_w;
    cactus_y = 55;
    if (random(0, 2) == 0) {
      cactusIsBig = false;
    }
    else {
      cactusIsBig = true;
    }
  }
}

void dino(void){
  u8g.setFont(u8g_font_unifont);
   u8g.drawStr(10, 10, String(dino_score).c_str());
    u8g.drawLine(0, 55, width, 55);
    if (isDino1){
      u8g.drawBitmapP(dino_x, dino_y, dino_w, dino_h, dino_run_1);
    }
    else{
      u8g.drawBitmapP(dino_x, dino_y, dino_w, dino_h, dino_run_2);
    }
    if (digitalRead(buttonUp) == 0 && !isJump){
      isJump = true;
    }
    if(isJump){
        if(jumpCount >= -20){
            if (jumpCount < 1)
                dino_y += (jumpCount * jumpCount) / 60;
            else
                dino_y -= (jumpCount * jumpCount) / 60;
            jumpCount -= 1;
        }
        else{
            jumpCount = 20;
            isJump = false;
        }
    }
    u8g.drawBitmapP(cactus_x, cactus_y - cactus_h , cactus_w, cactus_small_h, cactus);
}

void run_dino(void){
  dino_logic();
  u8g.firstPage(); 
  do {
    dino();
  } while( u8g.nextPage() );
  
  delay(20);
}

void menu(void) {
  u8g.firstPage();
  do {
    uint8_t start_menu_pos = 15;
    for (int i = 0; i < menu_length; i++) {
      u8g.setFont(u8g_font_6x13);
      u8g.setPrintPos((int)width / 2 - 40, start_menu_pos);
      u8g.print(menu_objects[i]);
      start_menu_pos += menu_offset;
    }
    //    u8g.drawFrame(menu_offset, menu_select * menu_offset + 5, width - menu_offset * 2, menu_offset);
    u8g.drawDisc(10, (menu_select + 1) * menu_offset - 5, 4);

  }
  while ( u8g.nextPage() );
  if (digitalRead(buttonUp) == 0) {
    menu_select--;
  }
  if (digitalRead(buttonDown) == 0) {
    menu_select++;
  }
  if (menu_select < 0) {
    menu_select = menu_length - 1;
  }
  if (menu_select > menu_length - 1) {
    menu_select = 0;
  }
  if (digitalRead(buttonRight) == 0 || digitalRead(buttonLeft) == 0) {
    load_screen();
    menu_state = menu_select + 1;
  }
}

void screensaver(void) {
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_unifont);
    u8g.drawStr(width / 2 - 50, 15, "PlayStation 5");
    u8g.drawStr(width / 2 - 50, 35, "by SedunovSSS");
    u8g.drawStr(width / 2 - 20, 55, _version);
  }
  while ( u8g.nextPage() );
  delay(1500);
}

void load_screen(void){
  u8g.firstPage(); 
  do {
    u8g.drawBitmapP( width/2-piggis_h/2-5, 5, piggis_w, piggis_h, piggis);
  } while( u8g.nextPage() );
  delay(1000);
}

void setup(void) {
  pinMode(buttonUp, INPUT);
  pinMode(buttonDown, INPUT);
  pinMode(buttonRight, INPUT);
  pinMode(buttonLeft, INPUT);
  pinMode(buttonBack2Menu, INPUT);
  screensaver();
}

void loop() {
  if (menu_state == 0)
    menu();
  if (menu_state == 1)
    run_snake();
  if (menu_state == 2)
    run_pong();
  if (menu_state == 3)
    run_ray_cast();
  if (menu_state == 4)
    run_dino();
  if (digitalRead(buttonBack2Menu) == 0) {
    menu_state = 0;
  }
}