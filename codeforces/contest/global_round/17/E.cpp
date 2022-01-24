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
int va[N];

void solve() {
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (va[i] == va[i - 1]) continue;

        int cnt = 1, ptr = i;
        while (ptr <= n) {
            ptr = lower_bound(va + ptr + 1, va + n + 1, 2 * va[ptr] - va[i]) - va;
            cnt += ptr <= n;
        }

        ans = max(ans, cnt);
    }
    cout << n - ans << endl;
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
        for (int i = 1; i <= n; i++) cin >> va[i];
        solve();
    }

    return 0;
}