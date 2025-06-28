#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>  // For time-related functions

// Constants for system configuration
#define MAX_MOVIES 5          // Maximum number of movies in the system
#define MAX_SHOWTIMES 5       // Maximum number of showtimes
#define MAX_NAME_LENGTH 50    // Maximum length for customer name
#define MAX_PHONE_LENGTH 15   // Maximum length for phone number
#define BASE_TICKET_PRICE 180.00  // Base price per ticket in INR
#define GST_PERCENT 18.0      // GST percentage (18%)
#define SEATS_PER_ROW 10      // Number of seats per row in theater
#define TOTAL_ROWS 5          // Total number of rows in theater

// Movie structure to store movie details
typedef struct {
    int id;                  // Unique movie ID
    char title[50];          // Movie title
    int duration;            // Duration in minutes
    char genre[20];          // Movie genre
    char language[20];       // Language of the movie
} Movie;

// Showtime structure to store screening details
typedef struct {
    int id;                  // Unique showtime ID
    int movie_id;            // Reference to movie ID
    char time[10];           // Showtime (format "HH:MM")
    char seats[TOTAL_ROWS][SEATS_PER_ROW]; // Seat matrix ('A'=Available, 'B'=Booked)
} Showtime;

// Booking structure to store customer booking details
typedef struct {
    char name[MAX_NAME_LENGTH];  // Customer name
    char phone[MAX_PHONE_LENGTH]; // Customer phone
    int movie_id;           // Selected movie ID
    int showtime_id;        // Selected showtime ID
    int num_tickets;        // Number of tickets booked
    char seat_numbers[10][5]; // Array to store seat numbers ("A1", "B2" etc.)
    float base_price;       // Total before GST
    float gst;              // GST amount
    float total_cost;       // Final amount (base + GST)
    time_t booking_time;     // Timestamp of booking
} Booking;

// Global arrays to store movies and showtimes
Movie movies[MAX_MOVIES] = {
    {1, "RRR", 182, "Action", "Telugu/Hindi"},
    {2, "Baahubali 2", 167, "Epic", "Telugu"},
    {3, "Dangal", 161, "Drama", "Hindi"},
    {4, "KGF Chapter 2", 168, "Action", "Kannada/Hindi"},
    {5, "Pushpa: The Rise", 179, "Action", "Telugu/Hindi"}
};

Showtime showtimes[MAX_SHOWTIMES] = {
    {1, 1, "10:00", {{'A'}}},
    {2, 2, "13:30", {{'A'}}},
    {3, 3, "16:45", {{'A'}}},
    {4, 4, "19:15", {{'A'}}},
    {5, 5, "22:00", {{'A'}}}
};

// Function prototypes
void initializeSeats();      // Initialize all seats as available
void displayMovies();        // Display available movies
void displayShowtimes(int movie_id); // Show showtimes for a movie
void displaySeatMap(int showtime_id); // Display seating arrangement
int validatePhone(const char *phone); // Validate phone number format
int bookSeats(int showtime_id, int num_tickets, char seat_numbers[][5]); // Book selected seats
void bookTicket();          // Main ticket booking function
void printBookingReceipt(Booking booking); // Print detailed receipt
void printTicket(Booking booking, int ticket_num); // Print individual ticket

