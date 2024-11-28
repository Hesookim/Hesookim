#include <iostream>
using namespace std;

int main() {
    unsigned int age;
    string answer;
      cout << "Enter your age:";
        cin >> age;
    if (age < 12)
    {
       cout << "your ticket price is 10 dollars.";
    }
    else if ((age >= 12) && (age <= 18))
    {
       cout << "Are you a member of the customer club?";
        cin >> answer;
    if (answer == "yes")
     cout << "your ticket price is 12 dollars.";
    else
     cout << "your ticket price is 15 dollars.";
    }
    else if ((age >= 18) && (age <= 60))
    {
     cout << "Are you a member of the customer club?";
        cin >> answer;
    if (answer == "yes")
     cout << "your ticket price is 20 dollars.";
    else
     cout << "your ticket price is 25 dollars.";
    }
    else
     cout << "your ticket price is 10 dollars.";
     return 0;
}
