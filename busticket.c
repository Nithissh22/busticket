#include <stdio.h>
#include <time.h>
       int seats[20] = {0}; 
int ticketPrice = 460; // Ticket price in Rupees
time_t departureTime;
time_t arrivalTime;
             void displaySeats() {
  printf("\n CHENNAI TO THENI\n");
    printf("Available seats:\n");
    for (int i = 0; i < 20; i++) {
        if (seats[i] == 0) {
            printf("Seat %d - Price: ₹%d\n", i + 1, ticketPrice);
        }
    }
}

int bookSeat(int seatNumber) {
    if (seatNumber < 1 || seatNumber > 20) {
        return -1; // Invalid seat number
    }
    if (seats[seatNumber - 1] == 0) {
        seats[seatNumber - 1] = 1; // Book the seat
        return 1; // Booking successful
    } else {
        return 0; // Seat already booked
    }
}

int cancelSeat(int seatNumber) {
    if (seatNumber < 1 || seatNumber > 20) {
        return -1; // Invalid seat number
    }

    time_t currentTime;
    time(&currentTime);
    double timeRemaining = difftime(departureTime, currentTime);

    if (timeRemaining < 1800) { // 1800 seconds = 30 minutes
        return -2; // Cancellation not allowed within 30 minutes of departure
    }

    if (seats[seatNumber - 1] == 1) {
        seats[seatNumber - 1] = 0; // Cancel the booking
        return 1; // Cancellation successful
    } else {
        return 0; // Seat was not booked
    }
}
int main() {
    int choice, seat;

   // Set the departure and arrival times
    time(&departureTime);
    time(&arrivalTime);
    departureTime += 3600; // 3600 seconds = 60 minutes
    arrivalTime += 35200; // 7200 seconds = 120 minutes

    while (1) {
        printf("\nBus Timings:\n");
        printf("Departure Time: %s", asctime(localtime(&departureTime)));
        printf("Arrival Time: %s", asctime(localtime(&arrivalTime)));

        printf("\n1. Display available seats\n");
        printf("2. Book a seat\n");
        printf("3. Cancel a booking\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displaySeats();
                break;
            case 2:
                printf("Enter the seat number you want to book: ");
                scanf("%d", &seat);
                int result = bookSeat(seat);
                if (result == 1) {
                    printf("Seat %d booked successfully. \nPrice: ₹%d", seat, ticketPrice);
                } else if (result == 0) {
                    printf("Seat %d is already booked.\n", seat);
                } else {
                    printf("Invalid seat number.\n");
                }
                break;
            case 3:
                printf("Enter the seat number you want to cancel: ");
                scanf("%d", &seat);
                int cancellationResult = cancelSeat(seat);
                if (cancellationResult == 1) {
                    printf("Booking for seat %d canceled successfully. Refund: ₹%d\n", seat, ticketPrice);
                } else if (cancellationResult == 0) {
                    printf("Seat %d was not booked.\n", seat);
                } else if (cancellationResult == -2) {
                    printf("Cancellation not allowed within 30 minutes of departure.\n");
                } else {
                    printf("Invalid seat number.\n");
                }
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
return 0;}
