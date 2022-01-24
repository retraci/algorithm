#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 55;
const int INF = 0x3f3f3f3f;

int n;
char vc[N * 2];
int va[N * 2];
int f[N * 2][N * 2], g[N * 2][N * 2];

void solve() {
    for (int i = 1; i <= n; i++) {
        vc[i + n] = vc[i];
        va[i + n] = va[i];
    }

    memset(f, -0x3f, sizeof f);
    memset(g, 0x3f, sizeof g);
    for (int len = 1; len <= n; len++) {
        for (int L = 1; L + len - 1 <= 2 * n; L++) {
            int R = L + len - 1;

            if (len == 1) {
                f[L][R] = g[L][R] = va[L];
                continue;
            }

            for (int k = L; k < R; k++) {
                char op = vc[k + 1];
                int maxL = f[L][k], maxR = f[k + 1][R], minL = g[L][k], minR = g[k + 1][R];

                if (op == 't') {
                    f[L][R] = max(f[L][R], maxL + maxR);
                    g[L][R] = min(g[L][R], minL + minR);
                } else {
                    int tmp[4] = {minL * minR, minL * maxR, maxL * minR, maxL * maxR};
                    f[L][R] = max(f[L][R], *max_element(tmp, tmp + 4));
                    g[L][R] = min(g[L][R], *min_element(tmp, tmp + 4));
                }
            }
        }
    }

    int ans = -INF;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, f[i][i + n - 1]);
    }
    cout << ans << endl;

    for (int i = 1; i <= n; i++) {
        if (ans == f[i][i + n - 1]) {
            cout << i << " ";
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> vc[i] >> va[i];
    }
    solve();

    return 0;
}