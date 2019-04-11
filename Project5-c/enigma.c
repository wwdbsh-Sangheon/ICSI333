/*
준비물
A~Z 와 ' ' 포함한 배열.
임의의 로터값 배열.

사용자로 부터 로터값의 인덱스 입력 받음. 입력값은 문자값이기 때문에 '0'(48)을 빼줘서
사용가능한 인덱스 값으로 변환.
사용자로 부터 문자열 입력 받음.
세개의 로터값 인덱스를 이용해 세개의 로터값을 모두 더한 것을 키값으로 씀.

문자 단위로 변환.
인크립트
특정 문자의 인덱스와 키값을 합산해 알파벳 배열에서 추출해 변환. 만약, 합산값이 26보다 크다면 27로 나눈 나머지 값 이용.
입력 받은 로터 인덱스 값 증가.
디크립트
특정 문자의 인덱스와 키값을 차감해 알파벳 배열에서 추출해 변환. 만약, 차감값이 26보다 작다면 27로 나눈 나머지 값 이용.
입력 받은 로터 인덱스 값 증가.

같은 과정 반복.
*/
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