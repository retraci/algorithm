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

    double ans = 1e18;
    ll left = 0, right = 1e18;
    while (left < right) {
        ll mid1 = left + (right - left) / 3, mid2 = right - (right - left) / 3;
        double yl = calc(mid1), yr = calc(mid2);
        ans = min({ans, yl, yr});
        if (yl > yr) left = mid1 + 1;
        else right = mid2 - 1;
    }

//    cout << k << " ";
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