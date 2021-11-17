#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <unordered_map>

using namespace std;

#define ll long long

struct Edge {
    ll from, to, cost;
    bool operator< (const Edge &that) const {
        return cost > that.cost;
    }
};

const int N = 2e5 + 10;

ll n, m, q;
Edge es[N];
ll qs[N];
int fa[N], sz[N];
ll ans[N];
int idx[N];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

bool cmp(int a, int b) {
    return qs[a] > qs[b];
}

ll Ck2(ll k) {
    return k * (k - 1) / 2;
}

void solve() {
    for (int i = 0; i < q; i++) idx[i] = i;
    sort(es, es + m);
    sort(idx, idx + q, cmp);

    for (int i = 0; i < n; i++) fa[i] = i, sz[i] = 1;
    int ptr = 0;
    ll cur = 0;
    for (int i = 0; i < q; i++) {
        int dam = qs[idx[i]];
        while (ptr < m && es[ptr].cost >= dam) {
            int tx = find(es[ptr].from), ty = find(es[ptr].to);
            ptr++;
            if (tx == ty) continue;
            if (sz[ty] < sz[tx]) swap(tx, ty);
            cur -= Ck2(sz[tx]) + Ck2(sz[ty]);
            fa[tx] = ty;
            sz[ty] += sz[tx];
            cur += Ck2(sz[ty]);
        }

        ans[idx[i]] = cur;
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m >> q;
        for (int i = 0; i < m; i++) {
            ll a, b, c;
            scanf("%lld%lld%lld", &a, &b, &c);
            a--, b--;
            es[i] = {a, b, c};
        }
        for (int i = 0; i < q; i++) {
            scanf("%lld", &qs[i]);
        }
        solve();
    }

    return 0;
}
