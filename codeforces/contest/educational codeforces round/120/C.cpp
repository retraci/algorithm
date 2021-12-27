#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <bitset>
#include <cmath>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

const int N = 2e5 + 10;

ll n, K;
ll va[N];

void solve() {
    ll mi = *min_element(va + 1, va + n + 1);
    ll sum = accumulate(va + 1, va + n + 1, 0LL);
    if (sum <= K) {
        cout << 0 << "\n";
        return;
    }

    sort(va + 1, va + n + 1, greater<>());
    for (int i = 1; i <= n; i++) va[i] += va[i - 1];

    ll ans = 1e18;
    for (int i = 0; i <= n - 1; i++) {
        ll rem = va[n - 1] - va[i];
        ll c = i + 1;
        ll tar = floor(1.0 * (K - rem) / c);

        ll op1 = max(0LL, mi - tar);
        ll op2 = i;
        ans = min(ans, op1 + op2);
    }

    cout << ans << "\n";
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
        cin >> n >> K;
        for (int i = 1; i <= n; i++) cin >> va[i];
        solve();
    }

    return 0;
}