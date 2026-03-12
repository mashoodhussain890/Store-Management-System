#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

const int MAX_PRODUCTS = 100;
const int MAX_NAME_LENGTH = 50;
const int MAX_CART_SIZE = 10;

void displayMenu();
void displayCustomerMenu();
void addProduct(char names[][MAX_NAME_LENGTH], double prices[], int& count);
void displayProducts(const char names[][MAX_NAME_LENGTH], const double prices[], int count);
void removeProduct(char names[][MAX_NAME_LENGTH], double prices[], int& count);
void updatePrices(char names[][MAX_NAME_LENGTH], double prices[], int count);
void readProductNamesFromFile(char names[][MAX_NAME_LENGTH], double prices[], int& count);
void writeProductNamesToFile(const char names[][MAX_NAME_LENGTH], const double prices[], int count);
void addToCart(char names[][MAX_NAME_LENGTH], double prices[], int productCount, int cartProductIds[], int cartQuantities[], int& cartSize);
void printBill(char names[][MAX_NAME_LENGTH], double prices[], int cartProductIds[], int cartQuantities[], int cartSize, string customerName, int customerAge, char customerGender);
double applyDiscount(double total, int age);

int main() {
    char productNames[MAX_PRODUCTS][MAX_NAME_LENGTH];
    double productPrices[MAX_PRODUCTS];
    int productCount = 0;

    int cartProductIds[MAX_CART_SIZE];
    int cartQuantities[MAX_CART_SIZE];
    int cartSize = 0;

    string customerName = "Guest";
    int customerAge = 0;
    char customerGender = 'U';
    char conditions;

    readProductNamesFromFile(productNames, productPrices, productCount);

    cout << "Press 'M' for Manager & 'C' for Customer: ";
    cin >> conditions;

    if (conditions == 'M' || conditions == 'm') {
        char password[50];
        cout << "Enter manager password: ";
        cin >> password;

        if (strcmp(password, "admin123") == 0) {
            int choice;
            do {
                displayMenu();
                cout << "Enter your choice: ";
                cin >> choice;

                switch(choice) {
                    case 1:
                        addProduct(productNames, productPrices, productCount);
                        break;
                    case 2:
                        displayProducts(productNames, productPrices, productCount);
                        break;
                    case 3:
                        removeProduct(productNames, productPrices, productCount);
                        break;
                    case 4:
                        updatePrices(productNames, productPrices, productCount);
                        break;
                    case 5:
                        writeProductNamesToFile(productNames, productPrices, productCount);
                        cout << "Products saved. Exiting program. Goodbye!" << endl;
                        break;
                    case 6:
                        cout << "\nEnter customer details:\n";
                        cout << "Name: ";
                        cin.ignore();
                        getline(cin, customerName);
                        cout << "Age: ";
                        cin >> customerAge;
                        cout << "Gender (M/F): ";
                        cin >> customerGender;
                        break;
                    case 7:
                        addToCart(productNames, productPrices, productCount, cartProductIds, cartQuantities, cartSize);
                        break;
                    case 8:
                        printBill(productNames, productPrices, cartProductIds, cartQuantities, cartSize, customerName, customerAge, customerGender);
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                }
            } while (choice != 5);
        } else {
            cout << "Incorrect password. Exiting program." << endl;
        }
    } 
    else if (conditions == 'C' || conditions == 'c') {
        int choice;
        do {
            displayCustomerMenu();
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    displayProducts(productNames, productPrices, productCount);
                    break;
                case 2:
                    cout << "\nEnter customer details:\n";
                    cout << "Name: ";
                    cin.ignore();
                    getline(cin, customerName);
                    cout << "Age: ";
                    cin >> customerAge;
                    cout << "Gender (M/F): ";
                    cin >> customerGender;
                    break;
                case 3:
                    addToCart(productNames, productPrices, productCount, cartProductIds, cartQuantities, cartSize);
                    break;
                case 4:
                    printBill(productNames, productPrices, cartProductIds, cartQuantities, cartSize, customerName, customerAge, customerGender);
                    break;
                case 5:
                    cout << "Exiting customer interface. Goodbye!" << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
            }
        } while (choice != 5);
    } else {
        cout << "Invalid input. Exiting program." << endl;
    }

    return 0;
}


void displayMenu() {
    cout << "\n======= Manager Menu =======\n";
    cout << "1. Add Product\n";
    cout << "2. Display Products\n";
    cout << "3. Remove Product\n";
    cout << "4. Update Prices\n";
    cout << "5. Save & Exit\n";
    cout << "6. Add Customer Details\n";
    cout << "7. Add to Cart\n";
    cout << "8. Print Bill\n";
}

void displayCustomerMenu() {
    cout << "\n======= Customer Menu =======\n";
    cout << "1. Display Products\n";
    cout << "2. Add Customer Details\n";
    cout << "3. Add to Cart\n";
    cout << "4. Print Bill\n";
    cout << "5. Exit\n";
}

void readProductNamesFromFile(char names[][MAX_NAME_LENGTH], double prices[], int& count) {
    ifstream inputFile("products.txt");
    if (!inputFile.is_open()) {
        cout << "No existing products.txt found. Starting fresh." << endl;
        return;
    }

    while (inputFile >> names[count] >> prices[count]) {
        count++;
    }
    inputFile.close();
}

void writeProductNamesToFile(const char names[][MAX_NAME_LENGTH], const double prices[], int count) {
    ofstream outputFile("products.txt");
    if (!outputFile.is_open()) {
        cout << "Error opening file: products.txt" << endl;
        return;
    }

    for (int i = 0; i < count; i++) {
        outputFile << names[i] << " " << prices[i] << "\n";
    }
    outputFile.close();
}

