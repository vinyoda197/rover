

const int led = 13;
//const int m1 = 16;
// const int m2 = 5;
const int m1 = 4;
const int m2 = 15;
const int m3 = 13;
const int m4 = 0;

void setupMobility() {
  pinMode(led, OUTPUT);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
}

void forward() {
  digitalWrite(m1, 0);
  digitalWrite(m2, 1);
  digitalWrite(m3, 1);
  digitalWrite(m4, 0);
}

void halt() {
  digitalWrite(m1, 0);
  digitalWrite(m2, 0);
  digitalWrite(m3, 0);
  digitalWrite(m4, 0);
}

void backing() {
  digitalWrite(m1, 1);
  digitalWrite(m2, 0);
  digitalWrite(m3, 0);
  digitalWrite(m4, 1);
}

void turnLeft() {
  digitalWrite(m1, 0);
  digitalWrite(m2, 1);
  digitalWrite(m3, 0);
    //digitalWrite(m4, 1);
}

void turnRight() {
    //digitalWrite(m1, 1);
  digitalWrite(m2, 0);
  digitalWrite(m3, 1);
  digitalWrite(m4, 0);
}
