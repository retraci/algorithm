#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const int N = 15;
const double eps = 1e-8;

int n;
double vv[N][N];
double a[N][N], b[N];

void solve() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            a[i][j] = -2 * (vv[i][j] - vv[i + 1][j]);
            b[i] += vv[i + 1][j] * vv[i + 1][j] - vv[i][j] * vv[i][j];
        }
    }

    for (int j = 1; j <= n; j++) {
        for (int i = j; i <= n; i++) {
            if (fabs(a[i][j]) > eps) {
                for (int k = 1; k <= n; k++) swap(a[j][k], a[i][k]);
                swap(b[j], b[i]);
            }
        }
        for (int i = 1; i <= n; i++) {
            if (i == j) continue;
            double rate = a[i][j] / a[j][j];
            for (int k = 1; k <= n; k++) a[i][k] -= a[j][k] * rate;
            b[i] -= b[j] * rate;
        }
    }
    for (int j = 1; j < n; j++) printf("%.3lf ", b[j] / a[j][j]);
    printf("%.3lf\n", b[n] / a[n][n]);
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> n;
    for (int i = 1; i <= n + 1; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%lf", &vv[i][j]);
        }
    }
    solve();

    return 0;
}