#ifndef __CONFIGS_H__
#define __CONFIGS_H__

#define UNIT 1000
#define PERIOD 20
#define INIT_GREEN 10

#define S_RED 4
#define S_YEL 3
#define S_GRE 2
#define S_BUTTON 9

#define W_RED 7
#define W_YEL 6
#define W_GRE 5
#define W_BUTTON 8

#define B0 11
#define B1 10
#define B2 9

#define DS 13
#define DW 12

void init_coordinate() {
  pinMode(B0, INPUT);
  pinMode(B1, INPUT);
  pinMode(B2, INPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(DS, INPUT);
  pinMode(DW, INPUT);
}

int init_x() {
  int x = analogRead(A2) > 30 ? 1 : 0;
  x = (x<<1) + analogRead(A1) > 30 ? 1 : 0;
  x = (x<<1) + analogRead(A0) > 30 ? 1 : 0;
}

int init_y() {
  int y = digitalRead(B2)==HIGH ? 1 : 0;
  y = (y<<1) + digitalRead(B1)==HIGH ? 1 : 0;
  y = (y<<1) + digitalRead(B0)==HIGH ? 1 : 0;
}

bool init_s() { return digitalRead(DS)==HIGH; }

bool init_w() { return digitalRead(DW)==HIGH; }

#endif
