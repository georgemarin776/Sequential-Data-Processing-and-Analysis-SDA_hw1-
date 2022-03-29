~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Solutia propusa utilizeaza pentru memorarea datelor (timestamp, numar intreg,
dintr-un anumit interval, si value, numar real) o lista dublu inlantuita (si
doi pointeri first si last, ce arata spre primul, respectiv ultimul element al
listei).

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Sarcina 2.1 (e1):
    Eliminare de except, ii folosind metode statistice
    
Am implementat doua functii - "medie" si "devitatie" ce calculeaza media
valorilor din fereastra, respectiv deviatia standard a valorilor din fereastra.
Campul "exists" este utilizat pentru stergerea nodurilor care nu se afla in
intervalul mentionat (devine 0 pe masura ce parcurgem lista - nu dorim sa
eliminam, inca, nodul, caci este necesar in calcularea deviatiei). Dupa
parcurgerea tuturor nodurilor, se apeleaza functia "remove_nodes()", ce sterge
nodurile (verifica valoarea campului "exists" si, in caz ca este 0, apeleaza
functia rm, ce elimina legaturile nodului cu "previous" si "next" si
elibereaza memoria).


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~