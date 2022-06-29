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

using pdd = pair<double, double>;

int n;
pdd a[N];

double get(pdd p1, pdd p2) {
    double dx = p1.fi - p2.fi;
    double dy = p1.se - p2.se;
    return sqrt(dx * dx + dy * dy);
}

// region 模拟退火
namespace SA {
    using sat = double;
    const double T = 0.8;

    sat rand(sat L, sat R) {
        return rnd(1e9) / 1e9 * (R - L) + L;
    }

    sat calc(pdd p) {
        sat res = 0;
        for (int i = 1; i <= n; i++) res += get(p, a[i]);
        return res;
    }

    sat sa(sat T0, sat TE, sat apl, int is_mx) {
        pdd p = {rand(0, T0), rand(0, T0)};
        sat f = calc(p), res = f;
        for (sat t = T0; t > TE; t *= apl) {
            auto [x, y] = p;
            pdd np = {rand(x - t, x + t), rand(y - t, y + t)};
            sat nf = calc(np);

            if (is_mx) {
                res = max(res, nf);
                sat dta = nf - f;
                if (exp(dta / t) > rand(0, 1)) p = np, f = nf;
            } else {
                res = min(res, nf);
                sat dta = nf - f;
                if (exp(-dta / t) > rand(0, 1)) p = np, f = nf;
            }
        }

        return res;
    }
}
// endregion

void solve() {
    double ans = 1e18;
    const double start = clock();
    while ((clock() - start) / CLOCKS_PER_SEC < 0.8) ans = min(ans, SA::sa(1e4, 1e-3, 0.97, 0));

    cout << (ll) (ans + 0.5) << "\n";
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
        for (int i = 1; i <= n; i++) cin >> a[i].fi >> a[i].se;
        solve();
    }

    return 0;
}