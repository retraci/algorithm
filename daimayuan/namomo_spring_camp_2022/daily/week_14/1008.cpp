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
const int M = 2 * N;

int n;
int a[N];
int h[N], ne[M * 2], e[M * 2], edm;
int d[N];

void add(int u, int v) {
    e[edm] = v, ne[edm] = h[u], h[u] = edm++;
}

void bfs(int bit) {
    queue<int> que;
    fill(d, d + n + 1, -1);

    for (int i = 1; i <= n; i++) {
        if ((a[i] & 1) == bit) que.push(i), d[i] = 0;
    }

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
}

void solve() {
    fill(h, h + n + 1, -1), edm = 0;
    for (int i = 1; i <= n; i++) {
        int v1 = i - a[i], v2 = i + a[i];
        if (v1 >= 1) add(v1, i);
        if (v2 <= n) add(v2, i);
    }

    vector<int> ans(n + 1, 1e9);
    bfs(0);
    for (int i = 1; i <= n; i++) {
        if ((a[i] & 1) == 0) continue;

        int dis = d[i] == -1 ? 1e9 : d[i];
        ans[i] = min(ans[i], dis);
    }
    bfs(1);
    for (int i = 1; i <= n; i++) {
        if ((a[i] & 1) == 1) continue;

        int dis = d[i] == -1 ? 1e9 : d[i];
        ans[i] = min(ans[i], dis);
    }

    for (int i = 1; i <= n; i++) cout << (ans[i] == 1e9 ? -1 : ans[i]) << " ";
    cout << "\n";
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
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}