#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <limits>
#include <map>

using namespace std;

class item {
    static int billNumber; // Static variable to keep track of bill number
    int total = 0, no = 0;
    map<string, int> Qty;
    map<string, int> price;
    map<string, int> totalprice;

public:
    item() {
        no = ++billNumber; // Initialize bill number automatically
    }
    void input();
    void output();
    void sumoutput();
    void non(int x) {
        no = 100;
        no += x;
    }

    // Public member functions for accessing private members
    const map<string, int>& getTotalPrice() const { return totalprice; }
    int getBillNo() const { return no; }
    const map<string, int>& getQty() const { return Qty; }
    const map<string, int>& getPrice() const { return price; }

    int getPositiveIntegerInput(string prompt);
};

// Initialize static variable outside class definition
int item::billNumber = 1;

int item::getPositiveIntegerInput(string prompt) {
    int input;
    while (true) {
        cout << prompt;
        cin >> input;

        if (cin.fail() || input <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a positive integer." << endl;
        } else {
            break;
        }
    }
    return input;
}

void item::input() {
    system("CLS");
    total = getPositiveIntegerInput("Enter the number of items: ");

    for (int i = 0; i < total; i++) {
        string itemName;
        cout << "\nEnter the name of Item " << i + 1 << ": ";
        cin >> itemName;

        Qty[itemName] += getPositiveIntegerInput("Enter the quantity: ");
        price[itemName] = getPositiveIntegerInput("Enter the price of the item: ");

        totalprice[itemName] = Qty[itemName] * price[itemName];
    }
    output();
}

void item::output() {
    system("CLS");
    cout << "Bill No: " << no << "\n";
    cout << "-------------------------------------------------------------------------------------------\n";
    cout << "S.no\tName of item\tQuantity\tPrice\tTotal Price\n";

    int i = 1;
    for (const auto &entry : totalprice) {
        cout << i++ << ".\t" << entry.first << "\t" << Qty[entry.first] << "\t" << price[entry.first] << "\t" << entry.second << "\n";
    }

    sumoutput();
}

void item::sumoutput() {
    int sum = 0, qty = 0, cash = 0;
    double totalGST = 0.0;

    for (const auto &entry : totalprice) {
        sum += entry.second;
        qty += Qty[entry.first];
    }

    // Calculate GST based on total sum
    totalGST = 0.18 * sum; // Assuming GST rate is 18%

    cout << "\n--------------------------------------------------------------------------------------------";
    cout << "\nTotal: ";
    cout << "\n\tQuantity: " << qty << "\t\tSum: " << sum << "\tWith Taxes: " << sum + totalGST;
    cout << "\n\t\t\tTotal GST: " << totalGST;
    cout << "\n--------------------------------------------------------------------------------------------";

    pay:
    cout << "\n\n\t\t\t*PAYMENT DETAILS*\n";
    cout << "\n\t\t\tTotal cash given: ";
    cin >> cash;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "Invalid input. Please enter a valid numeric value." << endl;
        goto pay;
    }
    if (cash >= (sum + totalGST))
        cout << "\n\t\t\tTotal cash repaid: " << cash - (sum + totalGST) << "\n";
    else {
        cout << "\n\t\t\tCash given is less than the total amount!!!";
        goto pay;
    }
    cout << "\n\t\t\t Payment Successful   ";
}

void displayPreviousEntries() {
    try {
        ifstream inf("database.csv");
        if (!inf) {
            throw runtime_error("Error opening the file for reading.");
        }

        cout << "\nPrevious Entries:\n\n";
        cout << setw(10) << left << "Bill No" << setw(20) << left << "Item Name" << setw(10) << left << "Quantity" << setw(10) << left << "Price" << setw(15) << left << "Total Price" << endl;
        cout << "------------------------------------------------------------------------------\n";

        string line;
        while (getline(inf, line)) {
            stringstream ss(line);
            string billNo, itemName, qty, price, totalPrice;

            getline(ss, billNo, ',');
            getline(ss, itemName, ',');
            getline(ss, qty, ',');
            getline(ss, price, ',');
            getline(ss, totalPrice, ',');

            cout << setw(10) << left << billNo << setw(20) << left << itemName << setw(10) << left << qty << setw(10) << left << price << setw(15) << left << totalPrice << endl;
        }
        inf.close();
    } catch (const exception &e) {
        cerr << "Exception: " << e.what() << endl;
    }
}

void makeNewEntry() {
    try {
        item it;
        it.input();

        // Open the CSV file for appending
        ofstream outf("database.csv", ios::app);
        if (!outf) {
            throw runtime_error("Error opening the file for writing.");
        }

        // Write data to CSV
        for (const auto &entry : it.getTotalPrice()) {
            outf << it.getBillNo() << "," << entry.first << "," << it.getQty().at(entry.first) << "," << it.getPrice().at(entry.first) << "," << entry.second << "\n";
        }
        outf.close();
    } catch (const exception &e) {
        cerr << "Exception: " << e.what() << endl;
    }
}

int main() {
    cout << "Welcome to BILLING MANAGEMENT SYSTEM\n\n";

    do {
        system("PAUSE");
        system("CLS");

        cout << "\n\nChoose Between 1 to 3";
        cout << "\n Press 1. Make a new entry";
        cout << "\n Press 2. Check all previous entries";
        cout << "\n Press 3. Exit";
        cout << "\n\n Choose your option: ";

        int option;
        cin >> option;

        if (option == 1) {
            try {
                item it;
                it.input();

                // Open the CSV file for appending
                ofstream outf("database.csv", ios::app);
                if (!outf) {
                    throw runtime_error("Error opening the file for writing.");
                }

                // Write data to CSV
                for (const auto &entry : it.getTotalPrice()) {
                    outf << it.getBillNo() << "," << entry.first << "," << it.getQty().at(entry.first) << "," << it.getPrice().at(entry.first) << "," << entry.second << "\n";
                }
                outf.close();
            } catch (const exception &e) {
                cerr << "Exception: " << e.what() << endl;
            }
        } else if (option == 2) {
            displayPreviousEntries(); // Print previous entries
        } else if (option == 3) {
            cout << "Thank you!!";
            exit(0);
        } else {
            cout << "\n\t\tPlease choose from 1 to 3 (both included)\n";
        }
    } while (true);

    return 0;
}
