#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int n, m;
double p[30];
double v[5] = {80, 54, 24, 16};

void solve() {
    double ans = p['S' - 'A'] * 10000;
    for (int i = 0; i < 4; i++) {
        ans += p[i] * v[i];
    }
    ans -= 23;

    cout << ans * m << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        char ch;
        double a;
        cin >> ch >> a;
        p[ch - 'A'] += a;
    }
    solve();

    return 0;
}