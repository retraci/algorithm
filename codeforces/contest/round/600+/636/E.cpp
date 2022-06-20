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
mt19937 mrnd(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 2e5 + 10;
const int M = 2e5 + 10;

int n, m, a, b, c;
ll w[N];
int h[N], ne[M * 2], e[M * 2], edm;

void add(int u, int v) {
    e[edm] = v, ne[edm] = h[u], h[u] = edm++;
}

ll qr(int L, int R) {
    return w[R] - w[L - 1];
}

vector<int> bfs(int S) {
    queue<int> que;
    vector<int> d(n + 1, -1);
    d[S] = 0;
    que.push(S);
    while (!que.empty()) {
        int u = que.front(); que.pop();
        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            if (d[v] == -1) {
                d[v] = d[u] + 1;
                que.push(v);
            }
        }
    }

    return d;
}

void solve() {
    sort(w + 1, w + m + 1);
    for (int i = 1; i <= m; i++) w[i] += w[i - 1];

    auto d1 = bfs(a);
    auto d2 = bfs(b);
    auto d3 = bfs(c);

    ll ans = 1e18;
    for (int i = 1; i <= n; i++) {
        int l1 = d1[i], l2 = d2[i], l3 = d3[i];
        if (l1 + l2 + l3 > m) continue;
        ll t = 2 * qr(1, l2) + qr(l2 + 1, l1 + l2 + l3);
        ans = min(ans, t);
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
    cin >> _;
    while (_--) {
        cin >> n >> m >> a >> b >> c;
        fill(h, h + n + 1, -1), edm = 0;

        for (int i = 1; i <= m; i++) cin >> w[i];
        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            add(u, v), add(v, u);
        }
        solve();
    }

    return 0;
}