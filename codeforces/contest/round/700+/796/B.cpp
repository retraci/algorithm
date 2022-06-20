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
    int has_odd = 0;
    for (int i = 1; i <= n; i++) has_odd |= a[i] & 1;

    if (has_odd) {
        int cnt = 0;
        for (int i = 1; i <= n; i++) cnt += ~a[i] & 1;
        cout << cnt << "\n";
    } else {
        ll ans = 0, mi = 1e9;
        for (int i = 1; i <= n; i++) {
            if (a[i] & 1) continue;
            ans++;
            ll cnt = 0;
            while (~a[i] & 1) a[i] >>= 1, cnt++;
            mi = min(mi, cnt);
        }

        ans += mi;
        cout << ans - 1 << "\n";
    }
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