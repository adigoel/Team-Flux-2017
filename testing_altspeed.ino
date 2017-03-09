int nofloops = 0;
int backupspd = 0;
int altitudes[50] = {50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
int altarray[6] = {0, 0, 0, 0, 0, 0};
int CurrentTime = 0;
int ElapsedTime = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  int alt = altitudes[nofloops];
  if (altarray[5] == 0) {
    for (int i=0; i<6; i++) {
      altarray[i] = alt;
    }
  }
  for (int i = 5; i > 0; i--) {
    altarray[i] = altarray[i-1];
  }
  altarray[0] = alt;
  int startalt = (altarray[0] + altarray[1] + altarray[2])/3;
  int endalt = (altarray[3] + altarray[4] + altarray[5])/3;
  int totaldiff = startalt - endalt;
  Serial.print("Loop: ");
  Serial.println(nofloops);
  Serial.print("Difference is ");
  Serial.println(totaldiff);
  Serial.print(altarray[0]);
  Serial.print(altarray[1]);
  Serial.print(altarray[2]);
  Serial.print(altarray[3]);
  Serial.print(altarray[4]);
  Serial.print(altarray[5]);
  if ((nofloops % 3) == 0) {
    Serial.println("now recalculate speed. ");
    ElapsedTime = nofloops - CurrentTime;
    Serial.print("the elapsed time since last time is ");
    Serial.println(ElapsedTime);
    int muhsped = (totaldiff / ElapsedTime); //dm/s
    CurrentTime = nofloops;
    backupspd = muhsped;
    Serial.print("speed is ");
    Serial.println(muhsped);
  }
  else {
    Serial.print("but now speed is ");
    Serial.println(backupspd);
  }
  delay(2000);
  nofloops += 1;
}
