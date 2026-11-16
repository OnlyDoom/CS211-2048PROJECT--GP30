#include "luhn.h"
#include <cctype>
using namespace std;

bool isvalid(const string& input, string& errormessage)
{
    //check for internal spaces or any non-digit characters
    for (size_t i = 0; i < input.length(); ++i)
    {
        if (input[i] == ' ')
        {
            errormessage = "Error: spaces not allowed.";
            return false;
        }
        if (!isdigit(static_cast<unsigned char>(input[i])))
        {
            errormessage = "Error: all characters must  be digits 0-9.";
            return false;
        }
    }

    //check exact length
    if (input.length() != 16)
    {
        errormessage = "Invalid length.";
        return false;
    }

    errormessage.clear();
    return true;
}

bool checkluhn(const string& number)
{
    int sum = 0;
    bool shoulddouble = false;

    for (int i = static_cast<int>(number.length()) - 1; i >= 0; --i)
    {
        int digit = number[i] - '0';

        if (shoulddouble)
        {
            digit *= 2;
            if (digit > 9)
            {
                digit -= 9;
            }
        }

        sum += digit;
        shoulddouble = !shoulddouble;
    }

    return (sum % 10 ==0);
}