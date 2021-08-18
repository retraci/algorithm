#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

#define ll long long

struct Point {
    ll x, y;
};

const int maxn = 1010;

int tot;
ll vn[maxn], va[maxn], vb[maxn];

Point dfs(ll n, ll m) {
    if (n == 0) return {0, 0};
    ll cnt = 1LL << (2 * n - 2);
    ll len = 1LL << (n - 1);
    Point pos = dfs(n - 1, m % cnt);
    ll x = pos.x, y = pos.y;
    int idx = m / cnt;

    if (idx == 0) return {y, x};
    else if (idx == 1) return {x, y + len};
    else if (idx == 2) return {x + len, y + len};
    else if (idx == 3) return {-y + len - 1 + len, -x + len - 1};
}

void solve() {
    for (int i = 0; i < tot; i++) {
        ll n = vn[i], a = va[i] - 1, b = vb[i] - 1;
        Point p1 = dfs(n, a);
        Point p2 = dfs(n, b);

        ll dx = p1.x - p2.x, dy = p1.y - p2.y;
        double ans = sqrt(dx * dx + dy * dy) * 10;
        printf("%.0lf\n", ans);
    }
}

int main() {
    cin >> tot;
    for (int i = 0; i < tot; i++) {
        scanf("%lld%lld%lld", &vn[i], &va[i], &vb[i]);
    }
    solve();

    return 0;
}

