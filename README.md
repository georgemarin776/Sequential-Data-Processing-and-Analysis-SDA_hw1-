~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Solutia propusa utilizeaza pentru memorarea datelor (timestamp, numar intreg,
dintr-un anumit interval, si value, numar real) o lista dublu inlantuita (si
doi pointeri first si last, ce arata spre primul, respectiv ultimul element al
listei).


Sarcina 2.1 (e1):
    *Eliminare de exceptii folosind metode statistice
    
Am implementat doua functii - "medie" si "devitatie" ce calculeaza media
valorilor din fereastra, respectiv deviatia standard a valorilor din fereastra.
Campul "exists" este utilizat pentru stergerea nodurilor care nu se afla in
intervalul mentionat (devine 0 pe masura ce parcurgem lista - nu dorim sa
eliminam, inca, nodul, caci este necesar in calcularea deviatiei). Dupa
parcurgerea tuturor nodurilor, se apeleaza functia "remove_nodes", ce sterge
nodurile (verifica valoarea campului "exists" si, in caz ca este 0, apeleaza
functia "rm", ce elimina legaturile nodului cu "previous" si "next" si
elibereaza memoria).


Sarcina 2.2.1 (e2) + Sarcina 2.2.2 (e3):
    *Eliminare de zgomot folosind filtre

Am adaugat un camp nou "value_alt". Functia "det_mid5"(e2) determina medianul
dintre 5 elemente (analog "medie"(e3)), valoare pe care o salveaza in 
"value_alt". Dupa ce se realizeaza filtrarea, se elimina toate elementele care
nu au o valoare in campul nou (if (Node->previous->value_alt == 0)), utilizand
functia "remove_nodes_e23", o mica variatie a functiei "remove_nodes". Pentru
a putea utiliza noile valori in cadrul altor sarcini (care folosesc campul
implicit "value"), "value" va primi valoarea memorata in "value_alt", fapt
realizat prin functia "set_value".


Sarcina 2.3 (u):
    *Uniformizarea frecventei in timp a datelor

Se calculeaza diferenta dintre doua timestamp-uri consecutive si, daca se
incadreaza in intervalul specificat (0.1, 1 secunde), campul "value"
este inlocuit conform cerintei.


Sarcina 2.4 (c):
    *Completarea datelor

Functia "w" returneaza mereu aceleasi 3 valori (ar putea fi hardcoded, utilizand
o precizie ceva mai mare a datelor). "(1 - C) * left_sum + C * right_sum"
este intocmai f(left[], right[], timestamp), valoarea ceruta in enunt.
Functia "add_before" adauga un nod nou in lista, inaintea celui specificat,
primit ca prim parametru, iar "i"-ul este timestamp-ul nou.


Sarcina 2.5 (c):
    *Statistici


Am determinat range-ul valorilor, cu "min_t6" si "max_t6". Ulterior,
se parcurge lista si se numara, pentru fiecare subdiviziune a [min_t6, max_t6],
cate valori se regasesc in interior (count++). Daca exista valori in intervalul
"delta * i" si "delta * (i + 1)", acesta este afisat.


main + "call_fct":

In "main" sunt realizate alocarile initiale ale listei. "call_fct" apeleaza
functiile precizate prin argumentele primite in linie de comanda. Daca se
detecteaza prezenta "t6", adica sarcina 2.5 (c), nu va mai fi apelata
functia "print", ce afiseaza lista integral, ci va ramane doar afisarea pentru
sarcina respectiva, cu intervalele de valori.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~