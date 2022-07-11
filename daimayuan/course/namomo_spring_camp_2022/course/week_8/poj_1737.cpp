#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <bitset>

using namespace std;

// region 高精
struct Big {
    int sign;
    std::vector<int> v;

    Big() : sign(1) {}

    Big(const std::string &s) { *this = s; }

    Big(int v) {
        char buf[21];
        sprintf(buf, "%d", v);
        *this = buf;
    }

    void zip(int unzip) {
        if (unzip == 0) {
            for (int i = 0; i < (int) v.size(); i++) {
                v[i] = get_pos(i * 4) + get_pos(i * 4 + 1) * 10 + get_pos(i * 4 + 2) * 100 + get_pos(i * 4 + 3) * 1000;
            }
        } else
            for (int i = (v.resize(v.size() * 4), (int) v.size() - 1), a; i >= 0; i--) {
                a = (i % 4 >= 2) ? v[i / 4] / 100 : v[i / 4] % 100, v[i] = (i & 1) ? a / 10 : a % 10;
            }
        setsign(1, 1);
    }

    int get_pos(unsigned pos) const {
        return pos >= v.size() ? 0 : v[pos];
    }

    Big &setsign(int newsign, int rev) {
        for (int i = (int) v.size() - 1; i > 0 && v[i] == 0; i--)
            v.erase(v.begin() + i);
        sign = (v.size() == 0 || (v.size() == 1 && v[0] == 0)) ? 1 : (rev ? newsign * sign : newsign);
        return *this;
    }

    std::string to_str() const {
        Big b = *this;
        std::string s;
        for (int i = (b.zip(1), 0); i < (int) b.v.size(); i++) {
            s += char(*(b.v.rbegin() + i) + '0');
        }
        return (sign < 0 ? "-" : "") + (s.empty() ? std::string("0") : s);
    }

    bool absless(const Big &b) const {
        if (v.size() != b.v.size()) return v.size() < b.v.size();
        for (int i = (int) v.size() - 1; i >= 0; i--)
            if (v[i] != b.v[i]) return v[i] < b.v[i];
        return false;
    }

    Big operator-() const {
        Big c = *this;
        c.sign = (v.size() > 1 || v[0]) ? -c.sign : 1;
        return c;
    }

    Big &operator=(const std::string &s) {
        if (s[0] == '-') {
            *this = s.substr(1);
        } else {
            for (int i = (v.clear(), 0); i < (int) s.size(); i++) {
                v.push_back(*(s.rbegin() + i) - '0');
            }
            zip(0);
        }
        return setsign(s[0] == '-' ? -1 : 1, sign = 1);
    }

    bool operator<(const Big &b) const {
        return sign != b.sign ? sign < b.sign : (sign == 1 ? absless(b) : b.absless(*this));
    }

    bool operator==(const Big &b) const {
        return v == b.v && sign == b.sign;
    }

    Big &operator+=(const Big &b) {
        if (sign != b.sign) return *this = (*this) - -b;
        v.resize(std::max(v.size(), b.v.size()) + 1);
        for (int i = 0, carry = 0; i < (int) b.v.size() || carry; i++) {
            carry += v[i] + b.get_pos(i);
            v[i] = carry % 10000, carry /= 10000;
        }
        return setsign(sign, 0);
    }

    Big operator+(const Big &b) const {
        Big c = *this;
        return c += b;
    }

    void add_mul(const Big &b, int mul) {
        v.resize(std::max(v.size(), b.v.size()) + 2);
        for (int i = 0, carry = 0; i < (int) b.v.size() || carry; i++) {
            carry += v[i] + b.get_pos(i) * mul;
            v[i] = carry % 10000, carry /= 10000;
        }
    }

    Big operator-(const Big &b) const {
        if (b.v.empty() || b.v.size() == 1 && b.v[0] == 0) return *this;
        if (sign != b.sign) return (*this) + -b;
        if (absless(b)) return -(b - *this);
        Big c;
        for (int i = 0, borrow = 0; i < (int) v.size(); i++) {
            borrow += v[i] - b.get_pos(i);
            c.v.push_back(borrow);
            c.v.back() -= 10000 * (borrow >>= 31);
        }
        return c.setsign(sign, 0);
    }

    Big operator*(const Big &b) const {
        if (b < *this) return b * *this;
        Big c, d = b;
        for (int i = 0; i < (int) v.size(); i++, d.v.insert(d.v.begin(), 0)) c.add_mul(d, v[i]);
        return c.setsign(sign * b.sign, 0);
    }

    Big operator/(const Big &b) const {
        Big c, d;
        d.v.resize(v.size());
        double db = 1.0 / (b.v.back()
                           + (b.get_pos((unsigned) b.v.size() - 2) / 1e4)
                           + (b.get_pos((unsigned) b.v.size() - 3) + 1) / 1e8);
        for (int i = (int) v.size() - 1; i >= 0; i--) {
            c.v.insert(c.v.begin(), v[i]);
            int m = (int) ((c.get_pos((int) b.v.size()) * 10000 + c.get_pos((int) b.v.size() - 1)) * db);
            c = c - b * m, d.v[i] += m;
            while (!(c < b)) c = c - b, d.v[i] += 1;
        }
        return d.setsign(sign * b.sign, 0);
    }

    Big operator%(const Big &b) const { return *this - *this / b * b; }

    bool operator>(const Big &b) const { return b < *this; }

    bool operator<=(const Big &b) const { return !(b < *this); }

    bool operator>=(const Big &b) const { return !(*this < b); }

    bool operator!=(const Big &b) const { return !(*this == b); }
};
// endregion

const int N = 55;

int n;
Big f[N];
Big C[N][N];
Big pw2[55];

void solve() {
    cout << f[n].to_str() << "\n";
}

void prework() {
    pw2[0] = Big(1);
    int lst = 0;
    Big cur = Big(1);
    for (int i = 1; i <= 50; i++) {
        int x = i * (i - 1) / 2;
        int dta = x - lst;
        while (dta--) cur = cur * 2;
        pw2[i] = cur;

        lst = x;
    }

    for (int i = 0; i <= 50; i++) C[i][0] = Big(1);
    for (int i = 1; i <= 50; i++) {
        for (int j = 1; j <= i; j++) {
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
        }
    }

    f[1] = Big(1);
    for (int i = 2; i <= 50; i++) {
        f[i] = pw2[i];
        for (int j = 1; j <= i - 1; j++) {
            f[i] = f[i] - C[i - 1][j - 1] * f[j] * pw2[i - j];
        }
    }
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
    while (cin >> n, n) {
        solve();
    }

    return 0;
}