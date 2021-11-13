#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define ll long long

const int maxn = 1e5 + 10;

int n, m, t;
ll va[maxn], vb[maxn];

ll work(int type, int tot) {
    ll* vv;
    if (type) vv = va;
    else vv = vb;

    ll tar = 0;
    for (int i = 1; i <= tot; i++) tar += vv[i];
    tar /= tot;

    for (int i = 1; i <= tot; i++) vv[i] -= tar;
    for (int i = 1; i <= tot; i++) vv[i] += vv[i-1];

    nth_element(vv+1, vv+1+tot/2, vv+1+tot);
    ll median = vv[1+tot/2];

    ll res = 0;
    for (int i = 1; i <= tot; i++) res += abs(median - vv[i]);

    return res;
}

void solve() {
    if (t % n && t % m) {
        puts("impossible");
        return;
    }

    if (t % n == 0 && t % m == 0) {
        ll res = work(1, n) + work(0, m);
        printf("both %lld\n", res);
    } else if (t % n == 0) {
        ll res = work(1, n);
        printf("row %lld\n", res);
    } else {
        ll res = work(0, m);
        printf("column %lld\n", res);
    }
}

int main() {
    cin >> n >> m >> t;
    ll x, y;
    for (int i = 0; i < t; i++) {
        scanf("%lld%lld", &x, &y);
        va[x]++;
        vb[y]++;
    }
    solve();

    return 0;
}

