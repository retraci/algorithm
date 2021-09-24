#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iomanip>

using namespace std;

const double PI = acos(-1);

const int N = 510;

int n, m;
double f[N];

double calc(double r) {
    double hu = 2.0 * PI * r / (2.0 * m);
    double a = 2.0 * PI / (2.0 * m);

    double res1 = 0, res2 = 0;
    double alp = 0;
    for (int i = 0; i < m - 1; i++) {
        alp += a;
        if (alp >= 2) {
            res1 += 2.0 * r;
        } else {
            res2 += hu * (i + 1);
        }
    }

    return 2.0 * (res1 + res2) + 2.0 * r;
}

void solve() {
    f[0] = 0;
    double ans = 0;
    for (int i = 1; i <= n; i++) {
        double s = (i - 1) * (2.0 * m);
        double cur = calc(i);

        ans += (f[i - 1] + s) * (2 * m) + (cur * 2.0 * m / 2);
        f[i] = f[i - 1] + s + cur;
    }
    ans += m > 1 ? n * (n + 1) / 2.0 * (2.0 * m) : 0;

    cout << fixed << setprecision(9);
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    solve();

    return 0;
}