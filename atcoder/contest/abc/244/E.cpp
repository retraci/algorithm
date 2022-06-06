#include <bits/stdc++.h>

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

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int MOD = 998244353;
const int N = 2010;
const int M = 2010;

int n, m, k, S, T, x;
int h[N], ne[M * 2], e[M * 2], edm;

void add(int u, int v) {
    e[edm] = v, ne[edm] = h[u], h[u] = edm++;
}

void solve() {
    int f[k + 1][n + 1][2];
    memset(f, 0, sizeof f);
    f[0][S][S == x] = 1;
    for (int i = 1; i <= k; i++) {
        for (int u = 1; u <= n; u++) {
            for (int y = 0; y <= 1; y++) {
                for (int j = h[u]; ~j; j = ne[j]) {
                    int v = e[j];

                    f[i][v][y ^ (v == x)] += f[i - 1][u][y];
                    f[i][v][y ^ (v == x)] %= MOD;
                }
            }
        }
    }

    cout << f[k][T][0] << "\n";
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
//    cin >> _;
    while (_--) {
        cin >> n >> m >> k >> S >> T >> x;
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