tal = 2
summa = 0

while True:
    primtal = True
    for delare in range(2, tal):
        if tal % delare == 0:
            primtal = False

    if primtal:
        summa += tal
    
          
    tal += 1
    if tal > 999:
        break
print(summa) 
