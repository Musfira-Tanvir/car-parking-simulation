#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int maxHoursAllowed = 24;
const double discountThreshold = 16.00;
const double eveningCharge = 2.00;
double dailyTotal = 0.0;

double calculatePricePerHour(int day, int hour) {
    if (day == 0 && hour >= 8 && hour < 16) {
        return 2.00;
    } else if ((day >= 1 && day <= 5) && hour >= 8 && hour < 16) {
        return 10.00;
    } else if (day == 6 && hour >= 8 && hour < 16) {
        return 3.00;
    } else {
        return 2.00;
    }
}

double calculateBasePrice(int day, int hour, int numHours) {
    double pricePerHour = calculatePricePerHour(day, hour);
    return pricePerHour * numHours;
}

double applyDiscount(double price, int hour) {
    if (hour >= discountThreshold) {
        return price * 0.5;
    } else {
        return price * 0.9;
    }
}

double addEveningCharge(double price, int hour, int numHours) {
    if (hour < discountThreshold && hour + numHours >= discountThreshold) {
        return price + eveningCharge;
    } else {
        return price;
    }
}

int getValidDay() {
    int day;
    do {
        cout << "Enter day (0 for Sunday, 1 for Monday, ..., 6 for Saturday): ";
        cin >> day;
        if (day < 0 || day > 6) {
            cout << "Invalid day. Please enter a value between 0 and 6." << endl;
        }
    } while (day < 0 || day > 6);
    return day;
}

int getValidHour() {
    int hour;
    do {
        cout << "Enter hour of arrival (0-23): ";
        cin >> hour;
        if (hour < 0 || hour > 23) {
            cout << "Invalid hour. Please enter a value between 0 and 23." << endl;
        }
    } while (hour < 0 || hour > 23);
    return hour;
}

int getValidNumHours() {
    int numHours;
    do {
        cout << "Enter number of hours to park: ";
        cin >> numHours;
        if (numHours <= 0 || numHours > maxHoursAllowed) {
            cout << "Invalid number of hours. Please enter a value greater than 0 and less than or equal to " << maxHoursAllowed << "." << endl;
        }
    } while (numHours <= 0 || numHours > maxHoursAllowed);
    return numHours;
}

string getFrequentParkingNumber() {
    string frequentParkingNumber;
    cout << "Enter your frequent parking number (5 digits): ";
    cin >> frequentParkingNumber;
    return frequentParkingNumber;
}

bool isValidFrequentParkingNumber(const string& frequentParkingNumber) {
    if (frequentParkingNumber.length() != 5) {
        cout << "Invalid frequent parking number length. Please enter a 5-digit number." << endl;
        return false;
    }

    string digits = frequentParkingNumber.substr(0, 4);
    char checkDigit = frequentParkingNumber[4];
    int number = stoi(digits);

    int sum = 0;
    int multiplier = 2;
    for (int i = digits.size() - 1; i >= 0; --i) {
        sum += (digits[i] - '0') * multiplier;
        ++multiplier;
    }

    int remainder = sum % 11;
    char expectedCheckDigit;

    if (remainder == 0) {
        expectedCheckDigit = '0';
    } else {
        expectedCheckDigit = '0' + (11 - remainder);
    }

    if (checkDigit != expectedCheckDigit) {
        cout << "Invalid check digit." << endl;
        return false;
    }

    return true;
}

bool hasFrequentParkingNumber() {
    char response;
    do {
        cout << "Do you have a frequent parking number? (Enter 'y' for yes, 'n' for no): ";
        cin >> response;
        if (response != 'y' && response != 'Y' && response != 'n' && response != 'N') {
            cout << "Invalid response. Please enter 'y' or 'n'." << endl;
        }
    } while (response != 'y' && response != 'Y' && response != 'n' && response != 'N');
    return (response == 'y' || response == 'Y');
}

int calculateDiscountPercentage(int hour) {
    return (hour >= discountThreshold) ? 50 : 10;
}

double calculatePrice() {
    int day, hour, numHours;
    bool hasFrequentNumber;
    string frequentParkingNumber;

    day = getValidDay();
    hour = getValidHour();
    numHours = getValidNumHours();

    hasFrequentNumber = hasFrequentParkingNumber();

    double basePrice = calculateBasePrice(day, hour, numHours);

    if (hasFrequentNumber) {
        frequentParkingNumber = getFrequentParkingNumber();

        if (!isValidFrequentParkingNumber(frequentParkingNumber)) {
            cout << "No discount applied." << endl;
        } else if (hour >= discountThreshold) {
            basePrice = applyDiscount(basePrice, hour);
            cout << "Discount applied: " << calculateDiscountPercentage(hour) << "%" << endl;
        }
    }

    if (hour < discountThreshold && (hour + numHours) >= discountThreshold) {
        basePrice += eveningCharge;
        cout << "Evening charge applied." << endl;
    }

    return basePrice;
}

void simulateParkingDay() {
    int numCustomers;
    cout << "Enter number of customers for today: ";
    cin >> numCustomers;

    for (int i = 0; i < numCustomers; ++i) {
        cout << "Customer " << (i + 1) << ":" << endl;
        double price = calculatePrice();
        cout << fixed << setprecision(2);
        cout << "Price to park: $" << price << endl;

        double payment;
        do {
            cout << "Enter amount paid: $";
            cin >> payment;

            if (payment < price) {
                cout << "Insufficient payment. Please enter an amount equal to or greater than the price." << endl;
            }
        } while (payment < price);

        dailyTotal += payment;
    }

    cout << fixed << setprecision(2);
    cout << "Daily total of payments: $" << dailyTotal << endl;
}

int main() {
    simulateParkingDay();
    return 0;
}
