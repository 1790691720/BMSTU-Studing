#include <iostream>
#include <cmath>

using namespace std;

long double Sochetaniye(int n, int k) {
    if (k == 0 || k == n) { return 1.0L; }
    if (k == 1 || k == n - 1) { return n; }

    int numeratorStart = k > n / 2 ? k + 1 : (n - k) + 1;
    int denomAmount = k > n / 2 ? n - k : k;

    int amount = denomAmount > (n - numeratorStart) ? n - numeratorStart + 1 : denomAmount;
    long double res = 1.0L;
    int a = 1, b = numeratorStart;
    for (int i = 1; i <= amount; ++i) 
    {
        res *= b++;
        res /= a++;
    }

    return res;
}

#pragma region Probabilities
long double ProbabilityBernulli(long double p, int n, int k) {
    long double s = Sochetaniye(n, k);
    long double q = 1.0L - p;
    return s * pow(p, k) * pow(q, n - k);
}

long double ProbabilityWithotReturn(int want, int all, int i, int n) {
    return Sochetaniye(want, i) * Sochetaniye(all - want, (n - i)) / Sochetaniye(all, n);
}


long double ProbabilityWithotReturnToR(int want, int all, int i) {
    long double result = 1.0L;
    result *= ProbabilityWithotReturn(want, all, want, want);
    result *= Sochetaniye(i - 1, i - want);
    return result;
}
#pragma endregion

#pragma region MathExpectings
long double MathExpecting(long double p, int n) {
    long double result = 0.0L;

    for (int i = 1; i <= n; i++) {
        result += ProbabilityBernulli(p, n, i) * i;
    }

    return result;
}

long double MathExpectingSqr(long double p, int n) {
    long double result = 0.0L;

    for (int i = 1; i <= n; i++) {
        result += ProbabilityBernulli(p, n, i) * i * i;
    }

    return result;
}

long double MathExpectingOtnosit(long double p, int n) {
    long double result = 0.0L;

    for (int i = 1; i <= n; i++) {
        result += ProbabilityBernulli(p, n, i) * i / n;
    }

    return result;
}

long double MathExpectingOtnositSqr(long double p, int n) {
    long double result = 0.0L;

    for (int i = 1; i <= n; i++) {
        result += ProbabilityBernulli(p, n, i) * pow((long double)i / n, 2);
    }

    return result;
}

long double MathExpectingWithoutReturn(int want, int all, int n) {
    long double result = 0.0L;

    for (int i = 1; i <= n; i++) {
        result += ProbabilityWithotReturn(want, all, i, n) * i;
    }

    return result;
}

long double MathExpectingWithoutReturnSqr(int want, int all, int n) {
    long double result = 0.0L;

    for (int i = 1; i <= n; i++) {
        result += ProbabilityWithotReturn(want, all, i, n) * i * i;
    }

    return result;
}

long double MathExpectingToR(int s, int all) {
    long double result = 0.0L;

    for (int i = s; i <= all; ++i) {
        result += ProbabilityWithotReturnToR(s, all, i) * i;
    }

    return result;
}

long double MathExpectingToRSqr(int s, int all) {
    long double result = 0.0L;

    for (int i = s; i <= all; ++i) {
        result += ProbabilityWithotReturnToR(s, all, i) * i * i;
    }

    return result;
}
#pragma endregion

#pragma region Dispersions
long double Dispersion(long double p, int n) {
    return MathExpectingSqr(p, n) - pow(MathExpecting(p, n), 2);
}

long double DispersionOtnosit(long double p, int n) {
    return MathExpectingOtnositSqr(p, n) - pow(MathExpectingOtnosit(p, n), 2);
}

long double DispersionWithoutReturn(int want, int all, int n) {
    return MathExpectingWithoutReturnSqr(want, all, n) - pow(MathExpectingWithoutReturn(want, all, n), 2);
}

