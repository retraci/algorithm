// 试题 历届试题 数字游戏

#include <bits/stdc++.h>

using namespace std;

#define ll long long

ll n, k, T;

void solve() {
    ll ret = 0;

    ll cur = 1;
    ll s = 1;
    for (int i = 0; i < T; i++) {
        ret += cur % k;

        ll tmp = (s * n + n * (n - 1) / 2) % k;
        s = (s + n) % k;
        cur = (cur + tmp) % k;
    }

    cout << ret << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> n >> k >> T;
    solve();

    return 0;
}