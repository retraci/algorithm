#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 3010;

int n;
int va[N], vb[N];
int f[N][N];

void solve() {
    for (int i = 1; i <= n; i++) {
        int tmp = 1;
        for (int j = 1; j <= n; j++) {
            f[i][j] = f[i - 1][j];

            if (va[i] == vb[j]) f[i][j] = max(f[i][j], tmp);
            if (va[i] > vb[j]) tmp = max(tmp, f[i - 1][j] + 1);
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) ans = max(ans, f[n][i]);
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n;
    for (int i = 1; i <= n; i++) scanf("%d", &va[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &vb[i]);
    solve();

    return 0;
}