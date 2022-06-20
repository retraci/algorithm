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

// 求直线是否相交
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

// 求线段是否严格相交(重叠 !=> 相交, 端点 !=> 相交)
bool checkSSStrict(P p1, P p2, P q1, P q2) {
    return crossOp(p1, p2, q1) * crossOp(p1, p2, q2) < 0
        && crossOp(q1, q2, p1) * crossOp(q1, q2, p2) < 0;
}

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

// 是否严格在线段上(在端点上 !=> 在线段上)
bool onSegStrict(P p1, P p2, P q) {
    return crossOp(p1, p2, q) == 0 && sign((q - p1).dot(p1 - p2)) * sign((q - p2).dot(p1 - p2)) < 0;
}

P proj(P p1, P p2, P q) {
    P dir = p2 - p1;
    return p1 + dir * (dir.dot(q - p1) / dir.abs2());
}

P reflect(P p1, P p2, P q) {
    return proj(p1, p2, q) * 2 - q;
}

cgt nearest(P p1, P p2, P q) {
    if (p1 == p2) return p1.distTo(q);
    P h = proj(p1, p2, q);
    if (isMiddle(p1, h, p2)) return q.distTo(h);
    return min(p1.distTo(q), p2.distTo(q));
}

cgt disSS(P p1, P p2, P q1, P q2) {
    if (isSS(p1, p2, q1, q2)) return 0;
    return min(min(nearest(p1, p2, q1), nearest(p1, p2, q2)), min(nearest(q1, q2, p1), nearest(q1, q2, p2)));
}

// 求 0->p1, 0->p2 构成的角的弧度
cgt rad(P p1, P p2) {
    return atan2l(p1.det(p2), p1.dot(p2));
}

cgt inCircle(P p1, P p2, P p3) {
    cgt A = p1.distTo(p2);
    cgt B = p2.distTo(p3);
    cgt C = p3.distTo(p1);
    return sqrtl(A * B * C / (A + B + C));
}

// polygon

// 切凸包, 把直线左边和交点都返回 (x)
vector<P> convexCut(const vector<P> &ps, P q1, P q2) {
    vector<P> res;
    for (int i = 0; i < ps.size(); i++) {
        P p1 = ps[i], p2 = ps[(i + 1) % ps.size()];
        int d1 = crossOp(q1, q2, p1), d2 = crossOp(q1, q2, p2);
        if (d1 >= 0) res.push_back(p1);
        if (d1 * d2 < 0) res.push_back(getLL(p1, p2, q1, q2));
    }
    return res;
}

// 点与多边形关系 (x)
int contain(const vector<P> &ps, P p) { // 2: inside, 1: on_seg, 0: outside
    int ret = 0;
    for (int i = 0; i < ps.size(); i++) {
        P u = ps[i], v = ps[(i + 1) % ps.size()];
        if (onSeg(u, v, p)) return 1;
        if (cmp(u.y, v.y) <= 0) swap(u, v);
        if (cmp(p.y, u.y) > 0 || cmp(p.y, v.y) <= 0) continue;
        ret ^= crossOp(p, u, v) > 0;
    }
    return ret * 2;
}

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

// 求多边形面积
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
    cgt ret = ps[i].distTo(ps[j]);
    do {
        if ((ps[(i + 1) % n] - ps[i]).det(ps[(j + 1) % n] - ps[j]) >= 0) j = (j + 1) % n;
        else i = (i + 1) % n;
        ret = max(ret, ps[i].distTo(ps[j]));
    } while (i != is || j != js);
    return ret;
}

// 最小矩形覆盖
using aP4 = array<P, 4>;
pair<cgt, aP4> rotatingCalipers(const vector<P> &ps) {
    cgt mi = 1e100;
    aP4 res;

    int n = ps.size();
    int j = 1, a = 1, b = 1;
    for (int i = 0; i < n; i++) {
        auto st = ps[i], ed = ps[(i + 1) % n];
        while (cmp(cross(st, ed, ps[j]), cross(st, ed, ps[(j + 1) % n])) < 0) j = (j + 1) % n;
        while (cmp(scalar(st, ed, ps[a]), scalar(st, ed, ps[(a + 1) % n])) < 0) a = (a + 1) % n;
        if (i == 0) b = j;
        while (cmp(scalar(st, ed, ps[b]), scalar(st, ed, ps[(b + 1) % n])) > 0) b = (b + 1) % n;

        cgt h = cross(st, ed, ps[j]) / (ed - st).abs();
        cgt w = (ed - st).dot(ps[a] - ps[b]) / (ed - st).abs();

        if (h * w < mi) {
            mi = h * w;
            auto vx = (ed - st).unit();
            res[0] = st + (vx * (scalar(st, ed, ps[a]) / (ed - st).abs()));
            res[3] = st + (vx * (scalar(st, ed, ps[b]) / (ed - st).abs()));
            auto vy = vx.rot90();
            res[1] = res[0] + (vy * h);
            res[2] = res[3] + (vy * h);
        }
    }

    return {mi, res};
}
// endregion

