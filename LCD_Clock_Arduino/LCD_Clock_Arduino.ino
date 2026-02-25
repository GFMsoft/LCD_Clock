#include <LiquidCrystal.h>
#include <time.h>
#include <TimeLib.h>

int i = 0;
tmElements_t tm;
const char *monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

// init library
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
String topLineMessage = "Warte auf sync...";

// Serial Vars
String serialData;
bool serialAlive = false;
bool timeSync = false;

void setup()
{

  Serial.begin (9600);
  lcd.begin(16, 2);

  // Print die erste Line aufs LCD
  lcd.print(topLineMessage);

  // Warte bis die aktuelle Zeit über Serial geschrieben wird
  while(timeSync == false)
  {
    Serial.println("warte auf sync....");
    delay(250);

    if(Serial.available() > 0)
      {
        serialAlive = true;
        serialData = Serial.readString();
        Serial.println("DATA: "+ serialData);
        lcd.begin(16, 2);
        lcd.clear();

        // ToplineMessage anpassen, wenn Sync done
        topLineMessage = "Willkommen";
        lcd.print(topLineMessage);
        timeSync = true;
      }
  }

  Serial.println("SETUP START");
  Serial.println(__DATE__);
  Serial.println(__TIME__);
  if (getDate(__DATE__) && getSyncTime(serialData))
  {
    Serial.println("AVR Macro strings converted to tmElements.");
  }
  setTime(makeTime(tm)); //set Ardino system clock to compiled time
}

void loop()
{
  lcd.setCursor(0, 1);

  // Stunde
  if (hour() < 10)
  {
    lcd.print('0');
  }
  lcd.print(hour());
  lcd.print(':');

  // Minute
  if (minute() < 10)
  {
    lcd.print('0');
  }
  lcd.print(minute());
  lcd.print(':');

  // Sekunde
  if (second() < 10)
  {
    lcd.print('0');
  }
  lcd.print(second());
  digitalClockDisplay();
  delay(1000);
}

// Sync die Zeit via Serial vom Hostrechner.
bool getSyncTime(String timeFromSerial)
{
  int std, min, sec;

  if (sscanf(timeFromSerial.c_str(), "%d:%d:%d", &std, &min, &sec) != 3)
  {
    return false;
  }  
  tm.Hour = std;
  tm.Minute = min;
  tm.Second = sec;
  return true;
}

// Wandelt ein Datum im Textformat in ein strukturiertes Zeit-Format.
bool getDate(const char *str)
{
  char Month[12];
  int Day, Year;
  uint8_t monthIndex;

  if (sscanf(str, "%s %d %d", Month, &Day, &Year) != 3)
  {
    return false;
  }

  for (monthIndex = 0; monthIndex < 12; monthIndex++)
  {
    if (strcmp(Month, monthName[monthIndex]) == 0)
    {
      break;
    }
  }
  if (monthIndex >= 12)
  {
    return false;
  }

  tm.Day = Day;
  tm.Month = monthIndex + 1;
  tm.Year = CalendarYrToTm(Year);
  return true;
}

void digitalClockDisplay()
{
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(month());
  Serial.print('/');
  Serial.print(day());
  Serial.print('/');
  Serial.print(year()); 
  Serial.println(); 
}

void printDigits(int digits)
{
  Serial.print(":");
  if(digits < 10)
  {
    Serial.print('0');
  }
  Serial.print(digits);
}