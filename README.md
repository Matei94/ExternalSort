ExternalSort
============


	Matei Razvan-Madalin
	313CA
	
					Tema 5 - Sortare externa prin interclasare naturala
					
			>>>	IMPLEMENTARE	<<<
			
		Algoritmul de sortare externa din aceasta implementare urmareste urmatorii pasi:
		
	1 -	Fisierul de intrare va fi copiat in fisierul de output.
		 	Prelucrarile se fac pe fisierul de output pentru a nu distruge
		 fisierul initial.
		 	Se calculeaza in acelasi timp si numarul de elemente din fisier.
		 
	2 -	Se testeaza daca fisierul de output este sortat.
		 	In cazul in care acesta este sortat, algoritmul s-a terminat
		 si se iese din bucla infinita.
		 
	3 -	Are loc distribuirea monotoniilor din fisierul de intrare in fisierele auxiliare
		 f1 si f2.
		 	In acest timp se creeaza si vectorul m care contine date despre dimensiunile monotoniilor.
		 	Acest vector a fost creat pentru a cunoaste sfarsitul unei monotonii.
		 	De exemplu, sirul de numere 1, 4, 6, 7, 9 formeaza o monotonie dar algoritmul implementat
		 trebuie sa le trateze ca 2 monotonii diferite: 1, 4, 6 si 7, 9.
		 	m[i] va contine numarul de elemente din a i-a monotonie.
		 	Dimensiunea lui m este mereu egala cu numarul de monotonii gasite + 1.
		 	Se impart acum alternativ monotoniile in f1 si f2.
		 	
	4 - 	Urmatorul pas este cel de interclasare al monotoniilor in f1 si f2.
			In cazul in care f1 are cu o monotonie mai mult, aceasta va fi copiata in F.
			
	5 - Se reiau pasii 2 - 4 pana cand obtinem un fisier "sortat".
	
	
	
	
																												Spor la corectat!
	
	
		 	 
