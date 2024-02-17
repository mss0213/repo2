#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char letter;
    struct node* next;
} node;

// Returns number of nodes in our linked list
int length(node* head) {
    int count = 0; // Initialize counter to 0, which will be incremented for each node.
    node* current = head;
    while (current != NULL) {
        count++; // Increment the count as we iterate through the list.
        current = current->next; // This will move to the next node until the null terminator is reached.
    }
    return count;
}

// parses the string in the linkedList
// if the linked list is head -> |a|->|b|->|c|
// then toCString function will return "abc"
char* toCString(node* head) {
    int len = length(head);
    char* str = (char*)malloc((len) * sizeof(char));
    if (str == NULL) {
        fprintf(stdout, "Memory allocation failed\n"); // This is our base case for when our allocation is not needed (the string is null).
        exit(EXIT_FAILURE); 
    }

    int i = 0; // Initialize our counter for the array to 0.
    node* current = head;
    while (current != NULL) {
        str[i] = current->letter; // Set the array at index i to the current letter.
        current = current->next;
        i++;
    }
    str[i] = '\0'; // Null-terminate the string, because otherwise our final string includes said null character.
    return str;
}

// inserts character to the linkedlist
// If the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as follows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c) {
    node* newNode = (node*)malloc(sizeof(node));
    if (newNode == NULL) {
        fprintf(stdout, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->letter = c; // Set the new node's letter to the character we want to insert.
    newNode->next = NULL; // Set the new node's next pointer to null, because we are inserting at the end of the list.

    if (*pHead == NULL) {
        *pHead = newNode; // If our head is null, it means we can instantly put it at the front since there is nothing else in the list.
    } else {
        node* current = *pHead;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// deletes all nodes in the linkedList.
void deleteList(node** pHead) {
    node* current = *pHead;
    node* nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    *pHead = NULL; // Set head to NULL after deletion, because we can't free it
}

int main(void) {
    int i, strLen, numInputs;
    node* head = NULL;
    char* str;
    char c;
    FILE* inFile = fopen("input.txt","r");
  
    fscanf(inFile, "%d", &numInputs);
  
    while (numInputs-- > 0) {
        fscanf(inFile, "%d", &strLen);
        for (i = 0; i < strLen; i++) {
            fscanf(inFile," %c", &c);
            insertChar(&head, c);
        }
        str = toCString(head);
        printf("String is : %s\n", str);
        free(str);
        deleteList(&head);
        if (head != NULL) {
            printf("deleteList is not correct!");
            break;
        }
    }
    fclose(inFile);

    return 0;
}
