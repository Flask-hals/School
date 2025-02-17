import os
import readchar

def main():
    print("Welcome to Sokoban, please choose a level:")

    levels = os.listdir(path='/home/jakno825/Downloads/levels') #Listar alla filer i katalogen
    levels = sorted(levels)

    for level in enumerate(levels, start=1):
        print(level)

    while True:
        try:
            choice = int(input("Choose: "))
        except ValueError:
            print("Invalid input")
            continue
        if choice > len(levels):
            print("Invalid input")
            continue
        if choice < 1:
            print("Invalid input")
        else:
            break

    current_level = choice_level(choice-1, levels)
    run_game(board, current_level)
    
    
def run_game(board, n):
    while True:
        os.system("cls" if os.name == 'nt' else 'clear')
        display_board(board)
        completed = completed_level(board)
        if completed == None:
            print(f"Congratulations, You completed level {n}!")
            return False
        else:
            print("Make your move (a)left, d(right), w(up), s(down), (q)quit.")
            move_player(board)

def choice_level(n, levels): #Laddar in den valda banan från katalogen
 with open('/home/jakno825/Downloads/levels/'+levels[n]) as file:
  sokoban_load('/home/jakno825/Downloads/levels/'+levels[n])
  return levels[n]

def completed_level(board): #Kollar ifall det finns några lådor kvar som inte står på storage
    if 'o' in board.values():
        return True
    else:
        return None
    
def create_board(): #Skapar en dict med alla x och y koordinater som nycklar, och väggar odyl som values
    board = {}
    return board

board = create_board()

def add_wall(board, y, x):
    board[(y, x)] = '#'
    return board

def add_box(board, y, x):
    board[(y, x)] = 'o'
    return board

def add_player(board, y, x):
    board[(y, x)] = '@'
    return board

def add_storage(board, y, x):
    board[(y, x)] = '.'
    return board

def check_coordinate(board, y, x): #Kollar value för specifika koordinater
    if (y, x) not in board.keys():
        return False
    else:
        return board[(y, x)]


def sokoban_load(n): #Läser av banan från filen och lägger in koordinaterna i board 
    level = []
    with open(n) as file:
        for lines in file:
            level.append(list(lines))
    for index, elements in enumerate(level):
        if '#' in elements:
            for value, items in enumerate(elements):
                if items == '#':
                    board[(index, value)] = '#'
    for index, elements in enumerate(level):
        if '@' in elements:
            for value, items in enumerate(elements):
                if items == '@':
                    board[(index, value)] = '@'
    for index, elements in enumerate(level):
        if 'o' in elements:
            for value, items in enumerate(elements):
                if items == 'o':
                    board[(index, value)] = 'o'
    for index, elements in enumerate(level):
        if '.' in elements:
            for value, items in enumerate(elements):
                if items == '.':
                    board[(index, value)] = '.'
                    
    return board

def display_board(board): #Loopar till högsta y och x värdet för att veta hur stor bana som behövs, printar ut allt
    highest_y = max(board.keys())[0]
    highest_x = max([coordinate[1] for coordinate in board.keys()])
    for y in range(highest_y+1):
        for x in range(highest_x+1):
            value = check_coordinate(board, y, x)
            if value:
                print(value, end="")
            else:
                print(" ", end="")
        print()

def player_location(board): #Håller koll på koordinaterna för spelaren under spelets gång
   for key, value in board.items():
       if value == '@':
           return key
       elif value == '+':
           return key

def player_can_move(board, n): #Kollar ett steg framför spelaren för att se vad som finns framför spelaren
    if n == 'w':
        player = player_location(board)
        next_spot = check_coordinate(board, player[0]-1, player[1])
        if next_spot == False:
            return False
        else:
            return next_spot
    elif n == 'a':
        player = player_location(board)
        next_spot = check_coordinate(board, player[0], player[1]-1)
        if next_spot == False:
            return False
        else:
            return next_spot
    elif n == 'd':
        player = player_location(board)
        next_spot = check_coordinate(board, player[0], player[1]+1)
        if next_spot == False:
            return False
        else:
            return next_spot
    elif n == 's':
        player = player_location(board)
        next_spot = check_coordinate(board, player[0]+1, player[1])
        if next_spot == False:
            return False
        else:
            return next_spot

