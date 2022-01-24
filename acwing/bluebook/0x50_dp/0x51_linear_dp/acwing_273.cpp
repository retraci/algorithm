#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 2010;
const int INF = 0x3f3f3f3f;

int n;
int va[N], vb[N];
int f[N][N];

int work() {
    memcpy(vb, va, sizeof va);
    sort(vb + 1, vb + n + 1);

    memset(f, INF, sizeof f);
    f[0][1] = 0;
    for (int i = 1; i <= n; i++) {
        int minv = INF;
        for (int j = 1; j <= n; j++) {
            minv = min(minv, f[i - 1][j]);
            f[i][j] = min(f[i][j], minv + abs(va[i] - vb[j]));
        }
    }

    return *min_element(f[n] + 1, f[n] + n + 1);
}

void solve() {
    int res = work();
    reverse(va + 1, va + n + 1);
    res = min(res, work());

    cout << res << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &va[i]);
    }
    solve();

    return 0;
}