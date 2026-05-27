Race condition presente solo su a.n; gli outcome di t1 e t3 sono: 1-2, 1-1, 2-2. Poi l'esecuzione di b può intromettersi e stampare
all'inizio (aggiungendo 1 in cima ai sopracitati), in mezzo o alla fine; se è in mezzo crea l'outcome 2-1-2 e se è alla fine
crea 1-2-1 e 2-2-1