#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int mutex = 1, full = 0, empty = 1, x = 0;
int buffer[1];

int wait(int s) { return --s; }
int signal(int s) { return ++s; }

void producer(int id) {
    if ((mutex == 1) && (empty != 0)) {
        mutex = wait(mutex);
        full = signal(full);
        empty = wait(empty);

        int item = rand() % 100 + 1;
        buffer[x] = item;
        x++;
        printf("Producer %d produced %d\n", id, item);
        printf("Buffer:%d\n", buffer[x-1]);

        mutex = signal(mutex);
    } else {
        printf("Buffer is full. Producer %d waiting...\n", id);
    }
}

void consumer(int id) {
    if ((mutex == 1) && (full != 0)) {
        mutex = wait(mutex);
        full = wait(full);
        empty = signal(empty);

        x--;
        int item = buffer[x];
        printf("Consumer %d consumed %d\n", id, item);
        printf("Current buffer len: %d\n", x);

        mutex = signal(mutex);
    } else {
        printf("Buffer is empty. Consumer %d waiting...\n", id);
    }
}

int main() {
    int num_producers, num_consumers, buffer_capacity;
    int choice;
    int producer_id = 1, consumer_id = 1;

    printf("Enter the number of Producers: ");
    scanf("%d", &num_producers);

    printf("Enter the number of Consumers: ");
    scanf("%d", &num_consumers);

    printf("Enter buffer capacity: ");
    scanf("%d", &buffer_capacity);
    empty = buffer_capacity;

    srand(time(0));

    if (num_producers > 0) printf("Successfully created producer 1\n");
    if (num_consumers > 0) printf("Successfully created consumer 1\n");

    while (1) {
        printf("\n1. Producer\n2. Consumer\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (num_producers > 0) {
                    producer(producer_id);
                } else {
                    printf("No producers available!\n");
                }
                break;

            case 2:
                if (num_consumers > 0) {
                    consumer(consumer_id);
                } else {
                    printf("No consumers available!\n");
                }
                break;

            case 3:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
