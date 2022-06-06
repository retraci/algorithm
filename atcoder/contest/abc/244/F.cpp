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
const int N = 23;
const int M = N * N;

int n, m;
int h[N], ne[M * 2], e[M * 2], edm;

void add(int u, int v) {
    e[edm] = v, ne[edm] = h[u], h[u] = edm++;
}

void solve() {
    int lim = 1 << n;
    int d[lim][n + 1];
    memset(d, -1, sizeof d);
    queue<pii> que;
    for (int i = 1; i <= n; i++) {
        int sta = 1 << (i - 1);
        d[sta][i] = 1;
        que.push({sta, i});
    }

    while (!que.empty()) {
        auto [sta, u] = que.front(); que.pop();

        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];

            int ns = sta ^ (1 << (v - 1));
            if (d[ns][v] == -1) {
                d[ns][v] = d[sta][u] + 1;
                que.push({ns, v});
            }
        }
    }

    int ans = 0;
    for (int mask = 1; mask < lim; mask++) {
        ans += *min_element(&d[mask][1], &d[mask][n] + 1);
    }
    cout << ans << "\n";
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
        cin >> n >> m;
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