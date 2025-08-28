//This code below takes the value from the json file and finds the roots using the Lagrange Interpolation equation
//This code reads `n` data points from a JSON file. Each point has an `x` key and a `y` value stored in some base. It first decodes each `y` into decimal using the `decode` function. Then, it uses the first `k` points to perform **Lagrange interpolation** at `x = 0` to find the constant term `c` of the hidden polynomial. Essentially, it converts all numbers into decimal, builds the interpolation polynomial from the given `(x, y)` pairs, and outputs the secret constant `c`.
#include <bits/stdc++.h>
#include "json.hpp" 
using namespace std;
using json = nlohmann::json;

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
    return llround(c);
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
