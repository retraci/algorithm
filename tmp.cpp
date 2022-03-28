#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <ext/pb_ds/priority_queue.hpp>

using namespace std;
using namespace std;
#define N 400050
#define M 400050
#define inf 2147483647
typedef long long ll;

__attribute__((optimize("-O3")))inline char nc() {
    static char buf[100000], *p1, *p2;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

__attribute__((optimize("-O3")))int rd() {
    int x = 0;
    char s = nc();
    while (s < '0' || s > '9') s = nc();
    while (s >= '0' && s <= '9') x = (x << 3) + (x << 1) + s - '0', s = nc();
    return x;
}

char pbuf[100000], *pp = pbuf;

__attribute__((optimize("-O3")))void push(const char c) {
    if (pp - pbuf == 100000) fwrite(pbuf, 1, 100000, stdout), pp = pbuf;
    *pp++ = c;
}

__attribute__((optimize("-O3")))void write(int x) {
    static int sta[35];
    int top = 0;
    do { sta[top++] = x % 10, x /= 10; } while (x);
    while (top) push(sta[--top] + '0');
}

int head[N], to[M << 1], nxt[M << 1], cnt, f[23][N], mn[N], val[M << 1], n, m, dis[N], vis[N], Lg[N];
int fa[N], w[N];

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

struct E {
    int x, y, z, w;

    bool operator<(const E &u) const {
        return w > u.w;
    }
} e[M];

__gnu_pbds::priority_queue<pair<int, int> > q;

__attribute__((optimize("-O3")))inline void add(int u, int v) {
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

__attribute__((optimize("-O3")))void add(int u, int v, int w) {
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
    val[cnt] = w;
}

__attribute__((optimize("-O3")))void dij() {
    int i;
    for (i = 1; i <= n; i++) dis[i] = 2147483647;
    dis[1] = 0;
    memset(vis, 0, sizeof(vis));
    q.push(make_pair(0, 1));
    while (!q.empty()) {
        int x = q.top().second, i;
        q.pop();
        if (vis[x]) continue;
        vis[x] = 1;
        if (dis[x] == inf) continue;
        for (i = head[x]; i; i = nxt[i]) {
            if (dis[to[i]] > dis[x] + val[i]) {
                dis[to[i]] = dis[x] + val[i];
                q.push(make_pair(-dis[to[i]], to[i]));
            }
        }
    }
}

__attribute__((optimize("-O3")))void dfs(int x) {
    int i;
    if (x <= n) mn[x] = dis[x];
    else mn[x] = inf;
    for (i = head[x]; i; i = nxt[i]) {
        f[0][to[i]] = x;
        dfs(to[i]);
        mn[x] = min(mn[x], mn[to[i]]);
    }
}

__attribute__((optimize("-O3")))void solve() {
    memset(head, 0, sizeof(head));
    cnt = 0;
    memset(f, 0, sizeof(f));
    n = rd();
    m = rd();
    int i, x, y, j;
    for (i = 1; i <= m; i++) {
        e[i].x = rd();
        e[i].y = rd();
        e[i].z = rd();
        e[i].w = rd();
        add(e[i].x, e[i].y, e[i].z);
        add(e[i].y, e[i].x, e[i].z);
    }
    dij();

    memset(head, 0, sizeof(head));
    cnt = 0;
    sort(e + 1, e + m + 1);
    for (Lg[0] = -1, i = 1; i <= 2 * n; i++) fa[i] = i, Lg[i] = Lg[i >> 1] + 1;
    int tot = n;
    for (i = 1; i <= m; i++) {
        int dx = find(e[i].x), dy = find(e[i].y);
        if (dx == dy) continue;

        tot++;
        fa[dx] = tot;
        fa[dy] = tot;
        add(tot, dx);
        add(tot, dy);
        w[tot] = e[i].w;
    }
    dfs(tot);

    for (i = 1; (1 << i) <= tot; i++) {
        for (j = 1; j <= tot; j++) {
            f[i][j] = f[i - 1][f[i - 1][j]];
        }
    }
    int opt, cas, S;
    cas = rd();
    opt = rd();
    S = rd();
    int ans = 0;
    while (cas--) {
        x = rd();
        y = rd();
        x = (ll(x) + opt * ans - 1) % n + 1;
        y = (ll(y) + opt * ans) % (S + 1);

        cout << x << " " << y << "\n";

        for (i = Lg[tot]; i >= 0; i--) {
            if (!f[i][x]) continue;
            if (w[f[i][x]] > y) x = f[i][x];
        }
        ans = mn[x];
        write(ans);
        push('\n');
    }
}

__attribute__((optimize("-O3")))int main() {
#ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../out.txt", "w", stdout);
#endif

    int T;
    T = rd();
    while (T--) solve();
    fwrite(pbuf, 1, pp - pbuf, stdout);
}