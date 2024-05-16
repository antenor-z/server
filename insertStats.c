#include "insertStats.h"

AccessedPagesList accessedPagesList = {.first = NULL};

void* insertStats(void* arg) {
    LogQueue* queue = (LogQueue*)arg;
    while (1) {
        char* log = (char*)dequeue(queue);
        if (log != NULL) {
            if (accessedPagesList.first == NULL) {
                AccessedPageNode* newPage = (AccessedPageNode*)malloque(sizeof(AccessedPageNode));
                newPage->next = NULL;
                newPage->numberOfAccess = 1;
                newPage->page = log;
                accessedPagesList.first = newPage;
            }
            else {
                AccessedPageNode* currentNode = accessedPagesList.first;
                AccessedPageNode* prevNode = NULL;
                while (currentNode != NULL) {
                    if (strcmp(currentNode->page, log) == 0) {
                        currentNode->numberOfAccess++;
                        free(log);
                        break;
                    }
                    prevNode = currentNode;
                    currentNode = currentNode->next;
                }
                if (currentNode == NULL) {
                    AccessedPageNode* newPage = (AccessedPageNode*)malloque(sizeof(AccessedPageNode));
                    newPage->next = NULL;
                    newPage->numberOfAccess = 1;
                    newPage->page = log;
                    prevNode->next = newPage;
                }
            }

            FILE* file = fopen(".stats.txt", "w");
            if (file == NULL) {
                panic(1, "Error opening file");
            }
            AccessedPageNode* currentNode = accessedPagesList.first;
            while (currentNode != NULL) {
                fprintf(file, "%s %d acesso(s)\n", currentNode->page, currentNode->numberOfAccess);
                currentNode = currentNode->next;
            }
            fclose(file);
        }
    }
    pthread_exit(NULL);
}