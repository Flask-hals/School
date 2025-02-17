import random

def create_deck():#Skapar en kortlek
    deck = []
    for i in range(1, 27):
        if i < 14:
            deck.append((i, 1))
        elif i < 27:
            deck.append((i, 2))
    deck.append((27, 1))
    deck.append((27, 2))
    return deck

def copy_deck(deck):#Kopierar en kortlek så man får två likadana
    deck2 = deck.copy()
    return deck2


def shuffle_deck(deck, n=0):#Blandar en kortlek om man endast skickar in deck som argument, skickar man in två argument aktiveras seed med det inmatade argumentet och kortleken blandas ut efter argumentet
    if n != 0:
        random.seed(n)
        random.shuffle(deck)
    else:
        random.shuffle(deck)
    return deck

def move_card(deck, cards, location):#Flyttar ett kort till en annan plats i kortleken
    card = deck.pop(cards)
    deck.insert(location, card)
    return deck

def remove_card(deck, n): #Tar bort ett kort
    deck.pop(n)
    return deck

def read_card(deck, n): #Låter användaren läsa av ett specifikt kort
    deck_dict = {"Ace of spades": (1, 1), "2 of spades": (2, 1), "3 of spades": (3, 1), "4 of spades": (4, 1), "5 of spades": (5, 1), "6 of spades": (6, 1), "7 of spades": (7, 1), "8 of spades": (8, 1), "9 of spades": (9, 1), "10 of spades": (10, 1), "Knight of spades": (11, 1), "Queen of spades": (12, 1), "King of spades": (13, 1), "Ace of hearts": (14, 2), "2 of hearts": (15, 2), "3 of hearts": (16, 2), "4 of hearts": (17, 2), "5 of hearts": (18, 2), "6 of hearts": (19, 2), "7 of hearts": (20, 2), "8 of hearts": (21, 2), "9 of hearts": (22, 2), "10 of hearts": (23, 2), "Knight of hearts": (24, 2), "Queen of hearts": (25, 2), "King of hearts": (26, 2), "Joker of spades": (27, 1), "Joker of hearts": (27, 2)}
    for cards in deck:
        if cards == deck[n - 1]:
            for key, value in deck_dict.items():
                if cards == value:           
                    return key
                
def read_deck(deck): #Läser av hela kortleken
    deck_dict = deck_dict = {"Ace of spades": (1, 1), "2 of spades": (2, 1), "3 of spades": (3, 1), "4 of spades": (4, 1), "5 of spades": (5, 1), "6 of spades": (6, 1), "7 of spades": (7, 1), "8 of spades": (8, 1), "9 of spades": (9, 1), "10 of spades": (10, 1), "Knight of spades": (11, 1), "Queen of spades": (12, 1), "King of spades": (13, 1), "Ace of hearts": (14, 2), "2 of hearts": (15, 2), "3 of hearts": (16, 2), "4 of hearts": (17, 2), "5 of hearts": (18, 2), "6 of hearts": (19, 2), "7 of hearts": (20, 2), "8 of hearts": (21, 2), "9 of hearts": (22, 2), "10 of hearts": (23, 2), "Knight of hearts": (24, 2), "Queen of hearts": (25, 2), "King of hearts": (26, 2), "Joker of spades": (27, 1), "Joker of hearts": (27, 2)}
    for cards in deck:
        for key, value in deck_dict.items():
            if cards == value:
                return key

def split_deck_switch_order(deck, lowest, biggest): #Delar kortleken i tre och byter ordning
    card = 0
    deck1 = []
    deck2 = []
    deck3 = []
    for cards in deck:
        if card < lowest:
            deck1.append(cards)
        elif card >= lowest and card <= biggest:
            deck2.append(cards)
        elif card > biggest:
            deck3.append(cards)
        card += 1
    deck.clear()
    deck.extend(deck3 + deck2 + deck1)
    return deck

def change_to_letters(deck, n): #Ger en bokstav beroende på värdet av ett kort
     key_to_letters = {1: "A", 2: "B", 3: "C", 4: "D", 5: "E", 6: "F", 7: "G", 8: "H", 9: "I", 10: "J", 11: "K", 12: "L", 13: "M", 14: "N", 15: "O", 16: "P", 17: "Q", 18: "R", 19: "S", 20: "T", 21: "U", 22: "V", 23: "W", 24: "X", 25: "Y", 26: "Z"}
     for key, value in key_to_letters.items():
         if __name__ == "__main__":
             if deck[n - 1][0] == 27: 
                 print("Joker dont have a letter")
                 break
             elif deck[n - 1][0] == key:
                     print(value)
         elif deck[n][0] == key:
             return value

def find_card_place(deck, n): #Visar vart ett specifikt kort i kortleken är
    deck_dict = deck_dict = {"Ace of spades": (1, 1), "2 of spades": (2, 1), "3 of spades": (3, 1), "4 of spades": (4, 1), "5 of spades": (5, 1), "6 of spades": (6, 1), "7 of spades": (7, 1), "8 of spades": (8, 1), "9 of spades": (9, 1), "10 of spades": (10, 1), "Knight of spades": (11, 1), "Queen of spades": (12, 1), "King of spades": (13, 1), "Ace of hearts": (14, 2), "2 of hearts": (15, 2), "3 of hearts": (16, 2), "4 of hearts": (17, 2), "5 of hearts": (18, 2), "6 of hearts": (19, 2), "7 of hearts": (20, 2), "8 of hearts": (21, 2), "9 of hearts": (22, 2), "10 of hearts": (23, 2), "Knight of hearts": (24, 2), "Queen of hearts": (25, 2), "King of hearts": (26, 2), "Joker of spades": (27, 1), "Joker of hearts": (27, 2)}
    for key, value in deck_dict.items():
        if n == key:
            for cards in deck:
                if cards == value:
                    card_place = deck.index(cards)
                    #print(f"{n} is at place {deck.index(cards) + 1}")
                    return card_place

def size_of_deck(deck): #Säger hur många kort som kortleken består av
    return len(deck)

def get_value(deck, n): #Ger värdet av ett specifikt kort
    if __name__ == "__main__":
        print(deck[n - 1][0])
    else:
        return deck[n][0]
