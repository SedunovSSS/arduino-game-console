#include "U8glib.h"

const uint8_t width = 128;
const uint8_t height = 64;

const uint8_t buttonUp = 4;
const uint8_t buttonDown = 2;
const uint8_t buttonRight = 3;
const uint8_t buttonLeft = 5;
const uint8_t buttonBack2Menu = 6;

const char* _version = "1.0.2";

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
const uint8_t menu_length = 3;
const char *menu_objects[] = {"SNAKE", "PONG", "RAY CAST"};
const uint8_t menu_offset = 20;

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0);

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

void menu(void) {
  u8g.firstPage();
  do {
    uint8_t start_menu_pos = 15;
    for (int i = 0; i < menu_length; i++) {
      u8g.setFont(u8g_font_6x13);
      u8g.setPrintPos((int)width / 3, start_menu_pos);
      u8g.print(menu_objects[i]);
      start_menu_pos += menu_offset;
    }
    u8g.drawFrame(20, menu_select * menu_offset, width - 40, menu_offset);

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
    delay(500);
    menu_state = menu_select + 1;
  }
}

void screensaver(void) {
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_unifont);
    u8g.drawStr(width / 2 - 50, 10, "PlayStation 5");
    u8g.drawStr(width / 2 - 50, 30, "by SedunovSSS");
    u8g.drawStr(width / 2 - 20, 50, _version);
  }
  while ( u8g.nextPage() );
  delay(1500);
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
  if (digitalRead(buttonBack2Menu) == 0) {
    menu_state = 0;
  }
}
