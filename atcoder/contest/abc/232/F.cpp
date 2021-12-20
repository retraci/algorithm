#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
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

const int N = 18;

int n;
ll x, y;
ll va[N], vb[N];
ll f[1 << N];

void solve() {
    int lim = 1 << n;
    memset(f, 0x3f, sizeof f);
    f[0] = 0;
    for (int mask = 0; mask < lim; mask++) {
        // i -> j
        int j = __builtin_popcount(mask);

        for (int i = 0; i < n; i++) {
            if (mask >> i & 1) continue;
            int ns = mask | (1 << i);

            ll a = abs(vb[j] - va[i]) * x;
            ll cnt = 0;
            for (int k = i + 1; k < n; k++) cnt += mask >> k & 1;
            ll b = cnt * y;
            f[ns] = min(f[ns], f[mask] + a + b);
        }
    }

    cout << f[lim - 1] << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> x >> y;
    for (int i = 0; i < n; i++) cin >> va[i];
    for (int i = 0; i < n; i++) cin >> vb[i];
    solve();

    return 0;
}