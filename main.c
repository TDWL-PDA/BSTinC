#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct nodeS
{
	char* word;
	int num;
	struct nodeS *right;
	struct nodeS *left;
};
typedef struct nodeS node;


node* addNum(node *currentNode, char* word)
{
	if (currentNode == NULL)
	{
		node *nodeToAdd = (node*)malloc(sizeof(node));
		nodeToAdd->word = (char*)malloc(strlen(word));
		strcpy(nodeToAdd->word, word);
		nodeToAdd->right = NULL;
		nodeToAdd->left = NULL;
		nodeToAdd->num = 1;
		return nodeToAdd;
	}
	//right is bigger (or equal to)
	//left is smaller
	int compareWords = strcmp(word, currentNode->word);
	if (compareWords > 0)
	{
		currentNode->right = addNum(currentNode->right, word);
	}
	else if (compareWords < 0)
	{
		currentNode->left = addNum(currentNode->left, word);
	}
	else if (compareWords == 0)
	{
		currentNode->num = currentNode->num + 1;
	}
	return currentNode;
}

node* findNum(node *head, char word)
{
	//right is bigger (or equal to)
	//left is smaller
	if (head == NULL || head->word == word)
	{
		return head;
	}
	else if (word >= head->word)
	{
		head = findNum(head->right, word);
	}
	else if (word < head->word)
	{
		head = findNum(head->left, word);
	}
}
void printInOrder(node *head)
{
	if (head != NULL)
	{
		printInOrder(head->left);
		printf("%s %d \n", head->word, head->num);
		printInOrder(head->right);
	}
}
void printPostOrder(node *head)
{
	if (head != NULL)
	{
		printPostOrder(head->left);
		printPostOrder(head->right);
		printf("%s %d \n", head->word, head->num);
	}
}
void printPreOrder(node *head)
{
	if (head != NULL)
	{
		printf("%s %d \n", head->word, head->num);
		printPreOrder(head->left);
		printPreOrder(head->right);
	}
}
void stripSpecialCharacter(char *str)
{
	char *newWord[182];
	int i = 0;
	for (i = 0; i < strlen(str); i++)
	{
		if (!((str[i] >= 48 & str[i] <= 57) | (str[i] >= 65 & str[i] <= 90) | (str[i] >= 97 & str[i] <= 122)))
		{
			str[i] = '\0';
		}
	}
}
void freeTree(node *head)
{
	if (head == NULL)
	{
		return;
	}
	freeTree(head->left);
	freeTree(head->right);

	free(head->word);
	free(head);
}
int main()
{
	FILE *fin;
	char *word[182];  //length of the longest published word in literature
	fin = fopen("myfile.txt", "r");
	if (!fin)
	{
		printf("Didn't open file");
	}
	//create binary tree head
	node *head = NULL;
	while (fscanf(fin, "%s", word) == 1)
	{
		stripSpecialCharacter(word);
		head = addNum(head, word);
	}
	printInOrder(head);

	fclose(fin);
	printf("\n");
	system("pause");
	return 0;
 }
