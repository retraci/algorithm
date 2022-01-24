// region 质因数分解
ll ps[N], cs[N], tt;

void divide(ll x) {
    tt = 0;
    for (ll i = 2; 1LL * i * i <= x; i++) {
        if (x % i == 0) {
            ps[++tt] = i, cs[tt] = 0;
            while (x % i == 0) cs[tt]++, x /= i;
        }
    }
    if (x > 1) ps[++tt] = x, cs[tt] = 1;
}
// endregion

// region 埃筛
int vis[N];

void primes(int lim) {
    memset(vis, 0, sizeof vis);
    vis[1] = 1;
    for (int i = 2; i <= lim; i++) {
        if (vis[i]) continue;
        for (int j = i; j <= lim / i; j++) vis[i * j] = 1;
    }
}
// endregion

// region 欧拉函数
int phi[N];

ll euler(ll x) {
    int res = x;

    for (int i = 2; 1LL * i * i <= x; i++) {
        if (x % i == 0) {
            res = res / i * (i - 1);
            while (x % i == 0) x /= i;
        }
    }
    if (x > 1) res = res / x * (x - 1);

    return res;
}
// endregion