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

    // 1: x轴上方, [0, PI), 0: x轴下方, [-PI, 0)
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
// 非严格就 return >= 0
bool check(L u, L v, L w) {
    P cp = getLL(u, v);
    return sign(w.dir().det(cp - w[0])) >= 0;
}

// 半平面交(保留左边, 删除右边)
vector<int> halfPlaneIS(vector<pair<L, vector<int>>> ls) {
    sort(ls.begin(), ls.end(), [](auto &l0, auto &l1) {
        // 同向, 左边的优先
        if (sameDir(l0.fi, l1.fi)) {
            return sign(l1.fi.dir().det(l0.fi[0] - l1.fi[0])) > 0;
        } else {
            P a = l0.fi.dir(), b = l1.fi.dir();
            if (a.quad() != b.quad()) {
                return a.quad() < b.quad();
            } else {
                return sign(a.det(b)) > 0;
            }
        }
    });

    deque<pair<L, vector<int>>> q;
    for (int i = 0; i < ls.size(); i++) {
        if (i && sameDir(ls[i].fi, ls[i - 1].fi)) continue;
        while (q.size() > 1 && !check(q[q.size() - 2].fi, q[q.size() - 1].fi, ls[i].fi)) q.pop_back();
        while (q.size() > 1 && !check(q[0].fi, q[1].fi, ls[i].fi)) q.pop_front();
        q.push_back(ls[i]);
    }
    while (q.size() > 2 && !check(q[q.size() - 2].fi, q[q.size() - 1].fi, q[0].fi)) q.pop_back();
    while (q.size() > 2 && !check(q[0].fi, q[1].fi, q[q.size() - 1].fi)) q.pop_front();

    vector<int> res;
    for (int i = 0; i < q.size(); i++) res.insert(res.end(), q[i].se.begin(), q[i].se.end());
    return res;
}
// endregion

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 10010;

int n;
int a[N], b[N];

void solve() {
    map<pii, vector<int>> mp;
    for (int i = 1; i <= n; i++) {
        mp[{a[i], b[i]}].push_back(i);
    }

    vector<pair<L, vector<int>>> ls;
    for (auto &[line, ids] : mp) {
        auto [ta, tb] = line;
        P p1 = {0, ta}, p2 = {1, ta + tb};
        ls.push_back({{p1, p2}, ids});
    }
    ls.push_back({L(P(0, 1), P(0, 0)), {}});
    ls.push_back({L(P(0, 0), P(1, 0)), {}});

    auto ans = halfPlaneIS(ls);
    sort(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    for (int x : ans) cout << x << " ";
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
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];
        solve();
    }

    return 0;
}