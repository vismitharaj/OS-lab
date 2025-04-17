#include <stdio.h>
#include <stdbool.h>

#define MAX_PROC 5
#define MAX_RES 3

int main() {
    int n, m, i, j, k;
    int alloc[MAX_PROC][MAX_RES];
    int request[MAX_PROC][MAX_RES];
    int avail[MAX_RES];
    bool finish[MAX_PROC] = {false};

    printf("Enter number of processes and resources:\n");
    scanf("%d %d", &n, &m);

    printf("Enter allocation matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter request matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    printf("Enter available matrix:\n");
    for (j = 0; j < m; j++) {
        scanf("%d", &avail[j]);
    }

    // Initialize finish array
    for (i = 0; i < n; i++) {
        bool all_zero = true;
        for (j = 0; j < m; j++) {
            if (alloc[i][j] != 0) {
                all_zero = false;
                break;
            }
        }
        finish[i] = all_zero;
    }

    // Deadlock detection
    bool changed;
    do {
        changed = false;
        for (i = 0; i < n; i++) {
            if (!finish[i]) {
                bool can_finish = true;
                for (j = 0; j < m; j++) {
                    if (request[i][j] > avail[j]) {
                        can_finish = false;
                        break;
                    }
                }

                if (can_finish) {
                    for (k = 0; k < m; k++) {
                        avail[k] += alloc[i][k];
                    }
                    finish[i] = true;
                    changed = true;
                    printf("Process %d can finish.\n", i);
                }
            }
        }
    } while (changed);

    // Check for deadlock
    bool deadlock = false;
    for (i = 0; i < n; i++) {
        if (!finish[i]) {
            deadlock = true;
            break;
        }
    }

    if (deadlock) {
        printf("System is in a deadlock state.\n");
    } else {
        printf("System is not in a deadlock state.\n");
    }

    return 0;
}
