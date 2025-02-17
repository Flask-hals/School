def main():
    slist = ["Kurslitteratur", "Anteckningsblock", "Penna"]
    print("Välkommen till shoppinglistan, välj ett alternativ:")
    list = ["Skriv ut en existerande lista", "Lägg till ett föremål i listan", "Ta bort ett föremål ur listan", "Ändra ett föremål i listan", "Avsluta"]
    while True:    
        for index, val in enumerate(list, +1):
            print(index, val, "\n")
        väg = int(input())
        if väg == 1:
            shopping_list(slist)
        elif väg == 2:
            shopping_add(slist)
        elif väg == 3:
            shopping_remove(slist)
        elif väg == 4:
            shopping_edit(slist)
        elif väg == 5:
            print("Hej då!")
            return False 
    
def shopping_list(n):
    for i, varor  in enumerate(n, +1):
        print(i, varor, "\n")

def shopping_add(n):
    add = str(input("Vad ska läggas till i listan?: "))
    n.append(add)

def shopping_remove(n):
    bort = int(input("Vilken sak vill du ta bort ur listan?: "))-1
    del n[bort]

def shopping_edit(n):
    ändra = int(input("Vilken sak vill du ändra på?: ")) - 1
    byt = input(f"Vad ska det stå istället för {n[ändra]}?: ")
    del n[ändra]
    n.insert(ändra, byt)

main()
