#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 256

typedef struct node_structure
{
	char str[MAX];
	int idx;
	struct node_structure* next;
} Node;

Node* create_node(Node* new_node, char str[]);
void insert_after(Node** head, Node* new_node, int idx);
void insert_before(Node** head, Node* new_node, int idx);
void delete_node(Node** head, int idx);
void replace_node(Node** head, Node* new_node, int idx);
void display_node(Node** head);

int main(void)
{
	char str[MAX];
	char cmd[4];
	int idx;

	Node** head = (Node**)malloc(sizeof(Node*));
	Node* cur = NULL;
	Node* new_node = NULL;
	
	*head = NULL;

	do
	{
		printf("Command? "); fflush(stdout);
		scanf("%s", cmd);

		if(strcmp(cmd, "ina") == 0)
		{
			scanf("%d", &idx);
			scanf("%s", str);
			new_node = create_node(new_node, str);
			insert_after(head, new_node, idx);
		}
		if(strcmp(cmd, "inb") == 0)
		{
			scanf("%d", &idx);
			scanf("%s", str);
			new_node = create_node(new_node, str);
			insert_before(head, new_node, idx);
		}
		if(strcmp(cmd, "del") == 0)
		{
			scanf("%d", &idx);
			delete_node(head, idx);
		}
		if(strcmp(cmd, "rep") == 0)
		{
			scanf("%d", &idx);
			scanf("%s", str);
			new_node = create_node(new_node, str);
			replace_node(head, new_node, idx);
		}
		if(strcmp(cmd, "prn") == 0)
		{
			display_node(head);
		}

	} while(strcmp(cmd, "end") != 0);

	free(head);
	head = NULL;

	return 0;
}

Node* create_node(Node* new_node, char str[])
{
	new_node = (Node*)malloc(sizeof(Node));

	strcpy(new_node->str, str);

	return new_node;
}

void insert_after(Node** head, Node* new_node, int idx)
{
	int flag = 0;

	Node* cur = NULL;

	for(cur = *head; cur != NULL; cur = cur->next)
	{
		if(strcmp(new_node->str, cur->str) == 0)
		{
			printf("Such text exists already.\n"); fflush(stdout);
			flag = -1;
			break;
		}
		if(cur->idx == idx)
		{
			flag = 1;
			break;
		}
	}

	if(flag == 0)
	{
		if(*head == NULL)
		{
			cur = new_node;
			cur->idx = idx;
			*head = cur;
		}
		else
		{
			new_node->idx = idx;
			
			for(cur = *head; cur != NULL; cur = cur->next)
			{
				if(cur->next == NULL)
				{
					new_node->next = NULL;
					cur->next = new_node;

					if(new_node->idx < cur->idx)
					{
						int i = cur->idx;

						for( ; cur != NULL; cur = cur->next)
						{
							cur->idx = i;
							i++;
							if(i > (cur->idx)+1) break;
						}
					}
					break;
				}
			}
		}
		printf("Text inserted at the end.\n"); fflush(stdout);
	}

	if(flag == 1)
	{
		for(cur = *head; cur != NULL; cur = cur->next)
		{
			if(cur->idx == idx && (*head)->next == NULL)
			{
				new_node->next = NULL;
				(*head)->next = new_node;
				new_node->idx = ((*head)->idx)+1;
				break;
			}
			else if(cur->idx == idx)
			{
				int i = cur->idx;

				new_node->next = cur->next;
				cur->next = new_node;

				for( ; cur != NULL; cur = cur->next)
				{
					cur->idx = i;
					i++;
				}
				break;
			}
		}
		printf("OK.\n"); fflush(stdout);
	}
}