def crate_can_move(board, n): #Kollar två steg framför spelaren när man står framför en låda, för att se steget efter lådan
    if n == 'w':
        player = player_location(board)
        next_spot = check_coordinate(board, player[0]-2, player[1])
        if next_spot == False:
            return False
        else:
            return next_spot
    elif n == 'a':
        player = player_location(board)
        next_spot = check_coordinate(board, player[0], player[1]-2)
        if next_spot == False:
            return False
        else:
            return next_spot
    elif n == 'd':
        player = player_location(board)
        next_spot = check_coordinate(board, player[0], player[1]+2)
        if next_spot == False:
            return False
        else:
            return next_spot
    elif n == 's':
        player = player_location(board)
        next_spot = check_coordinate(board, player[0]+2, player[1])
        if next_spot == False:
            return False
        else:
            return next_spot


def move_player(board):
        key = readchar.readkey().lower()
        player = player_location(board)
        if key == "w":
            moved_player = (player[0]-1, player[1]) #Moved_player används för att flytta spelaren beroende på nav
            spot = player_can_move(board, 'w') #Spot är ett steg framför spelaren
            player_value = check_coordinate(board, player[0], player[1]) #Håller koll på om spelaren representeras av @ eller +
            if spot == False:
                board[moved_player] = board.pop(player)
                if player_value == '+':
                    board.pop(player, '+')
                    board.update({player: '.'})
                    board.update({moved_player: '@'})
            elif spot == "o":
                box_spot = move_box(board, player, 'w')
                if box_spot == None:
                    pass
                else:
                    board[moved_player] = board.pop(player)
                    if player_value == '+':
                        board.pop(player, '+')
                        board.update({player: '.'})
                        board.update({moved_player: '@'})
            elif spot == "*":
                box_spot = move_box(board, player, 'w')
                if box_spot == None:
                    pass
                else:
                    board.pop(player, '@')
                    board.update({player: '.'})
                    board.update({moved_player: '+'})
                    if player_value == '+':
                        board.update({player: '.'})
            elif spot == ".":
                board.pop(player, '@')
                board.update({moved_player: '+'})
                if player_value == '+':
                    board.update({player: '.'})

        elif key == "a":
            spot = player_can_move(board, 'a')
            moved_player = (player[0], player[1]-1)
            player_value = check_coordinate(board, player[0], player[1])
            if spot == False:
                board[moved_player] = board.pop(player)
                if player_value == '+':
                    board.pop(player, '+')
                    board.update({player: '.'})
                    board.update({moved_player: '@'})
            elif spot == "o":
                box_spot = move_box(board, player, 'a')
                if box_spot == None:
                    pass
                else:
                    board[moved_player] = board.pop(player)
                    if player_value == '+':
                        board.pop(player, '+')
                        board.update({player: '.'})
                        board.update({moved_player: '@'})
            elif spot == "*":
                box_spot = move_box(board, player, 'a')
                if box_spot == None:
                    pass
                else:
                    board.pop(player, '@')
                    board.update({moved_player: '+'})
                    if player_value == '+':
                        board.update({player: '.'})
            elif spot == ".":
                board.pop(player, '@')
                board.update({moved_player: '+'})
                if player_value == '+':
                    board.update({player: '.'})

        elif key == "d":
            spot = player_can_move(board, 'd')
            moved_player = (player[0], player[1]+1)
            player_value = check_coordinate(board, player[0], player[1])
            if spot == False:
                board[moved_player] = board.pop(player)
                if player_value == '+':
                    board.pop(player, '+')
                    board.update({player: '.'})
                    board.update({moved_player: '@'})
            elif spot == "o":
                box_spot = move_box(board, player, 'd')
                if box_spot == None:
                    pass
                else:
                    board[moved_player] = board.pop(player)
                    if player_value == '+':
                        board.pop(player, '+')
                        board.update({player: '.'})
                        board.update({moved_player: '@'})
            elif spot == "*":
                box_spot = move_box(board, player, 'd')
                if box_spot == None:
                    pass
                else:
                    board.pop(player, '@')
                    board.update({moved_player: '+'})
                    if player_value == '+':
                        board.update({player: '.'})
            elif spot == ".":
                if player_value == '+':
                    board.pop(player, '+')
                    board.update({player: '.'})
                    board.update({moved_player: '+'})
                else:
                    board.pop(player, '@')
                    board.update({moved_player: '+'})

        elif key == "s":
            spot = player_can_move(board, 's')
            moved_player = (player[0]+1, player[1])
            player_value = check_coordinate(board, player[0], player[1])
            if spot == False:
                board[moved_player] = board.pop(player)
                if player_value == '+':
                    board.pop(player, '+')
                    board.update({player: '.'})
                    board.update({moved_player: '@'})
            elif spot == "o":
                box_spot = move_box(board, player, 's')
                if box_spot == None:
                    pass
                else:
                    board[moved_player] = board.pop(player)
                    if player_value == '+':
                        board.pop(player, '+')
                        board.update({player: '.'})
                        board.update({moved_player: '@'})
            elif spot == "*":
                box_spot = move_box(board, player, 's')
                if box_spot == None:
                    pass
                else:
                    board.pop(player, '@')
                    board.update({player: '.'})
                    board.update({moved_player: '+'})
                    if player_value == '+':
                        board.update({player: '.'})
            elif spot == ".":
                board.pop(player, '@')
                board.update({moved_player: '+'})
                if player_value == '+':
                    board.update({player: '.'})
        elif key == "q":
            print("Bye!")
            exit()
                          
