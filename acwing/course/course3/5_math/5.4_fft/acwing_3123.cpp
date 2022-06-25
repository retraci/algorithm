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
template<int SZ>
struct FFT {
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

    int base;
    num roots[1 << (__lg(SZ) + 2)];
    int rev[1 << (__lg(SZ) + 2)];
    num fa[1 << (__lg(SZ) + 1)], fb[1 << (__lg(SZ) + 1)];

    FFT() {
        base = 1;
        roots[0] = {0, 0}, roots[1] = {1, 0};
        rev[0] = 0, rev[1] = 1;
    }

    void ensure_base(int nbase) {
        if (nbase <= base) return;

        for (int i = 0; i < (1 << nbase); i++) {
            rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
        }
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

    void dft(num a[], int n) {
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

    vector<int> multiply(const vector<int> &a, const vector<int> &b) {
        int need = a.size() + b.size() - 1;
        int nbase = 0;
        while ((1 << nbase) < need) nbase++;
        ensure_base(nbase);
        int sz = 1 << nbase;
        for (int i = 0; i < sz; i++) {
            int x = (i < a.size() ? a[i] : 0);
            int y = (i < b.size() ? b[i] : 0);
            fa[i] = num(x, y);
        }

        dft(fa, sz);
        num r(0, -0.25 / sz);
        for (int i = 0; i <= (sz >> 1); i++) {
            int j = (sz - i) & (sz - 1);
            num z = (fa[j] * fa[j] - (fa[i] * fa[i]).conj()) * r;
            if (i != j) fa[j] = (fa[i] * fa[i] - (fa[j] * fa[j]).conj()) * r;
            fa[i] = z;
        }

        dft(fa, sz);
        vector<int> res(need);
        for (int i = 0; i < need; i++) res[i] = fa[i].x + 0.5;
        return res;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1e5 + 10;

string a, b;
FFT<N> fft;

void solve() {
    vector<int> A(a.size()), B(b.size());
    for (int i = 0; i < a.size(); i++) A[a.size() - 1 - i] = a[i] - '0';
    for (int i = 0; i < b.size(); i++) B[b.size() - 1 - i] = b[i] - '0';

    auto C = fft.multiply(A, B);
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