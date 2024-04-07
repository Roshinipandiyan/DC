#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_NODES 5  // Number of nodes in the ring

// Node structure
typedef struct Node {
    int id;
    bool isCoordinator;
    bool isFailed;
} Node;

// Function prototypes
void initiateElection(Node nodes[], int initiatingNode);
void printCoordinator(Node nodes[]);

int main() {
    Node nodes[NUM_NODES];

    // Initialize nodes
    for (int i = 0; i < NUM_NODES; i++) {
        nodes[i].id = i;
        nodes[i].isCoordinator = false;
        nodes[i].isFailed = false;
    }

    // Simulate a failed node (for example, node 2)
    int failed_process;
    printf("Enter the process that failed: ");
    scanf("%d",&failed_process);
    nodes[failed_process].isFailed = true;

    // User chooses the node that initiates the election (for example, node 1)
    int initiatingNode;
    printf("Enter the process ID that initiates the election (0 to %d): ", NUM_NODES - 1);
    scanf("%d", &initiatingNode);

    // Start election process
    initiateElection(nodes, initiatingNode);

    // Print coordinator
    printCoordinator(nodes);

    return 0;
}

// Function to initiate the election process
void initiateElection(Node nodes[], int initiatingNode) {
    int highestId = -1;
    int coordinatorIndex = -1;

    // Find the highest id among the nodes
    for (int i = 0; i < NUM_NODES; i++) {
        if (!nodes[i].isFailed && nodes[i].id > highestId) {
            highestId = nodes[i].id;
            coordinatorIndex = i;
        }
    }

    // Propagate the election message clockwise in a circular manner, skipping failed nodes
    printf("Election message initiated by process %d\n", initiatingNode);
    for (int i = initiatingNode; ; i = (i + 1) % NUM_NODES) {
        if (!nodes[i].isFailed) {
            printf("Process %d forwards the election message\n", nodes[i].id);
        }
        if (i == (initiatingNode - 1 + NUM_NODES) % NUM_NODES)
            break;  // Message has completed a full circle
    }

    // Declare the coordinator
    nodes[coordinatorIndex].isCoordinator = true;
    printf("Process %d becomes the coordinator\n", nodes[coordinatorIndex].id);
}

// Function to print the coordinator
void printCoordinator(Node nodes[]) {
    for (int i = 0; i < NUM_NODES; i++) {
        if (nodes[i].isCoordinator) {
            printf("Coordinator: Node %d\n", nodes[i].id);
            break;
        }
    }
}
