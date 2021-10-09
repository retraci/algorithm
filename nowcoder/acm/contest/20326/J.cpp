#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

ll n, p2, p3;

void solve() {
    ll c2 = (n + 1) / 2, c3 = (n + 2) / 3;
    ll a = c2 * p2, b = c3 * p3;
    ll c = 1e18, d = 1e18;
    if (n % 2 != 0) {
        if (c2 >= 2) c = a - 2LL * p2 + p3;
    }
    if (n % 3 != 0) {
        int rem = n % 3;
        if (rem == 1) {
            if (c3 >= 2) d = b - 2LL * p3 + 2LL * p2;
        } else {
            if (c3 >= 1) d = b - 1LL * p3 + p2;
        }
    }

    cout << min({a, b, c, d}) << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n >> p2 >> p3;
    solve();

    return 0;
}