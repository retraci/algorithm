#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

struct Edge {
    int u, v, w;
    bool operator< (const Edge &that) const {
        return w < that.w;
    }
};

const int N = 10010, M = 500010;

int n, m;
Edge es[M];
int mp[M], tt;
int vis[M];
int fa[N], sz[N];

template<typename T>
inline void rd(T &x) {
    T ret = 0, sgn = 1;
    char c = getchar();
    while (!isdigit(c)) sgn = (c == '-' ? -1 : 1), c = getchar();
    while (isdigit(c)) ret = (ret << 3) + (ret << 1) + c - '0', c = getchar();
    x = (sgn == -1 ? -ret : ret);
}

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

bool check(int mid) {
    for (int i = 1; i <= n; i++) fa[i] = i, sz[i] = 1;
    int cnt = 0;

    for (int i = mid; i <= m; i++) {
        auto &[u, v, w] = es[i];
        int fu = find(u), fv = find(v);
        if (fu == fv) continue;
        fa[fu] = fv;
        if (++cnt == n - 1) break;
    }

    return cnt == n - 1;
}

void solve() {
    sort(es + 1, es + 1 + m);
    for (int i = 1; i <= m; i++) {
        if (vis[es[i].w]) continue;
        mp[++tt] = i;
    }

    int left = 1, right = tt;
    while (left < right) {
        int mid = left + right + 1 >> 1;
        if (check(mid)) left = mid;
        else right = mid - 1;
    }

    vector<int> tmp;
    for (int i = 1; i <= n; i++) fa[i] = i, sz[i] = 1;
    int cnt = 0;
    for (int i = left; i <= m; i++) {
        auto &[u, v, w] = es[i];
        int fu = find(u), fv = find(v);
        if (fu == fv) continue;
        tmp.push_back(i);
        fa[fu] = fv;
        if (++cnt == n - 1) break;
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) fa[i] = i, sz[i] = 1;
    for (int i = tmp.size() - 1; i >= 0; i--) {
        auto &[u, v, w] = es[tmp[i]];
        int fu = find(u), fv = find(v);
        if (fu == fv) continue;

        ans += 1LL * sz[fu] * sz[fv] * w;

        fa[fu] = fv;
        sz[fv] += sz[fu];
        if (++cnt == n - 1) break;
    }

    printf("%lld\n", ans);
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    rd(n), rd(m);
    for (int i = 1; i <= m; i++) {
        rd(es[i].u);
        rd(es[i].v);
        rd(es[i].w);
    }
    solve();

    return 0;
}