// region 半平面交
// 求直线l1, l2交点
P getLL(P p1, P p2, P q1, P q2) {
    cgt a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
    return (p1 * a2 + p2 * a1) / (a1 + a2);
}

// 求直线l1, l2交点
P getLL(L l1, L l2) { return getLL(l1[0], l1[1], l2[0], l2[1]); }

// 直线平行(无方向)
bool parallel(L l0, L l1) { return sign(l0.dir().det(l1.dir())) == 0; }

// 直线同向(有方向)
bool sameDir(L l0, L l1) { return parallel(l0, l1) && sign(l0.dir().dot(l1.dir())) == 1; }

// endutil

// 半平面交, 检查是否要弹出队列, (u, v)交点是否严格在 w 的左边
// 严格: > 0, 非严格: return >= 0
bool check(L u, L v, L w) {
    P cp = getLL(u, v);
    return sign(w.dir().det(cp - w[0])) > 0;
}

// 半平面交(保留左边, 删除右边)
vector<P> halfPlaneIS(vector<L> ls) {
    sort(ls.begin(), ls.end(), [](L l0, L l1) {
        // 同向, 左边的优先
        if (sameDir(l0, l1)) {
            return sign(l1.dir().det(l0[0] - l1[0])) > 0;
        } else {
            P a = l0.dir(), b = l1.dir();
            if (a.quad() != b.quad()) {
                return a.quad() < b.quad();
            } else {
                return sign(a.det(b)) > 0;
            }
        }
    });

    deque<L> q;
    for (int i = 0; i < ls.size(); i++) {
        if (i && sameDir(ls[i], ls[i - 1])) continue;
        while (q.size() > 1 && !check(q[q.size() - 2], q[q.size() - 1], ls[i])) q.pop_back();
        while (q.size() > 1 && !check(q[0], q[1], ls[i])) q.pop_front();
        q.push_back(ls[i]);
    }
    while (q.size() > 2 && !check(q[q.size() - 2], q[q.size() - 1], q[0])) q.pop_back();
    while (q.size() > 2 && !check(q[0], q[1], q[q.size() - 1])) q.pop_front();

    vector<P> res;
    for (int i = 0; i < q.size(); i++) res.push_back(getLL(q[i], q[(i + 1) % q.size()]));
    return res;
}
// endregion

// region 最小圆覆盖
using C = pair<P, cgt>;

// 外心
P circumCenter(P a, P b, P c) {
    P bb = b - a, cc = c - a;
    cgt db = bb.abs2(), dc = cc.abs2(), d = 2 * bb.det(cc);
    return a - P(bb.y * dc - cc.y * db, cc.x * db - bb.x * dc) / d;
}

// endutil

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

// min_dist

// 平面最近点对
cgt min_dist(const vector<P> &ps, int l, int r) {
    if (r - l <= 5) {
        cgt ret = 1e100;
        for (int i = l; i < r; i++) {
            for (int j = l; j < i; j++) {
                ret = min(ret, ps[i].distTo(ps[j]));
            }
        }
        return ret;
    }
    int m = (l + r) >> 1;
    cgt ret = min(min_dist(ps, l, m), min_dist(ps, m, r));
    vector<P> qs;
    for (int i = l; i < r; i++) {
        if (abs(ps[i].x - ps[m].x) <= ret) qs.push_back(ps[i]);
    }
    sort(qs.begin(), qs.end(), [](P a, P b) { return a.y < b.y; });
    for (int i = 1; i < qs.size(); i++) {
        for (int j = i - 1; j >= 0 && qs[j].y >= qs[i].y - ret; --j) {
            ret = min(ret, qs[i].distTo(qs[j]));
        }
    }
    return ret;
}

int type(P o1, cgt r1, P o2, cgt r2) {
    cgt d = o1.distTo(o2);
    if (cmp(d, r1 + r2) == 1) return 4;
    if (cmp(d, r1 + r2) == 0) return 3;
    if (cmp(d, abs(r1 - r2)) == 1) return 2;
    if (cmp(d, abs(r1 - r2)) == 0) return 1;
    return 0;
}

