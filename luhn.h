#ifndef LUHN_H
#define LUHN_H
#include <string>
using namespace std;

//check if the input is exactly 16 characters and contains only digits 0-9
//sets error message if invalid
bool isvalid(const string& input, string& errormessage);

//calculates the luhn checksum on a valid string
//returns true if the checksum is divisible by 10
bool checkluhn(const string& number);

#endif //LUHN_H