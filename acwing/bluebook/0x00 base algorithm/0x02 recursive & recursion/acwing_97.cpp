#include <iostream>

using namespace std;

const int mod = 9901;

int a, b;

int qpow(int p, int c) {
    p %= mod;
    int res = 1;
    while (c) {
        if (c & 1) res = (res * p) % mod;
        p = (p * p) % mod;
        c >>= 1;
    }
    return res;
}

int sum(int p, int c) {
    if (c == 0) return 1;

    int res;
    if (c & 1) res = ((1 + qpow(p, (c + 1) / 2)) % mod * sum(p, (c - 1) / 2) % mod) % mod;
    else res = (((1 + qpow(p, c / 2)) % mod * sum(p, c / 2 - 1)) % mod + qpow(p, c)) % mod;

    return res;
}

void solve() {
    int ans = 1;
    for (int i = 2; i <= a; i++) {
        int cnt = 0;
        while (a % i == 0) {
            cnt++;
            a /= i;
        }
        if (cnt > 0) ans = (ans * sum(i, cnt * b)) % mod;
    }

    if (a == 0) ans = 0;
    cout << ans << endl;
}

int main() {
    cin >> a >> b;
    solve();

    return 0;
}

