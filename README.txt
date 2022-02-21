DRUGA MARIA-ALEXANDRA 313CB
PC - TEMA 1

Part 1 - Bits & Pieces
Part 1.1 - Bit by Bit
Functia get_bit verifica daca bitul i din nr este activ sau nu. 
Ne folosim de mask pentru a verifica daca bitul este 1 sau 0.
Functia flip_bit returneaza numarul cu bitul i schimbat.
Daca bitul i este 0, atunci bitul devine 1 si invers. Astfel, 
daca bitul i este 1 (verificare ce se realizeaza cu ajutorul mastii),
atunci il negam. In cazul in care bitul este 0, atunci il 
setam tot cu ajutorul mastii.
Functia activate_bit returneaza numarul cu bitul i setat.
Folosim o masca pentru a schimba bitul i in 1.
Functia clear_bit returneaza numarul cu bitul i transformat in 0.
Folosim o masca pentru a reseta bitul.

Part 1.2 - One gate to rule them all
Functia nand_gate returneaza poarta nand.
Functia and_gate returneaza poarta and folosind functia nand_gate anterioara.
Folosim functia nand_gate in care ambii parametrii sunt portile nand_gate 
dintre cei doi octeti.
Functia not_gate returneaza poarta not obtinuta prin apelarea functiei
nand_gate, in care ambii parametrii sunt reprezentati de octetul a.
Functia or_gate returneaza poarta or prin apelarea functiei nand_gate
in care primul parametru este poarta nand_gate aplicata octetului a,
iar al doilea parametru este poarta nand_gate aplicata octetului b.
Functia xor_gate returneaza poarta xor prin apelarea functiei nand_gate. 
Primul parametru este reprezentat de rezultatul apelarii functiei nand_gate 
aplicata rezultatului functiei nand_gate ce are ca parametrii pe 
a, b si parametrul a. Al doilea parametru este reprezentat de rezultatul 
apelarii functiei nand_gate aplicata rezultatului functiei nand_gate
ce are ca parametrii pe a, b si parametrul b.

Part 1.3 - Just Carry the Bit
Functia full_adder returneaza un octet in care pe prima pozitie pastrez suma, 
iar pe a doua pozitie pastrez transportul. S este calculcat cu ajutorul 
functiei xor_gate in care primul parametru este rezultatul functiei xor_gate 
aplicata lui a si b, iar al doilea parametru este c. 
C se calculeaza cu ajutorul functiei or_gate in care primul parametru 
este rezultatul returnat de functia and_gate aplicata lui a si b,
iar al doilea parametru este rezultatul returnat de functia and_gate 
aplicata lui c si rezultatului functiei xor_gate pentru a si b.
Functia ripple_carry_adder returneaza rezultatul sumei dintre a si b.
Parcurgen cu un for cei 64 de biti din a si b. In variabila A pastram 
rezultatul returnat de functia full_adder, aplicata bitului i din a 
si bitului i din b, impreuna cu variabila C (carry), initializata anterior
cu 0. Cu ajutorul functiei get_bit pastram C primul bit din A. 
Apoi verificam daca al doilea bit din A este 1 si in activam in res.

Part 2 - Shut Up Morty!
Part 2.1 The Beginning
In functia send_byte_message trimitem codificarile pentru caracterele 
'R', 'I', 'C', 'K' cu ajutorul functiei send_squanch ce are ca
parametru numarul corespunzator caracterului cerut.
In functia recv_byte_message primim 5 caractere codificate,
le decodam si le printam in format de caracter folosind fprintf. 
Parcurgem cele 5 caractere cu un for, variabila var primeste rezultatul
returnat de functia recv_squanch. Pentru a afisa caracterele in format 
standard out folosesc fprinf. Adun 64 la variabila var pentru a obtine
caracterul corespunzator.
In functia comm_byte primesc 10 caractere codificate si le trimit
inapoi codifcate. Parcurg cele 10 caractere cu ajutorul unui for,
in variabila var retin rezultatul returnat de functia recv_squanch 
si repet de doua ori functia send_squanch ce are ca parametru variabila var.

Part 2.2 - Waiting for the Message
In functia send_message trimit lungimea codificata si fiecare 
caracter codificat. Initializez variabila len cu 10 si shiftez la stanga prin
inmultirea cu 4. Cu functia send_squanch trimit lungimea codificata, 
iar apoi fiecare caracter in parte folosind tot functia send_squanch.
In functia recv_message primesc lungimea codificata, len caractere 
codificate pe care trebuie sa le afisez folosind fprint. In variabila
len retin rezultatul returnat de functia recv_squanch care reprezinta 
numarul de caractere. Pentru a decodifica lungimea shiftez la dreapta,
prin impartirea la 4. Negam bitii 4 si 5. Trimitem lungimea cu fprint.
Parcurgem cu un for toate caracterele si le afisam in format standard output.
In functia comm_message primesc un mesaj de la Rick si trebuie sa verific
daca ultimul caracter din mesaj este 'P' si in acest caz trebuie sa trimit
"PICKLERICK", iar in caz contrar trimit "VINDICATORS". In variabila len retin
lungimea codificata, o decodific prin shiftare si neg bitii 5 si 6. 
Parcurg mesajul cu for si in var retin rezultatul intors de 
functia recv_squanch. Verific daca ultimul caracter este 'P' prin
adunarea lui 64 la var si in acest caz codific lungimea len1 prin shiftare
la stanga si o trimit folosind functia send_squanch. Apoi cu aceeasi functie 
trimit si caracterele codificate. In caz contrar codific 
lungimea len2 cu shiftare la stanga si o trimit codificata 
ca apoi sa trimit si fiecare caracter codifcat. 

