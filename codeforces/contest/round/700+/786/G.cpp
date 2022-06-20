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
mt19937 mrnd(std::random_device{}());

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 2e5 + 10;
const int M = 2e5 + 10;

int n, m;
int h[N], ne[M * 2], e[M * 2], edm;
int in[N], out[N];

void add(int u, int v) {
    e[edm] = v, ne[edm] = h[u], h[u] = edm++;
}

void solve() {
    queue<int> que;
    vector<int> seq;
    for (int i = 1; i <= n; i++) {
        if (in[i] == 0) que.push(i);
    }

    vector<int> cnt(n + 1);
    while (!que.empty()) {
        int u = que.front(); que.pop();
        seq.push_back(u);

        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            if (++cnt[v] == in[v]) que.push(v);
        }
    }

    reverse(seq.begin(), seq.end());
    vector<int> f(n + 1, 1);
    for (int u : seq) {
        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            if (out[u] >= 2 && in[v] >= 2) f[u] = max(f[u], f[v] + 1);
        }
    }

    int ans = *max_element(f.begin() + 1, f.end());
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
            add(u, v);
            out[u]++, in[v]++;
        }
        solve();
    }

    return 0;
}