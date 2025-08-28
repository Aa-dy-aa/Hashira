#include <bits/stdc++.h>
#include "json.hpp" // nlohmann json library
using namespace std;
using json = nlohmann::json;

// Convert string in given base to decimal
long long decode(const string& value, int base) {
    long long result = 0;
    for (char c : value) {
        int digit;
        if (isdigit(c)) digit = c - '0';
        else digit = tolower(c) - 'a' + 10;
        result = result * base + digit;
    }
    return result;
}

// Lagrange interpolation at x=0 to find constant c
long long lagrangeInterpolation(const vector<long long>& X, const vector<long long>& Y, int k) {
    long double c = 0.0;
    for (int i = 0; i < k; i++) {
        long double term = Y[i];
        for (int j = 0; j < k; j++) {
            if (i != j) {
                term *= (0.0 - X[j]) * 1.0 / (X[i] - X[j]);
            }
        }
        c += term;
    }
    return llround(c); // rounded constant term
}

int main() {
    // Load JSON
    ifstream inFile("input.json");
    json j;
    inFile >> j;

    int n = j["keys"]["n"];
    int k = j["keys"]["k"];

    vector<long long> X, Y;

    for (auto& el : j.items()) {
        if (el.key() == "keys") continue;
        int x = stoi(el.key()); 
        int base = stoi(el.value()["base"].get<string>());
        string value = el.value()["value"];
        long long y = decode(value, base);
        X.push_back(x);
        Y.push_back(y);
    }

    long long c = lagrangeInterpolation(X, Y, k);

    cout << "The secret (c) is: " << c << endl;
    return 0;
}
