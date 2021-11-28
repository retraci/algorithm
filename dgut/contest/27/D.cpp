#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll n;
int times;

// 快速乘
ll qsc(ll a, ll b, ll m) {
    ll ans = 0;
    a %= m;
    while (b) {
        if (b & 1) {
            ans = (ans + a) % m;
            b--;
        }
        b >>= 1;
        a = (a + a) % m;
    }
    return ans;
}

// 快速幂
ll qsm(ll a, ll b, ll m) {
    ll ans = 1;
    a %= m;
    while (b) {
        if (b & 1) {
            ans = qsc(ans, a, m);
            b--;
        }
        b >>= 1;
        a = qsc(a, a, m);
    }
    return ans;
}

bool Miller_Rabin() {
    if (n == 2) return true;
    if (n < 2 || !(n & 1)) return false;
    ll m = n - 1;
    int k = 0;
    while ((m & 1) == 0) {
        k++;  // 这个k就是我们讲的时候的t
        m >>= 1;  // 这个m就是k
    }
    // Times就是我们事先定义的s（要找a的个数）
    for (int i = 0; i < times; i++) {
        ll a = rand() % (n - 1) + 1;  // 找一个[1,n-1]内的任意数
        ll x = qsm(a, m, n);
        ll y = 0;
        for (int j = 0; j < k; j++) {
            y = qsc(x, x, n);
            if (y == 1 && x != 1 && x != n - 1) return false;
            x = y;
        }
        if (y != 1) return false;
    }
    return true;
}

void solve() {
    times = 10;
    if (Miller_Rabin()) cout << "Yes" << endl;
    else cout << "No" << endl;
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
        cin >> n;
        solve();
    }

    return 0;
}