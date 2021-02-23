#include <iostream>
#include <iomanip> 
using namespace std;
#pragma region Utility
long double fact(int N)
{
	long double result = 1;
	for (int i = 1; i <= N; i++) {
		result = result * i;
	}
	return result;
}
long double Combinations(int n, int k)
{

	if (k == 0 || k == n) { return 1; }
	if (k == 1 || k == n - 1) { return n; }

	int numeratorStart = k > n / 2 ? k + 1 : (n - k) + 1;
	int denomAmount = k > n / 2 ? n - k : k;

	int amount = denomAmount > (n - numeratorStart) ? n - numeratorStart + 1 : denomAmount;
	long double result = 1;
	int a = 1, b = numeratorStart;
	for (int i = 1; i <= amount; ++i)
	{
		result *= b++;
		result /= a++;
	}

	return result;
}

#pragma endregion

#pragma region Probabilities
long double Bernulli(long double p, int n, int k)
{
	return Combinations(n, k) * pow(p, k) * pow(1 - p, n - k);
}
long double ProbabilityWithoutReturn(int n,int k,int N,int r)
{
	return Combinations(r,k)* Combinations(N-r, n-k)/ Combinations(N,n);
}

long double ProbabilityWithoutReturnToR(int r, int N, int k)
{
	return Combinations(k-1, k-r) / Combinations(N, r);
}



#pragma endregion

#pragma region MathExpectings
long double MathExpecting(long double p, int n)
{
	long double result = 0;
	for (int i = 0; i <= n; i++)
	{
		result = result+ Bernulli(p, n, i) * i;
	}
	return result;
}
long double MathExpectingSqr(long double p, int n)
{
	long double result = 0;
	for (int i = 0; i <= n; i++)
	{
		result = result + Bernulli(p, n, i) * i * i;
	}
	return result;
}
long double MathExpectingRelative(long double p, int n)
{
	long double result = 0;
	for (int i = 0; i <= n; i++)
	{
		result = result + Bernulli(p, n, i) * i/n;
	}
	return result;
}
long double MathExpectingRelativeSqr(long double p, int n)
{
	long double result = 0;
	for (int i = 0; i <= n; i++)
	{
		result = result + Bernulli(p, n, i) * i*i/((long double)n* (long double)n);
	}
	return result;
}

long double MathExpectingWithoutReturn(int r, int N, int n)
{
	long double result = 0.0;

	for (int i = 0; i < r; i++)
	{
		result += ProbabilityWithoutReturn(n,i,N,r)*(long double)i;
	}

	return result;

}
long double MathExpectingWithoutReturnSqr(int r, int N, int n)
{
	long double result = 0.0;

	for (int i = 0; i < r; i++)
	{
		result += ProbabilityWithoutReturn(n, i, N, r) * (long double)i* (long double)i;
	}

	return result;

}

long double MathExpectingWithoutReturnToR(int r, int N)
{
	long double result = 0;
	for (int i = r; i <= N; i++)
	{
		result += ProbabilityWithoutReturnToR(r, N, i) * (long double)i;
	}
	return result;
}
long double MathExpectingWithoutReturnToRSqr(int r, int N)
{
	long double result = 0;
	for (int i = r; i <= N; i++)
	{
		result += ProbabilityWithoutReturnToR(r, N, i) * (long double)i* (long double)i;
	}
	return result;
}
#pragma endregion

#pragma region Dispersions
long double Dispersion(long double p, int n) {
	return MathExpectingSqr(p, n) - pow(MathExpecting(p, n), 2);
}

long double DispersionRelative(long double p, int n) {
	return MathExpectingRelativeSqr(p, n) - pow(MathExpectingRelative(p, n), 2);
}

long double DispersionWithoutReturn(int r, int N, int n) {
	return MathExpectingWithoutReturnSqr(r, N,n) - pow(MathExpectingWithoutReturn(r, N, n), 2);
}
long double DispersionWithoutReturntoR(int r, int N) {
	return MathExpectingWithoutReturnToRSqr(r, N) - pow(MathExpectingWithoutReturnToR(r, N), 2);
}
#pragma endregion

#pragma region Deviation
long double StdDeviation(long double p, int n)
{
	return sqrtl(Dispersion(p, n));
}long double StdDeviationRelative(long double p, int n)
{
	return sqrtl(DispersionRelative(p, n));
}
#pragma endregion

