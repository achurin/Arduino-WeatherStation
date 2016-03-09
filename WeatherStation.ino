//Celsius to Fahrenheit conversion
double Fahrenheit(double celsius)
{
  return 1.8 * celsius + 32;
}

double dewPoint(double celsius, double humidity)
{
  // (1) Saturation Vapor Pressure = ESGG(T)
  double RATIO = 373.15 / (273.15 + celsius);
  double RHS = -7.90298 * (RATIO - 1);
  RHS += 5.02808 * log10(RATIO);
  RHS += -1.3816e-7 * (pow(10, (11.344 * (1 - 1/RATIO ))) - 1) ;
  RHS += 8.1328e-3 * (pow(10, (-3.49149 * (RATIO - 1))) - 1) ;
  RHS += log10(1013.246);
  double VP = pow(10, RHS - 3) * humidity;

  // (2) DEWPOINT = F(Vapor Pressure)
  double T = log(VP/0.61078);   // temp var
  return (241.88 * T) / (17.558 - T);
}


double dewPointFast(double celsius, double humidity)
{  double a = 17.271;
  double b = 237.7;
  double temp = (a * celsius) / (b + celsius) + log(humidity*0.01);
  double Td = (b * temp) / (a - temp);
  return Td;
}


#include <dht11.h>

dht11 DHT11;

#define DHT11PIN 3

void setup()
{
  Serial.begin(115200);
  Serial.println("Churin's Inc DHT11 Temperature Sensor ");
}

void loop()
{
  Serial.println("\n");

  int chk = DHT11.read(DHT11PIN);

  Serial.print("Humidity: ");
  Serial.print((float)DHT11.humidity, 2);
  Serial.println("%");
  
  Serial.print("Temperature: ");
  Serial.print(Fahrenheit(DHT11.temperature), 2);
  Serial.println(" F");

  Serial.print("Dew Point: ");
  Serial.print(Fahrenheit(dewPoint(DHT11.temperature, DHT11.humidity)),2);
  Serial.println(" F");

  // HUMIDITY SENSOR
  int sensorValue = analogRead(A0);
  String moistureReading = "ERROR";
  if (sensorValue > 900){
      moistureReading = "Dry!";
    }else if (sensorValue > 500){
      moistureReading = "Moist";
    }else{
        moistureReading = "Drenched!";
    }
  Serial.print("Soil Moisture: ");
  Serial.print(moistureReading);
  Serial.print(": ");
  Serial.println(sensorValue);
  // END HUMIDITY SENSOR
  
  // SOIL TEMPERATURE
  int tempSensorValue = analogRead(A1);
  Serial.print("Soil Temperature: ");
  Serial.println(tempSensorValue);
  // END SOIL TEMPERATURE
  
  // LUMINOCITY
  sensorValue = analogRead(A2);
  String luminReading = "ERROR";
  if (sensorValue > 900){
      luminReading = "Full Sun";
    }else if (sensorValue > 700){
      luminReading = "Daylight";
    }else if (sensorValue > 500){
      luminReading = "Daylight";
    }else if (sensorValue > 300){
      luminReading = "Dark";
    }else{
      luminReading = "Night";
    }
  Serial.print("Luminocity: ");
  Serial.print(luminReading );
  Serial.print(": ");
  Serial.println(sensorValue);
  // END LUMINOCITY
  
  delay(5000);
}
//
// END OF FILE
//
