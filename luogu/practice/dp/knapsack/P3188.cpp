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

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 110;

int n, w;
pii a[N];

void solve() {
    int s = 0;
    vector<pii> b[33];
    for (int i = 1; i <= n; i++) {
        auto [tw, tv] = a[i];

        int lev = __builtin_ctz(tw);
        tw >>= lev;
        b[lev].push_back({tw, tv});
        s += tw;
    }

    static int f[1010], pf[1010];
    fill(f, f + s + 1, -1e9);
    f[0] = 0;
    for (int k = __lg(w); k >= 0; k--) {
        swap(f, pf);
        fill(f, f + s + 1, -1e9);

        int dig = w >> k & 1;
        for (int i = 0; i <= s; i++) {
            int ns = min(s, i * 2 + dig);
            f[ns] = max(f[ns], pf[i]);
        }
        for (int i = s - 1; i >= 0; i--) f[i] = max(f[i], f[i + 1]);

        for (auto [tw, tv] : b[k]) {
            for (int i = tw; i <= s; i++) {
                f[i - tw] = max(f[i - tw], f[i] + tv);
            }
        }
    }

    cout << f[0] << "\n";
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
    while (cin >> n >> w, n != -1) {
        for (int i = 1; i <= n; i++) cin >> a[i].fi >> a[i].se;
        solve();
    }

    return 0;
}