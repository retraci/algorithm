#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 210, M = 22, L = 810, BASE = 400;

int n, m, T;
int vp[N], vd[N];
int f[N][M][L];
int ans[M], tt;

void solve() {
    memset(f, -0x3f, sizeof f);
    f[0][0][BASE] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m && j <= i; j++) {
            for (int k = 0; k < L; k++) {
                f[i][j][k] = f[i - 1][j][k];
                int c = k - vp[i] + vd[i];
                if (j < 1 || c < 0 || c > L) continue;
                f[i][j][k] = max(f[i][j][k], f[i - 1][j - 1][k - vp[i] + vd[i]] + vp[i] + vd[i]);
            }
        }
    }

    int del = 0, last;
    while (f[n][m][BASE + del] < 0 && f[n][m][BASE - del] < 0) del++;
    if (f[n][m][BASE + del] > f[n][m][BASE - del]) {
        last = BASE + del;
    } else {
        last = BASE - del;
    }

    tt = 0;
    int i = n, j = m, k = last;
    while (j) {
        if (f[i][j][k] == f[i - 1][j][k]) {
            i--;
        } else {
            ans[++tt] = i;
            k -= vp[i] - vd[i];
            j--, i--;
        }
    }

    int sp = 0, sd = 0;
    for (int i = 1; i <= m; i++) {
        sp += vp[ans[i]];
        sd += vd[ans[i]];
    }

    printf("Jury #%d\nBest jury has value %d for prosecution and value %d for defence:\n", ++T, sp, sd);

    sort(ans + 1, ans + 1 + m);
    for (int i = 1; i <= m; i++) {
        printf(" %d", ans[i]);
    }

    cout << endl << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    while (cin >> n >> m, n || m) {
        for (int i = 1; i <= n; i++) {
            cin >> vp[i] >> vd[i];
        }
        solve();
    }

    return 0;
}