Part 2.3 - In the Zone
In functia send_squanch2 combinam bitii din caracterul c1 cu bitii din
caracterul c2 si folosim functia send_squanch pentru a trimite noul octet. 
Parcurgem cu for bitii din c1 si c2. Verific daca bitul i din c2 este setat, 
daca bitul i este setat atunci setez bitul j din message. 
Verific daca bitul i din c1 este setat, daca bitul i este setat setez 
bitul j + 1 din message. Trimit message folosind send_squanch.
In functia decode_squanch2 trebuie sa decodez octetul dat. 
Parcurg octetul cu un for. Verific daca bitul i din c este setat si in cazul
in care este setat si i este par setez bitul j (i / 2), 
altfel daca bitul este setat si i este impar setez 
bitul j (i / 2 + 4) din C. Res devine C.

Part 3 - Toss a coin to your Witcher
Part 3.1 - Axii
In functia find_spell trebuie sa gasesc 5 biti de 1 consecutivi si 
urmatorii 16 sunt bitii de la spell. Parcurg cu un for memory si 
verific daca gasesc 5 biti consecutivi de 1. Cum gasesc 5 biti de 1 
consecutivi parcurg urmatorii 16 biti din vraja cu un for si verific 
daca sunt setati, in cazul afirmativ setez si bitii din res 
cu ajutorul variabilei auxiliare k.
In functia find_key trebuie sa gasesc 3 biti de 1 consecutivi si
cei 16 anteriori sunt bitii de la spell. Parcurg cu un for memory 
in sens invers si verific daca gasesc 3 biti consecutivi de 1. In momentul
in care gagsesc 3 biti consecutivi parcurg cu un for cei 16 biti anteriori
si verific daca sunt setati, in caz afirmativ setez si bitii din 
res cu ajutorul variabilei auxiliare k.
In functia decrypt_spell trebuie sa gasesc vraja folosind regula.
Astfel res devine rezultatul operatiei spell ^ key.

Part 3.2 -Sword Play
In functia choose_sword trebuie sa construiesc sabia care e alcatuita
din 32 de biti. Mai intai o sa numar cati biti activi sunt in enemy
cu ajutorul variabilei contor. Daca contor este par, atunci activez
bitii 28 si 31, altfel activez bitii 30 si 29. Daca este Monster, 
atunci parcurgem cu un for bitii din (enemy & (var - enemy)) si
verificam daca sunt setati, in caz afirmativ setam si bitii i din res. 
Daca este Human, atunci parcurgem cu un for bitii din (0 - enemy) 
si verificam daca sunt setati, in caz afirmativ setam si bitii i din res.

Part 3.3 - The Witcher Trials
In functia trial_of_the_grasses parcurg cu un for bitii. 
Daca bitul i din cocktail este setat, atunci activez bitul i + 16 din res
In functia trial_of_forrest_eyes trebuie sa identific padurea in care ma aflu.
Initializez res cu 5, pentru a verifica la finalul problemei daca nu sunt
in niciuna din primele 3 paduri. Cu variabila logic0 verific daca padurea
nu contine copaci.Daca variabila logic0 e 0 atunci verific daca gasesc grupari
de 4 pomi consecutivi. Astfel, parcurg cu un for padurea si daca elementul 
nu este copac, atunci sar peste el, altfel inseamna ca este copac si verific 
daca si urmatoarele 3 elemente de dupa el sunt pomi. In caz contrar aplic break
si variabila logic devine 0. Daca al cincilea element este pom,
atunci nu se respecta regula de 4 pomi consecutivi, pentru ca am avea 5. 
Daca variabila logic a ramas 1 inseamna ca am gasit o grupare de 4 pomi si 
sarim peste 3 elemente. Daca variabila logic a ramas 1 ne aflam
in prima padure. Cu variabila contor numar cati pomi am in map, 
iar cu variabila logic verific daca elementele din mijloc sunt pomi. 
Daca contor este 2 si cele doua variabile sunt pomi, 
atunci este padurea Hindar. Apoi verific daca padurea este plina de copaci
cu variabila logic; daca variabila logic a ramas 1 inseamna ca este padurea
Wolven Glade si returnez 2.In cazul in care res a ramas 5, valoarea 
cu care am initializat la inceput, inseamna ca este ultima padure
si returnez 3.
In functia trial_of_the_dreams trebuie sa aflu distanta dintre doi biti.  
Parcurg bitii din map si caut primul bit egal 1 si pastrez in variabila 
poz1 pozitia bitului. Parcurg bitii din map in sens invers si caut ultimul 
bit egal 1 si pastrez in variabila poz2 pozitia bitului. Aflu in variabila 
d distanta dintre pozitiile celor doi biti prin scaderea lui poz1 din poz2.
Res primeste d.