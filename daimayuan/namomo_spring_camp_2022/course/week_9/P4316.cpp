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

const int N = 1e5 + 10;
const int M = 2 * N;

int n, m;
pii e[M];
int h[N], ne[M], edm;
double f[N];

void add(int u, int v, int cost) {
    e[edm] = {v, cost}, ne[edm] = h[u], h[u] = edm++;
}

double dfs(int u) {
    if (u == n) return f[u] = 0;
    if (f[u] != -1) return f[u];

    f[u] = 0;
    int sz = 0;
    for (int i = h[u]; ~i; i = ne[i]) sz++;
    for (int i = h[u]; ~i; i = ne[i]) {
        auto [v, cost] = e[i];

        f[u] += 1.0 / sz * (cost + dfs(v));
    }

    return f[u];
}

void solve() {
    fill(f, f + n + 1, -1);

    cout << fixed << setprecision(2);
    cout << dfs(1) << "\n";
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
            int u, v, cost;
            cin >> u >> v >> cost;
            add(u, v, cost);
        }
        solve();
    }

    return 0;
}