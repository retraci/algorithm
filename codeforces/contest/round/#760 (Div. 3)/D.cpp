#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {0, 0, -1, 1, -1, -1, 1, 1, 0};
const int dy[9] = {-1, 1, 0, 0, -1, 1, -1, 1, 0};

const int N = 110;

int n, k;
int va[N];

void solve() {
    sort(va + 1, va + n + 1, greater<>());

    int ans = 0;
    for (int i = 2 * k + 1; i <= n; i++) ans += va[i];
    int cnt = 1, mx = 0;
    for (int i = 2; i <= 2 * k; i++) {
        if (va[i] == va[i - 1]) cnt++;
        else cnt = 1;
        mx = max(mx, cnt);
    }
    if (mx - k > 0) ans += mx - k;

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
        cin >> n >> k;
        for (int i = 1; i <= n; i++) cin >> va[i];
        solve();
    }

    return 0;
}