void addProduct(char names[][MAX_NAME_LENGTH], double prices[], int& count) {
    if (count < MAX_PRODUCTS) {
        cout << "\nEnter product name (no spaces): ";
        cin.ignore(); 
        cin.getline(names[count], MAX_NAME_LENGTH);

        cout << "Enter product price: $";
        cin >> prices[count];

        cout << "Product added successfully!\n";
        count++;
    } else {
        cout << "Maximum products reached!\n";
    }
}

void displayProducts(const char names[][MAX_NAME_LENGTH], const double prices[], int count) {
    if (count > 0) {
        cout << "\n--- Product List ---\n";
        for (int i = 0; i < count; i++) {
            cout << i + 1 << ". " << names[i] << " - $" << prices[i] << endl;
        }
    } else {
        cout << "No products available.\n";
    }
}

void removeProduct(char names[][MAX_NAME_LENGTH], double prices[], int& count) {
    if (count > 0) {
        int index;
        cout << "Enter the index of the product to remove: ";
        cin >> index;

        if (index >= 1 && index <= count) {
            for (int i = index - 1; i < count - 1; i++) {
                strcpy(names[i], names[i + 1]);
                prices[i] = prices[i + 1];
            }
            cout << "Product removed successfully!\n";
            count--;
        } else {
            cout << "Invalid index. No product removed.\n";
        }
    } else {
        cout << "No products available to remove.\n";
    }
}

void updatePrices(char names[][MAX_NAME_LENGTH], double prices[], int count) {
    if (count > 0) {
        int index;
        cout << "Enter the index of the product to update: ";
        cin >> index;

        if (index >= 1 && index <= count) {
            cout << "Enter the new price for " << names[index - 1] << " (Current: $" << prices[index - 1] << "): $";
            cin >> prices[index - 1];
            cout << "Price updated successfully!\n";
        } else {
            cout << "Invalid index. No price updated.\n";
        }
    } else {
        cout << "No products available to update prices.\n";
    }
}

void addToCart(char names[][MAX_NAME_LENGTH], double prices[], int productCount, int cartProductIds[], int cartQuantities[], int& cartSize) {
    int productId, quantity;
    displayProducts(names, prices, productCount);
    
    while (true) {
        cout << "\nEnter product ID to add to cart (-1 to exit): ";
        cin >> productId;
        
        if (productId == -1) {
            break;
        }
        
        if (productId >= 1 && productId <= productCount) {
            cout << "Enter quantity: ";
            cin >> quantity;
            
            if (quantity > 0 && cartSize < MAX_CART_SIZE) {
                cartProductIds[cartSize] = productId - 1;
                cartQuantities[cartSize] = quantity;
                cartSize++;
                cout << "Product added to cart.\n";
            } else if (cartSize >= MAX_CART_SIZE) {
                cout << "Cart is full.\n";
                break;
            } else {
                cout << "Invalid quantity.\n";
            }
        } else {
            cout << "Invalid product ID.\n";
        }
    }
}

void printBill(char names[][MAX_NAME_LENGTH], double prices[], int cartProductIds[], int cartQuantities[], int cartSize, string customerName, int customerAge, char customerGender) {
    if (cartSize == 0) {
        cout << "\nYour cart is empty! Cannot print bill.\n";
        return;
    }

    cout << "\n================= Bill =================\n";
    cout << "Customer: " << customerName << " | Age: " << customerAge << " | Gender: " << customerGender << "\n";
    cout << "----------------------------------------\n";
    cout << left << setw(20) << "Product" << setw(10) << "Quantity" << setw(15) << "Price/Item" << "Total\n";
    cout << "----------------------------------------\n";

    double totalBill = 0;

    for (int i = 0; i < cartSize; i++) {
        int productId = cartProductIds[i];
        int quantity = cartQuantities[i];
        double itemTotal = quantity * prices[productId];

        cout << left << setw(20) << names[productId] 
             << setw(10) << quantity 
             << "$" << setw(14) << prices[productId]
             << "$" << itemTotal << endl;

        totalBill += itemTotal;
    }

    double discountedBill = applyDiscount(totalBill, customerAge);
    cout << "----------------------------------------\n";
    cout << "Total Bill: $" << totalBill << endl;
    
    cout << "Discount Applied: ";
    if (totalBill == discountedBill) {
        cout << "0%\n";
    } else {
        cout << fixed << setprecision(2) << 100 * (totalBill - discountedBill) / totalBill << "%\n";
    }
    
    cout << "Discounted Bill: $" << discountedBill << endl;
    cout << "========================================\n";

    ofstream billFile("bill.txt", ios::app);
    if (billFile.is_open()) {
        billFile << "Customer: " << customerName << ", Age: " << customerAge << ", Gender: " << customerGender << "\n";
        billFile << left << setw(20) << "Product" << setw(10) << "Quantity" << setw(15) << "Price/Item" << "Total\n";
        for (int i = 0; i < cartSize; i++) {
            int productId = cartProductIds[i];
            int quantity = cartQuantities[i];
            billFile << left << setw(20) << names[productId] 
                     << setw(10) << quantity 
                     << "$" << setw(14) << prices[productId]
                     << "$" << quantity * prices[productId] << "\n";
        }
        billFile << "Total Bill: $" << totalBill << "\n";
        billFile << "Discounted Bill: $" << discountedBill << "\n";
        billFile << "=======================================\n";
        billFile.close();
    }
}

double applyDiscount(double total, int age) {
    double discount = 0;

    if (age > 0 && age < 18) {
        discount = 0.05;
    } else if (age >= 18 && age < 35) {
        discount = 0.1;
    } else if (age >= 35) {
        discount = 0.15;
    }
    
    return total - (total * discount);
}