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

#define N 200050
using namespace std;

int read() {
    int cnt = 0, f = 1;
    char ch = 0;
    while (!isdigit(ch)) {
        ch = getchar();
        if (ch == '-') f = -1;
    }
    while (isdigit(ch)) cnt = (cnt << 3) + (cnt << 1) + (ch - '0'), ch = getchar();
    return cnt * f;
}

const int inf = 0x3fffffff;
vector<int> v[N];
int mx;
int first[N], nxt[N], to[N], tot;

void add(int x, int y) { nxt[++tot] = first[x], first[x] = tot, to[tot] = y; }

int n, root, m, a[N], rt[N], cnt, lastans;
int dep[N], st[N], ed[N], sign;
struct Node {
    int ls, rs, val;
} t[N * 30];

void Build(int &x, int l, int r) {
    x = ++cnt;
    t[x].val = inf;
    if (l == r) return;
    int mid = (l + r) >> 1;
    Build(t[x].ls, l, mid);
    Build(t[x].rs, mid + 1, r);
}

void Insert(int &x, int last, int l, int r, int pos, int val) {
    x = ++cnt;
    t[x] = t[last];
    t[x].val = min(t[x].val, val);
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (pos <= mid) Insert(t[x].ls, t[last].ls, l, mid, pos, val);
    else Insert(t[x].rs, t[last].rs, mid + 1, r, pos, val);
}

int Quary(int x, int l, int r, int L, int R) {
    if (L <= l && r <= R) return t[x].val;
    int mid = (l + r) >> 1, ans = inf;
    if (L <= mid) ans = min(ans, Quary(t[x].ls, l, mid, L, R));
    if (R > mid) ans = min(ans, Quary(t[x].rs, mid + 1, r, L, R));
    return ans;
}

void dfs(int u, int fa) {
    st[u] = ++sign;
    v[dep[u]].push_back(u);
    mx = max(mx, dep[u]);
    for (int i = first[u]; i; i = nxt[i]) {
        int t = to[i];
        if (t == fa) continue;
        dep[t] = dep[u] + 1;
        dfs(t, u);
    }
    ed[u] = sign;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    n = read(), root = read();
    Build(rt[0], 1, n);
    for (int i = 1; i <= n; i++) a[i] = read();
    for (int i = 1; i < n; i++) {
        int x = read(), y = read();
        add(x, y);
        add(y, x);
    }
    dep[root] = 1;
    dfs(root, 0);
    for (int i = 1; i <= mx; i++) {
        rt[i] = rt[i - 1];
        for (int j = 0; j < v[i].size(); j++) {
            cout << i << " " << st[v[i][j]] << " " << a[v[i][j]] << "\n";
            Insert(rt[i], rt[i], 1, n, st[v[i][j]], a[v[i][j]]);
        }
    }
    m = read();
    while (m--) {
        int u = (read() + lastans) % n + 1, k = (read() + lastans) % n;
        int d = min(mx, dep[u] + k);
        cout << d << " " << st[u] << " " << ed[u] << "\n";
        lastans = Quary(rt[d], 1, n, st[u], ed[u]);
        printf("%d\n", lastans);
    }
    return 0;
}