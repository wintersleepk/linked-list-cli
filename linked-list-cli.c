#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


#define RESET_TEXT "\033[0m"
#define RED_BOLD "\033[1;31m"
#define GREEN_BOLD "\033[1;32m"
#define green_text "\033[32m"
#define red_text "\033[31m"
#define cyan_text "\033[46m"
#define CYAN_BOLD "\033[1;46m"


// Define the node
typedef struct Book {
    int data;
    struct Book* next;
} Book;

// Insert at end
int insert_end(Book** head, int value) {
    Book* new_node = malloc(sizeof(Book));
    if (!new_node) {
        printf(RED_BOLD "Memory allocation failed!\n" RESET_TEXT);
        return -1;
    }

    new_node->data = value;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return 0;
    }

    Book* temp = *head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = new_node;
    return 0;
}

// Insert at front
void insert_front(Book** head, int value) {
    Book* new_node = malloc(sizeof(Book));
    if (!new_node) {
        printf(RED_BOLD "Memory allocation failed!\n" RESET_TEXT);
        return;
    }

    new_node->data = value;
    new_node->next = *head;
    *head = new_node;
}

// Print the list
void print_list(Book* head) {
    if (head == NULL) {
        printf(RED_BOLD "List is empty.\n" RESET_TEXT);
        return;
    }

    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

// Delete a node with a given value
void delete_value(Book** head_ref, int value) {
    if (*head_ref == NULL) {
        printf(RED_BOLD "List is empty. Nothing to delete.\n" RESET_TEXT);
        return;
    }

    Book* temp = *head_ref;
    Book* prev = NULL;

    if (temp->data == value) {
        *head_ref = temp->next;
        free(temp);
        printf(GREEN_BOLD "Deleted %d from the list.\n" RESET_TEXT, value);
        return;
    }

    while (temp != NULL && temp->data != value) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf(RED_BOLD "Value %d not found in the list.\n" RESET_TEXT, value);
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf(GREEN_BOLD "Deleted %d from the list.\n" RESET_TEXT, value);
}

// Count the number of nodes
int count_nodes(Book* head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

// Free the entire list
void free_list(Book* head) {
    Book* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Book* head = NULL;
    int choice, value;

    while (1) {
        printf(CYAN_BOLD "\n========= LINKED LIST MENU =========\n" RESET_TEXT);
        printf(GREEN_BOLD "1. Insert at front\n");
        printf("2. Insert at end\n");
        printf("3. Delete a value\n");
        printf("4. Count nodes\n");
        printf("5. Print list\n");
        printf("6. Exit\n" RESET_TEXT);
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert at front: ");
                scanf("%d", &value);
                insert_front(&head, value);
                break;

            case 2:
                printf("Enter value to insert at end: ");
                scanf("%d", &value);
                insert_end(&head, value);
                break;

            case 3:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                delete_value(&head, value);
                break;

            case 4:
                printf(GREEN_BOLD "Total nodes: %d\n" RESET_TEXT, count_nodes(head));
                break;

            case 5:
                printf(GREEN_BOLD "Current List: " RESET_TEXT);
                print_list(head);
                break;

            case 6:
                free_list(head);
                printf(GREEN_BOLD "Exiting. Memory freed.\n" RESET_TEXT);
                return 0;

            default:
                printf(RED_BOLD "Invalid choice. Try again.\n" RESET_TEXT);
        }
    }

    return 0;
}

