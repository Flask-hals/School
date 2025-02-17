import re #Import av regex
import urllib.request #Import av urllib.request för att kunna hämta en sida

response = urllib.request.urlopen("https://www.ida.liu.se/~TDP001/2024/material/terminal/v37.shtml") #Här hämtas sidan och sparas i variabeln response, i form av en bytes-sträng

convert = response.read().decode("ISO-8859-1") #Här läser jag in bytes-strängen och använder .decode() för att omvandla dataan till en sträng som går att läsa med ISO format, jag valde ISO då det inte fungerade med utf-8
print(convert)
pattern = re.compile("<([a-zA-Z]{1,4})") #Här använder jag re.compile() för att spara mitt regex uttryck i variabeln pattern vilet gör det möjligt för mig att återanvände uttrycket

tags = (re.findall(pattern, convert)) #Här använder jag re.findall() från regex bibloteket (re) för att leta igenom datan(findall) efter allt som matchar uttrycket som finns i pattern, convert står då för datan jag letar igenom. Och sparar detta uttryck i variabeln tags för att använda den i en for-loop.

elements = [] #Tom lista som jag sparar allt som matchar pattern

for tag in tags: #Loopar igenom datan från tags
    elements.append(tag) #Appendar allt jag hittar i listan
print(elements) #Printar listan
