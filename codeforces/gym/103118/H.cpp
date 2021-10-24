#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

const int N = 1010, M = 310;

ll n, h, s;
ll hs[N], ss[N], wss[N];
ll f[2][M][M];

void solve() {
    for (int i = 0; i <= n - 1; i++) {
        ll hi = hs[i + 1], si = ss[i + 1], wi = wss[i + 1];

        for (int j = 0; j <= h - 1; j++) {
            for (int k = 0; k <= s; k++) {
                // 不选
                f[i + 1 & 1][j][k] = max(f[i + 1 & 1][j][k], f[i & 1][j][k]);
                // 选
                int nh = j + hi + (k + si <= s ? 0 : k + si - s);
                int ns = k + si <= s ? k + si : s;
                if (nh <= h - 1) f[i + 1 & 1][nh][ns] = max(f[i + 1 & 1][nh][ns], f[i & 1][j][k] + wi);
            }
        }
    }

    cout << f[n & 1][h - 1][s] << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> h >> s;
    for (int i = 1; i <= n; i++) cin >> hs[i] >> ss[i] >> wss[i];
    solve();

    return 0;
}