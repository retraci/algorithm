#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 110;

int n, L, R, K;
int va[N];

void solve() {
    sort(va + 1, va + n + 1);

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (va[i] < L || va[i] > R) continue;
        if (K - va[i] >= 0) {
            K -= va[i];
            ans++;
        }
    }

    cout << ans << endl;
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
        cin >> n >> L >> R >> K;
        for (int i = 1; i <= n; i++) cin >> va[i];
        solve();
    }

    return 0;
}