#include <bits/stdc++.h>

using namespace std;

#define ll long long

ll a, b, p;

ll qpow(ll a, ll b) {
    ll res = a;
    b--;
    while (b) {
        if (b & 1) {
            res = (res * a) % p;
        }
        a = (a * a) % p;
        b >>= 1;
    }

    return res;
}

void solve() {
    ll ans;
    if (b != 0) ans = qpow(a, b);
    else ans = 1;

    cout << ans%p << endl;
}

int main() {
    cin >> a >> b >> p;
    solve();

    return 0;
}
