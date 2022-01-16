#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 110;

int n, m;
int s[N];
int v[N][N], w[N][N];
int f[N];

void solve() {
    memset(f, 0, sizeof f);

    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= 0; j--) {
            for (int k = 1; k <= s[i]; k++) {
                if (j - v[i][k] >= 0) f[j] = max(f[j], f[j - v[i][k]] + w[i][k]);
            }
        }
    }

    cout << f[m] << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &s[i]);
        for (int j = 1; j <= s[i]; j++) {
            scanf("%d%d", &v[i][j], &w[i][j]);
        }
    }
    solve();

    return 0;
}