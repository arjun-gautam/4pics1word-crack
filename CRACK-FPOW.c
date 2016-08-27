#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define REMOVE_SYMBOL '*'
#define LEN strlen(RANDOM_ALPHABETS_LIST)

#define TRUE   1
#define FALSE  0


char RANDOM_ALPHABETS_LIST[ BUFFER_SIZE ];
int REQUIRED_TEXT_LENGTH;
	
int main( void )
{
	char ch;
	char word[ BUFFER_SIZE ]; 
	char temp[ BUFFER_SIZE ]; 
	char random_alphabet[ BUFFER_SIZE ];
	 
	// user input
	printf("Enter the random given alphabets: ");
	scanf(" %s", RANDOM_ALPHABETS_LIST);
	printf("Enter the size of empty space (the length of word to be found): ");
	scanf(" %d", &REQUIRED_TEXT_LENGTH);
	// user input
	
	int word_found, i;
	FILE *fp;
	
	void flush( char* );
	void push( char*, char );
	void compare_and_remove( char* , char* );
	int all_alphabet_replaced( char* );
	void fill( char* );
	
	fp = fopen( "dict.txt", "r" );
	
	word_found = FALSE;
	
	flush( word );
	flush( temp );
	flush( random_alphabet );
	
	fill( random_alphabet );
	
	printf("--------------\n Search Start\n--------------\n");
	
	while( (ch = getc( fp )) != EOF ){
		
		if( ch != '\n')
		push( word, ch );
		
		if( ch == '\n' ) {
			
			push( word, '\0' );
			flush( temp );
			strcpy( temp, word );
			
			if( strlen( temp ) == REQUIRED_TEXT_LENGTH )
				word_found = TRUE;
			else
				word_found = FALSE;
				
		}
		
		if( word_found ) {

			word_found = FALSE;
			compare_and_remove( random_alphabet, temp );

			if( all_alphabet_replaced( temp ) ) {
				printf("  ==>  %s\n", word);
			}

			flush( temp );
			fill( random_alphabet );
			
		}
		
		if( ch == '\n'){
			flush( word );
		}
		
	}
	
	printf("---------------\n Search end\n---------------\n");

	fclose(fp);
	
	return 0;
}

void flush( char* str )
{
	str[0] = '\0';
}

void push( char* word, char ch )
{
	char str[2];
	str[1] = '\0';
	str[0] = ch;
	
	strcat( word, str );
}


void compare_and_remove( char* random_alphabet, char* word )
{
	int i, j;
	
	for( i = 0; i < REQUIRED_TEXT_LENGTH; i++ ) {
		for( j = 0; j < LEN; j++) {
			if( *(word + i) == *( random_alphabet + j) ) {
				*(word + i) = *(random_alphabet + j) = REMOVE_SYMBOL;
			}
		}
	}	
}

int all_alphabet_replaced( char* word )
{
	int i;
	for( i = 0; i < REQUIRED_TEXT_LENGTH; i++ ){
		if( *( word + i) != REMOVE_SYMBOL ) {
			return 0;
		}
	}
	return 1;
}

void fill( char* random_alphabet )
{
	flush( random_alphabet );
	strcat( random_alphabet, RANDOM_ALPHABETS_LIST );
}
