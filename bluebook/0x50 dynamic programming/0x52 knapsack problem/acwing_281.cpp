#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <numeric>

using namespace std;

const int N = 110, M = 1e5 + 10;

int n, m;
int va[N], vc[N];
int f[M], cnt[M];

void solve() {
    memset(f, 0, sizeof f);
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        memset(cnt, 0, sizeof cnt);
        for (int j = va[i]; j <= m; j++) {
            if (f[j]) continue;

            if (f[j - va[i]] && cnt[j - va[i]] < vc[i]) {
                f[j] = 1;
                cnt[j] = cnt[j - va[i]] + 1;
            }
        }
    }

    int ans = accumulate(f + 1, f + 1 + m, 0);
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    while (cin >> n >> m, n || m) {
        for (int i = 1; i <= n; i++) {
            scanf("%d", &va[i]);
        }
        for (int i = 1; i <= n; i++) {
            scanf("%d", &vc[i]);
        }
        solve();
    }

    return 0;
}