#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 5e5 + 10;
const ll MOD = 998244353;

int n;
int va[N];
ll f[N][3];

void solve() {
    for (int i = 0; i <= n; i++) {
        for (int k = 0; k < 3; k++) f[i][k] = 0;
    }

    for (int i = 1; i <= n; i++) {
        int x = va[i];

        // 0
        // 接在自己后面
        f[x][0] = (f[x][0] + f[x][0]) % MOD;
        // 接在 x - 1 后面
        if (x - 1 >= 0) f[x][0] = (f[x][0] + f[x - 1][0]) % MOD;
        // 0 自己
        if (x == 0) f[x][0] = (f[x][0] + 1) % MOD;

        // 1
        // 接在自己后面
        f[x][1] = (f[x][1] + f[x][1]) % MOD;
        // 从 0, 2 转过来
        if (x - 2 >= 0) f[x][1] = (f[x][1] + f[x - 2][2] + f[x - 2][0]) % MOD;
        // 1 自己
        if (x == 1) f[x][1] = (f[x][1] + 1) % MOD;

        // 2
        // 接在自己后面
        f[x][2] = (f[x][2] + f[x][2]) % MOD;
        // 从 1 转过来
        if (x + 2 <= n) f[x][2] = (f[x][2] + f[x + 2][1]) % MOD;
    }

    ll ans = 0;
    for (int i = 0; i <= n; i++) {
        for (int k = 0; k < 3; k++) ans = (ans + f[i][k]) % MOD;
    }
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> va[i];
        solve();
    }

    return 0;
}