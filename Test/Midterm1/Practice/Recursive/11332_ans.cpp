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
    int sumDigit = recSumDigits(num);
    if (sumDigit < 10)
        return sumDigit;
    else
        return recFunction(sumDigit);
}

int recSumDigits( int num )
{
    if (num == 0)
        return 0;
    else
        return recSumDigits(num / 10) + num % 10;
}
