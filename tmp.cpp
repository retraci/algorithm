#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <bitset>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef tuple<int, int, int> ti3;
typedef tuple<ll, ll, ll> tl3;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

const int N = 66;
const int M = 5000;

int n, m;
vector<ti3> es;
vector<ti3> g[N];

int tt;
vector<int> tri[M];
vector<int> path;

vector<int> vx;

int get(int x) {
    return lower_bound(vx.begin(), vx.end(), x) - vx.begin() + 1;
}

void add(int u, int v, int c, int id) {
    g[u].push_back({v, c, id});
}

void dfs(int u, int from, int len) {
    if (len == 3) {
        if (u == from) tri[++tt] = path;
        return;
    }

    for (auto &[v, c, id]: g[u]) {
        if (v != from && v <= u) continue;

        path.push_back(id);
        dfs(v, from, len + 1);
        path.pop_back();
    }
}

void init() {
    tt = 0;
    for (int i = 1; i <= n; i++) dfs(i, i, 0);
}

ll lcm(ll a, ll b) {
    return a * b / __gcd(a, b);
}

ll rc, cc;
ll mat[M][N];
ll res[N];

int gauss(int r, int c) {
    int row = 1;
    for (int col = 1; col <= c; col++) {
        for (int i = row; i <= r; i++) {
            if (mat[i][col] != 0) {
                for (int j = col; j <= c + 1; j++) swap(mat[i][j], mat[row][j]);
                break;
            }
        }
        if (mat[row][col] == 0) break;

        for (int i = 1; i <= r; i++) {
            if (i != row && mat[i][col] != 0) {
                ll k = lcm(mat[i][col], mat[row][col]);
                ll r1 = k / mat[row][col], r2 = k / mat[i][col];
                for (int j = 1; j <= c + 1; j++) mat[row][j] *= r1, mat[i][j] *= r2;

                for (int j = c + 1; j >= col; j--) {
                    mat[i][j] -= mat[row][j];
                }
            }
        }
        row++;
    }

    for (int i = 1; i <= c; i++) {
        if (mat[i][i] == 0) res[i] = 0;
        else res[i] = mat[i][c + 1];
    }
    return 1;
}

void init_gauss() {
    vx = {};
    for (int i = 1; i <= m; i++) {
        auto &[u, v, c] = es[i];
        if (c != -1) continue;
        vx.push_back(i);
    }

    memset(mat, 0, sizeof mat);
    rc = 0, cc = vx.size();
    for (int i = 1; i <= tt; i++) {
        int a = tri[i][0], b = tri[i][1], c = tri[i][2];

        int c1 = get<2>(es[a]), c2 = get<2>(es[b]), c3 = get<2>(es[c]);
        if (c1 != -1 && c2 != -1 && c3 != -1) {
            int sum = c1 + c2 + c3;
            if (sum % 3 != 0) {
                cout << -1 << "\n";
                exit(0);
            }
            continue;
        }

        rc++;
        if (c1 == -1) mat[rc][get(a)] = 1;
        else mat[rc][cc + 1] -= c1;
        if (c2 == -1) mat[rc][get(b)] = 1;
        else mat[rc][cc + 1] -= c2;
        if (c3 == -1) mat[rc][get(c)] = 1;
        else mat[rc][cc + 1] -= c3;
    }

//    cout << rc << " " << cc << "\n";
//    for (int i = 1; i <= rc; i++) {
//        for (int j = 1; j <= cc + 1; j++) cout << mat[i][j] << " ";
//        cout << "\n";
//    }
}

void solve() {
    init();

    vector<int> ans(m + 1, -1);
    if (tt == 0) {
        for (int i = 1; i <= m; i++) {
            if (get<2>(es[i]) == -1) ans[i] = 1;
            else ans[i] = get<2>(es[i]);
        }
        for (int i = 1; i <= m; i++) cout << ans[i] << " ";
        cout << "\n";
        return;
    }

    init_gauss();

    ll ret = gauss(rc, cc);
//    for (int i = 1; i <= rc; i++) {
//        for (int j = 1; j <= cc + 1; j++) cout << mat[i][j] << " ";
//        cout << "\n";
//    }

    for (int i = 1; i <= m; i++) {
        if (ans[i] == -1) ans[i] = get<2>(es[i]);
    }
    for (int i = 1; i <= cc; i++) {
        int id = vx[i - 1];
        ans[id] = (res[i] % 3 + 3) % 3;
        if (ans[id] == 0) ans[id] = 3;
    }
    for (int i = 1; i <= m; i++) cout << ans[i] << " ";
    cout << "\n";
}

signed main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) g[i] = {};
        es = {{}};

        for (int i = 1; i <= m; i++) {
            int u, v, c;
            cin >> u >> v >> c;
            es.push_back({u, v, c});
            add(u, v, c, i), add(v, u, c, i);
        }
        solve();
    }

    return 0;
}
