#!/usr/bin/env python3
def frame():
    mening = input("Skriv en mening: ")
    längd = len(mening) + 2
    asterisker = längd * "*"
    mening1 = "*" + mening.center(längd - 2) + "*"
    print(asterisker)
    print(mening1)
    print(asterisker)
frame()
def triangle():
    höjd = int(input("Hur hög vill du ha din triangle?: "))
    for i in range(höjd):
        print("*", end="")
        print(i * "**")
triangle()
def flag():
    indata = int(input("Hur stor flagga vill du ha?: "))
    storlek = indata * 10
    for i in range(storlek):
        if i % (storlek // 2) == 0:
            print("")
        else:
            print(storlek * "*", end="")
            print(" ", end=" ")
            print(storlek * "*")
flag()
