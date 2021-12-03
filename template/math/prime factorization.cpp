#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

/*----------------------------------------*/

const int N = 1e5 + 10;

ll ps[N], cs[N], tt;

void divide(ll n) {
    tt = 0;
    for (ll i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            ps[++tt] = i, cs[tt] = 0;
            while (n % i == 0) cs[tt]++, n /= i;
        }
    }
    if (n > 1) ps[++tt] = n, cs[tt] = 1;
}

// 埃筛
int vis[N];

void primes(int n) {
    memset(vis, 0, sizeof vis);
    vis[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (vis[i]) continue;
        for (int j = i; j <= n / i; j++) vis[i * j] = 1;
    }
}