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
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ai3 = array<int, 3>;
mt19937 mrnd(time(0));
mt19937_64 mrnd64(time(0));

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1e5 + 5;

int n;
int xx[N];
double a[N], f[N];
int fa[N];
vector<int> e[N];
vector<int> topo;

bool sgn(double x) {
    if (x < 0) return 0;
    else return 1;
}

void dfs(int u, int fno) {
    fa[u] = fno;
    for (int v: e[u]) {
        if (v == fno) continue;

        dfs(v, u);
    }
    topo.push_back(u);
}

bool check(double md) {
    for (int u : topo) {
        double c1 = -1e100, c2 = -1e100;

        for (int v : e[u]) {
            if (v == fa[u]) continue;

            if (f[v] > c1) c2 = c1, c1 = f[v];
            else if (f[v] > c2) c2 = f[v];
        }

        if (sgn(c1 + c2 + a[u]) || sgn(c1 + a[u])) return true;
        f[u] = max(c1 + a[u], a[u]);
    }

    return false;
}

void solve() {
    dfs(1, 0);

    double left = -1e5, right = 1e5;
    for (int t = 1; t <= 66; t++) {
        double md = (left + right) / 2;
        for (int i = 1; i <= n; ++i) a[i] = xx[i] - md;
        if (check(md)) left = md;
        else right = md;
    }
    double res = left * left / 4;

    left = -1e5, right = 1e5;
    for (int t = 1; t <= 66; t++) {
        double md = (left + right) / 2;
        for (int i = 1; i <= n; ++i) a[i] = -xx[i] - md;
        if (check(md)) left = md;
        else right = md;
    }

    res = max(res, left * left / 4);
    cout << fixed << setprecision(6);
    cout << res << "\n";
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
        for (int i = 1; i <= n; i++) cin >> xx[i];
        for (int i = 1, u, v; i < n; i++) {
            cin >> u >> v;
            e[u].push_back(v);
            e[v].push_back(u);
        }
        solve();
    }

    return 0;
}