#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

const ll MOD = 9901;

ll a, b;
ll ps[20], cs[20], tt;

void getPrimFactor(int n) {
    tt = 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            int cnt = 0;
            while (n % i == 0) {
                cnt++;
                n /= i;
            }
            ps[tt] = i, cs[tt++] = cnt;
        }
    }
    if (n > 1) ps[tt] = n, cs[tt++] = 1;
}

ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

void solve() {
    if (a == 0) { cout << 0 << endl; return; }
    if (b == 0) { cout << 1 << endl; return; }

    getPrimFactor(a);

    ll ans = 1;
    for (int i = 0; i < tt; i++) {
        int p = ps[i], c = cs[i];
        if ((p - 1) % MOD == 0) {
            ll tmp = (b * c + 1) % MOD;
            ans = ans * tmp % MOD;
            continue;
        }

        ll x = (qpow(p, b * c + 1) - 1 + MOD) % MOD;
        ll y = p - 1;
        ll inv = qpow(y, MOD - 2);

//        cout << p << " " << c << endl;
//        cout << x << " " << y << " " << inv << endl;

        ans = ans * x % MOD * inv % MOD;
    }
    cout << ans << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> a >> b;
    solve();

    return 0;
}