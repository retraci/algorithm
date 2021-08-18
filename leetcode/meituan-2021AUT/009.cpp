#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MOD = 998244353;
const int N = 1010;

int n, m;
int f[N][N];

void solve() {
    memset(f, 0, sizeof f);
    for (int j = 1; j <= n; j++) f[1][j] = 1;
    for (int i = 1; i < m; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = j; k <= n; k += j) {
                f[i + 1][k] = (f[i + 1][k] + f[i][j]) % MOD;
            }
        }
    }

    int ans = 0;
    for (int j = 1; j <= n; j++) {
        ans = (ans + f[m][j]) % MOD;
    }
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n >> m;
    solve();

    return 0;
}