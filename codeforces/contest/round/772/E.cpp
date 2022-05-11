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
using ull = unsigned long long;
using pii = pair<int, int>;
using ai3 = array<int, 3>;

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 2e5 + 10;
const int M = 2e5 + 10;

int n, m;
ai3 es[M];
int co[N], in[N];
vector<int> seq;
int h[N], ne[M * 2], e[M * 2], edm;

void add(int u, int v) {
    e[edm] = v, ne[edm] = h[u], h[u] = edm++;
}

bool dfs(int u, int c) {
    co[u] = c;

    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];

        if (!co[v]) {
            if (!dfs(v, -c)) return false;
        } else {
            if (co[v] != -c) return false;
        }
    }

    return true;
}

void topo() {
    queue<int> que;
    for (int i = 1; i <= n; i++) {
        if (in[i] == 0) que.push(i);
    }

    while (!que.empty()) {
        int u = que.front(); que.pop();
        seq.push_back(u);

        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];

            if (--in[v] == 0) que.push(v);
        }
    }
}

void solve() {
    fill(h, h + n + 1, -1), edm = 0;
    for (int i = 1; i <= m; i++) {
        auto [ty, u, v] = es[i];

        add(u, v), add(v, u);
    }
    for (int i = 1; i <= n; i++) {
        if (!co[i]) {
            if (!dfs(i, 1)) {
                cout << "NO" << "\n";
                return;
            }
        }
    }

    fill(h, h + n + 1, -1), edm = 0;
    for (int i = 1; i <= m; i++) {
        auto [ty, u, v] = es[i];

        if (co[u] == 1) swap(u, v);
        if (ty == 1) add(u, v), in[v]++;
        else add(v, u), in[u]++;
    }
    topo();

    if (seq.size() < n) {
        cout << "NO" << "\n";
        return;
    }

    cout << "YES" << "\n";
    vector<pii> ans(n + 1);
    for (int i = 1; i <= n; i++) {
        ans[i].fi = co[i];
    }
    for (int i = 0; i < n; i++) {
        ans[seq[i]].se = i + 1;
    }
    for (int i = 1; i <= n; i++) {
        auto [c, x] = ans[i];

        cout << (c == -1 ? "L" : "R") << " ";
        cout << x << "\n";
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
        cin >> n >> m;
        for (int i = 1; i <= m; i++) {
            int ty, u, v;
            cin >> ty >> u >> v;
            es[i] = {ty, u, v};
        }
        solve();
    }

    return 0;
}