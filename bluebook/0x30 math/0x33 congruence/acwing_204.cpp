#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

const int N = 30;

int n;
ll as[N], ms[N];

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1, y = 0; return a; }
    ll d = exgcd(b, a % b, x, y);
    ll z = x; x = y; y = z - a / b * y;
    return d;
}

ll mod(ll a, ll b) {
    return (a % b + b) % b;
}

void solve() {
    ll a1 = as[0], m1 = ms[0];
    for (int i = 1, a2, m2; i < n; i++) {
        a2 = as[i], m2 = ms[i];
        ll k1, k2, d = exgcd(a1, -a2, k1, k2);
        if ((m2 - m1) % d) { cout << -1 << endl; return; }

        k1 = mod(k1 * (m2 - m1) / d, abs(a2 / d));
        m1 = k1 * a1 + m1;
        a1 = abs(a1 / d * a2);
    }
    cout << m1 << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> n;
    for (int i = 0; i < n; i++) {
        scanf("%lld%lld", &as[i], &ms[i]);
    }
    solve();

    return 0;
}