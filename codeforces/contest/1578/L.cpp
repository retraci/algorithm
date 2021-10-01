#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

const int N = 1e5 + 10;

ll n, m;
ll va[N];
ll fa[N], s[N], d[N];

struct Edge {
    ll a, b, c;
    bool operator< (const Edge &that) const {
        return c > that.c;
    }
};

Edge es[N];

ll find(ll x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

void solve() {
    sort(es + 1, es + m + 1);
    for (int i = 1; i <= n; i++) {
        fa[i] = i, s[i] = va[i], d[i] = 1e9;
    }

    for (int i = 1; i <= m; i++) {
        auto &[a, b, c] = es[i];

        ll fx = find(a), fy = find(b);
        if (fx == fy) continue;

        ll tmp = max(c - s[fx], c - s[fy]);
        d[fy] = min({d[fx], d[fy], tmp});
        fa[fx] = fy;
        s[fy] += s[fx];
    }

    ll ans = d[find(1)];
    cout << (ans <= 0 ? -1 : ans) << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> va[i];
    for (int i = 1; i <= m; i++) cin >> es[i].a >> es[i].b >> es[i].c;
    solve();

    return 0;
}