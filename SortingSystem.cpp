#include "SortingSystem.h"

#include <iostream>
using namespace std;

int main()
{
    while (true)
    {
        int n;
        cout << "Please, enter the number of items which you want to sort: \n";
        cin >> n;
        cin.ignore();
        cout << "Select a data type:\n";
        cout << "1.  Integer\n";
        cout << "2.  Double\n";
        cout << "3.  String\n";
        cout << "4.  Char\n";
        cout << "0.  Exit\n";
        cout << "Enter your choice (0-4): ";

        int user_choice;
        cin >> user_choice;

        if (user_choice == 0)
        {
            cout << "\nThank you for using the sorting system! Goodbye!\n";
            return 0;
        }

        switch (user_choice)
        {
        case 1:
        {
            SortingSystem<int> s(n);
            s.showMenu();
            break;
        }
        case 2:
        {
            SortingSystem<double> s(n);
            s.showMenu();
            break;
        }
        case 3:
        {
            SortingSystem<string> s(n);
            s.showMenu();
            break;
        }
        case 4:
        {
            SortingSystem<char> s(n);
            s.showMenu();
            break;
        }
        default:
            cout << "Invalid choice! Please enter a valid number (0-4)\n";
            continue;
        }
        cout << "\nDo you want to sort another dataset? (y/n):\n";
        char choice;
        cin >> choice;
        if (tolower(choice) == 'y')
        {
            continue;
        }
        else if (tolower(choice) == 'n')
        {
            cout << "\nThank you for using the sorting system! Goodbye!\n";
            return 0;
        }
    }

    return 0;
}
