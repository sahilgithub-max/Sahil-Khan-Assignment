#include <stdio.h>
#include <stdlib.h>

// Define an enumeration for data types
enum DataType { INT, FLOAT, CHAR, STRING };

// Define a node structure with a type identifier and a void pointer for data
struct Node {
  enum DataType type;
  void *data;
  struct Node *next;
};

// Function to create a new node
struct Node* createNode(enum DataType type) {
  struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
  if (newNode == NULL) {
    printf("Memory allocation failed!\n");
    return NULL;
  }
 newNode->type = type;
  newNode->data = NULL;
  newNode->next = NULL;
  return newNode;
}

// Function to read and store data based on type
void* readData(enum DataType type) {
  void *data = NULL;
  switch (type) {
    case INT:
      data = malloc(sizeof(int));
      printf("Enter an integer: ");
      scanf("%d", (int*)data);
      break;
    case FLOAT:
      data = malloc(sizeof(float));
      printf("Enter a float: ");
      scanf("%f", (float*)data);
      break;
    case CHAR:
      data = malloc(sizeof(char));
      printf("Enter a character: ");
scanf(" %c", (char*)data); // Extra space to avoid newline character issues
      break;
    case STRING: {
      char buffer[100];  // Adjust buffer size as needed
      printf("Enter a string: ");
      fgets(buffer, sizeof(buffer), stdin);
      // Allocate memory for the string (excluding newline)
      int len = strlen(buffer);
      data = malloc(len + 1);  // +1 for null terminator
      strncpy((char*)data, buffer, len);
      ((char*)data)[len] = '\0';  // Ensure null termination
      break;
    }
    default:
      printf("Invalid data type!\n");
  }
  return data;
}

// Function to add a node to the linked list
void insertNode(struct Node** head, enum DataType type) {
  struct Node* newNode = createNode(type);
  newNode->data = readData(type);
  newNode->next = *head;
  *head = newNode;
}

// Function to print the linked list content
void printList(struct Node* head) {
  while (head) {
    switch (head->type) {
case INT:
        printf("Integer: %d\n", (int)head->data);
        break;
      case FLOAT:
        printf("Float: %f\n", (float)head->data);
        break;
      case CHAR:
        printf("Character: %c\n", (char)head->data);
        break;
      case STRING:
        printf("String: %s\n", (char*)head->data);
        break;
    }
    head = head->next;
  }
}

// Function to free the allocated memory
void freeList(struct Node* head) {
  while (head) {
    struct Node* temp = head;
    free(head->data);
    head = head->next;
    free(temp);
  }
}

int main() {
  int choice;
  struct Node* head = NULL;

  while (1) {
    printf("\n1. Add Integer\n");
    printf("2. Add Float\n");
    printf("3. Add Character\n");
printf("4. Add String\n");
    printf("5. Print List\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
      case 1:
      case 2:
      case 3:
      case 4:
        insertNode(&head, choice - 1);
        break;
      case 5:
        printList(head);
        break;
      case 6:
        freeList(head);
        printf("Exiting...\n");
        return 0;
      default:
        printf("Invalid choice!\n");
    }
  }
}
