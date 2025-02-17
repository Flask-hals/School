import json
import itertools

def load(filename):
    try:
        with open(filename, encoding = "UTF-8") as file: #Öppnar json filen med encoding UTF-8
            db = json.load(file)
    except FileNotFoundError: #Ifall filen inte finns
        return None
    else:
        return db
db = load("/home/jakno825/datalager/data.json")

def get_project_count(db): #Räknar antalet projekt
    return len(db)
get_project_count(db)

def get_project(db, id): #Hämtar projektet med ett specifikt id
    for projects in range(len(db)):
        if id == db[projects]["project_id"]:
            return db[projects]
get_project(db, id)

def get_techniques(db): #Hämtar alla tekniker använda
    techniques = []
    for projects in db:
        for key, value in projects.items():
            if key == "techniques_used":
                    techniques.append(value)
                    
    techniques = list(itertools.chain(*techniques)) #Slår ihop alla listor i listan till en enda lista
    techniques = sorted(dict.fromkeys(techniques)) #Gör som en dict, och eftersom det inte kan finnas flera nycklar tas dubbletter bort, använder sorted för att göra det till en lista
    return techniques
get_techniques(db)

def get_technique_stats(db): #Hämtar alla projekt för specifika tekniker
    technique_stats = {}
    for projects in db:
        for techniques in projects["techniques_used"]:
            if techniques not in technique_stats:
                technique_stats[techniques] = [{'id': projects.get("project_id"), 'name': projects.get("project_name")}] #Techniques används som nyckeln, vi skapar en lista med en dict i där vi säger att nyckeln id ska hämta projekt_id och nyckeln namn ska hämta project_name
            else:
                technique_stats[techniques].append({'id': projects.get("project_id"), 'name': projects.get("project_name")}) #Lägger till flera projekt för samma teknik
    return technique_stats
get_technique_stats(db)

def search(db, sort_by='start_date', sort_order='desc', techniques=None, search=None, search_fields=None):
    project_list = []
    for projects in db:
        project_list.append(projects)

    if techniques != None: #Går igenom alla tekniker och matchar med de invalda teknikerna
        if techniques != []:
            techniques_pl = []
            techniques_result = []
            for tech in techniques:
                for projects in project_list:
                    if tech in projects["techniques_used"]:
                        techniques_pl.append(projects) #Gör en ny lista och lägger in allt som matchar de invalda teknikerna
                    
            for project in techniques_pl: #Loopar igenom den nya listan och skippar ifall projektet redan finns i listan
                if project not in techniques_result:
                    techniques_result.append(project)
                
            project_list = techniques_result
        
    if search != None: #Skippas ifall search är None eller tomt
        if search != []:
            search_results = []
            for fields in search_fields:
                for projects in project_list:
                    for key, value in projects.items():
                        if search_fields == None and search.lower() == value.lower(): #Ifall man vill söka inom alla fält
                            search_results.append(projects)
                        elif search_fields != None and search.lower() == projects[fields] or search.upper() == projects[fields]: #Kollar endast de inmatade fälten
                            search_results.append(projects)
                            break
            project_list = search_results

    sort_data = []
    project_order = []
    for projects in project_list: #Plockar ut de element man ska sortera projekten efter
        sort_data.append(projects[sort_by])
    sort_data = sorted(sort_data)
    for i in range(len(sort_data)): #Lägger in de sorterade projekten utefter sort_data
        for projects in project_list:
            if sort_data[i] == projects[sort_by]:
                project_order.append(projects)

    if sort_order == 'desc':
        return list(reversed(project_order))
    elif sort_order == 'asc':
        return project_order     
    
print(len(search(db)))
