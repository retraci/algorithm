#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <numeric>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

const int N = 1e5 + 10;

int n, m;
vector<int> g[N];
int dfn[N], rdfn[N], ti;
int sz[N], dep[N];

vector<int> va[N];

int dfs(int u, int fno, int deep) {
    dep[u] = deep, dfn[u] = ++ti;
    va[deep].push_back(u);

    int cnt = 1;
    for (auto v : g[u]) {
        if (v == fno) continue;
        cnt += dfs(v, u, deep + 1);
    }
    rdfn[u] = ti;

    return sz[u] = cnt;
}

void init() {
    dfs(1, 0, 1);

    for (int i = 1; i <= n; i++) {
        sort(va[i].begin(), va[i].end(), [&](const auto &a, const auto &b) {
            return dfn[a] < dfn[b];
        });
    }
}

ll get(int x, int k) {
    int lb = dfn[x], rb = rdfn[x];
    int id1, id2;
    {
        int left = 0, right = va[k].size();
        while (left < right) {
            int mid = left + right >> 1;
            if (dfn[va[k][mid]] >= lb) right = mid;
            else left = mid + 1;
        }
        id1 = left;
    }
    {
        int left = 0, right = va[k].size();
        while (left < right) {
            int mid = left + right >> 1;
            if (dfn[va[k][mid]] > rb) right = mid;
            else left = mid + 1;
        }
        id2 = left;
    }

    ll res = 0;
    for (int i = id1; i < id2; i++) res += sz[va[k][i]];
    return res;
}

void solve() {
    init();

    int cur = n + 1;
    while (m--) {
        int op, a;
        cin >> op >> a;
        if (op == 1) {
            cur = a;
        } else {
            if (dep[a] >= cur) {
                cout << sz[a] << "\n";
                continue;
            }

            cout << get(a, cur) << "\n";
        }
    }
}

void add(int u, int v) {
    g[u].push_back(v);
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v);
    }
    solve();

    return 0;
}