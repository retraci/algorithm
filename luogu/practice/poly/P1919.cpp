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

// region fft
namespace FFT {
    using fftt = double;
    const fftt PI = acosl(-1.0);

    struct num {
        fftt x, y;

        num() { x = y = 0; }
        num(fftt x, fftt y) : x(x), y(y) {}

        inline num operator+(num rhs) const { return num(x + rhs.x, y + rhs.y); }
        inline num operator-(num rhs) const { return num(x - rhs.x, y - rhs.y); }
        inline num operator*(num rhs) const { return num(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x); }
        inline num conj() const { return num(x, -y); }
    };

    int base = 1;
    vector<num> roots = {{0, 0}, {1, 0}};
    vector<int> rev = {0, 1};

    void ensure_base(int nbase) {
        if (nbase <= base) return;

        rev.resize(1 << nbase);
        for (int i = 0; i < (1 << nbase); i++) {
            rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
        }
        roots.resize(1 << nbase);
        while (base < nbase) {
            fftt angle = 2 * PI / (1 << (base + 1));
            for (int i = 1 << (base - 1); i < (1 << base); i++) {
                roots[i << 1] = roots[i];
                fftt angle_i = angle * (2 * i + 1 - (1 << base));
                roots[(i << 1) + 1] = num(cos(angle_i), sin(angle_i));
            }
            base++;
        }
    }

    void fft(vector<num> &a, int n = -1) {
        if (n == -1) n = a.size();
        assert((n & (n - 1)) == 0);

        int zeros = __builtin_ctz(n);
        ensure_base(zeros);
        int shift = base - zeros;
        for (int i = 0; i < n; i++) {
            int j = rev[i] >> shift;
            if (i < j) swap(a[i], a[j]);
        }
        for (int k = 1; k < n; k <<= 1) {
            for (int i = 0; i < n; i += 2 * k) {
                for (int j = 0; j < k; j++) {
                    num z = a[i + j + k] * roots[j + k];
                    a[i + j + k] = a[i + j] - z;
                    a[i + j] = a[i + j] + z;
                }
            }
        }
    }

    vector<num> fa, fb;
    vector<int> multiply(const vector<int> &a, const vector<int> &b) {
        int need = a.size() + b.size() - 1;
        int nbase = 0;
        while ((1 << nbase) < need) nbase++;
        ensure_base(nbase);
        int sz = 1 << nbase;
        if (sz > fa.size()) fa.resize(sz);
        for (int i = 0; i < sz; i++) {
            int x = (i < a.size() ? a[i] : 0);
            int y = (i < b.size() ? b[i] : 0);
            fa[i] = num(x, y);
        }

        fft(fa, sz);
        num r(0, -0.25 / sz);
        for (int i = 0; i <= (sz >> 1); i++) {
            int j = (sz - i) & (sz - 1);
            num z = (fa[j] * fa[j] - (fa[i] * fa[i]).conj()) * r;
            if (i != j) fa[j] = (fa[i] * fa[i] - (fa[j] * fa[j]).conj()) * r;
            fa[i] = z;
        }

        fft(fa, sz);
        vector<int> res(need);
        for (int i = 0; i < need; i++) res[i] = fa[i].x + 0.5;
        return res;
    }

    vector<int> multiply_mod(vector<int> &a, vector<int> &b, int m, int eq = 0) {
        int need = a.size() + b.size() - 1;
        int nbase = 0;
        while ((1 << nbase) < need) nbase++;
        ensure_base(nbase);
        int sz = 1 << nbase;
        if (sz > fa.size()) fa.resize(sz);
        for (int i = 0; i < a.size(); i++) {
            int x = (a[i] % m + m) % m;
            fa[i] = num(x & ((1 << 15) - 1), x >> 15);
        }
        fill(fa.begin() + a.size(), fa.begin() + sz, num {0, 0});
        fft(fa, sz);
        if (sz > fb.size()) {
            fb.resize(sz);
        }
        if (eq) {
            copy(fa.begin(), fa.begin() + sz, fb.begin());
        } else {
            for (int i = 0; i < b.size(); i++) {
                int x = (b[i] % m + m) % m;
                fb[i] = num(x & ((1 << 15) - 1), x >> 15);
            }
            fill(fb.begin() + b.size(), fb.begin() + sz, num {0, 0});
            fft(fb, sz);
        }
        fftt ratio = 0.25 / sz;
        num r2(0, -1);
        num r3(ratio, 0);
        num r4(0, -ratio);
        num r5(0, 1);
        for (int i = 0; i <= (sz >> 1); i++) {
            int j = (sz - i) & (sz - 1);
            num a1 = (fa[i] + fa[j].conj());
            num a2 = (fa[i] - fa[j].conj()) * r2;
            num b1 = (fb[i] + fb[j].conj()) * r3;
            num b2 = (fb[i] - fb[j].conj()) * r4;
            if (i != j) {
                num c1 = (fa[j] + fa[i].conj());
                num c2 = (fa[j] - fa[i].conj()) * r2;
                num d1 = (fb[j] + fb[i].conj()) * r3;
                num d2 = (fb[j] - fb[i].conj()) * r4;
                fa[i] = c1 * d1 + c2 * d2 * r5;
                fb[i] = c1 * d2 + c2 * d1;
            }
            fa[j] = a1 * b1 + a2 * b2 * r5;
            fb[j] = a1 * b2 + a2 * b1;
        }
        fft(fa, sz);
        fft(fb, sz);
        vector<int> res(need);
        for (int i = 0; i < need; i++) {
            ll aa = fa[i].x + 0.5;
            ll bb = fb[i].x + 0.5;
            ll cc = fa[i].y + 0.5;
            res[i] = (aa + ((bb % m) << 15) + ((cc % m) << 30)) % m;
        }
        return res;
    }

    vector<int> square_mod(vector<int> &a, int m) {
        return multiply_mod(a, a, m, 1);
    }
};
// ednregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};

string a, b;

void solve() {
    vector<int> A(a.size()), B(b.size());
    for (int i = 0; i < a.size(); i++) A[a.size() - 1 - i] = a[i] - '0';
    for (int i = 0; i < b.size(); i++) B[b.size() - 1 - i] = b[i] - '0';

    auto C = FFT::multiply(A, B);
    int lim = C.size();
    for (int i = 0; i < lim; i++) {
        int t = C[i];
        C[i] = t % 10;
        if (t >= 10) {
            if (i + 1 >= lim) C.push_back(0), lim++;
            C[i + 1] += t / 10;
        }
    }

    while (C.size() > 1 && C.back() == 0) C.pop_back();
    reverse(C.begin(), C.end());
    for (int x : C) cout << x;
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
        cin >> a >> b;
        solve();
    }

    return 0;
}