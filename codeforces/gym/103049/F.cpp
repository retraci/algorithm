#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <set>

using namespace std;

#define ll long long

typedef pair<ll, ll> pll;

const int N = 1e5 + 10;
int n, K;
pll va[N];
int nl[N], nr[N];
int vis[N];

void init() {
    va[0] = {-1e9 + 1, -1e9 - 1}, va[n + 1] = {1e9, 1e9 + 1};
    sort(va + 1, va + 1 + n);
    for (int i = 1; i <= n; i++) nl[i] = i - 1, nr[i] = i + 1;
}

struct Node {
    ll up, down;
    int x, y;

    bool operator<(const Node &that) const {
        return up * that.down - down * that.up > 0;
    }
};

void solve() {
    init();

    priority_queue<Node> que;
    for (int L = 0; L <= n; L++) {
        int R = L + 1;
        auto &[p1, v1] = va[L];
        auto &[p2, v2] = va[R];
        if (v1 - v2 > 0) que.push({p2 - p1, v1 - v2, L, R});
    }

    vis[0] = vis[n + 1] = 1;
    while (!que.empty()) {
        auto[_, __, L, R] = que.top(); que.pop();
        if (vis[L] || vis[R]) continue;
        vis[L] = vis[R] = 1;
        int LL = nl[L], RR = nr[R];
        nr[LL] = RR, nl[RR] = LL;

        if (LL == 0 || RR == n + 1) continue;

        auto &[p1, v1] = va[LL];
        auto &[p2, v2] = va[RR];
        if (v1 - v2 > 0) que.push({p2 - p1, v1 - v2, LL, RR});
    }

    int cnt = 0;
    for (int i = 1; i <= n; i++) cnt += !vis[i];
    cout << cnt << endl;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) cout << i << " ";
    }
    cout << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        ll p, v;
        cin >> p >> v;
        va[i] = {p, v};
    }
    solve();

    return 0;
}
