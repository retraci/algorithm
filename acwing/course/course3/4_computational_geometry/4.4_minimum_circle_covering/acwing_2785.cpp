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
const cgt eps = 1e-9;
const cgt PI = acosl(-1);

inline int sign(cgt a) { return a < -eps ? -1 : a > eps; }

inline int cmp(cgt a, cgt b) { return sign(a - b); }

struct P {
    cgt x, y;

    P() {}

    P(cgt _x, cgt _y) : x(_x), y(_y) {}

    P operator+(P p) { return {x + p.x, y + p.y}; }

    P operator-(P p) { return {x - p.x, y - p.y}; }

    P operator*(cgt d) { return {x * d, y * d}; }

    P operator/(cgt d) { return {x / d, y / d}; }

    bool operator==(P p) {
        return cmp(x, p.x) == 0 && cmp(y, p.y) == 0;
    }

    cgt dot(P p) { return x * p.x + y * p.y; }

    cgt det(P p) { return x * p.y - y * p.x; }

    cgt distTo(P p) { return (*this - p).abs(); }

    cgt alpha() { return atan2l(y, x); }

    void read() { cin >> x >> y; }

    void write() { cout << "(" << x << ", " << y << ")" << "\n"; }

    cgt abs() { return sqrtl(abs2()); }

    cgt abs2() { return x * x + y * y; }

    // 逆时针转90
    P rot90() { return P(-y, x); }

    P unit() { return *this / abs(); }

    // 1: x轴上方, [0, PI), 0: x轴下方, [-PI, 0)
    int quad() { return sign(y) == 1 || (sign(y) == 0 && sign(x) >= 0); }

    // 逆时针转
    P rot(cgt ang) { return {x * cosl(ang) - y * sinl(ang), x * sinl(ang) + y * cosl(ang)}; }
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

    P dir() { return ps[1] - ps[0]; }

    L push() {
        P delta = (ps[1] - ps[0]).rot90().unit() * eps;
        return {ps[0] + delta, ps[1] + delta};
    }
};

#define cross(p1, p2, p3) ((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y))
#define crossOp(p1, p2, p3) sign(cross(p1, p2, p3))
// endregion

// region 最小圆覆盖
using C = pair<P, cgt>;

// 外心
P circumCenter(P a, P b, P c) {
    P bb = b - a, cc = c - a;
    cgt db = bb.abs2(), dc = cc.abs2(), d = 2 * bb.det(cc);
    return a - P(bb.y * dc - cc.y * db, cc.x * db - bb.x * dc) / d;
}

C minimumCircleCovering(vector<P> ps) {
    shuffle(ps.begin(), ps.end(), mrnd);
    C res = {ps[0], 0};
    for (int i = 1; i < ps.size(); i++) {
        if (cmp(ps[i].distTo(res.fi), res.se) > 0) {
            res = {ps[i], 0};
            for (int j = 0; j < i; j++) {
                if (cmp(ps[j].distTo(res.fi), res.se) > 0) {
                    res = {(ps[i] + ps[j]) / 2, ps[i].distTo(ps[j]) / 2};
                    for (int k = 0; k < j; k++) {
                        if (cmp(ps[k].distTo(res.fi), res.se) > 0) {
                            P p = circumCenter(ps[i], ps[j], ps[k]);
                            cgt r = p.distTo(ps[i]);
                            res = {p, r};
                        }
                    }
                }
            }
        }
    }

    return res;
}
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 50010;

int n;
P a[N];
cgt alp, p;

void solve() {
    for (int i = 1; i <= n; i++) {
        a[i] = a[i].rot(-alp / 180 * PI);
        a[i].x /= p;
    }

    C c = minimumCircleCovering(vector<P>(a + 1, a + n + 1));
    cout << fixed << setprecision(3);
    cout << c.se << "\n";
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
        for (int i = 1; i <= n; i++) cin >> a[i].x >> a[i].y;
        cin >> alp >> p;
        solve();
    }

    return 0;
}