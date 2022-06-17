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

    bool operator<(P p) const {
        int c = cmp(x, p.x);
        if (c) return c == -1;
        return cmp(y, p.y) == -1;
    }

    bool operator==(P o) const {
        return cmp(x, o.x) == 0 && cmp(y, o.y) == 0;
    }

    cgt dot(P p) { return x * p.x + y * p.y; }

    cgt det(P p) const { return x * p.y - y * p.x; }

    cgt distTo(P p) { return (*this - p).abs(); }

    cgt alpha() { return atan2(y, x); }

    void read() { cin >> x >> y; }

    void write() { cout << "(" << x << ", " << y << ")" << "\n"; }

    cgt abs() { return sqrt(abs2()); }

    cgt abs2() { return x * x + y * y; }

    P rot90() { return P(-y, x); }

    P unit() { return *this / abs(); }

    int quad() const { return sign(y) == 1 || (sign(y) == 0 && sign(x) >= 0); }

    P rot(cgt an) { return {x * cos(an) - y * sin(an), x * sin(an) + y * cos(an)}; }
};

struct L { // ps[0] -> ps[1]
    P ps[2];

    P &operator[](int i) { return ps[i]; }

    P dir() { return ps[1] - ps[0]; }

    L(P a, P b) {
        ps[0] = a;
        ps[1] = b;
    }

    bool include(P p) { return sign((ps[1] - ps[0]).det(p - ps[0])) > 0; }

    L push() {
        P delta = (ps[1] - ps[0]).rot90().unit() * eps;
        return {ps[0] + delta, ps[1] + delta};
    }
};

#define cross(p1, p2, p3) ((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y))
#define crossOp(p1, p2, p3) sign(cross(p1, p2, p3))

vector<P> convexHull(vector<P> ps) {
    int n = ps.size();
    if (n <= 1) return ps;
    sort(ps.begin(), ps.end());
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

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 10010;

int n;
P a[N];

cgt dist(const P &p1, const P &p2) {
    cgt dx = p1.x - p2.x, dy = p1.y - p2.y;
    return sqrtl(dx * dx + dy * dy);
}

void solve() {
    auto t = convexHull(vector<P>(a + 1, a + n + 1));

    cgt ans = 0;
    for (int i = 1; i < t.size(); i++) {
        ans += dist(t[i], t[i - 1]);
    }
    ans += dist(t[0], t.back());

    cout << fixed << setprecision(2);
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
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i].x >> a[i].y;
        solve();
    }

    return 0;
}