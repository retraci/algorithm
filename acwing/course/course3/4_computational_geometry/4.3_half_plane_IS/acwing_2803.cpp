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
mt19937 mrnd(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int mod) {
    return mrnd() % mod;
}

// region 计算几何基础
using cgt = double;
const cgt eps = 1e-9;

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

    cgt abs() { return sqrt(abs2()); }

    cgt abs2() { return x * x + y * y; }

    // 逆时针转90
    P rot90() { return P(-y, x); }

    P unit() { return *this / abs(); }

    // 1: [0, PI), 0: [-PI, 0)
    int quad() { return sign(y) == 1 || (sign(y) == 0 && sign(x) >= 0); }

    // 逆时针转
    P rot(cgt an) { return {x * cos(an) - y * sin(an), x * sin(an) + y * cos(an)}; }
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

// 半平面交, 检查是否要弹出队列, u, v交点是否在 w 的左边
bool check(L u, L v, L w) {
    P cp = getLL(u, v);
    return sign(w.dir().det(cp - w[0])) > 0;
}

// 半平面交(保留左边, 删除右边)
vector<P> halfPlaneIS(vector<L> ls) {
    sort(ls.begin(), ls.end(), [](L &l0, L &l1) {
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

// 求凸包面积
cgt area(vector<P> &ps) {
    cgt res = 0;
    for (int i = 0; i < ps.size(); i++) {
        res += ps[i].det(ps[(i + 1) % ps.size()]);
    }
    return res / 2;
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 510;

int tt;
L a[N];

void solve() {
    auto t = halfPlaneIS(vector<L>(a + 1, a + tt + 1));
    cgt ans = area(t);

    cout << fixed << setprecision(3);
    cout << ans << "\n";
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
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            int m;
            cin >> m;
            vector<P> tmp;
            while (m--) {
                cgt x, y;
                cin >> x >> y;
                tmp.push_back({x, y});
            }

            for (int j = 0; j < tmp.size(); j++) {
                a[++tt] = {tmp[j], tmp[(j + 1) % tmp.size()]};
            }
        }
        solve();
    }

    return 0;
}