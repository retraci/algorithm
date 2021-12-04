#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

/*----------------------------------------*/

const int N = 1e5 + 10;

ll ps[N], cs[N], tt;

void divide(ll x) {
    tt = 0;
    for (ll i = 2; 1LL * i * i <= x; i++) {
        if (x % i == 0) {
            ps[++tt] = i, cs[tt] = 0;
            while (x % i == 0) cs[tt]++, x /= i;
        }
    }
    if (x > 1) ps[++tt] = x, cs[tt] = 1;
}

// 埃筛
int vis[N];

void primes(int lim) {
    memset(vis, 0, sizeof vis);
    vis[1] = 1;
    for (int i = 2; i <= lim; i++) {
        if (vis[i]) continue;
        for (int j = i; j <= lim / i; j++) vis[i * j] = 1;
    }
}