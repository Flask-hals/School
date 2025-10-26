Bildmatchning
=============

- Ungefärligt antal timmar spenderade på labben (valfritt):
  10h


- Vad är tidskomplexiteten på "slow.cpp" och din implementation av "fast.cpp",
  uttryckt i antalet bilder (n).

slow: O(n^2)
fast: O(n)


- Hur lång tid tar det att köra "slow.cpp" respektive "fast.cpp" på de olika
  datamängderna?
  Tips: Använd flaggan "--nowindow" för enklare tidsmätning.
  Tips: Det är okej att uppskatta tidsåtgången för de fall du inte orkar vänta
  på att de blir klara.
  Tips: Vid uppskattning av körtid för "slow.cpp" är det en bra idé att beräkna
  tiden det tar att läsa in (och skala ner) bilderna separat från tiden det tar att
  jämföra bilderna. (Varför?)
  -Load image är endast O(n) då man endat itererar genom bilderna 1*n gång, medan själva jämförelsen
    tar n*n -> O(n^2) (visa tiden för inläsning vs fast.cpp totala)

|--------+-----------+----------+----------|
|        | inläsning | slow.cpp | fast.cpp |
|--------+-----------+----------+----------|
| tiny   | 61        | 102      |  95      |
| small  | 279       | 369      |  376     |
| medium | 1014      | 1498     |  963     |
| large  | 26790     | 309849   |  26503   |
|--------+-----------+----------+----------|


- Testa olika värden på "summary_size" (exempelvis mellan 6 och 10). Hur
  påverkar detta vilka dubbletter som hittas i datamängden "large"?

  -10 -> färre matchningar
  -6 -> fler matchningar
  Ju mer downsizad, ju mer "generell" kommer bilden att bli.

- Algoritmen som implementeras i "compute_summary" kan ses som att vi beräknar
  en hash av en bild. Det är dock inte helt lätt att hitta en bra sådan funktion
  som helt motsvarar vad vi egentligen är ute efter. Vilken eller vilka
  egenskaper behöver "compute_summary" ha för att vi ska kunna använda den för
  att hitta bilder som liknar varandra? (Dvs. vilka egenskaper förväntar sig
  kod som *använder* "compute_summary"?) Tycker du att den givna funktionen
  uppfyller dessa egenskaper?

  - compute_summary är till för att skapa ett "unikt id" eller fingeravtyck som kan användas för att 
      sedan jämföra med andra bilder. Hashvärdet som räknas ut används för att lagra bilderna som är lika. 
      Därmed kan man tänka att de har liknande funktionalitet, men hashvärdet är platsen där det ska lagras,
      medan compute_summary är det specifika id:t för varje bild

- Ser du några problem med metoden för att se om två bilder är lika dana?
  Fundera exempelvis på vilka typer av olikheter som tolereras, och vilka
  typer av olikheter som anses vara för stora. Matchar detta din uppfattning
  om vad som borde vara lika?

  -Bilder som är likadana fast roterade

  Föreslå en alternativ metod för att åtgärda några av problemen du såg (dvs.
  hur skulle man kunna se till att några av de "för stora" olikheterna betraktas
  som "lika"?) Vad har ditt/dina förslag för för- och nackdelar jämfört med hur
  "compute_summary" fungerar? Fokusera på vilka typer av skillnader som hanteras,
  och ange också ifall det påverkar tidskomplexiteten gentemot "fast". Ditt förslag
  behöver inte vara snabbare än det som föreslås i labben, men du ska komma på
  åtminstone en fördel med din metod.

  - t.ex. att bilderna får ha någon form av stämpel så att man kan jänföra stämpeln 
  så att alla bilder har stämpeln på samma håll. Om stämpeln alltid är i ett av hörnen kan man 
  enkelt kontrollera denna. Om stämpeln t.ex ska sitta i övre vänstra hörnet men istället sitter i 
  lägre högre hörnet kan man traversera hörnen för att hitta den och rotera bilden. Detta borde inte 
  påverka tidskomplexiteten då värsta fallet är är O(3) då det är 3 extra hörn man måste kolla, vilket är 
  en försumbar tid.

