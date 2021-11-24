#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 42767;

int n;
int v[N], prime[N], tt;

void primes(int n) {
    memset(v, 0, sizeof v);
    tt = 0;
    for (int i = 2; i <= n; i++) {
        if (v[i] == 0) {
            v[i] = i;
            prime[++tt] = i;
        }
        for (int j = 1; j <= tt; j++) {
            if (prime[j] > v[i] || prime[j] > n / i)break;
            v[i * prime[j]] = prime[j];
        }
    }
}

void solve() {
    primes(n);

    int ans = 0;
    for (int i = 1; i <= tt; i++) {
        for (int j = i; j <= tt; j++) {
            if (prime[i] + prime[j] == n) ans++;
        }
    }

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n;
    solve();

    return 0;
}