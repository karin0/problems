#include <bits/stdc++.h>
using namespace std;

int n;
unsigned long long a, b;
double cbr, rnd;
int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    while (n--) {
        cin >> a >> b;
        if (a > b)
            swap(a, b); // Ensure a <= b
        a = a * a;
        if (a < b || (a % b)) {
            cout << "No" << endl;
            continue;
        }
        a = a / b;
        cbr = pow(a, 1.0 / 3);
        rnd = round(cbr);
        if (fabs(cbr - rnd) < 1e-5)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    
    }
    return 0;
}
