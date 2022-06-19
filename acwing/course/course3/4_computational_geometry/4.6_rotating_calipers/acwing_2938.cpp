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
using cgt = ll;
const cgt eps = 0;
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
// endregion

// region 凸包
// 求直线l1, l2交点
P getLL(P p1, P p2, P q1, P q2) {
    cgt a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
    return (p1 * a2 + p2 * a1) / (a1 + a2);
}

// 求直线l1, l2交点
P getLL(L l1, L l2) { return getLL(l1[0], l1[1], l2[0], l2[1]); }

bool operator<(P p1, P p2) {
    int c = cmp(p1.x, p2.x);
    if (c) return c == -1;
    return cmp(p1.y, p2.y) == -1;
}

// endutil

// 严格凸包(相同斜率 !=> 属于凸包)
// 严格: <= 0, 非严格: < 0
vector<P> convexHull(vector<P> ps) {
    int n = ps.size();
    if (n <= 1) return ps;
    sort(ps.begin(), ps.end(), [](P p1, P p2) {
        int c = cmp(p1.x, p2.x);
        if (c) return c == -1;
        return cmp(p1.y, p2.y) == -1;
    });

    vector<P> res(2 * n);
    int k = 0;
    for (int i = 0; i < n; res[k++] = ps[i++]) {
        while (k > 1 && crossOp(res[k - 2], res[k - 1], ps[i]) <= 0) k--;
    }
    for (int i = n - 2, t = k; i >= 0; res[k++] = ps[i--]) {
        while (k > t && crossOp(res[k - 2], res[k - 1], ps[i]) <= 0) k--;
    }
    res.resize(k - 1);
    return res;
}

// 求凸包面积
cgt area(const vector<P> &ps) {
    cgt res = 0;
    for (int i = 0; i < ps.size(); i++) {
        res += ps[i].det(ps[(i + 1) % ps.size()]);
    }
    return res / 2;
}

// 求凸包直径
cgt convexDiameter(const vector<P> &ps) {
    int n = ps.size();
    if (n <= 1) return 0;
    int is = 0, js = 0;
    for (int k = 1; k < n; k++) {
        is = ps[k] < ps[is] ? k : is, js = ps[js] < ps[k] ? k : js;
    }
    int i = is, j = js;
    cgt ret = ps[i].distTo2(ps[j]);
    do {
        if ((ps[(i + 1) % n] - ps[i]).det(ps[(j + 1) % n] - ps[j]) >= 0) j = (j + 1) % n;
        else i = (i + 1) % n;
        ret = max(ret, ps[i].distTo2(ps[j]));
    } while (i != is || j != js);
    return ret;
}
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 50010;

int n;
P a[N];

void solve() {
    auto hull = convexHull(vector<P>(a + 1, a + n + 1));
    ll d = convexDiameter(hull);
    cout << d << "\n";
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
        solve();
    }

    return 0;
}