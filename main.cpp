#include <iostream>
#include <fstream>
using namespace std;

class Shop {
private:
    int productCode;
    float price;
    float discount;
    string productName;

public:
    void start();
    void directorMenu();
    void buyerMenu();
    void add();
    void edit();
    void removeProduct();
    void list();
    void receipt();
    bool authenticateDirector();
};

void Shop::start() {
    int choice;

    do {
        cout << "\t\t\t**************************\n";
        cout << "\t\t\t                          \n";
        cout << "\t\t\t       shop         \n";
        cout << "\t\t\t**************************\n";
        cout << "\t\t\t|                         \n";
        cout << "\t\t\t|  1) Director            \n";
        cout << "\t\t\t|                         \n";
        cout << "\t\t\t|  2) Buyer               \n";
        cout << "\t\t\t|                         \n";
        cout << "\t\t\t|  3) Exit                \n";
        cout << "\t\t\t please select item!";
        cin >> choice;

        switch (choice) {
        case 1:
            if (authenticateDirector()) {
                directorMenu();
            } else {
                cout << "Wrong gmail/password";
            }
            break;

        case 2:
            buyerMenu();
            break;

        case 3:
            exit(0);
            break;

        default:
            cout << "Please select the given option";
        }
    } while (true);
}

bool Shop::authenticateDirector() {
    string gmail;
    string password;

    cout << "\t\t\t Please login \n";
    cout << "\t\t\t Enter gmail \n";
    cin >> gmail;
    cout << "\t\t\t Password      \n";
    cin >> password;

    return (gmail == "abc@gmail.com" && password == "12345");
}

void Shop::directorMenu() {
    int choice;
    do {
        cout << "\n\n\t\t Director menu";
        cout << "\n\t\t\t|****1) Add Product****|";
        cout << "\n\t\t\t|                     |";
        cout << "\n\t\t\t|****2) Update Product****|";
        cout << "\n\t\t\t|                     |";
        cout << "\n\t\t\t|****3) Remove Product****|";
        cout << "\n\t\t\t|                     |";
        cout << "\n\t\t\t|****4) Back to Menu****|";

        cout << "\n\n\t Please enter your choice ";
        cin >> choice;

        switch (choice) {
        case 1:
            add();
            break;

        case 2:
            edit();
            break;

        case 3:
            removeProduct();
            break;

        case 4:
            return;

        default:
            cout << "Invalid choice";
        }
    } while (true);
}

void Shop::buyerMenu() {
    int choice;
    do {
        cout << "\t\t\t Buyer  \n";
        cout << "\t\t\t********\n";
        cout << "\t\t\t        \n";
        cout << "\t\t\t 1) Buy Product \n";
        cout << "\t\t\t        \n";
        cout << "\t\t\t 2) Go back      \n";
        cout << "\t\t\t Enter your choice \n";

        cin >> choice;

        switch (choice) {
        case 1:
            receipt();
            break;

        case 2:
            return;

        default:
            cout << "Invalid choice";
        }
    } while (true);
}

void Shop::add() {
    fstream data;
    int token = 0;

    cout << "\n\n\t\t\t Add new product ";
    cout << "\n\n\t\t Product code of the product ";
    cin >> productCode;
    cout << "\n\n\t\t Name of the product ";
    cin >> productName;
    cout << "\n\n\t\t Price of the product ";
    cin >> price;
    cout << "\n\n\t\t Discount of the product";
    cin >> discount;

    data.open("database.txt", ios::app | ios::out);
    data << " " << productCode << " " << productName << " " << price << " " << discount << "\n";
    data.close();

    cout << "\n\n\n\t\t Record inserted !";
}

