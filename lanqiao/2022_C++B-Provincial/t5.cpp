#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <bitset>
#include <unordered_map>

using namespace std;

#define ll long long

const int N = 100010;
const ll MOD = 1000000007;

int n, ma, mb;
ll a[N], b[N];

void solve() {
    ll ans = 0;
    ll bas = 1;
    reverse(a + 1, a + ma + 1);
    reverse(b + 1, b + mb + 1);
    for (int i = 1; i <= max(ma, mb); i++) {
        int cur = max(2LL, max(a[i], b[i]) + 1);

        ans += (a[i] - b[i]) * bas % MOD;
        ans %= MOD;

        bas *= cur;
        bas %= MOD;
    }

    ans = (ans + MOD) % MOD;
    cout << ans;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    cin >> ma;
    for (int i = 1; i <= ma; i++) cin >> a[i];
    cin >> mb;
    for (int i = 1; i <= mb; i++) cin >> b[i];
    solve();

    return 0;
}
