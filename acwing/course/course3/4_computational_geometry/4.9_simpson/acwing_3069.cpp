#include <bits/stdc++.h>
#pragma GCC optimize(3)

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

// region 计算几何基础
using cgt = double;
const cgt EPS = 1e-9;
const cgt PI = acosl(-1);

inline int sign(cgt a) { return a < -EPS ? -1 : a > EPS; }

inline int cmp(cgt a, cgt b) { return sign(a - b); }

struct P {
    cgt x, y;

    P() {}

    P(cgt _x, cgt _y) : x(_x), y(_y) {}

    P operator+(P p) const { return {x + p.x, y + p.y}; }

    P operator-(P p) const { return {x - p.x, y - p.y}; }

    P operator*(cgt d) const { return {x * d, y * d}; }

    P operator/(cgt d) const { return {x / d, y / d}; }

    bool operator==(P p) const {
        return cmp(x, p.x) == 0 && cmp(y, p.y) == 0;
    }

    cgt dot(P p) const { return x * p.x + y * p.y; }

    cgt det(P p) const { return x * p.y - y * p.x; }

    cgt distTo(P p) const { return (*this - p).abs(); }

    cgt distTo2(P p) const { return (*this - p).abs2(); }

    cgt alpha() const { return atan2l(y, x); }

    void read() { cin >> x >> y; }

    void write() const { cout << "(" << x << ", " << y << ")" << "\n"; }

    cgt abs() const { return sqrtl(abs2()); }

    cgt abs2() const { return x * x + y * y; }

    // 逆时针转90
    P rot90() const { return P(-y, x); }

    P unit() const { return *this / abs(); }

    // 1: x轴上方, [0, PI), 0: x轴下方, [-PI, 0)
    int quad() const { return sign(y) == 1 || (sign(y) == 0 && sign(x) >= 0); }

    // 逆时针转
    P rot(cgt ang) const { return {x * cosl(ang) - y * sinl(ang), x * sinl(ang) + y * cosl(ang)}; }
};

struct L {
    // ps[0] -> ps[1]
    P ps[2];

    L() {}

    L(P a, P b) {
        ps[0] = a;
        ps[1] = b;
    }

    P &operator[](int i) { return ps[i]; }

    P dir() const { return ps[1] - ps[0]; }

    L push() const {
        P delta = (ps[1] - ps[0]).rot90().unit() * EPS;
        return {ps[0] + delta, ps[1] + delta};
    }
};

#define cross(p1, p2, p3) ((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y))
#define crossOp(p1, p2, p3) sign(cross(p1, p2, p3))
#define scalar(p1, p2, p3) ((p2.x - p1.x) * (p3.x - p1.x) + (p2.y - p1.y) * (p3.y - p1.y))
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1010;

using C = pair<P, cgt>;

int n;
C a[N];
int lid, rid;

// region 积分
cgt f(cgt x) {
    static pair<cgt, cgt> ls[N];
    int cnt = 0;

    for (int i = lid; i <= rid; i++) {
        auto [o, r] = a[i];

        cgt dx = abs(x - o.x);
        if (cmp(dx, r) < 0) {
            cgt dy = sqrtl(r * r - dx * dx);
            ls[++cnt] = {o.y - dy, o.y + dy};
        }
    }
    if (cnt == 0) return 0;

    sort(ls + 1, ls + cnt + 1);
    cgt res = 0, st = ls[1].fi, ed = ls[1].se;
    for (int i = 2; i <= cnt; i++) {
        auto [L, R] = ls[i];
        if (L <= ed) {
            ed = max(ed, R);
        } else {
            res += ed - st;
            st = L, ed = R;
        }
    }

    return res + ed - st;
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
    auto fl = coates(L, mid), fr = coates(mid, R);
    if (abs(fl + fr - s) <= 15 * eps) return fl + fr + (fl + fr - s) / 15;
    return asr(L, mid, fl, eps / 2) + asr(mid, R, fr, eps / 2);
}

cgt calc(cgt L, cgt R, cgt eps) {
    return asr(L, R, coates(L, R), eps);
}
// endregion

const cgt D = 100;

void solve() {
    cgt ans = 0;
    sort(a + 1, a + n + 1, [](auto &a, auto &b) {
        return a.fi.x - a.se < b.fi.x - b.se;
    });
    cgt x1 = a[1].fi.x - a[1].se, x2 = a[1].fi.x + a[1].se;
    lid = 1, rid = 1;
    for (int i = 2; i <= n; i++) {
        auto [o, r] = a[i];
        if (x2 >= o.x - r) {
            x2 = max(x2, o.x + r);
            rid = i;
        } else {
            ans += calc(x1 - D, x2 + D, 1e-5);
            x1 = o.x - r, x2 = o.x + r;
            lid = i, rid = i;
        }
    }
    ans += calc(x1 - D, x2 + D, 1e-5);
    cout << fixed << setprecision(3) << ans << "\n";
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
        for (int i = 1; i <= n; i++) {
            cgt x, y, r;
            cin >> x >> y >> r;
            a[i] = {{x, y}, r};
        }
        solve();
    }

    return 0;
}