#include <stdio.h>
#include <string.h>

#define MAX_SEATS 3    // Maximum number of seats available
#define MAX_WAITLIST 3 // Maximum number of passengers in the waiting list

typedef struct {
    char name[50];
    int seatNumber;
} Passenger;

Passenger reservationList[MAX_SEATS];
Passenger waitingList[MAX_WAITLIST];

int reservationCount = 0; // Tracks reserved seats
int waitingCount = 0;     // Tracks people in waiting list
int availableSeats[MAX_SEATS]; // Array to track available seats

// Initialize available seats
void initializeSeats() {
    for (int i = 0; i < MAX_SEATS; i++) {
        availableSeats[i] = 1; // 1 indicates the seat is available
    }
}

// Function to display current reservation and waiting list status
void displayStatus() {
    printf("\nCurrent Reservations:\n");
    for (int i = 0; i < reservationCount; i++) {
        if (reservationList[i].seatNumber != -1) { // Only display valid reservations
            printf("Seat %d: %s\n", reservationList[i].seatNumber, reservationList[i].name);
        }
    }

    printf("\nWaiting List:\n");
    for (int i = 0; i < waitingCount; i++) {
        printf("Waiting %d: %s\n", i + 1, waitingList[i].name);
    }
    printf("\n");
}

// Function to find the next available seat number
int getAvailableSeat() {
    for (int i = 0; i < MAX_SEATS; i++) {
        if (availableSeats[i] == 1) { // Seat is available
            availableSeats[i] = 0;    // Mark seat as taken
            return i + 1;             // Seat numbers start from 1
        }
    }
    return -1; // No seats available
}

// Function to reserve a seat if available or add to the waiting list if full
void reserveSeat(char name[]) {
    if (reservationCount < MAX_SEATS) {
        int seatNumber = getAvailableSeat();
        if (seatNumber != -1) {
            reservationList[reservationCount].seatNumber = seatNumber;
            strcpy(reservationList[reservationCount].name, name);
            reservationCount++;
            printf("Reservation successful! Seat number: %d\n", seatNumber);
        }
    } else if (waitingCount < MAX_WAITLIST) {
        strcpy(waitingList[waitingCount].name, name);
        waitingCount++;
        printf("Reservation full. Added to waiting list with number: %d\n", waitingCount);
    } else {
        printf("Both reservation and waiting list are full.\n");
    }
}

// Function to cancel a reservation by name
void cancelReservation(char name[]) {
    int found = 0;

    for (int i = 0; i < reservationCount; i++) {
        if (strcmp(reservationList[i].name, name) == 0) {
            found = 1;
            printf("Reservation cancelled for %s.\n", name);

            // Mark the seat as available
            availableSeats[reservationList[i].seatNumber - 1] = 1;
            reservationList[i].seatNumber = -1; // Invalidate the seat number

            // Move passengers up to fill the canceled seat if waiting list is not empty
            if (waitingCount > 0) {
                int seatNumber = getAvailableSeat();
                if (seatNumber != -1) {
                    reservationList[i].seatNumber = seatNumber;
                    strcpy(reservationList[i].name, waitingList[0].name);

                    // Shift waiting list up
                    for (int k = 0; k < waitingCount - 1; k++) {
                        waitingList[k] = waitingList[k + 1];
                    }
                    waitingCount--;

                    printf("Seat allocated to %s from waiting list.\n", reservationList[i].name);
                }
            }
            break;
        }
    }

    if (!found) {
        printf("Passenger %s not found in reservations.\n", name);
    }
}

int main() {
    int choice;
    char name[50];

    initializeSeats(); // Initialize available seats

    while (1) {
        printf("\n--- Railway Reservation System ---\n");
        printf("1. Reserve Seat\n");
        printf("2. Cancel Reservation\n");
        printf("3. Display Status\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter passenger name: ");
                scanf("%s", name);
                reserveSeat(name);
                break;
            case 2:
                printf("Enter passenger name to cancel: ");
                scanf("%s", name);
                cancelReservation(name);
                break;
            case 3:
                displayStatus();
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
