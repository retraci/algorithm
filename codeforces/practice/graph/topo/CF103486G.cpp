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

// region 无权图
template<int N, int M>
struct Graph {
    int n, m;
    int h[N + 10], ne[M * 2 + 10], e[M * 2 + 10], edm;

    Graph() {}

    void init(int _n, int _m) {
        n = _n, m = _m;
        fill(h, h + n + 1, -1), edm = 0;
    }

    void add(int u, int v) {
        e[edm] = v, ne[edm] = h[u], h[u] = edm++;
    }
};
// endregion

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int N = 1e3 + 10;

int n;
int a[N][N];
int r[N], c[N];
Graph<N * 2, N * N> g;

void solve() {
    vector<int> need(2 * n + 1);
    for (int i = 1; i <= n; i++) need[i] = r[i];
    for (int i = 1; i <= n; i++) need[n + i] = c[i];
    vector<int> cur(2 * n + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i][j] == -1) continue;

            cur[i] ^= a[i][j];
            cur[j + n] ^= a[i][j];
        }
    }

    vector<int> din(2 * n + 1);
    g.init(2 * n, -1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i][j] != -1) continue;

            g.add(i, n + j);
            g.add(n + j, i);
            din[n + j]++, din[i]++;
        }
    }

    vector<int> que;
    for (int i = 1; i <= 2 * n; i++) {
        if (din[i] == 1) que.push_back(i);
    }
    for (int k = 0; k < que.size(); k++) {
        int u = que[k];

        for (int i = g.h[u]; ~i; i = g.ne[i]) {
            int v = g.e[i];

            int x = min(u, v), y = max(u, v) - n;
            if (a[x][y] == -1) {
                a[x][y] = cur[u] == need[u] ? 0 : 1;

                cur[u] ^= a[x][y];
                cur[v] ^= a[x][y];
            }

            if (--din[v] == 1) que.push_back(v);
        }
    }

    int mxd = *max_element(din.begin() + 1, din.end());
    if (mxd > 1) {
        cout << -1 << "\n";
        return;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << a[i][j] << " \n"[j == n];
        }
    }
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
        cin >> n;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                cin >> a[i][j];
            }
        }
        for (int i = 1; i <= n; i++) cin >> r[i];
        for (int i = 1; i <= n; i++) cin >> c[i];
        solve();
    }

    return 0;
}