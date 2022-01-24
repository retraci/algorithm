#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1010;

int n, m;
int x, y;
double f[N][N];
double a[N][N];

void print() {
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m + 1; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void gauss() {
    for (int i = 1; i <= m - 1; i++) {
        double k = a[i + 1][i] / a[i][i];
        int tmp[] = {i + 1, m + 1};
        for (int j = 0; j < 2; j++) {
            a[i + 1][tmp[j]] -= k * a[i][tmp[j]];
        }
        a[i + 1][i] = 0;
    }
    for (int i = m; i >= 2; i--) {
        double k = a[i - 1][i] / a[i][i];
        a[i - 1][m + 1] -= k * a[i][m + 1];
        a[i - 1][i] = 0;
    }
}

void solve() {
    if (m == 1) {
        printf("%.4lf\n", 2.0 * (n - x));
        return;
    }

    for (int i = n - 1; i >= x; i--) {
        a[1][1] = 2.0 / 3, a[1][2] = -1.0 / 3, a[1][m + 1] = f[i + 1][1] / 3 + 1;
        a[m][m] = 2.0 / 3, a[m][m - 1] = -1.0 / 3, a[m][m + 1] = f[i + 1][m] / 3 + 1;
        for (int j = 2; j <= m - 1; j++) {
            a[j][j - 1] = -1.0 / 4, a[j][j] = 3.0 / 4, a[j][j + 1] = -1.0 / 4;
            a[j][m + 1] = f[i + 1][j] / 4 + 1;
        }

        gauss();
        for (int j = 1; j <= m; j++) {
            f[i][j] = a[j][m + 1] / a[j][j];
        }
    }

    printf("%.4lf\n", f[x][y]);
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n >> m >> x >> y;
    solve();

    return 0;
}