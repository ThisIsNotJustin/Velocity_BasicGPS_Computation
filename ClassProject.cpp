#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

void computeVelocity(double minutes) {
  // initialize seconds variable with the minutes argument * 60
  double seconds = minutes * 60;
  // initialize velocity and acceleration variables
  double velocity = 0, acceleration = 0;

  // if minutes is 0 set velocity and acceleration variables
  // to given velocity and acceleration in m/s and m/s^s respectively
  if (minutes == 0) {
    velocity = 180;
    acceleration = 1;
    // if minutes is 2 set velocity and acceleration variables
    // to their respective maximum (velocity) and minimum (acceleration)
  } else if (minutes >= 2) {
    velocity = 218;
    acceleration = 0;
    // else calculate the velocity and acceleration using the given formulas
    // with the seconds variables
  } else {
    velocity = .00001 * pow(seconds, 3) - .00488 * pow(seconds, 2) +
               .75795 * seconds + 181.3566;
    acceleration = 3 - .000062 * pow(velocity, 2);
  }
  // convert velocity and acceleration to use feet instead of meters
  double footVelocity = ((velocity * 39.37) / 12);
  double footAcceleration = ((acceleration * 39.37) / 12);

  // display the velocity in feet/second
  std::cout << "Velocity: " << std::fixed << std::setprecision(2)
            << footVelocity << " (f/s)\n";
  // validation if acceleration is calculated as less than 0
  // set acceleration to 0
  if (footAcceleration < 0) {
    footAcceleration = 0;
  }
  // display acceleration in feet/second^2
  std::cout << "Acceleration: " << std::fixed << std::setprecision(2)
            << footAcceleration << " (f/s^2)\n";
}

void gps(std::string satellites[], double times[], double high, int size) {
  // iterate over the times array and find the index of the highest value
  int index = 0;
  for (int i = 1; i < size; i++) {
    if (times[i] > times[index]) {
      index = i;
    }
  }
  // display the satellite number, satellite ID and the transmission time
  // as being the furthest away
  std::cout << "Satellite " << index + 1 << " (" << satellites[index]
            << ") is the furthest away with a "
            << "transmission time of " << std::fixed << std::setprecision(2)
            << times[index] << " seconds\n";
}

int main() {
  // boolean variable to display menu
  bool displayMenu = true;
  // variables for minutes, transmitTime, and satelliteID
  double minutes, transmitTime = 0;
  std::string satelliteID = "";

  // while displayMenu is true, the menu will be printed for the user to make a
  // selection
  while (displayMenu) {
    std::cout << "Operations\n";
    std::cout << "1. Velocity Computation\n";
    std::cout << "2. GPS\n";
    std::cout << "3. Exit\n";

    // initialize menu selection
    int selection = 0;

    // if the user inputted an integer update selection with this integer
    if (std::cin >> selection) {
      // switch statement for user's selection
      switch (selection) {
      // if user input 1
      case 1: {
        // validation to get the length of time as a double if a double is not
        // entered, this will loop
        do {
          std::cout << "Please enter the length of time in minutes: ";
          std::cin.clear(); // clear the error flag
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                          '\n'); // ignore input buffer
        } while (!(std::cin >> minutes));
        // store the length of time in minutes input from the user call
        // computeVelocity function, passing the minutes variable
        computeVelocity(minutes);
        std::cout << '\n'; // newline for formatting
        break;
      }
      // if user input 2
      case 2: {
        // create two arrays with a length of 5 for satellite ID's
        // and for transmit Times
        std::string satellites[5];
        double times[5];
        // double with the lowest value for an integer to start with
        // a very low number so transmit times will be higher
        double high = std::numeric_limits<int>::min();

        // iterate 5 times for each of the satellites
        for (int i = 1; i <= 5; i++) {
          std::cin.ignore();
          // boolean variable to validate duplicate satellite IDs
          bool duplicateID;
          // validate satellite ID input
          do {
            std::cout << "Please enter the Satellite ID for Satellite " << i
                      << ": \n";
            std::getline(std::cin, satelliteID);
            // initialize boolean variable to false
            duplicateID = false;

            for (int j = 0; j < i - 1; j++) {
              // if satelliteID has been repeated, update
              // boolean variable to true and break out of
              // for loop ask for satelliteID again
              if (satelliteID == satellites[j]) {
                std::cout << "Satellite ID '" << satelliteID
                          << "' has been entered\n";
                duplicateID = true;
                break;
              }
            }
          } while (satelliteID.empty() || duplicateID);

          // validate transmit time input
          do {
            std::cout
                << "Please enter the transmit time in seconds for Satellite "
                << i << " (" << satelliteID << "): \n";
          } while (!(std::cin >> transmitTime));

          // store satellite IDs
          satellites[i - 1] = satelliteID;
          // store transmit times
          times[i - 1] = transmitTime;

          // find highest input time
          if (transmitTime > high) {
            high = transmitTime;
          }
        }

        std::cout << std::endl;
        // pass the 2 arrays and the highest transmitTime to
        // the gps function
        gps(satellites, times, high, 5);
        std::cout << std::endl;
        break;
      }

      // if the user input 3, display a message for using the program
      // set displayMenu to false and exit the program
      case 3:
        std::cout << "Thank you for using the program!" << std::endl;
        displayMenu = false;
        std::exit(0);
        break;

      // if the user input a number other than 1, 2, or 3
      // display a messsage to enter 1, 2, or 3
      default:
        std::cout << "Please enter either 1, 2, or 3" << std::endl;
        break;
      }
    }
  }
  return 0;
}