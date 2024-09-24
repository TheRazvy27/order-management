#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Order {
    int id;
    char name[50];
    char product[50];
    int quantity;
    float price;
    char status[20];
    struct Order *next;
};

int order_count = 0;

struct Order* createOrder(int id, char name[], char product[], int quantity, float price) {
    struct Order *newOrder = (struct Order *) malloc(sizeof(struct Order));
    newOrder->id = id;
    strcpy(newOrder->name, name);
    strcpy(newOrder->product, product);
    newOrder->quantity = quantity;
    newOrder->price = price;
    strcpy(newOrder->status, "Pending");
    newOrder->next = NULL;
    return newOrder;
}

void insertOrderAtHead(struct Order **head) {
    char name[50], product[50];
    int quantity;
    float price;
    printf("Enter customer's name: ");
    scanf("%s", name);
    printf("Enter product name: ");
    scanf("%s", product);
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    printf("Enter price: ");
    scanf("%f", &price);
    struct Order *newOrder = createOrder(++order_count, name, product, quantity, price);
    newOrder->next = *head;
    *head = newOrder;
}

void insertOrderAtTail(struct Order **head) {
    char name[50], product[50];
    int quantity;
    float price;
    printf("Enter customer's name: ");
    scanf("%s", name);
    printf("Enter product name: ");
    scanf("%s", product);
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    printf("Enter price: ");
    scanf("%f", &price);
    struct Order *newOrder = createOrder(++order_count, name, product, quantity, price);
    if (*head == NULL) {
        *head = newOrder;
        return;
    }
    struct Order *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newOrder;
}

void confirmCancelOrder(struct Order **head, int id, char action[]) {
    struct Order *temp = *head;
    struct Order *prev = NULL;
    while (temp != NULL) {
        if (temp->id == id) {
            if (strcmp(action, "Confirm") == 0) {
                strcpy(temp->status, "Confirmed");
                printf("Order confirmed for %s\n", temp->name);
            } else if (strcmp(action, "Cancel") == 0) {
                if (prev == NULL) {
                    *head = temp->next;
                } else {
                    prev->next = temp->next;
                }
                free(temp);
                printf("Order cancelled ");
            }
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Order not found\n");
}

void printOrders(struct Order *node) {
    while (node != NULL) {
        printf("ID: %d\n", node->id);
        printf("Name: %s\n", node->name);
        printf("Product: %s\n", node->product);
        printf("Quantity: %d\n", node->quantity);
        printf("Price: %.2f\n", node->price);
        printf("Status: %s\n", node->status);
        printf("\n");
        node = node->next;
    }
}

int main() {
    char password[20];
    printf("Welcome to Altex Romania employee zone\n");
    printf("Enter Password: ");
    scanf("%s", password);
    if (strcmp(password, "admin") != 0) {
        printf("Invalid Password\n");
        return 0;
    }
    struct Order *head = NULL;
    int option, id;
    while(1){
        printf("Select an option:\n 1)Insert an important order\n 2)Insert order \n 3)Confirm order\n 4)Cancel order\n 5)Print orders\n 6) Exit\n Enter your option: ");
        scanf("%d", &option);
        switch (option)
        {
            case 1:
                insertOrderAtHead(&head);
                break;
            case 2:
                insertOrderAtTail(&head);
                break;
            case 3:
                printf("Enter order ID: ");
                scanf("%d", &id);
                confirmCancelOrder(&head, id, "Confirm");
                break;
            case 4:
                printf("Enter order ID: ");
                scanf("%d", &id);
                confirmCancelOrder(&head, id, "Cancel");
                break;
            case 5:
                printOrders(head);
                break;
            case 6:
                return 0;
                break;
            default:
                printf("Invalid option\n");
                break;
        }
    }
    return 0;
}

