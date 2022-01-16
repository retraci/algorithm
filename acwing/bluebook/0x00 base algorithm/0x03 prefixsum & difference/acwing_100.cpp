#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 1e5 + 10;

#define ll long long

int n;
ll va[maxn], vd[maxn];

void solve() {
    for (int i = 1; i <= n; i++) vd[i] = va[i] - va[i - 1];

    ll cnt1 = 0, cnt2 = 0;
    for (int i = 2; i <= n; i++) {
        if (vd[i] < 0) cnt1 -= vd[i];
        else cnt2 += vd[i];
    }

    ll ans1 = max(cnt1, cnt2);
    ll ans2 = max(cnt1, cnt2) - min(cnt1, cnt2) + 1;

    cout << ans1 << endl << ans2 << endl;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) scanf("%d", &va[i]);
    solve();

    return 0;
}

