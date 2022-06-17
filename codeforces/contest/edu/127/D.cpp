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

int n, x;
int a[N];

int calc(int y) {
    int res = min(abs(y - a[1]), abs(y - a[n]));
    for (int i = 2; i <= n; i++) {
        int t = abs(y - a[i]) + abs(y - a[i - 1]) - abs(a[i] - a[i - 1]);
        res = min(res, t);
    }
    return res;
}

void solve() {
    ll ans = 0;
    for (int i = 2; i <= n; i++) ans += abs(a[i] - a[i - 1]);
    if (*min_element(a + 1, a + n + 1) > 1) ans += calc(1);
    if (*max_element(a + 1, a + n + 1) < x) ans += calc(x);
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
        cin >> n >> x;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}