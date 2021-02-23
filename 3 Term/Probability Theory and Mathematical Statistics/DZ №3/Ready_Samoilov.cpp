#include <iostream>
#include <cmath>

using namespace std;

long double Factorial(int a) {
    long double r = 1.0L;
    for(int i = 2; i <= a; ++i) {
        r *= i;
    }
    return r;
}

long double SumMult(int amount, long double lambda, long double mu, long double nu, int p) {
    long double sum_p = 0.0L;
    long double mult_p = 1.0L;
    for(int i = 1; i <= p; ++i) {
        mult_p *= lambda;
        mult_p /= (amount*mu + i*nu);
        sum_p += mult_p;
    }
    return sum_p;
}

long double SumMultExp(int amount, long double lambda, long double mu, long double nu, int p) {
    long double sum_p = 0.0L;
    long double mult_p = 1.0L;
    for(int i = 1; i <= p; ++i) {
        mult_p *= lambda;
        mult_p /= (amount*mu + i*nu);
        sum_p += i * mult_p;
    }
    return sum_p;
}

long double CalculateDenominator(int amount,long double lambda, long double mu) {
    long double denominator = 0.0L;
    for (int i = 0; i <= amount; ++i) {
        denominator += pow(lambda, i) / (Factorial(i) * pow(mu, i));
    }
    return denominator;
}

long double CalculateDenominatorOchered(int amount, int ochered, long double lambda, long double mu)  
{
    long double denominator = CalculateDenominator(amount, lambda, mu);
    long double amountFactorial = Factorial(amount);
    for (int i = amount + 1; i <= ochered + amount; ++i) {
        denominator += pow(lambda, i) / (amountFactorial * pow(amount, i - amount) * pow(mu, i));
    }
    return denominator;
}

long double CalculateDenominatorInfiniteOchered(int amount, long double lambda, long double mu) {
    long double denominator = CalculateDenominator(amount, lambda, mu);
    long double a = lambda / (amount * mu);
    denominator += (pow(lambda, amount) / (Factorial(amount) * pow(mu, amount))) * (a / (1-a));
    return denominator;
}

long double CalculateDenominatorInfiniteOcheredWithLeaving(int amount, long double lambda, long  
double mu, long double nu, int p) {
    long double denominator = CalculateDenominator(amount, lambda, mu);
    denominator += (pow(lambda, amount) / (Factorial(amount) * pow(mu, amount))) * SumMult(amount,  
lambda, mu, nu, p);
    return denominator;
}

void RejectWithoutWaiting(int amount, long double lambda, long double mu) {
    long double denominator = CalculateDenominator(amount, lambda, mu);
    long double numerator = 1.0L;
    long double ro = lambda / mu;
    long double p = numerator / denominator;
    long double matexpecting = 0.0L;
    cout << "P0 = " << p << endl;
    for (int i = 1; i <= amount; ++i) {
        p *= ro;
        p /= i;
        cout << "P" << i << " = " << p << endl;
        matexpecting += i * p;
    }
    cout << "Math expecting is " << matexpecting << endl;
    
    long double n_occuped = ro * (1-p);
    long double k_occuped = n_occuped / amount;
    cout << "Coefficient occuped is " << k_occuped;
}

void RejectWithWaiting(int amount, int ochered, long double lambda, long double mu) {
    long double denominator = CalculateDenominatorOchered(amount, ochered, lambda, mu);
    long double numerator = 1.0L;
    long double ro = lambda / mu;
    long double p = numerator / denominator;
    long double matexpecting = 0.0L;
    cout << "P0 = " << p << endl;
    for (int i = 1; i <= amount; ++i) {
        p *= ro;
        p /= i;
        cout << "P" << i << " = " << p << endl;
        matexpecting += i * p;
    }
    long double p_och = 0.0L;
    long double matexpectingOchered = 0.0L;
    for (int i = 1; i <= ochered; ++i) {
        p *= ro;
        p /= amount;
        p_och += p; 
        cout << "P" << amount << "+" << i << " = " << p << endl;
        matexpecting += amount * p;
        matexpectingOchered += i * p;
    }
    cout << "Probability for waiting is " << p_och << endl;
    cout << "Math expecting is " << matexpecting << endl;
    cout << "Math expecting for waiting is " << matexpectingOchered << endl;
    
    long double n_occuped = ro * (1-p);
    long double k_occuped = n_occuped / amount;
    cout << "Coefficient occuped is " << k_occuped << endl;
    long double n_occuped_och = ro * (1-p_och);
    long double k_occuped_och = n_occuped_och / (amount + ochered);
    cout << "Coefficient occuped for waiting is " << k_occuped_och<< endl;
}

