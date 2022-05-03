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

const int N = 1e4 + 10;

int n, m;
int h[N], ne[2 * N], e[2 * N], edm;
int c[N], ins[N], vis[N];
int s[N], cnt, eid;
vector<int> ans;

void add(int u, int v) {
    e[edm] = v, ne[edm] = h[u], h[u] = edm++;
}

void dfs(int u, int fno, int col) {
    ins[u] = 1, c[u] = col;

    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        if (v == fno) continue;

        if (!c[v]) {
            dfs(v, u, -col);
        } else if (ins[v]) {
            if (c[u] != c[v]) {
                s[u]--, s[v]++;
            } else {
                cnt++, eid = i / 2;
                s[u]++, s[v]--;
            }
        }
    }

    ins[u] = 0;
}

void dfs2(int u, int fno) {
    vis[u] = 1;

    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        if (v == fno) continue;

        if (!vis[v]) {
            dfs2(v, u);

            if (s[v] == cnt) ans.push_back(i / 2);
            s[u] += s[v];
        }
    }
}

void solve() {
    for (int i = 1; i <= n; i++) {
        if (!c[i]) dfs(i, 0, 1);
    }

    if (cnt == 0) {
        cout << m << "\n";
        for (int i = 1; i <= m; i++) cout << i << " ";
        cout << "\n";
        return;
    }

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) dfs2(i, 0);
    }
    if (cnt == 1) ans.push_back(eid);

    sort(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    for (int x : ans) cout << x + 1 << " ";
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