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
mt19937 mrnd(std::random_device{}());

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int N = 3e5 + 10;

int n;
int a[N];

void solve() {
    ll f[n + 1][2];
    ll ans = 1e18;

    {
        memset(f, 0x3f, sizeof f);
        f[1][1] = a[1];
        for (int i = 2; i <= n; i++) {
            f[i][0] = min(f[i][0], f[i - 1][1]);

            ll t = min(f[i - 1][0], f[i - 1][1]) + a[i];
            f[i][1] = min(f[i][1], t);
        }
        ans = min({ans, f[n][0], f[n][1]});
    }

    {
        memset(f, 0x3f, sizeof f);
        f[1][0] = a[n];
        for (int i = 1; i <= n - 1; i++) {
            f[i][0] = min(f[i][0], f[i - 1][1]);

            ll t = min(f[i - 1][0], f[i - 1][1]) + a[i];
            f[i][1] = min(f[i][1], t);
        }
        ans = min({ans, f[n - 1][0], f[n - 1][1]});
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
//    cin >> _;
    while (_--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}