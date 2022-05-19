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
#include <cassert>
#include <random>
#include <cmath>

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
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ai3 = array<int, 3>;
mt19937 mrnd(time(0));
mt19937_64 mrnd64(time(0));

int rnd(int mod) {
    return mrnd() % mod;
}

// region SA
template<int SZ>
struct SA {
    int n, m, sa[SZ + 10], rk[SZ + 10], prk[SZ * 2 + 10], id[SZ + 10], px[SZ + 10], cnt[SZ + 10];

    SA () {}

    // s 下标从 1 开始
    vector<int> get_sa(const string &s) {
        n = s.size() - 1, m = 300;
        fill(cnt, cnt + m + 1, 0);
        fill(prk, prk + 2 * n + 1, 0);

        for (int i = 1; i <= n; i++) cnt[rk[i] = s[i]]++;
        for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (int i = n; i >= 1; i--) sa[cnt[rk[i]]--] = i;

        for (int k = 1; k <= n; k <<= 1) {
            int p = 0;
            for (int i = n; i >= n - k + 1; i--) id[++p] = i;
            for (int i = 1; i <= n; i++) {
                if (sa[i] - k >= 1) id[++p] = sa[i] - k;
            }

            fill(cnt, cnt + m + 1, 0);
            for (int i = 1; i <= n; i++) cnt[px[i] = rk[id[i]]]++;
            for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
            for (int i = n; i >= 1; i--) sa[cnt[px[i]]--] = id[i];

            for (int i = 1; i <= n; i++) prk[i] = rk[i];
            rk[sa[1]] = 1, p = 1;
            for (int i = 2; i <= n; i++) {
                int x = sa[i], y = sa[i - 1];
                rk[sa[i]] = prk[x] == prk[y] && prk[x + k] == prk[y + k] ? p : ++p;
            }

            if (p == n) {
                vector<int> res(n + 1);
                for (int i = 1; i <= n; i++) res[i] = sa[i];
                return res;
            }

            m = p;
        }
    }

    vector<int> get_h(const string &s) {
        vector<int> res(n + 1);
        int k = 0;
        for (int i = 1; i <= n; i++) {
            if (rk[i] == 0) continue;
            if (k) k--;
            int j = sa[rk[i] - 1];
            while (s[i + k] == s[j + k]) k++;
            res[rk[i]] = k;
        }

        return res;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1e6 + 10;

SA<N> sautil;
string s;

void solve() {
    auto sa = sautil.get_sa(s);
    auto h = sautil.get_h(s);

    int n = s.size() - 1;
    for (int i = 1; i <= n; i++) cout << sa[i] << " ";
    cout << "\n";
    for (int i = 1; i <= n; i++) cout << h[i] << " ";
    cout << "\n";
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
        cin >> s;
        s = ' ' + s;
        solve();
    }

    return 0;
}