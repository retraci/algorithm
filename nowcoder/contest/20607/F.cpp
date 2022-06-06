#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iomanip>

using namespace std;

#define ll long long

double n, m, p;

double calc(double k) {
    return (n * k + m) / (1 - pow(1 - p, k));
}

void solve() {
    p /= 1e4;

    ll left = 0, right = 1e18;
    while (left + 10 < right) {
        ll mdl = (2 * left + right) / 3;
        ll mdr = (left + 2 * right) / 3;
        double v1 = calc(mdl), v2 = calc(mdr);
        if (v1 > v2) left = mdl;
        else right = mdr;
    }
    double ans = 1e18;
    for (int k = left; k <= right; k++) ans = min(ans, calc(k));

    cout << fixed << setprecision(10);
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m >> p;
        solve();
    }

    return 0;
}