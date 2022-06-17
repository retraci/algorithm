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
const cgt eps = 1e-8;

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

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 110;

int n;
P a[N], b[N];

void solve() {
    vector<P> ps;
    for (int i = 1; i <= n; i++) {
        ps.push_back(a[i]);
        ps.push_back(b[i]);
    }

    for (int i = 0 ; i < 2 * n; i++) {
        for (int j = i + 1; j < 2 * n; j++) {
            if (ps[i] == ps[j]) continue;

            int flag = 0;
            for (int k = 1; k <= n; k++) {
                int sig1 = crossOp(ps[i], ps[j], a[k]), sig2 = crossOp(ps[i], ps[j], b[k]);
                if (sig1 * sig2 > 0) {
                    flag = 1;
                    break;
                }
            }
            if (!flag) {
                cout << "Yes!" << "\n";
                return;
            }
        }
    }

    cout << "No!" << "\n";
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
    cin >> _;
    while (_--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i].x >> a[i].y >> b[i].x >> b[i].y;
        }
        solve();
    }

    return 0;
}