#! /usr/bin/env python3
import re
import sys
import os

path = os.path.expanduser('~') #Path för att vi alltid ska söka underliggande filer/kataloger i hemkatalogen
pattern = '#BEGIN COPYRIGHT.*#END COPYRIGHT' #För att hitta copyright kommentarer

copyright_file = sys.argv[1] #Filen med copyright pattern
destination_file = sys.argv[2] #Fil eller katalog där vi ska söka
copyright_file_path = os.path.join(path, copyright_file) #Sätter ihop sökvägen från hemkatalog till copyright filen
    
with open(copyright_file_path, 'r') as file: #Öppnar och läser in copyright pattern
    copyright_content = file.read()

def copyrighter(copyright_content, destination_file_path):
    end = re.findall('.{3}$', destination_file_path) #Kollar de tre sista tecknena för att endast hitta filer med .py
    end = "".join(end) #Gör om till en sträng
    arg4 = '.'+sys.argv[4] #Lägger till . innan argument 4
    if sys.argv[3] == "-c" and end == arg4: #Kollar ifall det finns filer som matchar argument 4
        with open(destination_file_path, 'r') as file: 
            destination = file.read()
            destination = destination.split('#END COPYRIGHT') #Splittar på end copyright
            destination_list = []
            for items in destination:
                if '#BEGIN COPYRIGHT' in items:
                    items += '#END COPYRIGHT' 
                destination_list.append(items) #Lägger till end igen ifall det finns en begin copyright
        
            upd_destination = [] 
            for lines in destination_list: #Loopar listan med innehåll i filen
                if re.search(pattern, lines, re.DOTALL):
                    insert = re.sub(pattern, copyright_content, lines, flags=re.DOTALL)
                    upd_destination.append(insert) #Lägger till innehållet i en ny fil
            upd_destination = "".join(upd_destination)
            with open(destination_file_path, 'w') as file:
                file.write(upd_destination) #File skriver över allt i filen med det nya innehållet

            try:
                if sys.argv[5] == "-u":
                    new_name = re.sub(end, sys.argv[6], destination_file_path)
                    os.rename(destination_file_path, new_name) #Döper om vilen till argument 6
            except IndexError:
                pass


try:
    folder = os.listdir(path=sys.argv[2]) #Ifall det är en katalog som argument 2
except NotADirectoryError:
    destination_file_path = os.path.join(path, destination_file)
    copyrighter(copyright_content, destination_file_path) #Ifall det är en fil
else:
    for files in folder: #Ifall det är en katalog
        destination_file_path = os.path.join(path, destination_file, files)
        copyrighter(copyright_content, destination_file_path)



    
