#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 15;

int n;
int v[N];
int f[N][N * N];
int ans;

void dfs(int cur, int sum) {
    int rem = n - cur;
    if (sum > 90) return;
    if (rem * 10 + sum < 90) return;
    if (cur == n) {
        if (sum == 90) ans++;
        return;
    }

    for (int k = 0; k <= 10; k++) dfs(cur + 1, sum + k);
}

void solve() {
    n = 10;
    for (int i = 0; i <= 10; i++) v[i] = i;

    memset(f, 0, sizeof f);
    f[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= 10 * 10; j++) {
            for (int k = 0; k <= 10; k++) {
                if (j - k >= 0) f[i][j] += f[i - 1][j - k];
            }
        }
    }

    cout << f[n][90] << endl;

    ans = 0;
    dfs(0, 0);
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    solve();

    return 0;
}
