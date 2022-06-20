#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 2e5 + 10;

int n;
pll va[N];
int ans[N];

void solve() {
    sort(va + 1, va + n + 1);
    reverse(va + 1, va + n + 1);

    ll cnt = 0;
    for (int i = 1; i <= n; i += 2) {
        int id = (i + 1) / 2;
        ans[va[i].second] = -id;
        cnt += va[i].first * id;
        if (i + 1 <= n) {
            cnt += va[i + 1].first * id;
            ans[va[i + 1].second] = id;
        }
    }

    cout << cnt * 2 << endl;
    for (int i = 0; i <= n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            int a;
            cin >> a;
            va[i] = {a, i};
        }
        solve();
    }

    return 0;
}