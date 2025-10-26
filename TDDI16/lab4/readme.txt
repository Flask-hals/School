Mönsterigenkänning
==================

- Ungefärligt antal timmar spenderade på labben (valfritt):
  3h


- Vad är tidskomplexiteten (i ordo-notation) för värstafallstiden av
  programmen som en funktion av N (antal punkter). Ge en kort motivering.
    brute - O(n^4) - 4 for-loopar genom N (värsta), O(n^3) (bästa)
    fast - O(n^2 log n) - en yttre for-loop för N, sortering sker på O(n*log*n)
  
  Matchar brute-lösningen sitt värstafall i praktiken, eller har den ett
  medelfall som är bättre?
    Inte riktigt, hade brute-lösningen följt värstafallet så hade tidskomplexiteten varit O(n^4).
    Men eftersom brute har en optimering som skippar loopen ifall de tre första punkterna inte ligger i linjen så körs endast 3 loopar i vissa fall.
  
    brute:
    t.ex. (800/400)^4 = 16 dvs värstafall borde vara 16x större
    5360ms / 710ms ≈ 7.5  men ger här 7.5x
    
    fast:
    t.ex. (800^2 * log 800) / (400^2 * log 400) ≈ 4.5
    54 / 15  ≈ 3.6
    t.ex. (1600^2 * log 1600) / (800^2 * log 800) ≈ 4.4
    203 / 54 ≈ 3.8


- Fyll i tabellen nedan med riktiga körtider i sekunder när det känns
  vettigt att vänta på hela beräkningen.
  Ge uppskattningar av körtiden (baserat på tidskomplexiteten)
  i övriga fall.
    
      N       brute       sortering
 ----------------------------------
    150         45ms          3ms
    200        100ms          4ms
    300        330ms         13ms
    400        710ms         15ms
    800       5360ms         54ms
   1600      42880ms        203ms
   3200      ca 343s        777ms
   6400     ca 2744s      ca 3.5s
  12800    ca 21954s          15s


- Energianvändning

  Antag att du använder mönsterigenkänningsprogrammet för att analysera
  data från en kamera. Kameran sitter i en byggnad och tar en bild
  på stommen av byggnaden var 30:e minut. Bilden förbehandlas sedan
  lite, innan punkter som representerar stommen skickas till
  mönsterigenkänningsprogrammet. Hittas inte tillräckligt många raka
  linjer så betyder det att något håller på att gå sönder, och
  att byggnaden behöver noggrannare inspektion.

  Hur mycket energi sparar du på ett år om du använder din snabbare
  sorteringslösning i stället för brute-lösningen? Du kan anta följande:
  - Systemet körs 24/7 under hela året.
  - Inget annat körs på det här systemet.
  - Systemet drar 8 W när det inte gör något (idle)
  - Systemet drar 36 W när det arbetar (med 1 kärna)
  - Räkna med att ditt program körs var 30:e minut (= 2 gånger/timme)
  - För- och efterbehandling är snabba, så vi kan bortse från dem
  - Indata till programmet innehåller ca 6400 punkter
  - Det är inte skottår (= 365 dagar)

  Att jämföra med drar en kombinerad kyl/frys ca 200 kWh per år
  (enligt Energimyndigheten).
 
  Kom ihåg: energi mäts ofta i kWh, vilket är:
   energi (kWh) = effekt (kW) * tid (h)

  Tips: ett sätt att räkna på är att först räkna förbrukningen av
  ett system som inte gör något på ett helt år, sedan lägga till
  den extra förbrukningen (36 W - 8 W = 28 W) för tiden som systemet
  är aktiv.

  (Siffrorna är löst baserade på en Intel i9-9900K, vi räknar bara på
  CPU:n för enkelhets skull, besparingarna blir sannolikt större om
  vi räknar på större delar av systemet, även om andra komponenter
  också drar ström i "idle".)


Förbrukning av brute på ett år: 444,08 kWh
0.008 kW * 24 * 365 = 70.08 kWh - i idle
0.028 kW * 17520 * 2744/3600 = 374 kWh
374 + 70.08 = 444,08 kWh/år

Förbrukning av sortering på ett år: 70,56 kWh
0.008 kW * 24 * 365 = 70.08 kWh - i idle
0.028 kW * 17520 * 3.5/3600 = 0.48 kWh
0.48 + 70.08 = 70,56 kWh/år

Skillnad: ? kWh
374 - 0.48 = 373.52 kWh (utan idle i beräkningen)
444,08 - 70,56 = 373.52 kWh (med idle i beräkningen)

