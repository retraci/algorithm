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

// region general
#define ll long long
#define ld long double
#define ull unsigned long long
#define fi first
#define se second

typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
typedef std::tuple<int, int, int> ti3;
typedef std::tuple<ll, ll, ll> tl3;
typedef std::tuple<int, int, int, int> ti4;
typedef std::tuple<ll, ll, ll, ll> tl4;

inline void debug() {
    std::cout << "\n";
}

template<class T, class... OtherArgs>
inline void debug(T &&var, OtherArgs &&... args) {
    std::cout << std::forward<T>(var) << " ";
    debug(std::forward<OtherArgs>(args)...);
}
// endregion
// region grid_delta
namespace grid_delta {
    // 上, 右, 下, 左  |  左上, 右上, 右下, 左下
    const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
}
// endregion

using namespace std;
using namespace grid_delta;

const int N = 5e5 + 10;

int n;
string s;
vector<int> g[N];

// region 无边权的lca
int dep[N], fa[N][32];

void lca_init(int rt) {
    fill(dep, dep + n + 1, -1);

    queue<int> que;
    que.push(rt);
    dep[0] = 0, dep[rt] = 1;
    while (!que.empty()) {
        auto u = que.front();
        que.pop();

        for (int v : g[u]) {
            if (dep[v] == -1) {
                dep[v] = dep[u] + 1;
                fa[v][0] = u;
                que.push(v);

                for (int k = 1; k <= 31; k++) {
                    fa[v][k] = fa[fa[v][k - 1]][k - 1];
                }
            }
        }
    }
}

int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int k = 31; k >= 0; k--) {
        if (dep[fa[x][k]] >= dep[y]) x = fa[x][k];
    }
    if (x == y) return x;

    for (int k = 31; k >= 0; k--) {
        if (fa[x][k] != fa[y][k]) {
            x = fa[x][k], y = fa[y][k];
        }
    }
    return fa[x][0];
}
// endregion

// region 后缀数组
int sa[N], rk[N], tp[N], c[N], h[N];
int rkk[N], rk2[N];

bool cmp(int i, int k) {
    return tp[sa[i - 1]] == tp[sa[i]] && tp[fa[sa[i - 1]][k]] == tp[fa[sa[i]][k]];
}

void tsort(int ta[], int fir[], int sed[], int sz) {
    for (int i = 1; i <= sz; i++) c[i] = 0;
    for (int i = 1; i <= n; i++) c[fir[i]]++;
    for (int i = 1; i <= sz; i++) c[i] += c[i - 1];
    for (int i = n; i >= 1; i--) ta[c[fir[sed[i]]]--] = sed[i];
}

void get_sa() {
    int sz = 122, num = 0;
    for (int i = 1; i <= n; i++) rk[i] = s[i], tp[i] = i;
    tsort(sa, rk, tp, sz);
    rk[sa[1]] = rkk[sa[1]] = 1, num = 1;
    for (int i = 2; i <= n; i++) {
        rk[sa[i]] = s[sa[i]] == s[sa[i - 1]] ? num : ++num;
        rkk[sa[i]] = i;
    }
    sz = num;
    for (int k = 0; (1 << k) <= n; k++) {
        for (int i = 1; i <= n; i++) rk2[i] = rkk[fa[i][k]];
        tsort(tp, rk2, sa, n);

        tsort(sa, rk, tp, sz), swap(rk, tp);
        rk[sa[1]] = rkk[sa[1]] = 1, num = 1;
        for (int i = 2; i <= n; i++) {
            rk[sa[i]] = cmp(i, k) ? num : ++num;
            rkk[sa[i]] = i;
        }
        sz = num;
        if (num == n) break;
    }
}
// endregion

void add(int u, int v) {
    g[u].push_back(v);
}

void solve() {
    lca_init(1);
    get_sa();

    for (int i = 1; i <= n; i++) cout << sa[i] << " ";
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
    int T = 1;
//    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 2; i <= n; i++) {
            int f;
            cin >> f;
            add(f, i);
        }
        cin >> s;
        s = ' ' + s;

        solve();
    }

    return 0;
}