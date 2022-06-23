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

// region bsgs
ll bsgs(ll a, ll b, ll m) {
    static unordered_map<ll, ll> mp;

    if (1 % m == b % m) return 0;
    mp.clear();
    ll k = sqrt(m) + 1;
    for (ll y = 0, c = b % m; y <= k - 1; y++) {
        mp[c] = y;
        c = c * a % m;
    }

    ll ak = 1;
    for (int i = 1; i <= k; i++) ak = ak * a % m;

    for (ll x = 1, c = ak; x <= k; x++) {
        if (mp.count(c)) return x * k - mp[c];
        c = c * ak % m;
    }

    return -1e18;
}
// endregion

// region exbsgs
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }

    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

ll bsgs(ll a, ll b, ll m) {
    static unordered_map<ll, ll> mp;

    if (1 % m == b % m) return 0;
    mp.clear();
    ll k = sqrt(m) + 1;
    for (ll y = 0, c = b % m; y <= k - 1; y++) {
        mp[c] = y;
        c = c * a % m;
    }

    ll ak = 1;
    for (int i = 1; i <= k; i++) ak = ak * a % m;

    for (ll x = 1, c = ak; x <= k; x++) {
        if (mp.count(c)) return x * k - mp[c];
        c = c * ak % m;
    }

    return -1e18;
}

ll exbsgs(ll a, ll b, ll m) {
    b = (b % m + m) % m;
    if (1 % m == b % m) return 0;
    ll d = __gcd(a, m);
    if (d == 1) return bsgs(a, b, m);

    if (b % d) return -1e18;
    ll x, y;
    exgcd(a / d, m / d, x, y);
    return exbsgs(a, b / d * x % (m / d), m / d) + 1;
}
// endregion
