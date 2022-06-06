#include <bits/stdc++.h>

void debug() {
    std::cout << "\n";
}

template<class T, class... OtherArgs>
void debug(T &&var, OtherArgs &&... args) {
    std::cout << std::forward<T>(var) << " ";
    debug(std::forward<OtherArgs>(args)...);
}

using namespace std;

#define fi first
#define se second
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ai3 = array<int, 3>;
mt19937 mrnd(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 2e5 + 10;

int n;
int a[N];

void solve() {
    sort(a + 1, a + n + 1);

    vector<ll> s(n + 1);
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i];
    if (1LL * (n - 1) * a[1] + s[n] - s[1] > 0 || 1LL * (n - 1) * a[n] + s[n - 1] < 0) {
        cout << "INF" << "\n";
        return;
    }

    ll ans = -1e18;
    for (int i = 1; i <= n; i++) {
        ll t = -a[i];
        ll mi = a[1] + t, mx = a[n] + t;
        ll up = s[n] - s[i] + 1LL * (n - i) * t;
        ll dw = s[i - 1] + 1LL * (i - 1) * t;
        ll tmp = up * mi + dw * mx - mi * mx - (n - 1) * t * t;
        ans = max(ans, tmp);
    }
    cout << ans << "\n";
}

void prework() {
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    prework();
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _ = 1;
    cin >> _;
    while (_--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}