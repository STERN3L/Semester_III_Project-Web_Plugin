#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define _XOPEN_SOURCE 500 
#define TAILLE_MAX 1000

struct entry_s {
	char *key;
	char *value;
	struct entry_s *next;
};

typedef struct entry_s entry_t;

struct hashtable_s {
	int size;
	struct entry_s **table;	
};

typedef struct hashtable_s hashtable_t;


hashtable_t *ht_create( int size ) {

	hashtable_t *hashtable = NULL;
	int i;

	if( size < 1 ) return NULL;

	if( ( hashtable = malloc( sizeof( hashtable_t ) ) ) == NULL ) {
		return NULL;
	}

	if( ( hashtable->table = malloc( sizeof( entry_t * ) * size ) ) == NULL ) {
		return NULL;
	}
	for( i = 0; i < size; i++ ) {
		hashtable->table[i] = NULL;
	}

	hashtable->size = size;

	return hashtable;	
}

/*Take 2 argument : struct hashtable and pointer to a string*/
int ht_hash( hashtable_t *hashtable, char *key ) {

	unsigned long int hashval;
	int i = 0;

	/* Convert our string to an integer */
	while( hashval < ULONG_MAX && i < strlen( key ) ) {                                            /*either hashval reaches the maximum value of an unsigned long integer, or i reaches the length of the string key.*/
		hashval = hashval << 8;
		hashval += key[ i ];
		i++;
	}

	return hashval % hashtable->size;
}

entry_t *ht_newpair( char *key, char *value ) {
	entry_t *newpair;

	if( ( newpair = malloc( sizeof( entry_t ) ) ) == NULL ) {
		return NULL;
	}

	if( ( newpair->key = strdup( key ) ) == NULL ) {
		return NULL;
	}

	if( ( newpair->value = strdup( value ) ) == NULL ) {
		return NULL;
	}

	newpair->next = NULL;

	return newpair;
}

void ht_set( hashtable_t *hashtable, char *key, char *value ) {
	int bin = 0;
	entry_t *newpair = NULL;
	entry_t *next = NULL;
	entry_t *last = NULL;

	bin = ht_hash( hashtable, key );

	next = hashtable->table[ bin ];

	while( next != NULL && next->key != NULL && strcmp( key, next->key ) > 0 ) {
		last = next;
		next = next->next;
	}

	if( next != NULL && next->key != NULL && strcmp( key, next->key ) == 0 ) {

		free( next->value );
		next->value = strdup( value );

	} else {
		newpair = ht_newpair( key, value );

		if( next == hashtable->table[ bin ] ) {
			newpair->next = next;
			hashtable->table[ bin ] = newpair;
	
		} else if ( next == NULL ) {
			last->next = newpair;
	
		} else  {
			newpair->next = next;
			last->next = newpair;
		}
	}
}

char *ht_get( hashtable_t *hashtable, char *key ) {
	int bin = 0;
	entry_t *pair;

	bin = ht_hash( hashtable, key );

	pair = hashtable->table[ bin ];
	while( pair != NULL && pair->key != NULL && strcmp( key, pair->key ) > 0 ) {
		pair = pair->next;
	}

	if( pair == NULL || pair->key == NULL || strcmp( key, pair->key ) != 0 ) {
		return NULL;

	} else {
		return pair->value;
	}
	
}


void print_table(hashtable_t *hashtable)
{
    printf("\nHash Table\n-------------------\n");

    for (int i = 0; i < hashtable->size; i++)
    {
        if (hashtable -> table[i])
        {
            printf("Index:%d, Key:%s, Value:%s\n", i, hashtable -> table[i] -> key, hashtable -> table[i] -> value);
        }
    }

    printf("-------------------\n\n");
}


int writeFile(int IsPhishing,char * txt){

	FILE *fptr;

   fptr = fopen("history.txt","a");

   if(fptr == NULL)
   {
      printf("Error!");   
      exit(1);             
   }

   if (IsPhishing){
   	fprintf(fptr,"%s=0\n",txt);
   }
   else{
   	fprintf(fptr,"%s=1\n",txt);
   }
   //fprintf(fptr,"%s",txt);
   fclose(fptr);
   return 0;
}

int main() {

  printf("[/!\\] Enter a domain name and check if it is already listed as a phising site.\n");
  printf("[/!\\] If you want to quit this programm type 'quit' in the command line.\n");


  // Create an integer variable that will store the number we get from the user
  char myDomain[50];
  int Bool = 1;

  //Open file
  FILE *f;
  f = fopen("phising_site.txt","r");
  if (NULL == f){
    printf("[-] File can't be opened.\n");
    fclose(f);
  }
  printf("[+] File is loaded !\n");
  fclose(f);

  //Ouverture du fichier txt
  FILE* fichier = NULL;
  char chaine[TAILLE_MAX] = "";

  //initilisation de la hash table
  hashtable_t *hashtable = ht_create( 65536 );
    
  fichier = fopen("phising_site.txt", "rb"); //ouverture du .txt en binaire pour lire les caractères spéciaux

  if(fichier != NULL){
        while(fgets(chaine, TAILLE_MAX, fichier) != NULL){ //lis le fichier ligne par ligne
            if (strcmp(chaine, "\n") == 0){
                printf("[-] A Enter space detected \n");
            }
            else{
                chaine[strlen(chaine)-1]='\0';  
                ht_set( hashtable, chaine, chaine );
            }
        }
        fclose(fichier);
    }
    else{
        printf("[-] Unable to open the file\n");
    }

  while (Bool == 1)
    {
      printf("[/!\\] Enter a domain name : \n"); 
      scanf("%s", myDomain);
      if (strcmp(myDomain,"quit") == 0){
        printf("[/!\\] You leave the programm !");
        Bool = 0;
      }
      else{
          
        if (ht_get( hashtable, myDomain ) != NULL){
          printf("[+] The site : %s is a phising site\n", myDomain);
		  writeFile(0, myDomain);
        }
        else{
          printf("[-] The site : %s isn't a phising site\n", myDomain);
		  writeFile(1, myDomain);

        }
      }
    }

    return 0;
  }
