#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 2e5 + 10;

int n;
ll va[N], vb[N];
ll f[N][2][2];

void solve() {
    memset(f, 0x3f, sizeof f);
    f[1][1][1] = va[1];
    f[1][0][0] = 0;
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                for (int pj = 0; pj < 2; pj++) {
                    ll &prev = f[i - 1][pj][k], &cur = f[i][j][k];
                    if (j == 1) {
                        if (j == pj) cur = min(cur, prev + va[i] + vb[i - 1]);
                        else cur = min(cur, prev + va[i]);
                    } else {
                        if (j == pj) cur = min(cur, prev + vb[i - 1]);
                        else cur = min(cur, prev);
                    }
                }
            }
        }
    }

    ll ans = 1e18;
    for (int j = 0; j < 2; j++) {
        for (int k = 0; k < 2; k++) {
            ll tmp = f[n][j][k] + (j == k ? vb[n] : 0);
            ans = min(ans, tmp);
        }
    }
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> va[i];
    for (int i = 1; i <= n; i++) cin >> vb[i];
    solve();

    return 0;
}