#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <numeric>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

const int N = 1000010;
const ll MOD = 998244353;

ll n, m, k;
ll f[N][2][2];
ll x1, y1, x2, y2;

ll calc(ll x) {
    return max(0LL, x);
}

void solve() {
    f[0][x1 != x2][y1 != y2] = 1;

    for (int i = 1; i <= k; i++) {
        auto prev = f[i - 1], cur = f[i];

        cur[1][1] = (calc(n - 1) * prev[0][1] % MOD
                + calc(n - 2) * prev[1][1] % MOD
                + calc(m - 1) * prev[1][0] % MOD
                + calc(m - 2) * prev[1][1] % MOD) % MOD;

        cur[1][0] = (prev[1][1]
                + calc(n - 2) * prev[1][0] % MOD
                + calc(n - 1) * prev[0][0] % MOD) % MOD;

        cur[0][1] = (prev[1][1]
                + calc(m - 2) * prev[0][1] % MOD
                + calc(m - 1) * prev[0][0] % MOD) % MOD;

        cur[0][0] = (prev[0][1] + prev[1][0]) % MOD;
    }

    cout << f[k][0][0] << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> k;
    cin >> x1 >> y1 >> x2 >> y2;
    solve();

    return 0;
}