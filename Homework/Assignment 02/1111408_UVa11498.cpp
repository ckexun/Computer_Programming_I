#include <iostream>
using namespace std;
int main()
{
	int k;
	while(cin >> k)
	{
		int n, m;
		cin >> n >> m;
		for (int i = 0; i < k; ++i)
		{
			int x, y;
			cin >> x >> y;
			if (x == n || y == m)
			{
				cout << "divisa" << endl;//xy�b
			}
			else if (x > n)
			{
				if (y > m)
				{
					cout << "NE" << endl;//�F�_
				}
				else
				{
					cout << "SE" << endl;//�F�n
				}
			}
			else if (x < n)
			{
				if (y > m)
				{
					cout << "NO" << endl;//��_
				}
				else
				{
					cout << "SO" << endl;//��n
				}
			}
		}
	}
	return 0;
}