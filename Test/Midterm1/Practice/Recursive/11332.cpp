// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2307
// 11332 - Summing Digits
#include <iostream>
using namespace std;

int recFunction( int num );
int recSumDigits( int num );

int main()
{
    int num;
    while ( cin >> num && num ) 
    {
        cout << recFunction(num) << endl;
    }

   system( "pause" );
}

int recFunction( int num ) 
{
    if (num < 10)
        return num;
    return recFunction(recSumDigits(num));
}

int recSumDigits( int num )
{
    if (num == 0)
        return num;
    return recSumDigits(num / 10) + num % 10;
}
