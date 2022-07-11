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

#pragma comment(linker, "/STACK:102400000,102400000")

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

const int N = 100010;
const int M = 300010;

int n, m;
int h[N], ne[2 * M], e[2 * M], edm;
int c[N], fa[N], cnt[N], ins[N];
int ans1, ans2;

void add(int u, int v) {
    e[edm] = v, ne[edm] = h[u], h[u] = edm++;
}

void dfs(int u, int fno, int col) {
    ins[u] = 1, c[u] = col, fa[u] = fno;

    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        if (v == fno) continue;

        if (!c[v]) {
            dfs(v, u, -col);
        } else if (ins[v]) {
            if (c[u] != c[v]) {
                ans2 = 1;
            } else {
                ans1 = 1;

                int t = u;
                while (t != v) {
                    if (++cnt[t] >= 2) ans2 = 1;
                    t = fa[t];
                }
                if (++cnt[t] >= 2) ans2 = 1;
            }
        }
    }

    ins[u] = 0;
}

void solve() {
    fill(c, c + n + 1, 0);
    fill(fa, fa + n + 1, 0);
    fill(cnt, cnt + n + 1, 0);
    fill(ins, ins + n + 1, 0);

    ans1 = ans2 = 0;
    for (int i = 1; i <= n; i++) {
        if (!c[i]) dfs(i, 0, 1);
    }

    cout << (ans1 ? "YES" : "NO") << "\n";
    cout << (ans2 ? "YES" : "NO") << "\n";
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