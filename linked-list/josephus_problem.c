/* Given a problem, “people are standing in a circle waiting to be executed.
Counting begins at a specified point in the circle and proceeds in a specified
direction (e.g., clockwise). After a specified number of people is skipped,
the next person is executed (i.e., removed). The procedure is repeated with
the remaining people, starting with the next person, going in the same
direction and skipping the same number of people until only one person
remains and is freed”. The solution is to find the person to be freed. Solve
it using
i) 1D array
ii) A circular linked list.
iii) A circular doubly linked list */ 

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>


typedef struct node{
    struct node *prev, *next;
    uint64_t value;
} CircularDoublyListNode;

typedef struct node2{
  uint64_t value;
  struct node2 *next;
} CircularListNode;

// 1D Array approach
uint64_t josephus_1d_array(uint64_t n, uint64_t k) {
  uint64_t arr[1000];
  for(uint64_t i = 0; i < n; i++)
      arr[i] = 1;  // alive

  uint64_t count = n;
  uint64_t pos = 0;

  while(count > 1){
      uint64_t steps = 0;
      while(steps < k - 1){
          pos = (pos + 1) % n;
          if(arr[pos] == 1)
              steps++;
      }

      while (arr[pos] == 0)
          pos = (pos + 1) % n;

      arr[pos] = 0;
      count--;

      while (arr[pos] == 0)
          pos = (pos + 1) % n;
  }

  for(uint64_t i = 0; i < n; i++){
      if (arr[i] == 1)
          return i + 1;
  }

  return 0;
}


// Circular Linked List approach
CircularListNode* create_circular_list(uint64_t n) {
    CircularListNode *head = (CircularListNode*)malloc(sizeof(CircularListNode));
    head->value = 1;
    CircularListNode *current = head;
    
    for(uint64_t i = 2; i <= n; i++) {
        CircularListNode *new_node = (CircularListNode*)malloc(sizeof(CircularListNode));
        new_node->value = i;
        new_node->next = head;
        current->next = new_node;
        current = new_node;
    }
    
    return head;
}

uint64_t josephus_circular_list(uint64_t n, uint64_t k) {
  CircularListNode *head = create_circular_list(n);
  CircularListNode *current = head;

  while(current->next != current){
      for (uint64_t i = 1; i < k - 1; i++)
          current = current->next;

      CircularListNode *to_kill = current->next;
      current->next = to_kill->next;
      free(to_kill);
      current = current->next;
  }

  uint64_t result = current->value;
  free(current);
  return result;
}


// Circular Doubly Linked List approach
CircularDoublyListNode* create_circular_doubly_list(uint64_t n) {
    CircularDoublyListNode *head = (CircularDoublyListNode*)malloc(sizeof(CircularDoublyListNode));
    head->value = 1;
    CircularDoublyListNode *current = head;
    
    for(uint64_t i = 2; i <= n; i++) {
        CircularDoublyListNode *new_node = (CircularDoublyListNode*)malloc(sizeof(CircularDoublyListNode));
        new_node->value = i;
        new_node->next = head;
        new_node->prev = current;
        current->next = new_node;
        head->prev = new_node;
        current = new_node;
    }
    
    return head;
}

uint64_t josephus_circular_doubly_list(uint64_t n, uint64_t k) {
  CircularDoublyListNode *head = create_circular_doubly_list(n);
  CircularDoublyListNode *current = head;

  while (current->next != current) {
      for (uint64_t i = 1; i < k; i++)
          current = current->next;

      CircularDoublyListNode *to_kill = current;
      to_kill->prev->next = to_kill->next;
      to_kill->next->prev = to_kill->prev;
      current = to_kill->next;
      free(to_kill);
  }

  uint64_t result = current->value;
  free(current);
  return result;
}


void menu() {
    printf("\n----- Josephus Problem -----");
    printf("\n 1. 1D Array");
    printf("\n 2. Circular Linked List");
    printf("\n 3. Circular Doubly Linked List");
    printf("\n 0. Exit");
    printf("\n---------------------------");
    printf("\nEnter your choice: ");
}

int main() {
    uint64_t n, k;
    int choice;
    
    do {
        menu();
        scanf("%d", &choice);
        
        if(choice >= 1 && choice <= 3) {
            printf("Enter the number of people (n): ");
            scanf("%llu", &n);
            printf("Enter the counting number (k): ");
            scanf("%llu", &k);
            
            uint64_t result;
            
            switch(choice) {
                case 1:
                    result = josephus_1d_array(n, k);
                    printf("\nThe person to be freed using 1D Array approach is: %llu\n", result);
                    break;
                case 2:
                    result = josephus_circular_list(n, k);
                    printf("\nThe person to be freed using Circular Linked List approach is: %llu\n", result);
                    break;
                case 3:
                    result = josephus_circular_doubly_list(n, k);
                    printf("\nThe person to be freed using Circular Doubly Linked List approach is: %llu\n", result);
                    break;
            }
        }
        
    } while(choice != 0);
    
    return 0;
}
