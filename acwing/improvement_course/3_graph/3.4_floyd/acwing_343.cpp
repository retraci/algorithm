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

const int N = 33;

int n, m;
bitset<N> f[N];

int g[N * N];
int ne[N * N], h[N], edm;
int du[N];

void add(int u, int v) {
    g[edm] = v;
    ne[edm] = h[u], h[u] = edm++;
    du[v]++;
}

void floyd() {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (f[i][k]) f[i] |= f[k];
        }
    }
}

int check() {
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (f[u][v] && f[v][u]) {
                return 2;
            }
        }
    }

    int flag = 0;
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (u != v && !f[u][v] && !f[v][u]) {
                flag = 1;
            }
        }
    }

    return flag ? 0 : 1;
}

vector<int> topo() {
    vector<int> res;
    queue<int> que;
    for (int i = 0; i < n; i++) {
        if (du[i] == 0) que.push(i);
    }
    while (!que.empty()) {
        auto u = que.front(); que.pop();
        res.push_back(u);

        for (int i = h[u]; ~i; i = ne[i]) {
            int v = g[i];

            if (--du[v] == 0) que.push(v);
        }
    }

    return res;
}

void solve() {
    fill(h, h + n, -1), edm = 0;
    fill(du, du + n, 0);
    for (int i = 0; i < n; i++) f[i].reset();

    int ti = 0, stat = 0;
    for (int i = 1; i <= m; i++) {
        string str;
        cin >> str;
        int u = str[0] - 'A', v = str[2] - 'A';
        if (!stat) {
            f[u][v] = 1, add(u, v);
            floyd();
            stat = check();
            if (stat) ti = i;
        }
    }

    if (!stat) {
        cout << "Sorted sequence cannot be determined." << "\n";
    } else if (stat == 2) {
        cout << "Inconsistency found after " + to_string(ti) + " relations." << "\n";
    } else {
        cout << "Sorted sequence determined after " + to_string(ti) + " relations: ";
        vector<int> seq = topo();
        for (int x : seq) cout << (char) (x + 'A');
        cout << "." << "\n";
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
    int T = 1;
//    cin >> T;
    while (cin >> n >> m, n || m) {
        solve();
    }

    return 0;
}