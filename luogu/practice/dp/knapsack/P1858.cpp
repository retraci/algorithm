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
const int N = 5010;

int k, m, n;
pii a[N];

void solve() {
    vector<int> f[m + 1];
    f[0] = {0};
    for (int i = 1; i <= n; i++) {
        auto [v, w] = a[i];
        for (int j = m; j >= v; j--) {
            for (int x : f[j - v]) f[j].push_back(x + w);
            sort(f[j].rbegin(), f[j].rend());
            f[j].resize(min(k, (int) f[j].size()));
        }
    }

    ll ans = accumulate(f[m].begin(), f[m].end(), 0LL);
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
        cin >> k >> m >> n;
        for (int i = 1; i <= n; i++) cin >> a[i].fi >> a[i].se;
        solve();
    }

    return 0;
}