int main() {
    // Initialize all seats as available at program start
    initializeSeats();
    
    int choice;
    
    // Display system header
    printf("=============================================\n");
    printf("       INDIAN MOVIE TICKET BOOKING SYSTEM\n");
    printf("=============================================\n");
    
    // Main program loop
    do {
        printf("\nMain Menu:\n");
        printf("1. Book Tickets\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                bookTicket();  // Start booking process
                break;
            case 2:
                printf("\nThank you for using our system. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 2);  // Continue until user chooses to exit
    
    return 0;
}

// Initialize all seats to available ('A') for all showtimes
void initializeSeats() {
    for(int s = 0; s < MAX_SHOWTIMES; s++) {
        for(int i = 0; i < TOTAL_ROWS; i++) {
            for(int j = 0; j < SEATS_PER_ROW; j++) {
                showtimes[s].seats[i][j] = 'A'; // 'A' for Available
            }
        }
    }
}

// Display all available movies in a formatted table
void displayMovies() {
    printf("\nAvailable Movies:\n");
    printf("ID | Title                     | Duration | Language      | Genre\n");
    printf("---+---------------------------+----------+---------------+--------\n");
    for(int i = 0; i < MAX_MOVIES; i++) {
        printf("%-2d | %-25s | %3d min | %-13s | %-10s\n", 
               movies[i].id, 
               movies[i].title, 
               movies[i].duration, 
               movies[i].language,
               movies[i].genre);
    }
}

// Display showtimes for a specific movie
void displayShowtimes(int movie_id) {
    printf("\nAvailable Showtimes for %s:\n", movies[movie_id-1].title);
    printf("ID | Time   | Available Seats\n");
    printf("---+--------+----------------\n");
    
    int found = 0;
    for(int i = 0; i < MAX_SHOWTIMES; i++) {
        if(showtimes[i].movie_id == movie_id) {
            int available = 0;
            // Count available seats
            for(int r = 0; r < TOTAL_ROWS; r++) {
                for(int c = 0; c < SEATS_PER_ROW; c++) {
                    if(showtimes[i].seats[r][c] == 'A') available++;
                }
            }
            printf("%-2d | %-6s | %-3d\n", 
                   showtimes[i].id, 
                   showtimes[i].time, 
                   available);
            found = 1;
        }
    }
    
    if(!found) {
        printf("No showtimes available for this movie.\n");
    }
}

// Display the seat map for a specific showtime
void displaySeatMap(int showtime_id) {
    printf("\nSeat Map (Showtime ID: %d):\n", showtime_id);
    printf("     ");
    // Print column headers (seat numbers)
    for(int c = 0; c < SEATS_PER_ROW; c++) {
        printf("%-3d", c+1);
    }
    printf("\n");
    
    // Print each row with seat availability
    for(int r = 0; r < TOTAL_ROWS; r++) {
        printf("%c -> ", 'A' + r);  // Row label (A, B, C, etc.)
        for(int c = 0; c < SEATS_PER_ROW; c++) {
            printf("%-3c", showtimes[showtime_id-1].seats[r][c]);
        }
        printf("\n");
    }
    printf("\nLegend: A - Available, B - Booked\n");
}

// Validate Indian phone number (10 digits)
int validatePhone(const char *phone) {
    int len = strlen(phone);
    if(len != 10) return 0;  // Must be exactly 10 digits
    
    // Check each character is a digit
    for(int i = 0; i < len; i++) {
        if(!isdigit(phone[i])) {
            return 0;
        }
    }
    return 1;
}

// Book selected seats for a showtime
int bookSeats(int showtime_id, int num_tickets, char seat_numbers[][5]) {
    int booked = 0;
    
    for(int t = 0; t < num_tickets; t++) {
        // Extract row (letter) and column (number) from seat number
        char row_char = seat_numbers[t][0];
        int row = toupper(row_char) - 'A';  // Convert to 0-based index
        int col = atoi(&seat_numbers[t][1]) - 1;  // Convert to 0-based index
        
        // Validate seat coordinates
        if(row < 0 || row >= TOTAL_ROWS || col < 0 || col >= SEATS_PER_ROW) {
            printf("Invalid seat number: %s\n", seat_numbers[t]);
            continue;
        }
        
        // Check if seat is available
        if(showtimes[showtime_id-1].seats[row][col] == 'A') {
            showtimes[showtime_id-1].seats[row][col] = 'B';  // Mark as booked
            booked++;
        } else {
            printf("Seat %s is already booked or invalid.\n", seat_numbers[t]);
        }
    }
    
    return booked;  // Return number of successfully booked seats
}

// Main ticket booking function
void bookTicket() {
    Booking booking;
    int movie_choice, showtime_choice;
    
    // Display available movies and get selection
    displayMovies();
    printf("\nSelect a movie (ID): ");
    scanf("%d", &movie_choice);
    
    // Validate movie selection
    if(movie_choice < 1 || movie_choice > MAX_MOVIES) {
        printf("Invalid movie selection!\n");
        return;
    }
    
    // Display showtimes for selected movie and get selection
    displayShowtimes(movie_choice);
    printf("\nSelect a showtime (ID): ");
    scanf("%d", &showtime_choice);
    
    // Validate showtime selection
    if(showtime_choice < 1 || showtime_choice > MAX_SHOWTIMES || 
       showtimes[showtime_choice-1].movie_id != movie_choice) {
        printf("Invalid showtime selection!\n");
        return;
    }
    
    // Display seat map for selected showtime
    displaySeatMap(showtime_choice);
    
    // Get number of tickets
    printf("\nEnter number of tickets (max 10): ");
    scanf("%d", &booking.num_tickets);
    
    // Validate ticket quantity
    if(booking.num_tickets <= 0 || booking.num_tickets > 10) {
        printf("Invalid number of tickets! (1-10 allowed)\n");
        return;
    }
    
    // Get seat selection for each ticket
    printf("\nEnter seat numbers (e.g., A1, B3 etc.):\n");
    for(int i = 0; i < booking.num_tickets; i++) {
        printf("Seat %d: ", i+1);
        scanf("%s", booking.seat_numbers[i]);
        // Convert row letter to uppercase for consistency
        booking.seat_numbers[i][0] = toupper(booking.seat_numbers[i][0]);
    }
    
    // Attempt to book selected seats
    int seats_booked = bookSeats(showtime_choice, booking.num_tickets, booking.seat_numbers);
    if(seats_booked != booking.num_tickets) {
        printf("Couldn't book all seats. Only %d seats were booked.\n", seats_booked);
        if(seats_booked == 0) return;  // Exit if no seats were booked
        booking.num_tickets = seats_booked;  // Update with actual booked count
    }
    
    // Get customer details
    printf("\nEnter your name: ");
    scanf(" %[^\n]s", booking.name);  // Read full name including spaces
    
    // Validate phone number input
    do {
        printf("Enter your phone number (10 digits): ");
        scanf("%s", booking.phone);
        if(!validatePhone(booking.phone)) {
            printf("Invalid phone number! Please enter a 10-digit number.\n");
        }
    } while(!validatePhone(booking.phone));
    
    // Complete booking details
    booking.movie_id = movie_choice;
    booking.showtime_id = showtime_choice;
    booking.base_price = booking.num_tickets * BASE_TICKET_PRICE;
    booking.gst = booking.base_price * (GST_PERCENT / 100);
    booking.total_cost = booking.base_price + booking.gst;
    time(&booking.booking_time); // Set current timestamp
    
    // Print booking confirmation and tickets
    printBookingReceipt(booking);
    for(int i = 0; i < booking.num_tickets; i++) {
        printTicket(booking, i+1);
    }
}

// Print detailed booking receipt with GST breakdown
void printBookingReceipt(Booking booking) {
    char movie_title[50] = "";
    char showtime[10] = "";
    char date_time[30];
    struct tm *timeinfo;
    
    // Get movie title from ID
    for(int i = 0; i < MAX_MOVIES; i++) {
        if(movies[i].id == booking.movie_id) {
            strcpy(movie_title, movies[i].title);
            break;
        }
    }
    
    // Get showtime from ID
    for(int i = 0; i < MAX_SHOWTIMES; i++) {
        if(showtimes[i].id == booking.showtime_id) {
            strcpy(showtime, showtimes[i].time);
            break;
        }
    }
    
    // Format booking time
    timeinfo = localtime(&booking.booking_time);
    strftime(date_time, sizeof(date_time), "%d-%m-%Y %H:%M:%S", timeinfo);
    
    // Print receipt header
    printf("\n");
    printf("=============================================\n");
    printf("           PVR CINEMAS - RECEIPT\n");
    printf("=============================================\n");
    printf(" Booking Time: %s\n", date_time);
    printf("---------------------------------------------\n");
    
    // Print customer details
    printf(" Customer Name: %s\n", booking.name);
    printf(" Phone Number: %s\n", booking.phone);
    
    // Print booking details
    printf(" Movie: %s (%s)\n", movie_title, movies[booking.movie_id-1].language);
    printf(" Showtime: %s\n", showtime);
    printf(" Seats Booked: ");
    for(int i = 0; i < booking.num_tickets; i++) {
        printf("%s ", booking.seat_numbers[i]);
    }
    printf("\n");
    
    // Print pricing breakdown
    printf("---------------------------------------------\n");
    printf(" Base Price:    Rs.%.2f\n", booking.base_price);
    printf(" GST (%.1f%%):    Rs.%.2f\n", GST_PERCENT, booking.gst);
    printf(" Total Amount:  Rs.%.2f\n", booking.total_cost);
    
    // Print receipt footer
    printf("=============================================\n");
    printf("        Thank You! Enjoy Your Movie!\n");
    printf("=============================================\n\n");
}

// Print individual ticket for each seat
void printTicket(Booking booking, int ticket_num) {
    char movie_title[50] = "";
    char showtime[10] = "";
    char date_time[30];
    struct tm *timeinfo;
    
    // Get movie title from ID
    for(int i = 0; i < MAX_MOVIES; i++) {
        if(movies[i].id == booking.movie_id) {
            strcpy(movie_title, movies[i].title);
            break;
        }
    }
    
    // Get showtime from ID
    for(int i = 0; i < MAX_SHOWTIMES; i++) {
        if(showtimes[i].id == booking.showtime_id) {
            strcpy(showtime, showtimes[i].time);
            break;
        }
    }
    
    // Format booking time
    timeinfo = localtime(&booking.booking_time);
    strftime(date_time, sizeof(date_time), "%d-%m-%Y %H:%M:%S", timeinfo);
    
    // Print ticket header
    printf("\n");
    printf("=============================================\n");
    printf("           PVR CINEMAS - TICKET\n");
    printf("=============================================\n");
    
    // Print ticket details
    printf(" Booking Time: %s\n", date_time);
    printf(" Ticket No: %d/%d\n", ticket_num, booking.num_tickets);
    printf("---------------------------------------------\n");
    printf(" Movie: %s (%s)\n", movie_title, movies[booking.movie_id-1].language);
    printf(" Showtime: %s\n", showtime);
    printf(" Seat: %s\n", booking.seat_numbers[ticket_num-1]);
    printf(" Screen: Audi %d\n", (booking.showtime_id % 3) + 1); // Assign screen number
    
    // Print ticket footer
    printf("---------------------------------------------\n");
    printf(" Price: Rs.%.2f (incl. GST)\n", BASE_TICKET_PRICE);
    printf("=============================================\n");
    printf("   Please arrive at least 30 mins before\n");
    printf("=============================================\n\n");
}