// 求 圆-线 的交点
vector<P> getCL(P o, cgt r, P p1, P p2) {
    if (cmp(abs((o - p1).det(p2 - p1) / p1.distTo(p2)), r) > 0) return {};
    cgt x = (p1 - o).dot(p2 - p1), y = (p2 - p1).abs2(), d = x * x - y * ((p1 - o).abs2() - r * r);
    d = max(d, (cgt) 0.0);
    P m = p1 - (p2 - p1) * (x / y), dr = (p2 - p1) * (sqrtl(d) / y);
    return {m - dr, m + dr}; // along dir: p1->p2
}

// 求 圆-圆 的交点 (x)
vector<P> getCC(P o1, cgt r1, P o2, cgt r2) { // need to check whether two circles are the same
    cgt d = o1.distTo(o2);
    if (cmp(d, r1 + r2) == 1) return {};
    if (cmp(d, abs(r1 - r2)) == -1) return {};
    d = min(d, r1 + r2);
    cgt y = (r1 * r1 + d * d - r2 * r2) / (2 * d), x = sqrtl(r1 * r1 - y * y);
    P dr = (o2 - o1).unit();
    P q1 = o1 + dr * y, q2 = dr.rot90() * x;
    return {q1 - q2, q1 + q2}; // along circle 1
}

vector<P> tanCP(P o, cgt r, P p) {
    cgt x = (p - o).abs2(), d = x - r * r;
    if (sign(d) <= 0) return {}; // on circle => no tangent
    P q1 = o + (p - o) * (r * r / x);
    P q2 = (p - o).rot90() * (r * sqrtl(d) / x);
    return {q1 - q2, q1 + q2}; // counter clock-wise
}

vector<L> extanCC(P o1, cgt r1, P o2, cgt r2) {
    vector<L> ret;
    if (cmp(r1, r2) == 0) {
        P dr = (o2 - o1).unit().rot90() * r1;
        ret.push_back(L(o1 + dr, o2 + dr)), ret.push_back(L(o1 - dr, o2 - dr));
    } else {
        P p = (o2 * r1 - o1 * r2) / (r1 - r2);
        vector<P> ps = tanCP(o1, r1, p), qs = tanCP(o2, r2, p);
        for (int i = 0; i < min(ps.size(), qs.size()); i++) {
            ret.push_back(L(ps[i], qs[i])); // c1 counter-clock wise
        }
    }
    return ret;
}

vector<L> intanCC(P o1, cgt r1, P o2, cgt r2) {
    vector<L> ret;
    P p = (o1 * r2 + o2 * r1) / (r1 + r2);
    vector<P> ps = tanCP(o1, r1, p), qs = tanCP(o2, r2, p);
    for (int i = 0; i < min(ps.size(), qs.size()); i++) {
        ret.push_back(L(ps[i], qs[i])); // c1 counter-clock wise
    }
    return ret;
}

cgt areaCT(cgt r, P p1, P p2) {
    vector<P> is = getCL(P(0, 0), r, p1, p2);
    if (is.empty()) return r * r * rad(p1, p2) / 2;
    bool b1 = cmp(p1.abs2(), r * r) == 1, b2 = cmp(p2.abs2(), r * r) == 1;
    if (b1 && b2) {
        if (sign((p1 - is[0]).dot(p2 - is[0])) <= 0 && sign((p1 - is[0]).dot(p2 - is[0])) <= 0) {
            return r * r * (rad(p1, is[0]) + rad(is[1], p2)) / 2 + is[0].det(is[1]) / 2;
        } else {
            return r * r * rad(p1, p2) / 2;
        }
    }
    if (b1) return (r * r * rad(p1, is[0]) + is[0].det(p2)) / 2;
    if (b2) return (p1.det(is[1]) + r * r * rad(is[1], p2)) / 2;
    return p1.det(p2) / 2;
}

// 内心 (x)
P inCenter(P A, P B, P C) {
    cgt a = (B - C).abs(), b = (C - A).abs(), c = (A - B).abs();
    return (A * a + B * b + C * c) / (a + b + c);
}

// 外心
P circumCenter(P a, P b, P c) {
    P bb = b - a, cc = c - a;
    cgt db = bb.abs2(), dc = cc.abs2(), d = 2 * bb.det(cc);
    return a - P(bb.y * dc - cc.y * db, cc.x * db - bb.x * dc) / d;
}

// 垂心 (x)
P othroCenter(P a, P b, P c) {
    P ba = b - a, ca = c - a, bc = b - c;
    cgt Y = ba.y * ca.y * bc.y;
    cgt A = ca.x * ba.y - ba.x * ca.y;
    cgt x0 = (Y + ca.x * ba.y * b.x - ba.x * ca.y * c.x) / A;
    cgt y0 = -ba.x * (x0 - c.x) / ba.y + ca.y;
    return {x0, y0};
}
