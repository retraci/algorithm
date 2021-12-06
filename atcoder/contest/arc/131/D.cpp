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

const int N = 1e5 + 10;

ll n, m, d;
ll vr[N], vs[N];

int get_id(ll x) {
    return lower_bound(vr, vr + m + 1, abs(x)) - vr - 1;
}

ll calc(ll x) {
    ll res = vs[get_id(x)];
    ll lb = x - d, rb = x + d;
    int rem = n - 1;
    while (rem--) {
        int id1 = get_id(lb), id2 = get_id(rb);
        if (vs[id1] > vs[id2]) {
            res += vs[id1];
            lb -= d;
        } else {
            res += vs[id2];
            rb += d;
        }
    }

    if (res == 240) cout << x << "\n";

    return res;
}

void solve() {
    vr[++m] = 1e18;

    ll ans = 0;
    ll left = -vr[m - 1], right = vr[m - 1];
    while (left < right) {
        ll mid1 = left + (right - left) / 3, mid2 = right - (right - left) / 3;
        ll yl = calc(mid1), yr = calc(mid2);
        ans = max({ans, yl, yr});
        if (yl < yr) left = mid1 + 1;
        else right = mid2 - 1;
    }
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> d;
    for (int i = 0; i <= m; i++) cin >> vr[i];
    for (int i = 0; i <= m; i++) cin >> vs[i];
    solve();

    return 0;
}