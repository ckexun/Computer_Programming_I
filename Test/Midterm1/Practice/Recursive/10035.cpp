// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=976
// 10035 - Primary Arithmetic
#include <iostream>
using namespace std;

int recCountCarry( long long integer1, long long integer2, bool isCarry);

int main()
{
    int integer1;
    int integer2;
    cin >> integer1 >> integer2;
    while ( integer1 != 0 || integer2 != 0 ) 
    {
        int numCarry = recCountCarry(integer1, integer2, false);

        if (numCarry == 0)
            cout << "No carry operation.\n";
        else if (numCarry == 1)
            cout << "1 carry operation.\n";
        else
            cout << numCarry << " carry operations.\n";
        
        cin >> integer1 >> integer2;
    }

   system( "pause" );
}

int recCountCarry( long long integer1, long long integer2, bool isCarry)
{
    if (integer1 + integer2 + isCarry < 10)
        return isCarry;
    if ((integer1 % 10 + integer2 % 10) + isCarry >= 10)
        return recCountCarry(integer1 / 10, integer2 / 10, true) + isCarry;
    else
        return recCountCarry(integer1 / 10, integer2 / 10, false) + isCarry;
}