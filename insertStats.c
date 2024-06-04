#include "insertStats.h"

void* insertStats(void* arg) {
    AccessedPagesList accessedPagesList = {.first = NULL};

    insertStatsArgs *a = arg;
    char* logPath = a->logPath;
    Queue* queue = a->queue;
    debug(queue, "Insert stats consumer created: %s", logPath);
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

            FILE* file = fopen(logPath, "w");
            if (file == NULL) {
                panic(1, "Error opening file");
            }
            AccessedPageNode* currentNode = accessedPagesList.first;
            while (currentNode != NULL) {
                if (currentNode->numberOfAccess > 1)
                    fprintf(file, "%d acessos: %s\n", currentNode->numberOfAccess, currentNode->page);
                else
                    fprintf(file, "%d acesso:  %s\n", currentNode->numberOfAccess, currentNode->page);
                currentNode = currentNode->next;
            }
            fclose(file);
        }
    }
    pthread_exit(NULL);
}