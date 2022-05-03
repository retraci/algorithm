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

// region 普通方程
template<int SZ>
struct Gauss {
    const ld eps = 1e-9;

    ld mat[SZ + 10][SZ + 10];

    Gauss() {
        memset(mat, 0, sizeof mat);
    }

    // r 为方程个数, c 为未知数个数, 无解返回-1, 多解返回自由元个数
    // mat[1 ~ c]: 增广矩阵, c + 1 位置为常数
    const pair<int, vector<ld>> work(int r, int c) {
        int row = 1;
        for (int col = 1; col <= c; col++) {
            for (int i = row; i <= r; i++) {
                if (fabs(mat[i][col]) > eps) {
                    for (int j = col; j <= c + 1; j++) swap(mat[i][j], mat[row][j]);
                    break;
                }
            }
            if (fabs(mat[row][col]) < eps) break;

            for (int i = 1; i <= r; i++) {
                if (i != row && fabs(mat[i][col]) > eps) {
                    ld rate = mat[i][col] / mat[row][col];
                    for (int j = c + 1; j >= col; j--) {
                        mat[i][j] -= mat[row][j] * rate;
                    }
                }
            }
            row++;
        }

        if (row <= r) {
            for (int i = row; i <= r; i++) {
                if (fabs(mat[i][c + 1]) > eps) return {-1, {}};
            }
            return {r - row + 1, {}};
        }

        vector<ld> res(c + 1);
        for (int i = 1; i <= c; i++) res[i] = mat[i][c + 1] /= mat[i][i];

        return {0, res};
    }
};
// endregion

const int N = 510;
const int M = 125010;

int n, m;
pii es[M];
int h[N], ne[2 * M], e[2 * M], edm;
int deg[N];
Gauss<N> gauss;

void add(int u, int v) {
    e[edm] = v, ne[edm] = h[u], h[u] = edm++;
}

void init() {
    fill(h + 1, h + n + 1, -1), edm = 0;
    for (int i = 1; i <= m; i++) {
        auto [u, v] = es[i];
        add(u, v), add(v, u);
        deg[u]++, deg[v]++;
    }

    for (int i = 1; i <= n - 1; i++) {
        gauss.mat[i][i] = -1;
        gauss.mat[i][n] = i == 1 ? -1 : 0;
        for (int j = h[i]; ~j; j = ne[j]) {
            int v = e[j];
            if (v == n) continue;

            ld p = 1.0 / deg[v];
            gauss.mat[i][v] = p;
        }
    }
}

void solve() {
    init();

    auto [t1, t2] = gauss.work(n - 1, n - 1);
    if (t1 != 0) return;

    vector<ld> t3(m + 1, 0);
    for (int i = 1; i <= m; i++) {
        auto [u, v] = es[i];

        if (u != n) t3[i] += t2[u] / deg[u];
        if (v != n) t3[i] += t2[v] / deg[v];
    }
    ld ans = 0;
    sort(t3.begin() + 1, t3.end());
    for (int i = 1; i <= m; i++) {
        auto [u, v] = es[i];
        ans += (m - i + 1) * t3[i];
    }
    cout << fixed << setprecision(3);
    cout << ans << "\n";
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
            int u, v;
            cin >> u >> v;
            es[i] = {u, v};
        }
        solve();
    }

    return 0;
}