void Shop::edit() {
    fstream data, data1;
    int productKey, token = 0;

    cout << "\n\n\t\t Update the record";
    cout << "\n\t\t\t Product code : ";
    cin >> productKey;

    data.open("database.txt", ios::in);

    if (!data) {
        cout << "\n\n File does not exist ";
    } else {
        data1.open("database1.txt", ios::app | ios::out);

        data >> productCode >> productName >> price >> discount;

        while (!data.eof()) {
            if (productKey == productCode) {
                cout << "\n\n\t\t Product new code :";
                cin >> productCode;
                cout << "\n\n\t\t Name of the product :";
                cin >> productName;
                cout << "\n\n\t\t Price of the product :";
                cin >> price;
                cout << "\n\n\t\t Discount of the product :";
                cin >> discount;

                data1 << " " << productCode << " " << productName << " " << price << " " << discount << "\n";
                cout << "\n\n\t\t\t Record edited ";
                token++;
            } else {
                data1 << " " << productCode << " " << productName << " " << price << " " << discount << "\n";
            }
            data >> productCode >> productName >> price >> discount;
        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0) {
            cout << "\n\n\n Sorry record not found !";
        }
    }
}

void Shop::removeProduct() {
    fstream data, data1;
    int productKey, token = 0;

    cout << "\n\n\t\t Delete product ";
    cout << "\n\n\t\t Product code ";
    cin >> productKey;

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "File does not exist ";
    } else {
        data1.open("database1.txt", ios::app | ios::out);

        data >> productCode >> productName >> price >> discount;

        while (!data.eof()) {
            if (productCode == productKey) {
                cout << "\n\n\t\t Product successfully deleted ";
                token++;
            } else {
                data1 << " " << productCode << " " << productName << " " << price << " " << discount << "\n";
            }
            data >> productCode >> productName >> price >> discount;
        }
        data.close();
        data1.close();
        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0) {
            cout << "\n\n\n Record not found ";
        }
    }
}

void Shop::list() {
    fstream data;
    data.open("database.txt", ios::in);

    cout << "\n\n\n|************************************************************************************************|\n";
    cout << "SerialNo\t\t\tName\t\t\tPrice \n";
    cout << "\n\n\n|************************************************************************************************|\n";

    data >> productCode >> productName >> price >> discount;
    while (!data.eof()) {
        cout << productCode << "\t\t\t" << productName << "\t\t\t" << price << "\n";
        data >> productCode >> productName >> price >> discount;
    }

    data.close();
}

void Shop::receipt() {
    fstream data;
    int arrc[80];
    int arrq[80];
    char choice;
    int c = 0;
    float amount = 0;
    float dis = 0;
    float total = 0;

    cout << "\n\n\n\t\t\t\t Receipt ";
    data.open("database.txt", ios::in);

    if (!data) {
        cout << "\n\n\n Empty database ";
    } else {
        data.close();

        list();

        cout << "\n|********************************************|\n";
        cout << "\n\n|    please place the order                 |\n";
        cout << "\n|*********************************************|\n";

        do {
            cout << "\n\n\n Enter product code :";
            cin >> arrc[c];
            cout << "\n\n\n Enter the product quantity :";
            cin >> arrq[c];

            for (int i = 0; i < c; i++) {
                if (arrc[c] == arrc[i]) {
                    cout << "\n\n\n Duplicate product code. Please try again";
                }
            }

            c++;
            cout << "\n\n\n Do you want to add another product? If yes, then press 'y' else 'n': ";
            cin >> choice;

        } while (choice == 'y' );

        cout << "\n\n\n\t\t\t*****************Receipt***************\n";
        cout << "\n\n Product No \t\t Product quantity \t\t Price\t\t Amount \t\t Discount amount \n";

        for (int i = 0; i < c; i++) {
            data.open("database.txt", ios::in);
            data >> productCode >> productName >> price >> discount;

            while (!data.eof()) {
                if (productCode == arrc[i]) {
                    amount = price * arrq[i];
                    dis = amount - (amount * discount / 100);
                    total += dis;
                    cout << "\n\n" << productCode << "\t\t" << productName << "\t\t" << arrq[i] << "\t\t" << price << "\t\t" << amount << "\t\t" << dis;
                }

                data >> productCode >> productName >> price >> discount;
            }

            data.close();
        }

        cout << "\n\n__________________________\n";
        cout << "\n\n Total amount : " << total;
    }
}

int main() {
    Shop s;
    s.start();
    return 0;
}
