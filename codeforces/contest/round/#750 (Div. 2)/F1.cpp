#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1e5 + 10, M = 511 + 10;

int n;
int va[N];
int f[N][M];

void solve() {
    memset(f, 0x3f, sizeof f);
    f[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= 511; j++) {
            int tmp = j ^ va[i];
            // 选
            if (va[i] > f[i - 1][tmp]) f[i][j] = min(f[i][j], va[i]);
            // 不选
            f[i][j] = min(f[i][j], f[i - 1][j]);
        }
    }

    int cnt = 0;
    for (int j = 0; j < M; j++) cnt += f[n][j] < 0x3f3f3f3f;
    cout << cnt << endl;
    for (int j = 0; j < M; j++) {
        if (f[n][j] < 0x3f3f3f3f) cout << j << " ";
    }
    cout << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> va[i];
    solve();

    return 0;
}