// 分配口罩

#include <bits/stdc++.h>

using namespace std;

#define ll long long

void solve() {
    ll num[] = {9090400, 8499400, 5926800, 8547000, 4958200,
            4422600, 5751200, 4175600, 6309600, 5865200,
            6604400, 4635000, 10663400, 8087200, 4554000
    };

    ll sum = 0;
    for (int i = 0; i < 15; i++) sum += num[i];

    int lim = 1 << 15;
    ll ans = 0x3f3f3f3f;
    for (int s = 1; s < lim; s++) {
        ll cur = 0;
        for (int i = 0; i < 15; i++) {
            if (s >> i & 1) cur += num[i];
            ans = min(ans, abs(sum - 2 * cur));
        }
    }

    cout << ans << endl;
}

int main() {
//    freopen("../in.txt", "r", stdin);

    solve();

    return 0;
}