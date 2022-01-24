#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll x1, p1, x2, p2;

ll get(ll x) {
    ll res = 0;
    while (x) {
        res++;
        x /= 10;
    }
    return res;
}

void solve() {
    ll b1 = get(x1), b2 = get(x2);
    ll delta = abs(b1 - b2);

    if (delta > 7) {
        if (b1 > b2) cout << ">" << endl;
        else cout << "<" << endl;
        return;
    }

    if (b1 > b2) {
        p2 -= delta;
        for (int i = 0; i < delta; i++) x2 *= 10;
    } else {
        p1 -= delta;
        for (int i = 0; i < delta; i++) x1 *= 10;
    }

//    cout << b1 << " " << b2 << endl;
//    cout << p1 << " " << p2 << endl;
//    cout << x1 << " " << x2 << endl;

    if (p1 == p2) {
        if (x1 == x2) cout << "=" << endl;
        else if (x1 < x2) cout << "<" << endl;
        else cout << ">" << endl;
    } else if (p1 < p2) {
        cout << "<" << endl;
    } else {
        cout << ">" << endl;
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> x1 >> p1;
        cin >> x2 >> p2;
        solve();
    }

    return 0;
}