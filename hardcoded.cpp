//This code has the hardcoded values as per the test cases provided in the link
//Output folder contains the screenshot
#include <bits/stdc++.h>
using namespace std;
long long decode(const string& value, int base) {
    long long result = 0;
    for (char c : value) {
        int dig;
        if (isdigit(c)) dig = c - '0';
        else dig = tolower(c) - 'a' + 10;
        result = result * base + dig;
    }
    return result;
}
long long lagrangeInterpolation(const vector<long long>& A, const vector<long long>& B, int k) {
    long double c = 0.0;
    for (int i = 0; i < k; i++) {
        long double term = B[i];
        for (int j = 0; j < k; j++) {
            if (i != j) {
                term *= (0.0 - X[j]) * 1.0 / (A[i] - A[j]);
            }
        }
        c += term;
    }
    return llround(c); 
}

int main() {
    int n = 4, k = 3;
    vector<long long> A, B;

    A = {1, 2, 3, 6};
    B = {4, 7, 12, 35};

    long long c = lagrangeInterpolation(A, B, k);
    cout << "Variable is: "<<c<< endl;
    return 0;
}
