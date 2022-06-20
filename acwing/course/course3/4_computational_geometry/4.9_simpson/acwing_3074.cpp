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

using cgt = double;

// region 积分
cgt f(cgt x) {
    return sinl(x) / x;
}

cgt simpson(cgt L, cgt R) {
    cgt mid = (L + R) / 2;
    return (R - L) * (f(L) + 4 * f(mid) + f(R)) / 6;
}

cgt coates(cgt L, cgt R) {
    cgt d = (R - L) / 4;
    cgt x0 = L, x1 = L + d, x2 = x1 + d, x3 = R - d, x4 = R;
    return (R - L) * (7 * f(x0) + 32 * f(x1) + 12 * f(x2) + 32 * f(x3) + 7 * f(x4)) / 90;
}

cgt asr(cgt L, cgt R, cgt s, cgt eps) {
    cgt mid = (L + R) / 2;
    auto fl = simpson(L, mid), fr = simpson(mid, R);
    if (abs(fl + fr - s) <= 15 * eps) return fl + fr + (fl + fr - s) / 15;
    return asr(L, mid, fl, eps / 2) + asr(mid, R, fr, eps / 2);
}

cgt calc(cgt L, cgt R, cgt eps) {
    return asr(L, R, simpson(L, R), eps);
}
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};

cgt L, R;

void solve() {
    cgt ans = calc(L, R, 1e-8);
    cout << fixed << setprecision(6) << ans << "\n";
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
        cin >> L >> R;
        solve();
    }

    return 0;
}