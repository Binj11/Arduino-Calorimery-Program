#include <TimerOne.h>
#include <math.h>
float inputJoules;
double Thermistor(float RawADC) {
double Temp;
Temp = log(((10240000/RawADC) - 10000));
Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
Temp = Temp - 273.15;            // Convert Kelvin to Celcius

return Temp;
}

void setup() {
  Serial.begin(9600);
  analogReference(EXTERNAL);
  Timer1.initialize(2000000);
  Timer1.attachInterrupt(calcWattsaddJoules,1000000);
}
void calcWattsaddJoules(){
  float sensorValue = analogRead(A0);
  float thermValue  = analogRead(A1);
  float therm2      = analogRead(A2);
  float Isense      = analogRead(A3);
  float current;
  float Vcurrent;
  float sensorVoltage;
  float thermResistance;
  float inputWatts;
  // print out the value you read:
  Serial.print("(VoltDivData) = ");
  Serial.print(sensorValue );
  Serial.print(",");
  sensorVoltage = sensorValue / 1023 * 4.096 * 10;
  Serial.print("(InVolt) = ");
  Serial.print(sensorVoltage );
  Serial.print(",");
  Serial.print("(ThermData) = ");
  Serial.print(thermValue );
  Serial.print(",");
  Serial.print("(TempDegCelcius) = ");
  Serial.print(float(Thermistor(analogRead(A1))));
  Serial.print(",");
  Serial.print("(CurrentData) = ");
  Serial.print(Isense );
  Vcurrent = Isense / 1023 * 1000;
  Serial.print(",");
  Serial.print("(CurrentIn mA) = ");
  Serial.print(Vcurrent );
  Serial.print(",");
  inputWatts = (Vcurrent / 1000) * sensorVoltage;
  Serial.print("(InWatts) = ");
  Serial.print(inputWatts );
  inputJoules = inputJoules + inputWatts;
  Serial.print(",");
  Serial.print("(InJoules) = ");
  Serial.print(inputJoules );
  Serial.println(",");
 }


void loop() {
   
  
}
