//	Matei Razvan-Madalin
// 313CA

#include<stdio.h>
#include<stdlib.h>

typedef unsigned long ulong;

// Functie ce verifica daca elementele dintr-un fisier sunt sortate.
int sort_test (FILE *);

int main (int argc, char *argv[]) {

	int i, file, file_size,
		 nr_elem, nr_elem_copy;
	ulong pre, urm, x1, x2;
	FILE *ff, *f1, *f2, *F;
	
	ulong *m;
	int nr_mon, mon_cur;
	
	// Creez fisierul de output (F).
	ff = fopen (argv[1], "rb");
	F  = fopen (argv[2], "wb");
	
	// Calculez dimensiunea fisierului si numarul de elemente.
	fseek (ff, 0, SEEK_END);
	file_size = ftell (ff);
	nr_elem = file_size / sizeof (ulong);
	nr_elem_copy = nr_elem;
	
	fseek (ff, 0, SEEK_SET);
	
	do {
	
		fread ( &i, sizeof (ulong), 1, ff );
		fwrite( &i, sizeof (ulong), 1, F  );
		nr_elem--;
		
	} while ( nr_elem != 0 );
	
	fflush (F );
	fclose (F );
	fclose (ff);
	// Am terminat fisierul de output.
	
	do {
	
		nr_elem = nr_elem_copy;
		
		// Testez daca fisierul este sortat.
		F = fopen (argv[2], "rb");
		if( sort_test(F) == 0 ) {
			fclose(F);
			break;
		}
		fclose (F);



		/* >>>___   PAS 1   ___<<< */
		
		// Impart monotoniile alternativ in f1 si f2.
		F  = fopen (argv[2] , "rb");
		f1 = fopen ("f1.dat", "wb");
		f2 = fopen ("f2.dat", "wb");
	
		// In vectorul m vor fi stocate dimensiunile monotoniilor.
		// De exemplu, daca prima monotonie are 3 elemente, atunci m[1] = 3.
		m = calloc(2 , sizeof(ulong));
			
		// Citesc primul element din F in pre (precedentul);
		fread ( &pre, sizeof (ulong), 1, F  );
		fwrite( &pre, sizeof (ulong), 1, f1 );
		
		// nr_mon (numarul de monotonii) este egal cu 1.
		nr_mon = 1;
		m[1]++;
		
		// file va memora fisierul in care a fost scris ultimul element.
		// Daca ultimul element a fost scris in f1, file = 1.
		// Daca ultimul element a fost scris in f2, file = 2.
		file=1;
		nr_elem--;
	
		do {
			
			// Citesc urm (urmatorul).
			fread ( &urm, sizeof(ulong), 1, F );
			nr_elem--;
		
			//Compar ultimul element citit cu precedentul.
			if ( urm >= pre ) {
			
				if ( file==1 ) {
					fwrite (&urm, sizeof(ulong), 1, f1);
					m[nr_mon]+=1;
					file=1;
					pre = urm;
					continue;
				}
				
				if ( file==2 ) {
					fwrite (&urm, sizeof(ulong), 1, f2);
					m[nr_mon]+=1;
					file=2;
				}
				
			}
		
			if ( urm < pre ) {
			
				if ( file==1 ) {
					fwrite (&urm, sizeof(ulong), 1, f2);
					m = realloc (m, (nr_mon+2) * sizeof(ulong));
					nr_mon++;
					m[nr_mon]=0;
					m[nr_mon]+=1;
					file=2;
					pre = urm;
					continue;
				}
				
				if ( file==2 ) {
					fwrite (&urm, sizeof(ulong), 1, f1);
					m = realloc (m, (nr_mon+2) * sizeof(ulong));
					nr_mon++;
					m[nr_mon]=0;
					m[nr_mon]+=1;
					file=1;
				}
				
			}
			
			pre = urm;
			
		} while ( nr_elem != 0 );
	
		fflush (f1);
		fflush (f2);
	
		fclose (F );
		fclose (f1);
		fclose (f2);
	
		// Am terminat PAS 1
	

	
		/* >>>___   PAS 2   ___<<< */
		
		// Interclasez monotoniile in F.
		F  = fopen (argv[2] , "wb");
		f1 = fopen ("f1.dat", "rb");
		f2 = fopen ("f2.dat", "rb");
		
		// mon_cur (monotonia curenta) este 1 (prima).
		mon_cur = 1;

		do {
		
			//	 Luam cazul in care numarul de monotonii este impar 
			// si f1 are o monotonie in plus.
			//  In acest caz copiem monotonia in F.
			if( mon_cur == nr_mon ) {
			
				do {
					fread  ( &x1, sizeof (ulong), 1, f1);
					fwrite ( &x1, sizeof (ulong), 1, F  );
					m[mon_cur]--;
				} while ( m[mon_cur] != 0 );
				
				break;
			}
			
			else {
			
					fread ( &x1, sizeof(ulong), 1, f1);
					fread ( &x2, sizeof(ulong), 1, f2);
					
				do {
			
					if ( x1 < x2) {
						fwrite ( &x1, sizeof (ulong), 1, F  );
						if( m[mon_cur] > 1 ) {
							fread  ( &x1, sizeof (ulong), 1, f1 );
						}
						m[mon_cur]-=1;
					}
		
					if ( x1 >= x2 ) {
						fwrite ( &x2, sizeof (ulong), 1, F  );
						if( m[mon_cur+1] > 1 ) {
							fread  ( &x2, sizeof (ulong), 1, f2 );
						}
						m[mon_cur+1]-=1;
					}
		
				} while ( m[mon_cur] != 0 && m[mon_cur+1] != 0 );

				//  Tratam acum cazurile in care raman elemente in monotonii
				// si nu au fost transcrise in F.
					
				if ( m[mon_cur] != 0 ) {
				
					do {
		
						fwrite( &x1, sizeof (ulong), 1, F  );
						if( m[mon_cur] > 1 ) {
							fread ( &x1, sizeof (ulong), 1, f1 );
						}
						m[mon_cur]--;
			
					} while ( m[mon_cur] != 0 );
					
				}
	
				if ( m[mon_cur+1] != 0 ) {
				
					do {
	
						fwrite( &x2, sizeof (ulong), 1, F  );
						if( m[mon_cur+1] > 1 ) {
							fread ( &x2, sizeof (ulong), 1, f2 );
						}
						m[mon_cur+1]--;
			
					} while ( m[mon_cur+1] != 0 );
					
				}
			
				mon_cur = mon_cur + 2;
			
			}
			
		} while ( mon_cur <= nr_mon );
	
		fflush (F );
		fclose (F );
		fclose (f1);
		fclose (f2);
		
		free(m);

		// Am terminat PAS 2.

	} while (1);
	
	return 0;
}



// Functie ce verifica daca elementele dintr-un fisier sunt sortate.
int sort_test (FILE *ff) {

	ulong x1, x2;
	int file_size, nr_elem;
	
	// getting file dimension
	fseek (ff, 0, SEEK_END);
	file_size = ftell (ff);
	nr_elem = file_size / sizeof (ulong);
	
	fseek (ff, 0, SEEK_SET);
	
	fread (&x1, sizeof (ulong), 1, ff);
	nr_elem--;
	fread (&x2, sizeof (ulong), 1, ff);
	nr_elem--;
	
	do {
	
		if (x2 < x1) {
			return -1;
		}
		
		if ( x2 >= x1 ) {
			x1 = x2;
			fread (&x2, sizeof (ulong), 1, ff);
			nr_elem--;
		}
	
	} while ( nr_elem != 0 );
	
	if ( x2 < x1 ) {
		return -1;
	}
	
	return 0;
	
}
	
