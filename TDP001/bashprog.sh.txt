#!/bin/bash

echo "Vänligen mata in ett tal: "
read start
echo "Och ett större tal: "
read end

function prime_numbers(){
    prime_numbers=() #Array, liknande en lista i python
    for numbers in $(seq $start $end); do #Loopar alla nummer
	prime=1 #Motsvarar prime = True, antar att alla nummer är primtal
	for divider in $(seq 2 $((numbers-1))); do #Loopar från två upp till en under det aktuella numret
	    if (( numbers % divider == 0 )); then #Om numret modulo något tal mellan 2 till nummer -1 är det inte ett primtal
		prime=0 #Sätter då primtal = False
		break
	    fi #Avslutar if-satsen
	done #Avslutar for loopen
	if (( prime == 1 )); then
	    prime_numbers+=($numbers) #Liknande att appenda till en lista i python
	    counter=0 #Funkar som index i arrayen
	    resultat=()
	    while [ $counter -lt ${#prime_numbers[@]} ]; do #Fortsätter sålänge counter är mindre än längden på arrayen
		#${#prime_numbers[@]} detta uttryck funkar som len(lista) i python, # är lite som len funktionen och kollar hur många element som finns i arrayen, [@] specifiserar att det är alla element vi ska kolla
		resultat+=("${prime_numbers[$counter]}") #Skriver ut elementen som matchar counter
		counter=$((counter + 2)) #Plussar counter med 2 för att endast visa vartannat primtal
	    done
	
	fi
	
    done
    echo ${resultat[@]}
}

prime_numbers start end
