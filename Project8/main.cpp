#include "inf_int.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

int main()
{
	
	inf_int a, c, d, e;
	inf_int b(100);
	inf_int inf_num1("1111111111122222222222233333333333444444444445555555555");
	inf_int inf_num2("1111111111122222222222233333333333444444444440000000000");
	inf_int f = inf_num2;
	inf_int g(f);
	inf_int k("-11111111111111111111111111111111111111111111111111");
	// cin >> g ;   // not required
	a = b * inf_num1;
	// e=g/f;       // not required
	c = inf_num1 - inf_num2;
	d = inf_num1 + inf_num2;

	if (f == inf_num2) {
		cout << "inf_num1 : " << inf_num1 << endl;
		cout << "" << endl;
		cout << "inf_num2 : " << inf_num2 << endl;
		cout << "" << endl;
		cout << "inf_num1 * 100 = " << a << endl;
		cout << "" << endl;
		cout << "inf_num1 + inf_num2 = " << d << endl;
		cout << "" << endl;
		cout << "inf_num1 - inf_num2 = " << c << endl;
		cout << "" << endl;


		// cout << "e : " << e << endl;
		// cout << "f : " << f << endl;
		// cout << "g : " << g << endl;
	}
	
	
	return 0;
}