long double DispersionToR(int want, int all) {
    return MathExpectingToRSqr(want, all) - pow(MathExpectingToR(want, all), 2);
}
#pragma endregion

#pragma region Deviation
long double StandardOtklon(long double p, int n) {
    return sqrt(Dispersion(p, n));
}

long double StandardOtklonOtnosit(long double p, int n) {
    return sqrt(DispersionOtnosit(p, n));
}
#pragma endregion

#pragma region Punkt1
void Number1Point4(int r, int g, int b, int n) {
    long double p = (long double)r / (r + g + b);
    cout << "M(x) = " << MathExpecting(p, n)
        << "\nM(x^2) = " << MathExpectingSqr(p, n)
        << "\nM^2(x) = " << pow(MathExpecting(p, n), 2)
        << "\nD = " << Dispersion(p, n)
        << "\nsigma = " << StandardOtklon(p, n) << endl;
}

void Number1Point5(int r, int g, int b, int n) {
    long double p = (long double)r / (r + g + b);
    cout << "M(x) = " << MathExpectingOtnosit(p, n)
        << "\nM(x^2) = " << MathExpectingOtnositSqr(p, n)
        << "\nM^2(x) = " << pow(MathExpectingOtnosit(p, n), 2)
        << "\nD = " << DispersionOtnosit(p, n)
        << "\nsigma = " << StandardOtklonOtnosit(p, n) << endl;
}

void Number1Point7(int r, int g, int b, int n) {
    long double p = (long double)r / (r + g + b);
    long double N1 = r + g + b;
    for (int i = 1; i <= n; ++i) {
        cout << "n = " << i
            << "\nphi2 = " << ((long double)i * sqrt(13.0L / 19.0L)) / (sqrt((long double)i * 6.0L / 19.0L))
            << "\nphi1 = " << (N1 - (long double)i * 6.0L / 19.0L) / (sqrt((long double)i * 6.0L / 19.0L * 13.0L / 19.0L)) << endl;
    }
}
#pragma endregion

#pragma region Punkt2
void Number2Point1(int r, int g, int b, int n) {
    for (int i = 0; i <= r; ++i) {
        cout << ProbabilityWithotReturn(r, r + g + b, i, n) << endl;
    }
}

void Number2Point3(int r, int g, int b, int n) {
    cout << MathExpectingWithoutReturn(r, r + g + b, n) << endl;
}

void Number2Point5(int r, int g, int b, int n) {
    cout << "M = " << MathExpectingWithoutReturn(r, r + g + b, n)
        << "\nM(x^2) = " << MathExpectingWithoutReturnSqr(r, r + g + b, n)
        << "\nM^2 = " << pow(MathExpectingWithoutReturn(r, r + g + b, n), 2)
        << "\nD = " << DispersionWithoutReturn(r, r + g + b, n) << endl;
}
#pragma endregion

#pragma region Punkt3
void Number3Point1(int r, int g, int b, int n) {
    for (int i = r; i <= n; ++i) {
        cout << i << "  " << ProbabilityWithotReturnToR(r, r + g + b, i) << endl;
    }
}

void Number3Point2(int r, int g, int b, int n) {
    cout << MathExpectingToR(r, r + g + b) << endl;
}

void Number3Point3(int r, int g, int b, int n) {
    cout << "M = " << MathExpectingToR(r, r + g + b)
        << "\nM(x^2) = " << MathExpectingToRSqr(r, r + g + b)
        << "\nM^2 = " << pow(MathExpectingToR(r, r + g + b), 2)
        << "\nD = " << DispersionToR(r, r + g + b) << endl;
}
#pragma endregion
int main(int argc, char** argv)
{
    //if (argc < 5) { cout << "Nothing inptted!\n"; return -1; }

    int r = atoi(argv[1]);
    int g = atoi(argv[2]);
    int b = atoi(argv[3]);
    int n = atoi(argv[4]);

    Number3Point3(r, g, b, n);
    return 0;
}
