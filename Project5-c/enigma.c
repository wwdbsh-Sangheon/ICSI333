#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

const char LETTERS[27] = {'A','B','C','D','E','F','G','H','I','J', 
                          'K','L','M','N','O','P','Q','R','S','T',
						  'U','V','W','X','Y','Z', ' '}; // 1D array for letters.
const char ROTOR_VALUES[10] = {7, 3, 0, 1, 9, 5, 2, 6, 4, 8}; // 1D array for rotor values.
const int ROTOR_SIZE = 10; // Int variable for roter size.
const int TEXT_SIZE = 256; // Int variable for text size.
int rotorPosition1, rotorPosition2, rotorPosition3; // Int variables for rotor position.

int findCharIndex(char c); // Prototypes
char encryptLetter(char unencrypted, int key);
char decryptLetter(char encrypted, int key);
void incrementRotors();
int mod(int a, int b);
int getKey();

int main(int argc, char* argv[])
{
	char inputText[TEXT_SIZE]; // 1D array for input text.
	char outputText[TEXT_SIZE]; // 1D array for output text.
	int input_text_size, i = 1; // Int variables for input text size and i.
	
	if(strcmp(argv[4], "e") != 0 && strcmp(argv[4], "d") != 0) // Condition: argv[4] is not both "e" and "d".
	{
		fprintf(stderr, "%s is wrong command!\n", argv[4]); fflush(stdout); // Error message.
		exit(1); // Exit program.
	}

	for( ; i < 4; i++) 
	{
		printf("Rotor #%d Position is set to %s\n", i, argv[i]); fflush(stdout); // Print messages for roter information.
	}

	rotorPosition1 = (int)(*argv[1] - '0'); // Getting rotor positions by using cast operator and ascii code.
	rotorPosition2 = (int)(*argv[2] - '0');
	rotorPosition3 = (int)(*argv[3] - '0');
    
	scanf("%[^\n]", inputText); // Prompt the user to enter text.
	printf("Input text supplied is: %s\n", inputText); fflush(stdout);
    input_text_size = strlen(inputText) - 1; //minus 1 to ignore \n char

    for(i = 0; i <= input_text_size; i++)
    {
    	if(strcmp(argv[4], "e") == 0) // Condition: argv[4] is "e".
    	{
    		outputText[i] = encryptLetter(inputText[i], getKey()); // Encrypting input text.
    		printf("unencrypted letter: %c | encrypted to letter: %c\n", inputText[i], outputText[i]); fflush(stdout);
    	}
    	else
    	{
    		outputText[i] = decryptLetter(inputText[i], getKey()); // Decrypting input text.
    		printf("encrypted letter: %c | unencrypted to letter: %c\n", inputText[i], outputText[i]); fflush(stdout);
    	}
	}

	outputText[input_text_size + 1] = '\0'; // Put '\0' as a last element of outputText 1D array.
	printf("Output text: %s\n", outputText); fflush(stdout);

	return EXIT_SUCCESS;
}

int findCharIndex(char c)
{
	int i = 0;

	while(LETTERS[i] != c) i++; // Increasing i, which is index, by adding 1.

	return i; // Return i.
}

char encryptLetter(char unencrypted, int key)
{
	int idx = findCharIndex(unencrypted); // Deciding index.
	// Condition: idx + key is greater than 26.
	idx + key > 26 ? (unencrypted = LETTERS[mod(idx + key, 27)]) : (unencrypted = LETTERS[idx + key]);
	incrementRotors(); // Incrementing rotors.

	return unencrypted; // return unencrypted.
}

char decryptLetter(char encrypted, int key)
{
 	int idx = findCharIndex(encrypted); // Deciding indext.
 	// Condition: idx - key is less than 0.
 	idx - key < 0 ? (encrypted = LETTERS[mod(idx - key, 27)]) : (encrypted = LETTERS[idx -key]);
 	incrementRotors(); // Incrementing rotors.

	return encrypted; // return encrypted.
}

int getKey()
{
	return ROTOR_VALUES[rotorPosition1] + ROTOR_VALUES[rotorPosition2] + ROTOR_VALUES[rotorPosition3]; // Return key value.
}

int mod(int a, int b)
{
    int r = a % b;
    
    return r < 0 ? r + b : r; // Condition: a % b is less than 0.
}

void incrementRotors() // Function for incrementing rotors.
{
	rotorPosition1++;
	if(rotorPosition1 == ROTOR_SIZE)
	{
		rotorPosition1 = 0;
		rotorPosition2++;
	}
	if(rotorPosition2 == ROTOR_SIZE)
	{
		rotorPosition2 = 0;
		rotorPosition3++;
	}
	if(rotorPosition3 == ROTOR_SIZE)
		rotorPosition3 = 0;
}
