#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <iomanip>

using namespace std;

double n, K, d, s;

void solve() {
    double ans = (n * d - K * s) / (n - K);
    if (ans >= 0 && ans <= 100) cout << fixed << setprecision(6) << ans << endl;
    else cout << "impossible" << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> K >> d >> s;
    solve();

    return 0;
}