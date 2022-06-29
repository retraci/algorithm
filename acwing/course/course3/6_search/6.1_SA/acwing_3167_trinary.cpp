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
const double eps = 1e-3;

using pdd = pair<double, double>;

int n;
pdd a[N];

double get(pdd p1, pdd p2) {
    double dx = p1.fi - p2.fi;
    double dy = p1.se - p2.se;
    return sqrt(dx * dx + dy * dy);
}

double calc2(double x, double y) {
    pdd p = {x, y};
    double res = 0;
    for (int i = 1; i <= n; i++) res += get(p, a[i]);
    return res;
}

double calc(double x) {
    double left = 0, right = 10000;
    while (left + eps < right) {
        double mdl = (2 * left + right) / 3;
        double mdr = (left + 2 * right) / 3;
        double v1 = calc2(x, mdl), v2 = calc2(x, mdr);
        if (v1 > v2) left = mdl;
        else right = mdr;
    }
    double res = calc2(x, left);

    return res;
}

void solve() {
    double left = 0, right = 10000;
    while (left + eps < right) {
        double mdl = (2 * left + right) / 3;
        double mdr = (left + 2 * right) / 3;
        double v1 = calc(mdl), v2 = calc(mdr);
        if (v1 > v2) left = mdl;
        else right = mdr;
    }
    double ans = calc(left);

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