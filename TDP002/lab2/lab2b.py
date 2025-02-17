def create_shopping_list():
    slist = ["Kurslitteratur", "Anteckningsblock", "Penna"]
    return slist
    
def shopping_list(n):
    for i, varor  in enumerate(slist, +1):
        print(i, varor)

def shopping_add(n):
    add = str(input("Vad ska läggas till i listan?: "))
    slist.append(add)

def shopping_remove(n):
    bort = int(input("Vilken sak vill du ta bort ur listan?: "))-1
    del slist[bort]

def shopping_edit(n):
    ändra = int(input("Vilken sak vill du ändra på?: "))-1
    byt = input(f"Vad ska det stå istället för {n[ändra]}?: ")
    del slist[ändra]
    slist.insert(ändra, byt)
