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
mt19937 mrnd(time(0));
mt19937_64 mrnd64(time(0));

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1e6 + 10;
const int M = 1e6 + 10;

int n;
int h[N], ne[M * 2], e[M * 2], edm;
int sz[N], dep[N];
ll f[N], rf[N];

void add(int u, int v) {
    e[edm] = v, ne[edm] = h[u], h[u] = edm++;
}

void predfs(int u, int fno, int depth) {
    sz[u] = 1, dep[u] = depth;

    f[u] = depth;
    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        if (v == fno) continue;

        predfs(v, u, depth + 1);
        f[u] += f[v];
        sz[u] += sz[v];
    }
}

void dfs(int u, int fno) {
    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        if (v == fno) continue;

        rf[v] = rf[u] - sz[v] + (n - sz[v]);
        dfs(v, u);
    }
}

void solve() {
    predfs(1, -1, 0);
    rf[1] = f[1];
    dfs(1, -1);

    cout << max_element(rf + 1, rf + n + 1) - rf << "\n";
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
        fill(h, h + n + 1, -1), edm = 0;

        for (int i = 1; i <= n - 1; i++) {
            int u, v;
            cin >> u >> v;
            add(u, v), add(v, u);
        }
        solve();
    }

    return 0;
}