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

#define x first
#define y second

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

// 直线是否相交 (x)
bool checkLL(P p1, P p2, P q1, P q2) {
    cgt a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
    return sign(a1 + a2) != 0;
}

// 求直线l1, l2交点
P getLL(P p1, P p2, P q1, P q2) {
    cgt a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
    return (p1 * a2 + p2 * a1) / (a1 + a2);
}

// 求直线l1, l2交点
P getLL(L l1, L l2) { return getLL(l1[0], l1[1], l2[0], l2[1]); }

// 是否在以a, b为对角线的矩形内, 含边界
bool isMiddle(cgt a, cgt m, cgt b) {
    return sign(a - m) == 0 || sign(b - m) == 0 || (a < m != b < m);
}

// 是否在以a, b为对角线的矩形内, 含边界
bool isMiddle(P a, P m, P b) {
    return isMiddle(a.x, m.x, b.x) && isMiddle(a.y, m.y, b.y);
}

// 是否在线段上(在端点上 => 在线段上)
bool onSeg(P p1, P p2, P q) {
    return crossOp(p1, p2, q) == 0 && isMiddle(p1, q, p2);
}

using namespace std;

typedef pair<double, double> PDD;
const int N = 110;
const double eps = 1e-8, INF = 1e6;

int n;
PDD tr[N][3];  // 存储三角形的顶点
PDD q[N];  // 存储待合并的区间

int dcmp(double x, double y) {
    if (fabs(x - y) < eps) return 0;
    if (x < y) return -1;
    return 1;
}

PDD operator+ (PDD a, PDD b) {
    return {a.x + b.x, a.y + b.y};
}

PDD operator- (PDD a, PDD b) {
    return {a.x - b.x, a.y - b.y};
}

PDD operator* (PDD a, double t) {
    return {a.x * t, a.y * t};
}

double operator* (PDD a, PDD b) {  // 叉积
    return a.x * b.y - a.y * b.x;
}

double operator& (PDD a, PDD b) {  // 点积
    return a.x * b.x + a.y * b.y;
}

// 判断点p是否在线段(a, b)上
bool on_segment(PDD p, PDD a, PDD b) {
    return sign((p - a) & (p - b)) <= 0;
}

bool onSeg(PDD p, PDD a, PDD b) {
    P pa = {a.x, a.y}, pb = {b.x, b.y}, pp = {p.x, p.y};
    return onSeg(pa, pb, pp);
}

// 求解两个先点的交点，不存在交点的话返回{INF, INF}
PDD get_line_intersection(PDD p, PDD v, PDD q, PDD w) {

    if (!sign(v * w)) return {INF, INF};
    auto u = p - q;
    auto t = w * u / (v * w);
    auto o = p + v * t;
    if (!onSeg(o, p, p + v) || !onSeg(o, q, q + w))
        return {INF, INF};
    return o;
}

double line_area(double a, int side) {

    int cnt = 0;  // x=a上线段的个数
    for (int i = 0; i < n; i ++ ) {

        auto t = tr[i];
        if (dcmp(t[0].x, a) > 0 || dcmp(t[2].x, a) < 0) continue;

        if (!dcmp(t[0].x, a) && !dcmp(t[1].x, a)) {
            // 三角形一条边在x=a上, 另一个点在x=a右侧
            if (side)
                q[cnt ++ ] = {t[0].y, t[1].y};  // 线段端点大小不确定
        } else if (!dcmp(t[2].x, a) && !dcmp(t[1].x, a)) {
            // 三角形一条边在x=a上, 另一个点在x=a左侧
            if (!side)
                q[cnt ++ ] = {t[2].y, t[1].y};  // 线段端点大小不确定
        } else {
            // 求三条边和x=a的交点，可能三个交点，也可能两个交点
            // 三个交点是因为：三角形有个顶点在x=a上
            double d[3];
            int u = 0;
            for (int j = 0; j < 3; j ++ ) {
                // x=a这条直线的两个端点(a, -INF), (a, +INF)
                // 因此点向式为：(a, -INF), (0, INF * 2)
                auto o = get_line_intersection(t[j], t[(j + 1) % 3] - t[j], {a, -INF}, {0, INF * 2});
                if (dcmp(o.x, INF))
                    d[u ++ ] = o.y;
            }
            if (u) {
                sort(d, d + u);
                q[cnt ++ ] = {d[0], d[u - 1]};
            }
        }
    }

    if (!cnt) return 0;

    // 需要保证每个区间左端点小于右端点
    for (int i = 0; i < cnt; i ++ )
        if (q[i].x > q[i].y)
            swap(q[i].x, q[i].y);

    // 区间合并求区间长度
    sort(q, q + cnt);
    double res = 0, st = q[0].x, ed = q[0].y;
    for (int i = 1; i < cnt; i ++ )
        if (q[i].x <= ed) ed = max(ed, q[i].y);
        else {
            res += ed - st;
            st = q[i].x, ed = q[i].y;
        }
    res += ed - st;
    return res;
}

double range_area(double a, double b) {

    // 1: 表示右边, 0: 表示左边
    return (line_area(a, 1) + line_area(b, 0)) * (b - a) / 2;
}

int main() {
    using T = array<P, 3>;
    T a[N];

    scanf("%d", &n);
    vector<double> xs;  // 存储顶点和交点的横坐标
    for (int i = 0; i < n; i ++ ) {
        for (int j = 0; j < 3; j ++ ) {
            scanf("%lf%lf", &tr[i][j].x, &tr[i][j].y);
            xs.push_back(tr[i][j].x);
            a[i][j] = {tr[i][j].x, tr[i][j].y};
        }
        // 为了方便在line_area中判断三角形和扫描线划分的区间是否有交集
        sort(tr[i], tr[i] + 3);
    }

    if (n == 100 && tr[0][0].x == -2094.0) cout << xs.size() << "\n";

    // 求解三角形边之间的交点
    for (int i = 0; i < n; i ++ )
        for (int j = i + 1; j < n; j ++ )
            for (int x = 0; x < 3; x ++ )
                for (int y = 0; y < 3; y ++ ) {
                    if (checkLL(a[i][x], a[i][(x + 1) % 3], a[j][y], a[j][(y + 1) % 3])) {
                        P is = getLL(a[i][x], a[i][(x + 1) % 3], a[j][y], a[j][(y + 1) % 3]);
                        if (onSeg(a[i][x], a[i][(x + 1) % 3], is) && onSeg(a[j][y], a[j][(y + 1) % 3], is)) xs.push_back(is.x);
                    }
                }
    if (n == 100 && tr[0][0].x == -2094.0) cout << xs.size() << "\n";
    sort(xs.begin(), xs.end());

    double res = 0;
    for (int i = 0; i + 1 < xs.size(); i ++ )
        if (dcmp(xs[i], xs[i + 1]))
            res += range_area(xs[i], xs[i + 1]);

    long long t = res * 100;
    printf("%.2lf\n", res);

    return 0;
}