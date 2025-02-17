from lab5 import *
import os

print("Welcome to Sokoban, please choose a level:")

levels = os.listdir(path='/home/jakno825/Downloads/levels')
levels = sorted(levels)

for level in enumerate(levels, start=1):
 print(level)

choice = int(input("Choose: "))

def choice_level(n):
 with open('/home/jakno825/Downloads/levels/'+levels[n]) as file:
  sokoban_load('/home/jakno825/Downloads/levels/'+levels[n])
  move_player(board)

choice_level(choice-1)

