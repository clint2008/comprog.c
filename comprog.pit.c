
#include <stdio.h>
#include <string.h>

#define MAX_APPOINTMENTS 25
#define MAX_SLOTS 5
#define TOTAL_DATES 5

// Appointment information
struct Appointment {
    char name[50];
    char contact[20];
    char purpose[1000];
    int dateIndex;
};

// Function declarations
void showDates(char dates[][20], int counts[]);
void bookAppointment(struct Appointment appointments[],
                    int *total, char dates[][20], int counts[]);
void adminMenu(struct Appointment appointments[],
               int total, char dates[][20], int counts[]);

int main() {
    char dates[TOTAL_DATES][20] = {
        "2026-10-12",
        "2026-10-13",
        "2026-10-14",
        "2026-10-15",
        "2026-10-16"
    };

    struct Appointment appointments[MAX_APPOINTMENTS];
    int counts[TOTAL_DATES] = {0};
    int total = 0;
    int choice;

    do {
        printf("\n====================================\n");
        printf(" APPOINTMENT BOOKING SYSTEM\n");
        printf("====================================\n");
        printf("1. User - Book Appointment\n");
        printf("2. Admin - Manage Appointments\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            printf("Invalid input! Enter a number.\n");
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1:
                bookAppointment(appointments, &total,
                                dates, counts);
                break;

            case 2:
                adminMenu(appointments, total, dates, counts);
                break;

            case 3:
                printf("\nThank you for using the system!\n");
                break;

            default:
                printf("\nInvalid choice! Select 1, 2, or 3.\n");
        }

    } while (choice != 3);

    return 0;
}

// Display dates and their availability
void showDates(char dates[][20], int counts[]) {
    int i;

    printf("\n========== APPOINTMENT DATES ==========\n");

    for (i = 0; i < TOTAL_DATES; i++) {
        printf("%d. %s - ", i + 1, dates[i]);

        if (counts[i] < MAX_SLOTS) {
            printf("AVAILABLE (%d slots left)\n",
                   MAX_SLOTS - counts[i]);
        } else {
            printf("UNAVAILABLE - FULLY BOOKED\n");
        }
    }
}

// User booking function
void bookAppointment(struct Appointment appointments[],
                     int *total, char dates[][20], int counts[]) {
    int dateChoice;
    int ch;

    if (*total >= MAX_APPOINTMENTS) {
        printf("\nThe appointment system is full.\n");
        return;
    }

    printf("\n========== USER BOOKING ==========\n");

    printf("Enter your full name: ");
    scanf(" %49[^\n]", appointments[*total].name);

    printf("Enter your contact number: ");
    scanf(" %19s", appointments[*total].contact);

    printf("Enter purpose of visit: ");
    scanf(" %999[^\n]", appointments[*total].purpose);

    showDates(dates, counts);

    printf("\nChoose a date (1-%d): ", TOTAL_DATES);

    if (scanf("%d", &dateChoice) != 1) {
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        printf("Invalid date choice. Booking cancelled.\n");
        return;
    }

    while (dateChoice < 1 || dateChoice > TOTAL_DATES) {
        printf("Invalid choice! Choose a date (1-%d): ",
               TOTAL_DATES);

        if (scanf("%d", &dateChoice) != 1) {
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            printf("Invalid input. Booking cancelled.\n");
            return;
        }
    }

    int index = dateChoice - 1;

    if (counts[index] >= MAX_SLOTS) {
        printf("\nSorry, that date is fully booked.\n");
        printf("Please book another available date.\n");
        return;
    }

    appointments[*total].dateIndex = index;
    counts[index]++;
    (*total)++;

    printf("\nAppointment successfully booked!\n");
    printf("Date: %s\n", dates[index]);
    printf("Booking number: %d\n", *total);
}

// Admin function
void adminMenu(struct Appointment appointments[],
               int total, char dates[][20], int counts[]) {
    char password[20];
    int choice;
    int i;

    printf("\n========== ADMIN LOGIN ==========\n");
    printf("Enter admin password: ");
    scanf("%19s", password);

    // Demo password only; not secure authentication
    if (strcmp(password, "admin123") != 0) {
        printf("Incorrect password!\n");
        return;
    }

    do {
        printf("\n========== ADMIN MENU ==========\n");
        printf("1. View all appointments\n");
        printf("2. View appointments per date\n");
        printf("3. Return to main menu\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            printf("Invalid input!\n");
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1:
                if (total == 0) {
                    printf("\nNo appointments have been booked.\n");
                } else {
                    printf("\n========== ALL APPOINTMENTS ==========\n");

                    for (i = 0; i < total; i++) {
                        printf("\nBooking No.: %d\n", i + 1);
                        printf("Name: %s\n", appointments[i].name);
                        printf("Contact: %s\n", appointments[i].contact);
                        printf("Purpose: %s\n", appointments[i].purpose);
                        printf("Date: %s\n",
                               dates[appointments[i].dateIndex]);
                    }
                }
                break;

            case 2:
                printf("\n====== DAILY APPOINTMENT SUMMARY ======\n");

                for (i = 0; i < TOTAL_DATES; i++) {
                    printf("%s: %d appointment(s)\n",
                           dates[i], counts[i]);
                }
                break;

            case 3:
                printf("Returning to main menu...\n");
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }

    } while (choice != 3);
}
