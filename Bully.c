#include <stdio.h>
#include <stdbool.h>

#define NUM_PROCESSES 7

struct Process {
    int id;
    bool coordinator;
    bool active;
};

struct Process processes[NUM_PROCESSES];
int coordinator_id = -1; // Initially no coordinator

void initiate_election(int process_id) {
    printf("Process %d initiates election.\n", process_id);

    int highest_id = process_id;
    bool higher_priority_accepted = false;

    // Send election messages to all higher priority processes
    for (int i = process_id + 1; i < NUM_PROCESSES; i++) {
        if (processes[i].active) {
            printf("Process %d sends election message to Process %d\n", process_id, i);
            // Assume there is a function to send messages
            highest_id = i;
            // Assume higher-priority process accepts to become coordinator
            higher_priority_accepted = true;
            break; // Only one higher priority process will be contacted
        }
    }

    // If no response received, declare itself as coordinator
    if (highest_id == process_id) {
        printf("Process %d becomes coordinator.\n", process_id);
        processes[process_id].coordinator = true;
        coordinator_id = process_id;

        // Inform other processes about becoming coordinator
        for (int i = 0; i < NUM_PROCESSES; i++) {
            if (i != process_id && processes[i].active) {
                printf("Process %d sends coordinator announcement to Process %d\n", process_id, i);
                // Assume there is a function to send messages
            }
        }
    } else if (higher_priority_accepted) {
        printf("Process %d accepts to become coordinator.\n", highest_id);
    }
}

void process_failure(int process_id) {
    printf("Process %d has failed.\n", process_id);
    processes[process_id].active = false;
    if (process_id == coordinator_id) {
        coordinator_id = -1; // Reset coordinator ID
    }
}

int main() {
    // Initialize processes
    for (int i = 0; i < NUM_PROCESSES; i++) {
        processes[i].id = i;
        processes[i].coordinator = false;
        processes[i].active = true;
    }

    // Simulate failure of process with ID 3
    int failed_process_id = 3;
    process_failure(failed_process_id);

    // Assume process 2 initiates the election and sends a message to the next higher-priority process
    int initiating_process_id = 2; // Change as required
    printf("Process %d initiates election.\n", initiating_process_id);

    for (int i = initiating_process_id + 1; i < NUM_PROCESSES; i++) {
        if (processes[i].active) {
            printf("Process %d sends election message to Process %d\n", initiating_process_id, i);
            // Assume there is a function to send messages

            // Simulate process forwarding the election message to the next higher-priority process
            printf("Process %d forwards election message to Process %d\n", i, i+1);
            // Assume there is a function to send messages

            break;
        }
    }

    // Assume the last process receives the election message and accepts to become the coordinator
    int last_process_id = NUM_PROCESSES - 1;
    printf("Process %d accepts to become coordinator.\n", last_process_id);

    // After message passing is completed, the last process becomes the coordinator
    printf("Process %d becomes coordinator.\n", last_process_id);
    processes[last_process_id].coordinator = true;
    coordinator_id = last_process_id;

    // Inform other processes about becoming coordinator
    for (int i = 0; i < NUM_PROCESSES; i++) {
        if (i != last_process_id && processes[i].active) {
            printf("Process %d sends coordinator announcement to Process %d\n", last_process_id, i);
            // Assume there is a function to send messages
        }
    }

    return 0;
}
