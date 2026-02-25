# LCD_Clock - Auto-Sync Arduino Uhr

Dieses Projekt besteht aus einer Arduino-basierten LCD-Uhr, die sich bei jedem Systemstart automatisch mit der aktuellen Uhrzeit eines Windows-Rechners synchronisiert. 

Kein manuelles Einstellen der Uhrzeit mehr nötig – einfach anstecken, Sync-Tool starten, fertig.

## Features
* **Automatischer Com-Port Scan:** Das C#-Tool findet den Arduino Uno automatisch (via WMI).
* **Präzise Synchronisation:** Überträgt die aktuelle PC-Zeit sekundengenau via Serial.
* **Sauberes Display-Design:** Formatiertes HH:MM:SS Layout mit führenden Nullen (kein Flackern).
* **Resistent gegen Drift:** Durch den Sync bei jedem Start läuft die Uhr immer exakt.

## Hardware-Anforderungen
* Arduino Uno (oder kompatibel)
* LCD Display (16x2 Zeichen, Hitachi HD44780 kompatibel)
* Jumper-Kabel & Breadboard

### Pin-Belegung (Standard)
| LCD Pin | Arduino Pin |
| :--- | :--- |
| RS | 7 |
| Enable | 8 |
| D4 | 9 |
| D5 | 10 |
| D6 | 11 |
| D7 | 12 |

## Funktionsweise
Beim Öffnen der seriellen Schnittstelle löst der Arduino einen Auto-Reset aus. Im `setup()` wartet er, bis das C#-Tool das Zeitpaket im Format `HH:mm:ss` sendet. Erst nach erfolgreichem Empfang beginnt die Uhr zu laufen und zeigt "Willkommen" in der ersten Zeile an.

## Schematic und Bilder

---
Entwickelt von [GFMsoft](https://github.com/GFMsoft)