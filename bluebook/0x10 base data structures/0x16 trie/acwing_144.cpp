#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

typedef pair<int, int> pii;

const int N = 100010;

int n;
vector<pii> g[N];
int va[N];
int trie[N * 30][2], cnt[N * 30], tt;

void add(int u, int v, int w) {
    g[u].push_back({v, w});
}

void dfs(int u, int fa, int s) {
    va[u] = s;

    for (auto &[v, w] : g[u]) {
        if (v == fa) continue;
        dfs(v, u, s ^ w);
    }
}

void insert(int x) {
    int p = 0;
    for (int i = 30; i >= 0; i--) {
        int bi = x >> i & 1;
        int &s = trie[p][bi];
        if (!s) s = ++tt;
        p = s;
    }
    cnt[p]++;
}

int query(int x) {
    int p = 0, res = 0;
    for (int i = 30; i >= 0; i--) {
        int bi = x >> i & 1;
        if (trie[p][!bi]) {
            res += 1 << i;
            p = trie[p][!bi];
        } else {
            p = trie[p][bi];
        }
    }
    return res;
}

void solve() {
    dfs(0, -1, 0);

    for (int i = 0; i < n; i++) insert(va[i]);
    int ans = 0;
    for (int i = 0; i < n; i++) ans = max(ans, query(va[i]));

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    solve();

    return 0;
}