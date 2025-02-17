#$ python3 lab1a.py
namn = input("Vad heter du: ")
print(f"Hej {namn}!")
ålder = int(input("Mata in din ålder:"))
år = 2024 - ålder
print(f"Du föddes år {år}.")
lan = input("Vilket län föddes du i: ")

lista = []

halva = len(namn) // 2
halva_lan = len(lan) // 2

for bokstaver in range(halva):
    lista.append (namn[bokstaver])

for bokstaver in range(halva_lan, len(lan)):
    lista.append(lan[bokstaver])

ihopslagning = "".join(lista)

print(f"Första halvan av ditt namn och andra halvan av ditt län är: {ihopslagning} ")
