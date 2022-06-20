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

// 直线是否相交
bool checkLL(P p1, P p2, P q1, P q2) {
    cgt a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
    return sign(a1 + a2) != 0;
}

// 求线段是否重叠
bool intersect(cgt l1, cgt r1, cgt l2, cgt r2) {
    if (l1 > r1) swap(l1, r1);
    if (l2 > r2) swap(l2, r2);
    return !(cmp(r1, l2) == -1 || cmp(r2, l1) == -1);
}

// 求线段是否相交(重叠 => 相交, 端点 => 相交)
bool checkSS(P p1, P p2, P q1, P q2) {
    return intersect(p1.x, p2.x, q1.x, q2.x)
        && intersect(p1.y, p2.y, q1.y, q2.y)
        && crossOp(p1, p2, q1) * crossOp(p1, p2, q2) <= 0
        && crossOp(q1, q2, p1) * crossOp(q1, q2, p2) <= 0;
}

// 求直线l1, l2交点
P getLL(P p1, P p2, P q1, P q2) {
    cgt a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
    return (p1 * a2 + p2 * a1) / (a1 + a2);
}

// 求直线l1, l2交点
P getLL(L l1, L l2) { return getLL(l1[0], l1[1], l2[0], l2[1]); }

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};

using T = array<P, 3>;
const int N = 110;

int n;
T a[N];

cgt get(cgt x, int ty) {
    static pair<cgt, cgt> ys[N];
    int cnt = 0;

    for (int i = 1; i <= n; i++) {
        if (cmp(a[i][0].x, x) > 0 || cmp(a[i][2].x, x) < 0) continue;

        if (cmp(a[i][0].x, x) == 0 && cmp(a[i][1].x, x) == 0) {
            if (!ty) ys[++cnt] = {a[i][0].y, a[i][1].y};
        } else if (cmp(a[i][2].x, x) == 0 && cmp(a[i][1].x, x) == 0) {
            if (ty) ys[++cnt] = {a[i][1].y, a[i][2].y};
        } else {
            static cgt d[4];
            int sz = 0;
            for (int j = 0; j < 3; j++) {
                if (checkLL(a[i][j], a[i][(j + 1) % 3], {x, -1e9}, {x, 1e9})
                && checkSS(a[i][j], a[i][(j + 1) % 3], {x, -1e9}, {x, 1e9})) {
                    P is = getLL(a[i][j], a[i][(j + 1) % 3], {x, -1e9}, {x, 1e9});
                    d[++sz] = is.y;
                }
            }
            if (sz >= 2) {
                sort(d + 1, d + sz + 1);
                ys[++cnt] = {d[1], d[sz]};
            }
        }
    }
    if (cnt == 0) return 0;

    sort(ys + 1, ys + cnt + 1, [](auto &a, auto &b) {
        return a.fi < b.fi;
    });
    cgt res = 0, st = ys[1].fi, ed = ys[1].se;
    for (int i = 2; i <= cnt; i++) {
        if (ys[i].fi <= ed) {
            ed = max(ed, ys[i].se);
        } else {
            res += ed - st;
            st = ys[i].fi, ed = ys[i].se;
        }
    }
    return res + ed - st;
}

cgt calc(cgt lb, cgt rb) {
    return (get(lb, 0) + get(rb, 1)) * (rb - lb) / 2;
}

void solve() {
    for (int i = 1; i <= n; i++) {
        sort(&a[i][0], &a[i][3], [](auto &a, auto &b) {
            if (cmp(a.x, b.x) == 0) return a.y < b.y;
            return a.x < b.x;
        });
    }

    vector<cgt> xs;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 3; j++) {
            xs.push_back(a[i][j].x);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            for (int x = 0; x < 3; x++) {
                for (int y = 0; y < 3; y++) {
                    if (checkLL(a[i][x], a[i][(x + 1) % 3], a[j][y], a[j][(y + 1) % 3])
                    && checkSS(a[i][x], a[i][(x + 1) % 3], a[j][y], a[j][(y + 1) % 3])) {
                        P is = getLL(a[i][x], a[i][(x + 1) % 3], a[j][y], a[j][(y + 1) % 3]);
                        xs.push_back(is.x);
                    }
                }
            }
        }
    }

    sort(xs.begin(), xs.end());
    cgt ans = 0;
    for (int i = 1; i < xs.size(); i++) {
        if (cmp(xs[i - 1], xs[i]) == 0) continue;
        ans += calc(xs[i - 1], xs[i]);
    }
    cout << fixed << setprecision(2) << ans << "\n";
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
            for (int j = 0; j < 3; j++) {
                cgt x, y;
                cin >> x >> y;
                a[i][j] = {x, y};
            }
        }
        solve();
    }

    return 0;
}