def move_box(board, player, n):
    if n == "w":
        next_spot = crate_can_move(board, 'w') #Ett steg framför lådan
        box_value = check_coordinate(board, player[0]-1, player[1]) #Håller koll på ifall lådan är o eller *
        if next_spot == False:
            box = (player[0]-1, player[1])
            moved_box = (box[0]-1, box[1])
            board[moved_box] = board.pop(box)
            if box_value == '*':
                board.pop(box, '*')
                board.update({moved_box: 'o'})
        elif next_spot == '.':
            box = (player[0]-1, player[1])
            moved_box = (box[0]-1, box[1])
            board.pop(box, 'o')
            board.update({moved_box: '*'})
        else:
            return None
    elif n == "a":
        next_spot = crate_can_move(board, 'a')
        box_value = check_coordinate(board, player[0], player[1]-1)
        if next_spot == False:
            box = (player[0], player[1]-1)
            moved_box = (box[0], box[1]-1)
            board[moved_box] = board.pop(box)
            if box_value == '*':
                board.pop(box, '*')
                board.update({moved_box: 'o'})
        elif next_spot == '.':
            box = (player[0], player[1]-1)
            moved_box = (box[0], box[1]-1)
            board.pop(box, 'o')
            board.update({moved_box: '*'})
        else:
            return None
    elif n == "d":
        next_spot = crate_can_move(board, 'd')
        box_value = check_coordinate(board, player[0], player[1]+1)
        if next_spot == False:
            box = (player[0], player[1]+1)
            moved_box = (box[0], box[1]+1)
            board[moved_box] = board.pop(box)
            if box_value == '*':
                board.pop(box, '*')
                board.update({moved_box: 'o'})
        elif next_spot == '.':
            box = (player[0], player[1]+1)
            moved_box = (box[0], box[1]+1)
            board.pop(box, 'o')
            board.update({moved_box: '*'})
        else:
            return None
    elif n == "s":
        next_spot = crate_can_move(board, 's')
        box_value = check_coordinate(board, player[0]+1, player[1])
        if next_spot == False:
            box = (player[0]+1, player[1])
            moved_box = (box[0]+1, box[1])
            board[moved_box] = board.pop(box)
            if box_value == '*':
                board.pop(box, '*')
                board.update({moved_box: 'o'})
        elif next_spot == '.':
            box = (player[0]+1, player[1])
            moved_box = (box[0]+1, box[1])
            board.pop(box, 'o')
            board.update({moved_box: '*'})
        else:
            return None
    return board

main()
