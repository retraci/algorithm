#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>

using namespace std;

const int N = 110;

// 有向图 缩点
int n, m;
vector<int> g[N];
int dfn[N], low[N], num;
stack<int> stk;
int in_stk[N];

int scc, c[N];
vector<int> gc[N];

int in[N], out[N];

void add(int u, int v) {
    g[u].push_back(v);
}

void add_c(int u, int v) {
    gc[u].push_back(v);
    in[v]++, out[u]++;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++num;
    stk.push(u), in_stk[u] = 1;
    for (int v: g[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (in_stk[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (dfn[u] == low[u]) {
        ++scc;
        int v;
        do {
            v = stk.top(); stk.pop();
            in_stk[v] = 0;
            c[v] = scc;
        } while (v != u);
    }
}

void suodian() {
    for (int u = 1; u <= n; u++) {
        for (int v : g[u]) {
            if (c[u] == c[v]) continue;
            add_c(c[u], c[v]);
        }
    }
}

void solve() {
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) tarjan(i);
    }
    suodian();

    int cnt1 = 0, cnt2 = 0;
    for (int i = 1; i <= scc; i++) {
        cnt1 += in[i] == 0;
        cnt2 += out[i] == 0;
    }

    cout << cnt1 << endl;
    cout << (scc == 1 ? 0 : max(cnt1, cnt2)) << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int v;
        while (cin >> v, v) {
            add(i, v);
        }
    }
    solve();

    return 0;
}