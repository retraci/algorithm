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
using ai3 = array<int, 3>;
mt19937 mrnd(time(0));
mt19937_64 mrnd64(time(0));

// region 质因数分解, 枚举最小质数 (x < N)
vector<int> isp, mip, pr;

void init_prime(int lim) {
    isp = vector<int>(lim + 1, 1);
    mip.resize(lim + 1);

    isp[0] = isp[1] = 0;
    for (int i = 2; i <= lim; i++) {
        if (isp[i]) {
            pr.push_back(i);
            mip[i] = i;
        }

        for (int p : pr) {
            if (p > lim / i) break;

            mip[i * p] = p;
            isp[i * p] = 0;
            if (i % p == 0) break;
        }
    }
}

vector<pii> fs;

void divide(int x) {
    fs = {};
    while (x > 1) {
        int p = mip[x];
        int c = 0;
        while (x % p == 0) x /= p, c++;
        fs.push_back({p, c});
    }
}
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 2e5 + 10;

int n, m;
int a[N];
ai3 qs[N];
int bl, cur, cnt[(int) 1e6 + 1];
vector<pii> b[N];

int get(int i) {
    return (i - 1) / bl + 1;
}

void add(int i) {
    for (auto [p, c] : b[i]) {
        int pre = cnt[p];
        cnt[p] += c;
        if (pre % 3 == 0 && cnt[p] % 3 != 0) cur++;
        if (pre % 3 != 0 && cnt[p] % 3 == 0) cur--;
    }
}

void del(int i) {
    for (auto [p, c] : b[i]) {
        int pre = cnt[p];
        cnt[p] -= c;
        if (pre % 3 == 0 && cnt[p] % 3 != 0) cur++;
        if (pre % 3 != 0 && cnt[p] % 3 == 0) cur--;
    }
}

void solve() {
    for (int i = 1; i <= n; i++) {
        divide(a[i]);
        b[i] = fs;
    }

    bl = sqrt(n);
    sort(qs + 1, qs + m + 1, [](auto &a, auto &b) {
        int bid1 = get(a[1]), bid2 = get(b[1]);
        if (bid1 != bid2) return bid1 < bid2;
        return bid1 & 1 ? a[2] < b[2] : a[2] > b[2];
    });

    vector<int> ans(m + 1);
    int cl = 1, cr = 0;
    for (int i = 1; i <= m; i++) {
        auto [qid, L, R] = qs[i];

        while (cl < L) del(cl++);
        while (cl > L) add(--cl);
        while (cr > R) del(cr--);
        while (cr < R) add(++cr);

        ans[qid] = cur;
    }

    for (int i = 1; i <= m; i++) cout << (ans[i] ? "No" : "Yes") << "\n";
}

void prework() {
    init_prime(1e6);
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
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= m; i++) {
            int L, R;
            cin >> L >> R;
            qs[i] = {i, L, R};
        }
        solve();
    }

    return 0;
}