// Purchase Requisition to Purchase Order

#include <iostream>
#include <conio.h>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <ctime>
#include <stdio.h>
#include <windows.h>

using namespace std;

// function for setting cursor position in the console window
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// price list of items
float price_list[20] = {865, 2.25, 44, 10, 20, 7710, 33.33, 48.97, 0.5, 0.01, 88, 999, 25000, 87, 4, 22, 200, 20, 150, 120};

// forward declaration of po class for friend function
class po;

class requisition
{
    // Defining data members for storing requisition details
    static int req_no;
    int item_code;
    int qty;
    string delivery_date;

public:
    // Class function declaration
    void getdata();
    void display();
    friend void generate(requisition, po); // friend function declaration
};

void requisition::getdata()
{
    system("cls");

    cout << "Item Code      Price\n";
    for (int i = 0; i < 20; i++)
    {
        cout << "  " << i + 1 << "\t\t" << price_list[i] << "\n";
    }

    req_no++;
    cout << "Product Item Code: ";
    cin >> item_code;
    cout << "Quantity: ";
    cin >> qty;
    cout << "Delivery Date: ";
    cin.clear();
    cin.ignore(1000, '\n');
    getline(cin, delivery_date);
}

// defining static data member
int requisition::req_no;

// function for displaying requisition details
void requisition::display()
{
    system("cls");

    cout << "Requisition Number: " << req_no;
    cout << "\nProduct Item Code: " << item_code;
    cout << "\nQuantity: " << qty;
    cout << "\nDelivery Date: " << delivery_date;
    cout << "\n\t\tPress any key to continue...";
    _getch();
}

class po
{
    static int po_no;

public:
    // constructor is used for incrementing the static variable po_no

    po()
    {
        po_no++;
    }

    friend void generate(requisition, po); // friend function declaration
};

// defining static data member
int po::po_no;

// defining friend function
void generate(requisition r, po p)
{
    ofstream fout;

    // retreiving system date and time
    time_t current = time(0);
    char *dt = ctime(&current);

    // opening the Current_PO.txt file in which PO details are stored
    fout.open("Current_PO.txt");

    // Generating the PO and storing it in the Current_PO.txt file in a formatted manner
    fout << "\t\t\t Purchase Order#: " << p.po_no << "\n";
    fout << "\t\t\t___________________\n\n";
    fout << "Requisition#: " << r.req_no << "\t\t\t\t Issue Date: " << dt << "\n\n";

    if (r.item_code >= 1 && r.item_code <= 10)
        fout << "Supplier: "
             << "SKS Inc\n\n";

    else if (r.item_code >= 11 && r.item_code <= 20)
        fout << "Supplier: "
             << "KC Spare Parts Ltd.\n\n";

    else
        fout << "Supplier: "
             << "Other\n\n";

    fout << "Delivery Date: " << r.delivery_date << "\n\n";
    fout << "-------------------------------------------------------------------------\n";
    fout << "    \t\t\t\t*Line Items*\n";

    fout << "-------------------------------------------------------------------------\n";
    fout << "Item Code\t\tQuantity\t\tPrice\t\tTotal\n";
    fout << "_________\t\t________\t\t_____\t\t_____\n\n";
    fout << "    " << r.item_code << "\t\t      " << r.qty << " ";

    if (r.item_code >= 1 && r.item_code <= 20)
    {
        fout << "\t\t\t " << price_list[r.item_code - 1] << "\t\t " << price_list[r.item_code - 1] * r.qty << "\n\n\n\n";
    }
    else
    {
        fout << "_\t\t\t___\n\n\n\n";
    }

    fout.close();
}

int main()
{
    requisition r;
    char flag = 'f';
    char ch;

    // Displaying menu to accept user commands
    while (true)
    {

        system("cls");
        gotoxy(40, 8);

        cout << "PR_2_PO";
        gotoxy(30, 9);
        cout << "__________________________";
        gotoxy(30, 12);
        cout << "1->Create New Requisition";
        gotoxy(30, 13);
        cout << "2->Display Requisition";
        gotoxy(30, 14);
        cout << "3->Generate PO";
        gotoxy(30, 15);
        cout << "4->Exit";
        gotoxy(38, 17);
        cout << "Select an option by typing the numeric code: ";

        ch = _getch();
        switch (ch)
        {
        case '1':
        {
            r.getdata();
            flag = 't';
            break;
        }

        case '2':
        {
            if (flag == 'f')
            {
                gotoxy(38, 17);
                cout << "Requisition Details not Entered! Press any key to continue...";
                _getch();
            }

            else
            {
                r.display();
            }
            break;
        }

        case '3':
        {
            po p;
            generate(r, p);
            gotoxy(38, 17);
            cout << "PR has been converted into a PO. You can view the Current_PO.txt file to view the generated PO and take its printout. Press any key to continue...";
            _getch();
            break;
        }

        case '4':
        {
            exit(1);
            break;
        }

        default:
        {
            gotoxy(38, 17);
            cout << "Invalid Choice! Press any key to continue...";
            _getch();
        }
        }
    }
    return 0;
}