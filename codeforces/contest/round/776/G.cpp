#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <cassert>
#include <random>
#include <cmath>

void debug() {
    std::cout << "\n";
}

template<class T, class... OtherArgs>
void debug(T &&var, OtherArgs &&... args) {
    std::cout << std::forward<T>(var) << " ";
    debug(std::forward<OtherArgs>(args)...);
}

using namespace std;

#define fi first
#define se second
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ai3 = array<int, 3>;
mt19937 mrnd(time(0));
mt19937_64 mrnd64(time(0));

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 2e5 + 10;
const int M = 2e5 + 10;
const int MOD = 1e9 + 7;

int n, m, S, T;
int h[N], ne[M * 2], e[M * 2], edm;

void add(int u, int v) {
    e[edm] = v, ne[edm] = h[u], h[u] = edm++;
}

int dij() {
    int d[n + 1][2], c[n + 1][2], vis[n + 1][2];
    memset(d, 0x3f, sizeof d), memset(c, 0, sizeof c), memset(vis, 0, sizeof vis);

    queue<pii> que;
    c[S][0] = 1, d[S][0] = 0;
    que.push({S, 0});
    while (!que.empty()) {
        auto [u, ty] = que.front(); que.pop();
        if (vis[u][ty]) continue;
        vis[u][ty] = 1;

        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];

            if (d[v][0] > d[u][ty] + 1) {
                d[v][0] = d[u][ty] + 1;
                c[v][0] = c[u][ty];
                que.push({v, 0});
            } else if (d[v][0] == d[u][ty] + 1) {
                c[v][0] += c[u][ty];
                c[v][0] %= MOD;
                que.push({v, 0});
            } else if (d[v][1] > d[u][ty] + 1) {
                d[v][1] = d[u][ty] + 1;
                c[v][1] = c[u][ty];
                que.push({v, 1});
            } else if (d[v][1] == d[u][ty] + 1) {
                c[v][1] += c[u][ty];
                c[v][1] %= MOD;
                que.push({v, 1});
            }
        }
    }

    int res = c[T][0];
    if (d[T][1] == d[T][0] + 1) res += c[T][1];
    return res % MOD;
}

void solve() {
    cout << dij() << "\n";
}

void prework() {
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    prework();
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _ = 1;
    cin >> _;
    while (_--) {
        cin >> n >> m >> S >> T;
        fill(h, h + n + 1, -1), edm = 0;

        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            add(u, v), add(v, u);
        }
        solve();
    }

    return 0;
}