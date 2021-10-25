#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 200000 + 10;

int n;
int va[N];
int cnt[31];

void calc(int x) {
    for (int i = 30; i >= 0; i--) {
        int bi = x >> i & 1;
        if (bi) cnt[i]++;
    }
}

void solve() {
    memset(cnt, 0, sizeof cnt);
    for (int i = 1; i <= n; i++) {
        calc(va[i]);
    }

    int mx = -1;
    int flag = 0;
    for (int i = 0; i <= 30; i++) {
        if (cnt[i] == 0) continue;
        flag = 1;
        if (mx == -1) {
            mx = cnt[i];
            continue;
        }
        mx = __gcd(mx, cnt[i]);
    }

    if (!flag) {
        for (int i = 1; i <= n; i++) cout << i << " ";
        cout << endl;
        return;
    }

    for (int i = 1; i <= mx; i++) {
        if (mx % i == 0) cout << i << " ";
    }
    cout << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> va[i];
        solve();
    }

    return 0;
}