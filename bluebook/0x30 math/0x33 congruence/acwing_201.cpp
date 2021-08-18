#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1010;

int Ti;
int n;
int phi[N];

int euler(int x) {
    int res = x;

    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            res = res / i * (i - 1);
            while (x % i == 0) x /= i;
        }
    }
    if (x > 1) res = res / x * (x - 1);

    return res;
}

void init() {
    for (int i = 2; i < N; i++) phi[i] = euler(i);
}

void solve() {
    if (n == 1) {
        printf("%d %d %d\n", ++Ti, n, 3);
        return;
    }

    long long ans = 0;
    for (int i = 2; i <= n; i++) ans += phi[i] * 2;
    ans += 3;

    printf("%d %d %d\n", ++Ti, n, ans);
}

int main() {
    freopen("../in.txt", "r", stdin);

    init();
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        solve();
    }

    return 0;
}