#pragma region Punkt1
void Number1Point1(int r, int g, int b, int n)
{
	long double p = (long double)r / ((long double)r + (long double)g + (long double)b);
	for (int i = 0; i <= n; i++)
	{
		cout << "P(" << i << ") = " << setprecision(10)<< Bernulli(p, n, i)<<endl;
	}
}
void Number1Point3(int r, int g, int b, int n)
{
	int k;
	long double p = (long double)r / ((long double)r + (long double)g + (long double)b);
	long double q = 1 - p;
	long double fi;
	while (1)
	{
		cout << "Enter k = ";
		cin >> k;
		long double forFi = (k - n * p) / sqrtl(n * q * p);
		cout << "ForFi = " << forFi << endl;
		cout << "Enter fi = ";
		cin >> fi;
		cout << "P(" << k << ") = " << fi / sqrtl(n * q * p)<<endl<<endl;
	}
}
void Number1Point4(int r, int g, int b, int n)
{
	long double p = (long double)r / ((long double)r + (long double)g + (long double)b);
	long double q = 1 - p;
	long double F;
	long double forF;
	//long double forF = MathExpecting(p,n)/StdDeviation(p,n)æ
		forF =r / StdDeviation(p, 25);
	cout << "ForF = " << forF << endl;
	cout << "Enter F = ";
	cin >> F;
	cout << "for n = 25"  << ": " << 2*F << endl << endl;

 forF = r / StdDeviation(p, 50);
	cout << "ForF = " << forF << endl;
	cout << "Enter F = ";
	cin >> F;
	cout << "for n = 50"  << ": " << 2 * F << endl << endl;

 forF = r / StdDeviation(p, 100);
	cout << "ForF = " << forF << endl;
	cout << "Enter F = ";
	cin >> F;
	cout << "for n = 100"  << ": " << 2 * F << endl << endl;
}
void Number1Point5(int r, int g, int b, int n)
{
	long double p = (long double)r / ((long double)r + (long double)g + (long double)b);
	long double q = 1 - p;
	long double F;
	long double forF;

	forF = p / StdDeviationRelative(p, 100);
	cout << "ForF = " << forF << endl;
	cout << "Enter F = ";
	cin >> F;
	cout << "for n = 100" << ": " << 2 * F << endl << endl;

	forF = p / StdDeviationRelative(p, 200);
	cout << "ForF = " << forF << endl;
	cout << "Enter F = ";
	cin >> F;
	cout << "for n = 200" << ": " << 2 * F << endl << endl;

	forF = p / StdDeviationRelative(p, 400);
	cout << "ForF = " << forF << endl;
	cout << "Enter F = ";
	cin >> F;
	cout << "for n = 400" << ": " << 2 * F << endl << endl;
}
void Number1Point6(int r, int g, int b, int n)
{
	long double p = (long double)r / ((long double)r + (long double)g + (long double)b);
	cout <<"Deviation: " <<StdDeviation(p, n)<<endl;
	cout << "MathExpecting: " << MathExpecting(p, n) << endl;
}
void Number1Point7(int r, int g, int b, int n)
{
	long double N1 = (long double)r + (long double)g + (long double)b;
	long double phi;
	long double i=19;
	for(int i=19;i<=n;i++)
	{
		phi = (1024-11* (long double)i)/sqrtl(231* (long double)i);
		cout << i << ": " << phi << endl;
	}
}
#pragma endregion

#pragma region Punkt2
void Number2Point1(int r, int g, int b, int n)
{
	std::cout << "P(k)=...\n";
	for (int i = 0; i <= r; i++)
	{
		std::cout << i << "\t" <<setprecision(10)<< ProbabilityWithoutReturn(n,i,r+g+b,r)<<endl;
	}
}
void Number2Point3(int r, int g, int b, int n) 
{
	cout << MathExpectingWithoutReturn(r, r + g + b, n) << endl;
}
void Number2Point4(int r, int g, int b, int n)
{
	cout << DispersionWithoutReturn(r, r + g + b, n) << endl;
}
#pragma endregion

#pragma region Punkt3
void Number3Point1(int r, int g, int b, int n)
{
	std::cout << "P(k)=...\n";
	for (int i = r; i <= (r+g+b); i++)
	{
		std::cout << i << "\t" << setprecision(10) << ProbabilityWithoutReturnToR(r, r + g + b, i) << endl;
	}
}
void Number3Point2(int r, int g, int b, int n)
{
	std::cout << "M(k) = " << setprecision(10) << MathExpectingWithoutReturnToR(r, r + g + b) << endl;;
}
void Number3Point3(int r, int g, int b, int n)
{
	cout << DispersionWithoutReturntoR(r, r + g + b) << endl;
}
#pragma endregion

int main()
{
#pragma region input
	cout.setf(ios::fixed);
	cout << "Enter R,G,B,n:"<<endl;

	int R=0, G=0, B=0, n=1000;
	cout << "R= ";
	cin >> R;
	cout << "G= ";
	cin >> G;
	cout << "B= ";
	cin >> B;
	cout << "n= ";
	//cin >> n; //For punkt1
	//n = G + B;//FOr punkt2
	//Nothing for punkt3
	cout << n << endl;
	cout << "End of enter" << endl << endl;

#pragma endregion

	Number1Point6(R, G, B, n);
	return 0;
}