void RejectWithInfiniteWaiting(int amount, long double lambda, long double mu) {
    long double denominator = CalculateDenominatorInfiniteOchered(amount, lambda, mu);
    long double numerator = 1.0L;
    long double ro = lambda /  mu;
    long double a = lambda / (amount * mu);
    long double p0 = numerator / denominator;
    long double p = p0;
    long double matexpecting = 0.0L;
    cout << "P0 = " << p0 << endl;
    for (int i = 1; i <= amount; ++i) {
        p *= ro;
        p /= i;
        cout << "P" << i << " = " << p << endl;
        matexpecting += i * p;
    }
    matexpecting += amount * p * (a/(1.0L-a));
    long double p_och = p * (a/(1.0L-a));
    long double matexpectingOchered = p * a * (1.0L/pow(1.0L - a, 2));

    cout << "Probability for waiting is " << p_och << endl;
    cout << "Math expecting is " << matexpecting << endl;
    cout << "Math expecting for waiting is " << matexpectingOchered << endl;

    /*long double n_occuped = ro * (1-p);
    long double k_occuped = n_occuped / amount;
    cout << "Coefficient occuped is " << k_occuped << endl;
    long double n_occuped_och = ro * (1-p_och);
    long double k_occuped_och = n_occuped_och / (amount + ochered);
    cout << "Coefficient occuped for waiting is " << k_occuped_och<< endl;*/
}

void RejectWithInfiniteWaitingWithLeaving(int amount, long double lambda, long double mu, long double  
nu) {
    long double denominatorPrev = CalculateDenominatorInfiniteOcheredWithLeaving(amount, lambda, mu,  
nu, 0);
    long double denominator = CalculateDenominatorInfiniteOcheredWithLeaving(amount, lambda, mu, nu,  
1);
   
    long double numerator = 1.0L;
    long double ro = lambda /  mu;
    
    int i = 2;
    long double p0_prev = numerator / denominatorPrev;
    long double p0 = numerator / denominator;
    while (abs(p0_prev - p0) >= 0.0001L) {
        denominator = CalculateDenominatorInfiniteOcheredWithLeaving(amount, lambda, mu, nu, i);
        ++i;
        
        p0_prev = p0;
        p0 = numerator / denominator;
    }
    
    long double p = p0;
    long double matexpecting_const = 0.0L;
    cout << "P0 = " << p0 << endl;
    for (int i = 1; i <= amount; ++i) {
        p *= ro;
        p /= i;
        cout << "P" << i << " = " << p << endl;
        matexpecting_const += i * p;
    }
    
    long double matexpecting_prev = matexpecting_const;
    long double matexpecting = matexpecting_const;
    matexpecting_prev += amount * p * SumMult(amount, lambda, mu, nu, 1);
    matexpecting += amount * p * SumMult(amount, lambda, mu, nu, 2);
    i = 3;
    while (abs(matexpecting - matexpecting_prev) >= 0.0001L) {
        matexpecting_prev = matexpecting;
        matexpecting = matexpecting_const;
        matexpecting += amount * p * SumMult(amount, lambda, mu, nu, i);
        ++i;
    }
    
    i = 3;
    long double p_och_prev = p * SumMult(amount, lambda, mu, nu, 1);
    long double p_och = p * SumMult(amount, lambda, mu, nu, 2);
    while (abs(p_och - p_och_prev) >= 0.0001L) {
        p_och_prev = p_och;
        p_och = p * SumMult(amount, lambda, mu, nu, i);
        ++i;
    }
    
    i = 3;
    long double matexpectingOchered_prev = p * SumMultExp(amount, lambda, mu, nu, 1);
    long double matexpectingOchered = p * SumMultExp(amount, lambda, mu, nu, 2);
    while (abs(matexpectingOchered - matexpectingOchered_prev) >= 0.0001L) {
        matexpectingOchered_prev = matexpectingOchered;
        matexpectingOchered = p * SumMultExp(amount, lambda, mu, nu, i);
        ++i;
    }

    cout << "Probability for waiting is " << p_och << endl;
    cout << "Math expecting is " << matexpecting << endl;
    cout << "Math expecting for waiting is " << matexpectingOchered << endl;

    /*long double n_occuped = ro * (1-p);
    long double k_occuped = n_occuped / amount;
    cout << "Coefficient occuped is " << k_occuped << endl;
    long double n_occuped_och = ro * (1-p_och);
    long double k_occuped_och = n_occuped_och / (amount + ochered);
    cout << "Coefficient occuped for waiting is " << k_occuped_och<< endl;*/
}

int main(int argc, char **argv)
{
    if (argc < 3) { return -1; }
    
    int amount = atoi(argv[1]);
    //int amountOchered = atoi(argv[4]);
    long double lambda = 1.0L / atoi(argv[2]);
    long double mu = 1.0L / atoi(argv[3]);
    long double nu = 1.0L / atoi(argv[4]);
    
    RejectWithInfiniteWaitingWithLeaving(amount, lambda, mu, nu);
    //RejectWithInfiniteWaiting(amount, lambda, mu);
    //RejectWithWaiting(amount, amountOchered, lambda, mu);
    //RejectWithoutWaiting(amount, lambda, mu);
    return 0;
}
