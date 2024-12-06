#include <iostream>
using namespace std;

int main()
{
    int n;
    float x , y , res;
    cout << "Hello! This is the menu that does as follows :"" \n1)sum of the numbers \n2)Subtraction of numbers\n"
    "3)multiplication of numbers \n4)division of numbers\n5)exit the menu\n"
    "Type the number of your selected mathematics operation : ";
    cin >> n;
    while (! ((n == 1)||(n == 2)||(n == 3)||(n == 4)||(n == 5)))
    {
        cout << "The number you entered is not defined!\nPlease try again: ";
        cin >> n;
    }
    while (n != 5)
        {
        if( n == 1 )
        {
            cout << "please enter two numbers: ";
            cin >> x >> y;
            res = x + y;
            cout << "The result of operation 1 is: " << res;
        }
        if( n == 2 )
        {
            cout << "please enter two number: ";
            cin >> x >> y;
            res = x - y;
            cout << "The result of operation 2 is: " << res;
        }
        if( n == 3 )
        {
            cout << "please enter two numbers: ";
            cin >> x >> y;
            res = (x * y);
            cout << "The result of operation 3 is: " << res;
        }
        if( n == 4 )
        {
            cout << "please enter two numbers: ";
            cin >> x >> y;
            while(y == 0)
            {
            cout <<"You can't use zero for second number.\nplease enter another number to replace: ";
            cin >> y;
            }
            res = (x / y);
            cout << "The result of operation 4 is: " << res;
        }
        cout << "\nIf you want to use another operation choose another number.\nMENU :\n1)sum of numbers \n2)subtraction of numbers\n"
        "3)multiplication of numbers \n4)division of numbers\n5)exit\n"
        "Type the number of your selected mathematics operation : ";
        cin >> n;
        cout << "The menu is closed. ""Thank you for using this program.";

    return 0;
}
}