void insert_before(Node** head, Node* new_node, int idx)
{
	int flag = 0;
	
	Node* cur = NULL;
	
	for(cur = *head; cur != NULL; cur = cur->next)
	{
		if(strcmp(new_node->str, cur->str) == 0)
		{
			printf("Such text exists already.\n"); fflush(stdout);
			flag = -1;
			break;
		}
		if(cur->idx == idx)
		{
			flag = 1;

			for(cur = *head; cur != NULL; cur = cur->next)
			{
				if(strcmp(new_node->str, cur->str) == 0)
				{
					printf("Such text exists already.\n"); fflush(stdout);
					flag = -1;
					break;
				}
			} 
			break;
		}
	}

	if(flag == 0)
	{
		cur = new_node;
		cur->idx = idx;

		if(*head == NULL)
			*head = cur;
		else
		{
			cur->next = *head;
			cur->idx = ((*head)->idx)-1;
			*head = cur;

			if((*head)->idx < 1)
			{
				int i = 1;

				for(cur = *head; cur != NULL; cur = cur->next)
				{
					cur->idx = i;
					i++;
				}
			}
		}
		printf("Text inserted at the beginning\n"); fflush(stdout);
	}

	if(flag == 1)
	{
		for(cur = *head; cur != NULL; cur = cur->next)
		{
			if(cur->idx == idx && cur == *head)
			{
				new_node->idx = idx-1;
				new_node->next = cur;
				*head = new_node;

				if((*head)->idx < 1)
				{
					int i = 1;

					for(cur = *head; cur != NULL; cur = cur->next)
					{
						cur->idx = i;
						i++;
					}
				}
				break;
			}
			else if(cur->next->idx == idx)
			{
				new_node->idx = idx-1;
				new_node->next = cur->next;
				cur->next = new_node;
				
				if(cur->idx == new_node->idx)
				{
					int i = idx-1;

					for( ; cur != NULL; cur = cur->next)
					{
						cur->idx = i;
						i++;
					}
				}
				break;
			}
		}
		printf("OK.\n"); fflush(stdout);
	}
}

void delete_node(Node** head, int idx)
{
	int flag = 0;

	Node* cur = NULL;
	Node* del = NULL;

	for(cur = *head; cur != NULL; cur = cur->next)
		if(cur->idx == idx) flag = 1;

	if(flag == 0)
	{
		printf("No such index.\n"); fflush(stdout);
	}
	else
	{
		for(cur = *head; cur != NULL; cur = cur->next)
		{	
			if(cur->idx == idx && cur == *head)
			{
				int i = 1;

				del = cur;
				*head = cur->next;

				for(cur = *head; cur != NULL; cur = cur->next)
				{
					cur->idx = i;
					i++;
				}

				free(del);
				del = NULL;
				flag = 1;

				break;
			}	
			else if(cur->next->idx == idx)
			{
				int i = cur->idx;

				del = cur->next;
				cur->next = cur->next->next;

				for( ; cur != NULL; cur = cur->next)
				{
					cur->idx = i;
					i++;
				}

				free(del);
				del = NULL;
				flag = 1;

				break;
			}	
		}
		printf("Deleted.\n"); fflush(stdout);
	}
}

void replace_node(Node** head, Node* new_node, int idx) // required modification
{
	int flag = 0;

	Node* cur = NULL;

	for(cur = *head; cur != NULL; cur = cur->next)
		if(cur->idx == idx) flag = 1;

	if(flag == 0)
	{
		printf("No such index.\n"); fflush(stdout);
	}
	else
	{
		new_node->idx = idx;

		for(cur = *head; cur != NULL; cur = cur->next)
		{
			if((*head)->next == NULL)
			{
				*head = new_node;
				break;
			}
			else if(cur->idx == idx && cur == *head)
			{
				new_node->next = (*head)->next;
				*head = new_node;
				break;
			}
			else if(cur->next->idx == idx)
			{
				new_node->next = cur->next->next;
				cur->next = new_node;
				break;
			}
		}
		printf("Replaced.\n"); fflush(stdout);
	}
}

void display_node(Node** head)
{
	Node* cur = NULL;

	if(*head == NULL)
	{
		printf("The list is empty\n"); fflush(stdout);
	}
	
	for(cur = *head; cur != NULL; cur = cur->next)
	{
		printf("%d %s\n", cur->idx, cur->str); fflush(stdout);
	}
}