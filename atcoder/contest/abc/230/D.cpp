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

const int N = 2e5 + 10;

ll n, d;
pll va[N];

void solve() {
    sort(va + 1, va + n + 1);

    int ans = 0;
    int last = -1;
    for (int i = 1; i <= n; i++) {
        auto &[R, L] = va[i];
        if (last >= L) continue;
        ans++;
        last = R + d - 1;
    }
    cout << ans << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> d;
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        va[i] = {b, a};
    }
    solve();

    return 0;
}