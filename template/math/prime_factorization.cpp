// region 质因数分解
vector<pii> ps;

void divide(ll x) {
    ps = {};
    for (int i = 2; 1LL * i * i <= x; i++) {
        if (x % i == 0) {
            int cnt = 0;
            while (x % i == 0) x /= i, cnt++;
            ps.push_back({i, cnt});
        }
    }
    if (x > 1) ps.push_back({x, 1});
}
// endregion

// region 埃筛
int vis[N];

void primes(int lim) {
    memset(vis, 0, sizeof vis);
    vis[1] = 1;
    for (int i = 2; i <= lim; i++) {
        if (vis[i]) continue;

        for (int j = i; j <= lim; j += i) vis[j] = 1;
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