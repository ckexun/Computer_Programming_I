#include <iostream>
using namespace std;
int main()
{
	int t;
	cin >> t;
	for (int i = 1; i <=t; ++i)//t������
	{
		int n;//�����
		int high{ 0 }, low{ 0 };//���G��l��
		int stand, jump;//������P��
		cin >> n;
		cin >> stand;
		while (n > 1)
		{
			cin >> jump;
			if (jump > stand)
			{
				high += 1;
			}
			else if (jump < stand)
			{
				low += 1;
			}
			stand = jump;
			n -= 1;
		}
		cout << "Case " << i<<": "<<high<<" " << low << endl;
	}
}