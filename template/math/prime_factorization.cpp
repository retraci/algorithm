// region 质因数分解
vector<pll> fs;

void divide(ll x) {
    fs = {};
    for (int i = 2; i <= x / i; i++) {
        if (x % i == 0) {
            int c = 0;
            while (x % i == 0) x /= i, c++;
            fs.push_back({i, c});
        }
    }
    if (x > 1) fs.push_back({x, 1});
}
// endregion

// region 质因数分解, 枚举质数
int isp[N];
vector<int> pr;

void prime(int lim) {
    fill(isp, isp + lim + 1, 1);

    isp[0] = isp[1] = 0;
    for (int i = 2; i <= lim; i++) {
        if (isp[i]) pr.push_back(i);

        for (int p : pr) {
            if (p > lim / i) break;

            isp[i * p] = 0;
            if (i % p == 0) break;
        }
    }
}

vector<pll> fs;

void divide(ll x) {
    fs = {};
    for (int p : pr) {
        if (p > x / p) break;

        if (x % p == 0) {
            int c = 0;
            while (x % p == 0) x /= p, c++;
            fs.push_back({p, c});
        }
    }
    if (x > 1) fs.push_back({x, 1});
}
// endregion

// region 质因数分解, 枚举最小质数 (x < N)
int isp[N], mip[N];
vector<int> pr;

void prime(int lim) {
    fill(isp, isp + lim + 1, 1);

    isp[0] = isp[1] = 0;
    for (int i = 2; i <= lim; i++) {
        if (isp[i]) {
            pr.push_back(i);
            mip[i] = i;
        }

        for (int p : pr) {
            if (p > lim / i) break;

            mip[i * p] = p;
            isp[i * p] = 0;
            if (i % p == 0) break;
        }
    }
}

vector<pii> fs;

void divide(int x) {
    fs = {};
    while (x > 1) {
        int p = mip[x];
        int c = 0;
        while (x % p == 0) x /= p, c++;
        fs.push_back({p, c});
    }
}
// endregion

// region 枚举约数
vector<ll> ds;

void dfs(int u, ll cur) {
    if (u == fs.size()) {
        ds.push_back(cur);
        return;
    }

    auto [p, c] = fs[u];
    for (int i = 0; i <= c; i++) {
        dfs(u + 1, cur);
        cur *= p;
    }
}

// endregion

// region 埃筛
int isp[N];
vector<int> ps;

void prime(int lim) {
    fill(isp, isp + lim + 1, 1);

    isp[0] = isp[1] = 0;
    for (int i = 2; i <= lim; i++) {
        if (!isp[i]) continue;

        ps.push_back(i);
        for (int j = i * 2; j <= lim; j += i) isp[j] = 0;
    }
}
// endregion

// region 欧拉函数
ll eula(ll x) {
    ll res = x;

    for (ll i = 2; i <= x / i; i++) {
        if (x % i == 0) {
            res = res / i * (i - 1);
            while (x % i == 0) x /= i;
        }
    }
    if (x > 1) res = res / x * (x - 1);

    return res;
}
// endregion

// region 欧拉函数(埃筛)
int phi[N];

void prime(int lim) {
    iota(phi, phi + lim + 1, 0);

    for (int i = 2; i <= lim; i++) {
        if (phi[i] != i) continue;

        for (int j = i; j <= lim; j += i) phi[j] = phi[j] / i * (i - 1);
    }
}
// endregion

// region 扩欧
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }

    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}
// endregion

// region 中国剩余定理
int n;
ll a[N], m[N];

ll crt() {
    ll a1 = a[1], m1 = m[1];
    for (int i = 2; i <= n; i++) {
        ll a2 = a[i], m2 = m[i];
        ll k1, k2;
        ll d = exgcd(m1, m2, k1, k2);
        if ((a2 - a1) % d) return -1;

        k1 *= (a2 - a1) / d;
        ll tmp = m2 / d;
        k1 = (k1 % tmp + tmp) % tmp;

        a1 = k1 * m1 + a1;
        m1 = m1 / d * m2;
    }

    ll x = (a1 % m1 + m1) % m1;
    return x;
}
// endregion

// region 欧拉筛
int isp[N];
vector<int> pr;

void prime(int lim) {
    fill(isp, isp + lim + 1, 1);

    isp[0] = isp[1] = 0;
    for (int i = 2; i <= lim; i++) {
        if (isp[i]) pr.push_back(i);

        for (int p : pr) {
            if (p > lim / i) break;

            isp[i * p] = 0;
            if (i % p == 0) break;
        }
    }
}
// endregion

// region 欧拉函数(欧拉筛)
int isp[N];
vector<int> pr;
int phi[N];

void prime(int lim) {
    fill(isp, isp + lim + 1, 1);

    phi[1] = 1;
    isp[0] = isp[1] = 0;
    for (int i = 2; i <= lim; i++) {
        if (isp[i]) {
            pr.push_back(i);
            phi[i] = i - 1;
        }

        for (int p : pr) {
            if (p > lim / i) break;

            isp[i * p] = 0;
            if (i % p == 0) {
                phi[i * p] = phi[i] * p;
                break;
            } else {
                phi[i * p] = phi[i] * phi[p];
            }
        }
    }
}
// endregion

// region 莫比乌斯函数(欧拉筛)
int isp[N];
vector<int> pr;
int mu[N];

void prime(int lim) {
    fill(isp, isp + lim + 1, 1);

    mu[1] = 1;
    isp[0] = isp[1] = 0;
    for (int i = 2; i <= lim; i++) {
        if (isp[i]) {
            pr.push_back(i);
            mu[i] = -1;
        }

        for (int p : pr) {
            if (p > lim / i) break;

            isp[i * p] = 0;
            if (i % p == 0) {
                mu[i * p] = 0;
                break;
            }
            mu[i * p] = -mu[i];
        }
    }
}
// endregion

// region 积性函数(欧拉筛)
int isp[N];
vector<int> pr;
int low[N], f[N];

void prime(int lim) {
    fill(isp, isp + lim + 1, 1);

    f[1] = 1;
    isp[0] = isp[1] = 0;
    for (int i = 2; i <= lim; i++) {
        if (isp[i]) {
            pr.push_back(i);
            low[i] = i;
            // 待修
            f[i] = 2 * i - 1;
        }

        for (int p : pr) {
            if (p > lim / i) break;

            isp[i * p] = 0;
            low[i * p] = p;
            if (i % p == 0) {
                low[i * p] = low[i] * p;
                // 待修
                if (low[i] == i) {
                    f[i * p] = 1LL * f[i] * p % MOD + phi[i * p];
                    f[i * p] %= MOD;
                } else {
                    f[i * p] = 1LL * f[low[i] * p] * f[i / low[i]] % MOD;
                }
                break;
            }
            f[i * p] = 1LL * f[i] * f[p] % MOD;
        }
    }
}
// endregion