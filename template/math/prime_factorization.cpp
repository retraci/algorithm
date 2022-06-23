// region 质因数分解
vector<pll> divide(ll x) {
    vector<pll> res;
    for (int i = 2; i <= x / i; i++) {
        if (x % i == 0) {
            int c = 0;
            while (x % i == 0) x /= i, c++;
            res.push_back({i, c});
        }
    }
    if (x > 1) res.push_back({x, 1});

    return res;
}
// endregion

// region 质因数分解, 枚举最小质数 (x < N)
vector<int> isp, mip, pr;

void init_prime(int lim) {
    isp = vector<int>(lim + 1, 1);
    mip.resize(lim + 1);

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

vector<pii> divide(int x) {
    vector<pii> res;
    res.clear();
    while (x > 1) {
        int p = mip[x];
        int c = 0;
        while (x % p == 0) x /= p, c++;
        res.push_back({p, c});
    }

    return res;
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

// region [1, x]里 与 y 互质的个数
// fs 为 y 分解质因数的结果
ll calc(ll x, const vector<pll> &fs) {
    ll s = 0;
    int lim = 1 << fs.size();
    for (int mask = 1; mask < lim; mask++) {
        ll t = 1, c = 0;
        for (int i = 0; i < fs.size(); i++) {
            if (mask >> i & 1) {
                t *= fs[i].fi;
                c++;
            }
        }

        int sgn = c & 1 ? 1 : -1;
        s += sgn * x / t;
    }

    return x - s;
}
// endregion

// region 埃筛
vector<int> isp, ps;

void init_prime(int lim) {
    isp = vector<int>(lim + 1, 1);

    isp[0] = isp[1] = 0;
    for (int i = 2; i <= lim; i++) {
        if (!isp[i]) continue;

        ps.push_back(i);
        for (int j = i * 2; j <= lim; j += i) isp[j] = 0;
    }
}
// endregion86

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

// region 欧拉函数 (埃筛)
vector<int> phi;

void init_prime(int lim) {
    phi.resize(lim + 1);
    iota(phi.begin(), phi.end(), 0);

    for (int i = 2; i <= lim; i++) {
        if (phi[i] != i) continue;

        for (int j = i; j <= lim; j += i) phi[j] = phi[j] / i * (i - 1);
    }
}
// endregion

// region 欧拉筛
vector<int> isp, pr;

void init_prime(int lim) {
    isp = vector<int>(lim + 1, 1);

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

// region 欧拉函数 (线性筛)
vector<int> isp, pr, phi;

void init_prime(int lim) {
    isp = vector<int>(lim + 1, 1);
    phi.resize(lim + 1);

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

// region 莫比乌斯函数 (线性筛)
vector<int> isp, pr, mu;

void init_prime(int lim) {
    isp = vector<int>(lim + 1, 1);
    mu.resize(lim + 1);

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

// region 积性函数 (线性筛)
vector<int> isp, pr, low, f;

void init_prime(int lim) {
    isp = vector<int>(lim + 1, 1);
    low.resize(lim + 1), f.resize(lim + 1);

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
