#include <iostream>
using namespace std;

// returns the summation of all the odd integers in the range [a, b]
int oddSum( int a, int b )
{
	if (a == b) {
		if (a % 2 == 1)
			return a;
		else
			return 0;
	}
	if (a % 2 == 1)
		return oddSum(a + 1, b) + a;
	else 
		return oddSum(a + 1, b);
}

int main()
{
   int a, b;
   int numCases;
   cin >> numCases;
   for (int i = 1; i <= numCases; i++) {
	   cin >> a >> b;
	   int c;
	   if (b < a) {
		   c = a;
		   a = b;
		   b = c;
	   }
	   cout << "Case " << i << ": " << oddSum(a, b)<<endl;
   }
}