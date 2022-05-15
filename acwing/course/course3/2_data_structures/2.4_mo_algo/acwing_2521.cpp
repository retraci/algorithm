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
using ai4 = array<int, 4>;

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 10010;

int n, m, cq, cm;
int a[N];
ai4 qs[N];
pii ms[N];
int bl;
int cnt[(int) 1e6 + 1], cur;

void add(int x) {
    if (++cnt[x] == 1) cur++;
}

void del(int x) {
    if (--cnt[x] == 0) cur--;
}

int get(int i) {
    return (i - 1) / bl + 1;
}

void solve() {
    bl = cbrt(1LL * n * (cm + 1));

    sort(qs + 1, qs + cq + 1, [](auto &a, auto &b) {
        int al = get(a[1]), bl = get(b[1]);
        int ar = get(a[2]), br = get(b[2]);

        if (al != bl) return al < bl;
        if (ar != br) return ar < br;
        return a[3] < b[3];
    });

    fill(cnt, cnt + (int) 1e6 + 1, 0), cur = 0;
    vector<int> ans(cq + 1);
    int cl = 1, cr = 0, ck = 0;
    for (int i = 1; i <= cq; i++) {
        auto [qid, L, R, k] = qs[i];

        while (k > ck) {
            auto &[p, x] = ms[++ck];

            if (cl <= p && p <= cr) del(a[p]), add(x);
            swap(a[p], x);
        }
        while (k < ck) {
            auto &[p, x] = ms[ck--];

            if (cl <= p && p <= cr) del(a[p]), add(x);
            swap(a[p], x);
        }

        while (cl < L) del(a[cl++]);
        while (cl > L) add(a[--cl]);
        while (cr > R) del(a[cr--]);
        while (cr < R) add(a[++cr]);

        ans[qid] = cur;
    }

    for (int i = 1; i <= cq; i++) cout << ans[i] << "\n";
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
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= m; i++) {
            string op;
            cin >> op;

            if (op[0] == 'Q') {
                int L, R;
                cin >> L >> R;

                cq++;
                qs[cq] = {cq, L, R, cm};
            } else {
                int p, x;
                cin >> p >> x;

                ms[++cm] = {p, x};
            }
        }

        solve();
    }

    return 0;
}