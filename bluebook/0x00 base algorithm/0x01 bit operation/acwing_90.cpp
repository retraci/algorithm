#include <bits/stdc++.h>

using namespace std;

#define ll long long

ll a, b, p;

ll qmult(ll a, ll b) {
    ll res = 0;
    while (b) {
        if (b & 1) {
            res = (res + a) % p;
        }
        a = (a * 2) % p;
        b >>= 1;
    }

    return res;
}

void solve() {
    ll ans = qmult(a, b);

    cout << ans%p << endl;
}

int main() {
    cin >> a >> b >> p;
    solve();

    return 0;
}
