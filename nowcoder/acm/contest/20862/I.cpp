#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

#define ll long long

ll n, a, b, c, d;

void solve() {
    ll left = 1, right = 1e9 + 10;
    while (left < right) {
        ll mid = left + right + 1 >> 1;
        if (mid * (mid + 1) < n) left = mid;
        else right = mid - 1;
    }

    if (n < (left + 1) * (left + 1)) {
        a = left * (left - 1);
        b = (left + 1) * (left - 1);
        c = left * left;
        d = left * (left + 1);
    } else {
        a = (left - 1) * (left + 1);
        b = (left - 1) * (left + 2);
        c = left * (left + 1);
        d = left * (left + 2);
    }

    cout << a << " " << b << " " << c << " " << d << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        solve();
    }

    return 0;
}