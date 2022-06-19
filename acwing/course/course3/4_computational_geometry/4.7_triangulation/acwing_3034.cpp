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
        P delta = (ps[1] - ps[0]).rot90().unit() * eps;
        return {ps[0] + delta, ps[1] + delta};
    }
};

#define cross(p1, p2, p3) ((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y))
#define crossOp(p1, p2, p3) sign(cross(p1, p2, p3))
#define scalar(p1, p2, p3) ((p2.x - p1.x) * (p3.x - p1.x) + (p2.y - p1.y) * (p3.y - p1.y))
// endregion

// region 三角剖分
// 求直线l1, l2交点
P getLL(P p1, P p2, P q1, P q2) {
    cgt a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
    return (p1 * a2 + p2 * a1) / (a1 + a2);
}

// 求 圆-线 的交点
vector<P> getCL(P o, cgt r, P p1, P p2) {
    if (cmp(abs((o - p1).det(p2 - p1) / p1.distTo(p2)), r) > 0) return {};
    cgt xy = (p1 - o).dot(p2 - p1), y2 = (p2 - p1).abs2(), d2 = xy * xy - y2 * ((p1 - o).abs2() - r * r);
    d2 = max(d2, (cgt) 0.0);
    P m = p1 - (p2 - p1) * (xy / y2), dr = (p2 - p1) * (sqrtl(d2) / y2);
    return {m - dr, m + dr}; // along dir: p1->p2
}

// 求 0->p1, 0->p2 构成的角的弧度
cgt rad(P p1, P p2) {
    return atan2l(p1.det(p2), p1.dot(p2));
}

// 求 扇形 有向面积
cgt sectorErea(P o, cgt r, P p1, P p2) {
    cgt ang = rad(p1 - o, p2 - o);
    return r * r * ang / 2;
}

// 是否在线段上(在端点上 => 在线段上)
bool onSeg(P p1, P p2, P q) {
    return crossOp(p1, p2, q) == 0 && sign((q - p1).dot(q - p2)) <= 0;
}

// endutil

cgt triangulation(P o, cgt r, P p1, P p2) {
    auto da = o.distTo(p1), db = o.distTo(p2);
    if (cmp(r, da) >= 0 && cmp(r, db) >= 0) return (p1 - o).det((p2 - o)) / 2;
    if (sign((p1 - o).det((p2 - o)) == 0)) return 0;
    P mid = getLL(p1, p2, o, o + (p1 - p2).rot90());
    cgt d = mid.distTo(o);
    if (!onSeg(p1, p2, mid)) d = min(o.distTo(p1), o.distTo(p2));
    if (cmp(r, d) <= 0) return sectorErea(o, r, p1, p2);

    auto is = getCL(o, r, p1, p2);
    assert(!is.empty());
    P pa = is[0], pb = is[1];
    if (cmp(r, da) >= 0) return (p1 - o).det((pb - o)) / 2 + sectorErea(o, r, pb, p2);
    if (cmp(r, db) >= 0) return (pa - o).det((p2 - o)) / 2 + sectorErea(o, r, p1, pa);
    return (pa - o).det((pb - o)) / 2 + sectorErea(o, r, pb, p2) + sectorErea(o, r, p1, pa);
}
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 55;

int n;
cgt r;
P a[N];

void solve() {
    cgt ans = 0;
    for (int i = 0; i < n; i++) {
        ans += triangulation(P(0, 0), r, a[i], a[(i + 1) % n]);
    }
    ans = abs(ans);
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
    while (cin >> r >> n) {
        for (int i = 0; i < n; i++) cin >> a[i].x >> a[i].y;
        solve();
    }

    return 0;
}