#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#define MAX 81
#define MAX_NUM_LABEL 100

typedef struct id_structure
{
	char id[11];
	struct id_structure* next;
}Node;

Node* create_node(Node* new_node, char* token);
FILE* print_variable_id(Node* head, FILE* input_file, FILE* output_file, char line[], int offset);
FILE* print_flow_control(Node* head, FILE* input_file, FILE* output_file, char line[], int offset);

int main(int argc, char* argv[])
{
	if(argc != 4 || (strcmp(argv[1], "-v") != 0 && strcmp(argv[1], "-f") != 0 && strcmp(argv[1], "-b") != 0))
	{
		fprintf(stderr, "Usage: prog4.out flag inputfile outputfile\n"); fflush(stdout);
		exit(1);
	}

	Node* head = (Node*)malloc(sizeof(Node)*MAX_NUM_LABEL);
	Node* new_node = NULL;
	Node* cur = NULL;

	FILE* input_file;
	FILE* output_file;

	char line[MAX];
	char* token;
	char* token2;
	int flag = 0;
	int offset = 1;
	
	head = NULL; 
	cur = head; 
	
	if((input_file = fopen(argv[2], "r")) == NULL || (output_file = fopen(argv[3], "w")) == NULL)
	{
		perror("Open failed.");
		exit(1);
	}
	
	while(fgets(line, MAX, input_file) != NULL)
	{
		if(strstr(line, ".text")) flag = 2;

		if(flag == 1)
		{	
			if(token[0] == '\n') continue;
			
			token2 = strtok(token, ": \t");
			new_node = create_node(new_node, token2);

			if(head == NULL)
			{
				cur = new_node;
				head = cur;
				cur->next = NULL;
			}
			else
			{
				new_node->next = cur->next;
				cur->next = new_node; 
				cur = cur->next;
			}
			offset++;
		}

		if(flag == 2)
		{
			if(line[0] == '\n') continue;
			if(strchr(line, ':'))
			{
				token2 = strtok(token, ": \t");
				new_node = create_node(new_node, token2);
				new_node->next = cur->next;
				cur->next = new_node; 
				cur = cur->next;
			}
		}

		if(strstr(line, ".data")) flag = 1;
		token = strtok(line, "#\n");
	}

	if(strcmp(argv[1], "-v") == 0)
	{
		output_file = print_variable_id(head, input_file, output_file, line, offset);
	}
	if(strcmp(argv[1], "-f") == 0)
	{
		output_file = print_flow_control(head, input_file, output_file, line, offset);
	}
	if(strcmp(argv[1], "-b") == 0)
	{
		output_file = print_variable_id(head, input_file, output_file, line, offset);
		output_file = print_flow_control(head, input_file, output_file, line, offset);
	}
	
	for(cur = head; cur != NULL; cur = cur->next) free(cur);
	
	fclose(output_file);
	fclose(input_file);

	return 0;
}

Node* create_node(Node* new_node, char* token)
{
	new_node = (Node*)malloc(sizeof(Node));
	
	strcpy(new_node->id, token);

	return new_node;
}

FILE* print_variable_id(Node* head, FILE* input_file, FILE* output_file, char line[], int offset)
{
	Node* cur = NULL;

	char identifier[7];
	char* token;
	int position = 1;
	int flag = 0;
	
	for(cur = head; position < offset; cur = cur->next)
	{
		rewind(input_file);
		fprintf(output_file, "Variable ID -%s-\n", cur->id); fflush(stdout);
		
		while(fgets(line, MAX, input_file) != NULL)
		{
			memcpy(identifier, line, 7);

			if(strstr(identifier, cur->id)) continue;
			if(line[0] == '\n' || line[0] == '#') continue;
			if(flag == 1)
			{
				token = strtok(line, "#\n");
				
				if(strstr(token, cur->id))
				{
					fprintf(output_file, "\t%s\n", token); fflush(stdout);
				}
			}
			if(strstr(line, ".text")) flag = 1;
		}
		position++;
		flag = 0;
	}

	return output_file;
}

FILE* print_flow_control(Node* head, FILE* input_file, FILE* output_file, char line[], int offset)
{
	Node* cur = NULL;

	char identifier[7];
	char* token;
	int position = 1;
	int flag = 0;
	
	for(cur = head; position < offset; cur = cur->next) position++;
	
	for( ; cur != NULL; cur = cur->next)
	{	
		rewind(input_file);
		fprintf(output_file, "Flow Control ID -%s-\n", cur->id); fflush(stdout);

		while(fgets(line, MAX, input_file) != NULL)
		{
			memcpy(identifier, line, 7);
			if(strstr(identifier, cur->id)) continue;
			if(line[0] == '\n' || line[0] == '#') continue;
			if(flag == 1)
			{
				token = strtok(line, "#\t\n");

				if(strstr(token, cur->id) && (strchr(token, ':') == NULL))
				{
					fprintf(output_file, "\t%s\n", token); fflush(stdout);
				}
			}
			if(strstr(line, ".text")) flag = 1;
		}
		flag = 0;
	}

	return output_file;
}