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

const int N = 1e6 + 10;

ll x;
int vis[2 * N];
int vs[2 * N];

void primes(int lim) {
    memset(vis, 0, sizeof vis);
    vis[1] = 1;
    for (int i = 2; i <= lim; i++) {
        if (vis[i]) continue;
        for (int j = i; j <= lim / i; j++) vis[i * j] = 1;
    }
}

void init() {
    primes(2 * N - 1);

    for (int i = 2; i < 2 * N; i++) {
        vs[i] += vs[i - 1] + !vis[i];
    }
}

void solve() {
    int ans = 0;
    for (int i = 0; i < 22; i++) {
        if (x >> i & 1) {
            int lb = 1 << i, rb = (1 << (i + 1)) - 1;
            ans += vs[rb] - vs[lb - 1];
        }
    }

    cout << ans << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    init();
    int T;
    cin >> T;
    while (T--) {
        cin >> x;
        solve();
    }

    return 0;
}