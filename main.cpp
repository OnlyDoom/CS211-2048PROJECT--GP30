#include <iostream>
#include <string>
#include "luhn.h"
using namespace std;

int main()
{
    string input;

    cout<<"=== 16-Digit Luhn Checksum Validator ===\n";
    cout<<"Note: A passing checksum verifies format math only, not card authorization.\n";
    cout<<"Enter a 16-Digit number to check, or type 'exit' to quit.\n\n";

    while (true)
    {
        cout<<"Please enter a number or 'exit': ";

        //handle end of input
        if (!getline(cin, input))
        {
            cout<<"\nEnd of input reached. Exiting program.\n";
            break;
        }

        //handle windows style carriage return if piped from a test file
        if (!input.empty() && input.back() == '\r')
        {
            input.pop_back();
        }

        if (input == "exit" || input == "EXIT")
        {
            cout<<"Exiting program.\n";
            break;
        }

        string errormessage;
        if (!isvalid(input, errormessage))
        {
            cout<<"REJECTED - "<<errormessage <<"\n\n";
            continue;
        }

        if (checkluhn(input))
        {
            cout<<"VALID - Correct format; Luhn checksum PASSED.\n\n";
        }
        else
        {
            cout<<"INVALID - Correct format; Luhn checksum FAILED.\n\n";
        }
    }
    return 0;
}