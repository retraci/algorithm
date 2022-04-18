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
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <cmath>

using namespace std;
constexpr int P = 998244353;
using i64 = long long;

int norm(int x) {
    if (x < 0) {
        x += P;
    }
    if (x >= P) {
        x -= P;
    }
    return x;
}

template<class T>
T power(T a, int b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}

struct Z {
    int x;

    Z(int x = 0) : x(norm(x)) {}

    int val() const {
        return x;
    }

    Z operator-() const {
        return Z(norm(P - x));
    }

    Z inv() const {
        return power(*this, P - 2);
    }

    Z &operator*=(const Z &rhs) {
        x = i64(x) * rhs.x % P;
        return *this;
    }

    Z &operator+=(const Z &rhs) {
        x = norm(x + rhs.x);
        return *this;
    }

    Z &operator-=(const Z &rhs) {
        x = norm(x - rhs.x);
        return *this;
    }

    Z &operator/=(const Z &rhs) {
        return *this *= rhs.inv();
    }

    friend Z operator*(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res *= rhs;
        return res;
    }

    friend Z operator+(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res += rhs;
        return res;
    }

    friend Z operator-(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res -= rhs;
        return res;
    }

    friend Z operator/(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res /= rhs;
        return res;
    }
};

const int N = 1e7 + 5;
Z phi[N], f[N], s[N];
vector<int> pri;

Z find(long long n, long long m) {
    Z ans = 0;
    for (int i = 1; i * i <= m; i++)
        if (m % i == 0) {
            int j = m / i;
            ans = ans + phi[i] * ((n / i) % P);
            if (i != j)
                ans = ans + phi[j] * ((n / j) % P);
        }
    return ans;
}

bool vis[N];
int cnt[N];

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int m = 1e7;
    phi[1] = f[1] = 1;
    for (int i = 2; i <= m; ++i) {
        if (!vis[i]) {
            pri.push_back(i);
            phi[i] = i - 1;
            f[i] = phi[i] + i;
            cnt[i] = i;
        }
        for (int j: pri) {
            if (i * j > m) break;
            vis[i * j] = 1;
            cnt[i * j] = j;
            if (i % j == 0) {
                cnt[i * j] = cnt[i] * j;
                phi[i * j] = phi[i] * j;
                int pre = cnt[i * j] / j;
                if (cnt[i] == i) f[i * j] = f[i] * j + phi[i * j];
                else f[i * j] = f[cnt[i] * j] * f[i / cnt[i]];
                break;
            }
            phi[i * j] = phi[i] * phi[j];
            f[i * j] = f[i] * f[j];
        }
    }
    for (int i = 1; i <= m; ++i) s[i] = s[i - 1] + f[i] * (3 * i + 3) + i;


    int t;
    cin >> t;
//    int cur = 10000;
    while (t--) {
        __int128_t n = 0;
        string a;
        cin >> a;
        int len = a.size();
        for (int i = 0; i < len; i++)
            n = n * 10 + a[i] - 48;
        __int128_t l = 0, r = N, lim = 0;
        while (l <= r) {
            __int128_t mid = (l + r) >> 1;
            if (mid * mid * mid <= n) l = mid + 1;
            else r = mid - 1;
        }
        l--;
        Z ans = (n / l - l * l) % P * f[l] + l + find(n % l, l);
        ans += s[l - 1];
        cout << ans.val() << "\n";
    }
    return 0;
}
