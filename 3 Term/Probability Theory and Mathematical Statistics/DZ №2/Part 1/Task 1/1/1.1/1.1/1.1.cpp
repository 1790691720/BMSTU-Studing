#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;
long double fact(int N)
{
	long double res = 1;
	for (int i = 1; i <= N; i++) {
		res = res * i;
	}
	return res;
}


int main()
{
	cout.setf(ios::fixed);

	long double R, G, B,p,q,Pk;
	R = 11;
	G = 10;
	B = 11;
	p = R / (R + G + B);
	q = 1 - p;
	long double n;
	cin >> n;
	cout << "P(k); n=" << n<<endl<<endl;
	for (int k = 0; k <= n; k++)
	{
		Pk = pow(p, k) * pow(q, n - k) * fact(n) / (fact(k) * fact(n - k));
		cout << k << "\t" << setprecision(10) << Pk<<endl;
	}

	return 0;
}
