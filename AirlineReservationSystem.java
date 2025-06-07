import java.util.*;

// Class representing a Flight
class Flight {
    String flightNumber;
    String source;
    String destination;
    String date;
    int capacity;
    int bookedSeats;

    public Flight(String flightNumber, String source, String destination, String date, int capacity) {
        this.flightNumber = flightNumber;
        this.source = source;
        this.destination = destination;
        this.date = date;
        this.capacity = capacity;
        this.bookedSeats = 0;
    }

    public boolean bookSeat() {
        if (bookedSeats < capacity) {
            bookedSeats++;
            return true;
        } else {
            return false;
        }
    }

    public void cancelSeat() {
        if (bookedSeats > 0) {
            bookedSeats--;
        }
    }

    @Override
    public String toString() {
        return "Flight " + flightNumber + " from " + source + " to " + destination + " on " + date +
                " (" + bookedSeats + "/" + capacity + " booked)";
    }
}

// Class representing a Passenger
class Passenger {
    String name;
    String passportNumber;

    public Passenger(String name, String passportNumber) {
        this.name = name;
        this.passportNumber = passportNumber;
    }
}

// Main Airline Reservation System
public class AirlineReservationSystem {
    private static List<Flight> flights = new ArrayList<>();
    private static Map<String, List<Passenger>> flightPassengers = new HashMap<>();

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Sample data
        flights.add(new Flight("AI101", "New York", "Los Angeles", "2024-12-30", 100));
        flights.add(new Flight("BA202", "London", "Paris", "2024-12-31", 50));

        while (true) {
            System.out.println("\n--- Airline Reservation System ---");
            System.out.println("1. Search Flights");
            System.out.println("2. Book Flight");
            System.out.println("3. Cancel Booking");
            System.out.println("4. View Flight Details");
            System.out.println("5. Exit");
            System.out.print("Enter your choice: ");
            int choice = scanner.nextInt();
            scanner.nextLine(); // consume newline

            switch (choice) {
                case 1 -> searchFlights(scanner);
                case 2 -> bookFlight(scanner);
                case 3 -> cancelBooking(scanner);
                case 4 -> viewFlightDetails(scanner);
                case 5 -> {
                    System.out.println("Exiting system. Goodbye!");
                    return;
                }
                default -> System.out.println("Invalid choice. Please try again.");
            }
        }
    }

    private static void searchFlights(Scanner scanner) {
        System.out.print("Enter source: ");
        String source = scanner.nextLine();
        System.out.print("Enter destination: ");
        String destination = scanner.nextLine();
        System.out.print("Enter date (YYYY-MM-DD): ");
        String date = scanner.nextLine();

        System.out.println("\nAvailable Flights:");
        for (Flight flight : flights) {
            if (flight.source.equalsIgnoreCase(source) &&
                    flight.destination.equalsIgnoreCase(destination) &&
                    flight.date.equals(date)) {
                System.out.println(flight);
            }
        }
    }

    private static void bookFlight(Scanner scanner) {
        System.out.print("Enter flight number: ");
        String flightNumber = scanner.nextLine();
        Flight flight = getFlightByNumber(flightNumber);
        if (flight == null) {
            System.out.println("Flight not found.");
            return;
        }

        System.out.print("Enter passenger name: ");
        String name = scanner.nextLine();
        System.out.print("Enter passport number: ");
        String passportNumber = scanner.nextLine();

        if (flight.bookSeat()) {
            Passenger passenger = new Passenger(name, passportNumber);
            flightPassengers.computeIfAbsent(flightNumber, k -> new ArrayList<>()).add(passenger);
            System.out.println("Booking successful!");
        } else {
            System.out.println("No seats available.");
        }
    }

    private static void cancelBooking(Scanner scanner) {
        System.out.print("Enter flight number: ");
        String flightNumber = scanner.nextLine();
        Flight flight = getFlightByNumber(flightNumber);
        if (flight == null) {
            System.out.println("Flight not found.");
            return;
        }

        System.out.print("Enter passenger passport number: ");
        String passportNumber = scanner.nextLine();

        List<Passenger> passengers = flightPassengers.get(flightNumber);
        if (passengers != null) {
            for (Passenger passenger : passengers) {
                if (passenger.passportNumber.equals(passportNumber)) {
                    passengers.remove(passenger);
                    flight.cancelSeat();
                    System.out.println("Booking canceled.");
                    return;
                }
            }
        }
        System.out.println("Passenger not found.");
    }

    private static void viewFlightDetails(Scanner scanner) {
        System.out.print("Enter flight number: ");
        String flightNumber = scanner.nextLine();
        Flight flight = getFlightByNumber(flightNumber);
        if (flight == null) {
            System.out.println("Flight not found.");
            return;
        }
        System.out.println(flight);
        List<Passenger> passengers = flightPassengers.get(flightNumber);
        if (passengers != null && !passengers.isEmpty()) {
            System.out.println("Passenger List:");
            for (Passenger passenger : passengers) {
                System.out.println("- " + passenger.name + " (" + passenger.passportNumber + ")");
            }
        } else {
            System.out.println("No passengers booked.");
        }
    }

    private static Flight getFlightByNumber(String flightNumber) {
        for (Flight flight : flights) {
            if (flight.flightNumber.equalsIgnoreCase(flightNumber)) {
                return flight;
            }
        }
        return null;
    }
}