# 🎬  Movie Ticket Booking System

A console-based movie ticket booking system written in C that I made in my first semester. This project simulates the experience of booking movie tickets at Indian cinema chains like PVR Cinemas.

## ✨ Features

- **Movie Management**: Pre-loaded with popular Indian movies (RRR, Baahubali 2, Dangal, KGF Chapter 2, Pushpa)
- **Showtime Management**: Multiple showtimes throughout the day for different movies
- **Interactive Seat Selection**: Visual seat map with real-time availability
- **Customer Validation**: Phone number validation for Indian mobile numbers (10 digits)
- **Price Calculation**: Automatic GST calculation (18%) on ticket prices
- **Receipt Generation**: Detailed booking receipts and individual tickets
- **Multi-language Support**: Movies in Telugu, Hindi, and Kannada

## 🎯 System Specifications

- **Theater Capacity**: 50 seats (5 rows × 10 seats per row)
- **Base Ticket Price**: ₹180 per ticket
- **GST Rate**: 18%
- **Maximum Movies**: 5 movies
- **Maximum Showtimes**: 5 showtimes per day
- **Booking Limit**: 1-10 tickets per transaction

## 🚀 Getting Started

### Prerequisites

- GCC compiler (or any C compiler)
- Terminal/Command Prompt

### Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/yourusername/movie-ticket-booking-system.git
   cd movie-ticket-booking-system
   ```

2. **Compile the program**
   ```bash
   gcc -o movie_booking movie_booking.c
   ```

3. **Run the application**
   ```bash
   ./movie_booking
   ```

## 📖 How to Use

### 1. Main Menu
Upon starting the application, you'll see:
- **Option 1**: Book Tickets
- **Option 2**: Exit

### 2. Booking Process

1. **Select a Movie**: Choose from the available movies by entering the movie ID
2. **Select Showtime**: Pick your preferred showtime from available slots
3. **View Seat Map**: See the current seat availability
4. **Choose Seats**: Enter seat numbers (e.g., A1, B5, C10)
5. **Enter Details**: Provide your name and 10-digit phone number
6. **Confirmation**: Receive booking receipt and individual tickets

### 3. Seat Numbering System
- **Rows**: A, B, C, D, E (5 rows)
- **Columns**: 1-10 (10 seats per row)
- **Format**: Row + Number (e.g., A1, B5, E10)

## 🎮 Example Usage

```
Select a movie (ID): 1
Select a showtime (ID): 1

Seat Map (Showtime ID: 1):
     1  2  3  4  5  6  7  8  9  10
A -> A  A  A  A  A  A  A  A  A  A
B -> A  A  A  A  A  A  A  A  A  A
C -> A  A  A  A  A  A  A  A  A  A
D -> A  A  A  A  A  A  A  A  A  A
E -> A  A  A  A  A  A  A  A  A  A

Enter number of tickets: 2
Seat 1: A5
Seat 2: A6

Enter your name: Aditya
Enter your phone number: 9876543210
```

## 💳 Pricing Structure

| Component | Amount |
|-----------|---------|
| Base Price per Ticket | ₹180.00 |
| GST (18%) | Auto-calculated |
| **Total per Ticket** | **₹212.40** |

## 🏗️ Code Structure

### Key Data Structures

- **Movie**: Stores movie details (ID, title, duration, genre, language)
- **Showtime**: Manages screening times and seat availability
- **Booking**: Handles customer booking information and pricing

### Main Functions

- `initializeSeats()`: Sets all seats as available
- `displayMovies()`: Shows available movies
- `displaySeatMap()`: Visual representation of theater layout
- `bookTicket()`: Main booking workflow
- `validatePhone()`: Indian phone number validation
- `printBookingReceipt()`: Generates detailed receipt

## 🛠️ Technical Details

### Memory Management
- Fixed-size arrays for movies and showtimes
- No dynamic memory allocation
- Efficient seat tracking using 2D character arrays

### Input Validation
- Movie and showtime ID validation
- Seat number format checking
- Phone number validation (10 digits)
- Ticket quantity limits (1-10)

### Error Handling
- Invalid seat selection handling
- Already booked seat detection
- Input format validation
- Boundary checking for arrays

## 🎨 Sample Output

```
=============================================
           PVR CINEMAS - RECEIPT
=============================================
 Booking Time: 29-06-2025 14:30:45
---------------------------------------------
 Customer Name: Aditya
 Phone Number: 9876543210
 Movie: RRR (Telugu/Hindi)
 Showtime: 10:00
 Seats Booked: A5 A6 
---------------------------------------------
 Base Price:    Rs.360.00
 GST (18.0%):   Rs.64.80
 Total Amount:  Rs.424.80
=============================================
        Thank You! Enjoy Your Movie!
=============================================
```

## 🔧 Customization

### Adding New Movies
Modify the `movies` array in the global section:
```c
Movie movies[MAX_MOVIES] = {
    {6, "Your Movie", 150, "Genre", "Language"},
    // Add more movies...
};
```

### Changing Pricing
Update the constants at the top of the file:
```c
#define BASE_TICKET_PRICE 200.00  // Change base price
#define GST_PERCENT 18.0          // Modify GST rate
```

### Theater Layout
Adjust theater size by modifying:
```c
#define SEATS_PER_ROW 12     // Change seats per row
#define TOTAL_ROWS 8         // Change number of rows
```

## 📋 Requirements

- **Compiler**: GCC 4.8+ or compatible C compiler
- **Platform**: Cross-platform (Windows, Linux, macOS)
- **Memory**: Minimal (~1MB)
- **Dependencies**: Standard C libraries only

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## 🔗 Connect with Me

- 🔗 GitHub: [@ADiTyaRaj8969](https://github.com/ADiTyaRaj8969)  
- ✉️ Email: adivid198986@gmail.com  
- 💼 LinkedIn: [Aditya Raj](https://www.linkedin.com/in/aditya-raj-710a5a291/)

## 🙏 Acknowledgments

- Inspired by Indian cinema booking systems
- Built for educational purposes
- Perfect for learning C programming concepts

---

⭐ **Star this repository if you found it helpful!**
