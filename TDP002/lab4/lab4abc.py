from lab4 import *
def main():
    deck = create_deck()
    shuffle_deck(deck)
    keystring = solitaire_keystream(deck, 30)
    print(keystring)
    
    deck1 = create_deck()
    shuffle_deck(deck1, 1)
    deck2 = copy_deck(deck1)

    secret_message = solitaire_encrypt("Python", deck1)
    print(secret_message)
    decrypted = solitaire_decrypt(secret_message, deck2)
    print(decrypted)
    
def solitaire_keystream(deck, length = 30):
    #deck = create_deck()
    #shuffle_deck(deck)
    keystring = ""
    while True:
        if len(keystring) < length: #Bestämmer längden på det krypterade meddelandet
            length_of_deck = size_of_deck(deck) #Hämtar längden på kortleken
            jokerA = find_card_place(deck, "Joker of spades") #Hämtar index för jokerA
            jokerB = find_card_place(deck, "Joker of hearts") #Hämtar index för joker B
            if jokerA == - 1: #Om jokerA är sist i leken flyttas den näst längst upp
                move_card(deck, jokerA, 1)
            else: #Annars flyttas jokerA ner ett steg
                move_card(deck, jokerA, jokerA - 1)

            if jokerB == - 1: #Om jokerB är sist i leken flyttas den till tredje uppifrån
                move_card(deck, jokerB, 2)
            elif jokerB == - 2: #Är jokerB näst sist flyttas den näst överst
                move_card(deck, jokerB, 1)
            else: #Annars flyttas jokerB ner två steg
                move_card(deck, jokerB, jokerB - 2)

            jokerA = find_card_place(deck, "Joker of spades")
            jokerB = find_card_place(deck, "Joker of hearts")
            if jokerA > jokerB: #Bestämmer vilken joker som är först för att kunna dela på kortleken
                deck = split_deck_switch_order(deck, jokerA, jokerB)
            else:
                deck = split_deck_switch_order(deck, jokerB, jokerA)

            bottom_card = get_value(deck, -1) #Värdet på sista kortet
            card = 0
            while card <= bottom_card: #Flyttar så många kort från toppen av kortleken till näst sist, beroende på värdet av sista kortet
                move_card(deck, 0, -1)
                card += 1
                
            top_card = get_value(deck, 0) #Värdet på översta kortet
        
            if top_card <= 26: #Om värdet på första kortet är 26 eller mindre
                first_letter_value = get_value(deck, top_card) #Tar reda på värdet av kortet som är lika många steg ner i kortleken som värdet på första kortet
                if first_letter_value > 26: #Är kortet en joker skippar vi det
                    continue
                else: #Annars adderas bokstaven till keystring
                    keystream = change_to_letters(deck, top_card) #Byter värdena mot bokstäver
                    keystring += keystream
                
        else:
            #print(keystring)
            return keystring
            break

       
def number_letter_convertion(n):
    number_to_letters = {"1": "A", "2": "B", "3": "C", "4": "D", "5": "E", "6": "F", "7": "G", "8": "H", "9": "I", "10": "J", "11": "K", "12": "L", "13": "M", "14": "N", "15": "O", "16": "P", "17": "Q", "18": "R", "19": "S", "20": "T", "21": "U", "22": "V", "23": "W", "24": "X", "25": "Y", "26": "Z"} #Dict för att konvertera bokstäver till siffror och tvärtom
    encrypt = []
    for letters in n:
        for key, value in number_to_letters.items():
            if letters == value: #Om man skickar in bokstäver
                encrypt.append(int(key))
                break
            if letters == key: #Om man skickar in siffror
                encrypt.append(value)
    return encrypt

def solitaire_encrypt(message, deck):
    message = message.upper() #Gör om meddelande till versaler
    key = solitaire_keystream(deck, len(message)) #Skapar en nyckel beroende på längden av meddelandet samt kortlekens blanding
    crypt = number_letter_convertion(message) #Gör om meddelandet till siffror

    crypt_key = number_letter_convertion(key) #Gör om nyckeln till siffror

    sums = list(zip(crypt, crypt_key)) #Lägger ihop meddelande med nyckel
    
    num = 0
    crypt_sums = []
    while True:
        if num <= len(sums) - 1:
            add = sum(sums[num]) #Summerar första siffran av meddelande och första siffran av nyckeln, osv
            crypt_sums.append(add)
            num += 1
        else:
            break
    for numbers in crypt_sums:
        if numbers > 26: #Om de ihopslagna siffrorna blir mer än 26 tar vi minus 26
            spot = crypt_sums.index(numbers)
            crypt_sums[spot] = crypt_sums[spot] - 26
        else:
            pass
    crypt_sums_str = []
    for elements in crypt_sums: #Gör om siffrorna till bokstäver
        crypt_sums_str.append(str(elements))
    convert_back = number_letter_convertion(crypt_sums_str)

    final_string = "" 
    for number in convert_back: #Lägger bokstäverna i en sträng
        final_string += number
        
    #print(f"{final_string} final")
    return final_string

#deck = create_deck()
#solitaire_encrypt("Python", deck)

def solitaire_decrypt(message, deck):  
    crypt = number_letter_convertion(message) #Gör om meddelandet till siffror
    
    key = solitaire_keystream(deck, len(message)) #Skapar en nyckel med samma längd som meddelandet
 
    crypt_key = number_letter_convertion(key) #Gör om nyckeln till siffror

    sums = list(zip(crypt_key, crypt))
    num = 0
    crypt_sums = []
    while True:
        if num <= len(sums) - 1: #Tar första siffran av meddelande minus första siffran av nyckeln, osv
            subtract = sums[num][1] - sums[num][0]
            crypt_sums.append(subtract)
            num += 1
        else:
            break
    for numbers in crypt_sums:
        if numbers < 1: #Om någon siffra blir mindre än 1 så adderar vi 26
            spot = crypt_sums.index(numbers)
            crypt_sums[spot] = crypt_sums[spot] + 26
        else:
            pass
    crypt_sums_str = []
    for elements in crypt_sums: #Gör om siffrorna till bokstäver
        crypt_sums_str.append(str(elements))
    convert_back = number_letter_convertion(crypt_sums_str)

    final_string = ""
    for number in convert_back: #Lägger bokstäverna i en sträng
        final_string += number
        
    return final_string

main()
