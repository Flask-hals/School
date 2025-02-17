tal = 1
stora_tal = 13

while True:
    if tal > 13:
        break
    delbart = stora_tal % tal == 0
    if delbart:
        tal += 1
    else:
        tal = 1
        stora_tal += 1
print(stora_tal)
        
  
            
