#include <stdio.h>
#include <stdlib.h>
//#include <string.h> // Not needed in this example

#include "list.h"

list_t *list_alloc() {
    list_t *newList = malloc(sizeof(list_t));
    if (newList != NULL) {
        newList->head = NULL;
    }
    return newList;
}

void list_free(list_t *l) {
    if (l != NULL) {
        // Free all nodes in the list
        node_t *current = l->head;
        while (current != NULL) {
            node_t *next = current->next;
            free(current);
            current = next;
        }
        free(l);
    }
}

void list_print(list_t *l) {
    if (l == NULL) {
        printf("List is not allocated.\n");
        return;
    }

    node_t *current = l->head;
    printf("List: ");
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

int list_length(list_t *l) {
    if (l == NULL) {
        return 0;
    }

    int length = 0;
    node_t *current = l->head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

void list_add_to_back(list_t *l, elem value) {
    if (l == NULL) {
        return;
    }

    node_t *newNode = malloc(sizeof(node_t));
    newNode->value = value;
    newNode->next = NULL;

    if (l->head == NULL) {
        l->head = newNode;
    } else {
        node_t *current = l->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void list_add_to_front(list_t *l, elem value) {
    if (l == NULL) {
        return;
    }

    node_t *newNode = malloc(sizeof(node_t));
    newNode->value = value;
    newNode->next = l->head;
    l->head = newNode;
}

void list_add_at_index(list_t *l, elem value, int index) {
    if (l == NULL) {
        return;
    }

    if (index < 0) {
        // Invalid index, do nothing
        return;
    }

    node_t *newNode = malloc(sizeof(node_t));
    newNode->value = value;
    
    if (index == 0 || l->head == NULL) {
        // Add at the front
        newNode->next = l->head;
        l->head = newNode;
    } else {
        node_t *current = l->head;
        int currentIndex = 0;
        while (current != NULL && currentIndex < index - 1) {
            current = current->next;
            currentIndex++;
        }
        if (current != NULL) {
            newNode->next = current->next;
            current->next = newNode;
        } else {
            // Invalid index, do nothing
            free(newNode);
        }
    }
}

elem list_remove_from_back(list_t *l) {
    if (l == NULL || l->head == NULL) {
        return -1; // List is empty
    }

    if (l->head->next == NULL) {
        // Only one element in the list
        elem value = l->head->value;
        free(l->head);
        l->head = NULL;
        return value;
    }

    node_t *current = l->head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    elem value = current->next->value;
    free(current->next);
    current->next = NULL;
    return value;
}

elem list_remove_from_front(list_t *l) {
    if (l == NULL || l->head == NULL) {
        return -1; // List is empty
    }

    node_t *frontNode = l->head;
    elem value = frontNode->value;
    l->head = frontNode->next;
    free(frontNode);
    return value;
}

elem list_remove_at_index(list_t *l, int index) {
    if (l == NULL || l->head == NULL || index < 0) {
        return -1; // Invalid operation
    }

    if (index == 0) {
        // Remove the first element
        return list_remove_from_front(l);
    }

    node_t *current = l->head;
    int currentIndex = 0;
    while (current->next != NULL && currentIndex < index - 1) {
        current = current->next;
        currentIndex++;
    }

    if (current->next != NULL) {
        node_t *removedNode = current->next;
        elem value = removedNode->value;
        current->next = removedNode->next;
        free(removedNode);
        return value;
    }

    return -1; // Invalid index
}

bool list_is_in(list_t *l, elem value) {
    if (l == NULL) {
        return false;
    }

    node_t *current = l->head;
    while (current != NULL) {
        if (current->value == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

elem list_get_elem_at(list_t *l, int index) {
    if (l == NULL || l->head == NULL || index < 0) {
        return -1; // Invalid operation
    }

    node_t *current = l->head;
    int currentIndex = 0;
    while (current != NULL && currentIndex < index) {
        current = current->next;
        currentIndex++;
    }

    if (current != NULL) {
        return current->value;
    }

    return -1; // Invalid index
}

int list_get_index_of(list_t *l, elem value) {
    if (l == NULL) {
        return -1;
    }

    node_t *current = l->head;
    int index = 0;
    while (current != NULL) {
        if (current->value == value) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1; // Value not found
}
