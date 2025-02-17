import requests
def main():   
    while True:
        site = server_requests("https://www.ida.liu.se/~TDP002/pokeapi/api/v2/poemon/") #Hämtar json fil

        if site == None:
            continue # Eller break
        
        pokemon = input("Enter a Pokemon name: ")
        pokemon_data = pokemon_info(site, pokemon) #Url för pokemonen
        
        if pokemon_data == None: #Ifall input pokemonen inte finns så returnerar pokemon_data none och while-loopen börjar om
            print("Invalid Pokemon!")
            continue

        
        ability_info_url = ability_site(pokemon_data) #Sparar två listor i en lista med ability namn, samt ability url

        
        if ability_info_url == None:
            continue
        
        description = ability_info(ability_info_url[1]) #Beskrivning av abilityn, skickar endast in listan med index 1 för att den består av url

        print(f"{pokemon} has {len(description)} abilities. \n")

        name_info = zip(ability_info_url[0], description) #Använder zip() för att lägga ihop två listor
        name_info = dict(name_info) #Gör om den listan till en dict
        for ability_names in name_info:
            ability_description = name_info.get(ability_names)
            print(f"Ability {ability_names}: \n{ability_description} \n")

def server_requests(n):
      site = requests.get(n)
      if site.status_code != 200:
          print("Problem with url or server")
          return None
      else:
          site_dict = site.json()
          return site_dict
    
def pokemon_info(data, pokemon): #Funkton för att jämför input med pokemons samt returnerar url för pokemon
    url = ("https://www.ida.liu.se/~TDP002/pokeapi")
    for pokemons in data["results"]:
        if pokemon == pokemons["name"]:
            ability_url = url + pokemons["url"]
            return ability_url
    return None
            

def ability_site(pokemon_data): #Går in på urlen för pokemonen och hämtar ability namnen samt url för abilitys
    url = ("https://www.ida.liu.se/~TDP002/pokeapi")
    site = server_requests(pokemon_data)
    if site == None:
        return None
    else:
        attack_url = [] #Urlen för varje ability sparas i denna lista
        attack_name = [] #Namnet för varje ability sparas i denna lista
        for attacks in site["abilities"]:
            attack_name.append(attacks["ability"]["name"])
            attack_url.append(url + attacks["ability"]["url"])
        attacks = attack_name, attack_url #Listorna läggs ihop för att kunna returnera en lista
        return attacks

def ability_info(ability_info_url): #Returnerar rätt ability beskrivning
    ability_description = [] #Beskrivningen av varje ability läggs i denna lista
    for urls in range(len(ability_info_url)):
        site = server_requests(ability_info_url[urls])
        #info_site_dict = info_site.json()
        for ability in site["flavor_text_entries"]:
            if ability["language"]["name"] == "en" and ability["version_group"]["name"] == "ultra-sun-ultra-moon":
                ability_description.append(ability["flavor_text"])
    return ability_description  



main()
