#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

const int N = 50010;
const int M = 1e6 + 10;

ll lb, rb;
bool st[M];
vector<ll> ps1, ps2;

void init() {
    memset(st, 0, sizeof st);
    for (int i = 2; i < N; i++) {
        if (st[i]) continue;
        ps1.push_back(i);
        for (int k = 2; k * i < N; k++) {
            st[i * k] = 1;
        }
    }
}

void solve() {
    memset(st, 0, sizeof st);
    for (ll p : ps1) {
        for (ll j = max(2 * p, (lb + p - 1) / p * p); j <= rb; j += p) {
            st[j - lb] = 1;
        }
    }
    ps2.clear();
    for (int i = 0; i < rb - lb + 1; i++) {
        if (!st[i] && i + lb >= 2) ps2.push_back(i + lb);
    }

    if (ps2.size() < 2) {
        puts("There are no adjacent primes.");
        return;
    }

    int a, b, c, d;
    ll mi = 1e15, mx = 0;
    for (int i = 1; i < ps2.size(); i++) {
        if (mi > ps2[i] - ps2[i - 1]) {
            mi = ps2[i] - ps2[i - 1];
            a = ps2[i - 1], b = ps2[i];
        }
        if (mx < ps2[i] - ps2[i - 1]) {
            mx = ps2[i] - ps2[i - 1];
            c = ps2[i - 1], d = ps2[i];
        }
    }

    printf("%d,%d are closest, %d,%d are most distant.\n", a, b, c, d);
}

int main() {
    freopen("../in.txt", "r", stdin);

    init();
    while (~scanf("%lld%lld", &lb, &rb)) {
        solve();
    }

    return 0;
}