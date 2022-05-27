// 整数拼接

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

const int N = 1e5 + 10;

int n, K;
int va[N];
int cnt[11][N];

int calc(int x) {
    int res = 0;
    while (x) {
        res++;
        x /= 10;
    }

    return res;
}

ll work() {
    ll res = 0;
    for (int i = 0; i < n; i++) {
        int a = calc(va[i]);
        int b = (K - va[i] % K) % K;
        res += cnt[a][b];

        ll cur = va[i] % K;
        for (int j = 0; j <= 10; j++) {
            cnt[j][cur]++;
            cur = (cur * 10) % K;
        }
    }

    return res;
}

void solve() {
    ll ans = 0;

    memset(cnt, 0, sizeof cnt);
    ans += work();

    reverse(va, va + n);
    memset(cnt, 0, sizeof cnt);
    ans += work();

    cout << ans << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> n >> K;
    for (int i = 0; i < n; i++) {
        scanf("%d", &va[i]);
    }
    solve();

    return 0;
}