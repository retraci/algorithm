#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 2e5 + 10;

int n, m;
vector<int> g[N];
int fa[N];

void add(int u, int v) {
    g[u].push_back(v);
}

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void solve() {
    for (int i = 1; i <= n; i++) fa[i] = i;

    vector<int> ans;
    int cur = 0;
    for (int i = n; i >= 1; i--) {
        ans.push_back(cur++);
        for (auto v: g[i]) {
            if (v < i) continue;
            int tx = find(i), ty = find(v);
            if (tx == ty) continue;
            fa[tx] = ty;
            cur--;
        }
    }

    reverse(ans.begin(), ans.end());
    for (int x: ans) cout << x << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v), add(v, u);
    }
    solve();

    return 0;
}