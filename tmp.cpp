#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

typedef long long LL;
const int N = 100010;

int n, m, k, len;
int w[N];
LL ans[N];
struct Query {
    int id, l, r;
    LL res;
} q[N];
struct Range {
    int id, l, r, t;
};
vector<Range> range[N];
int f[N], g[N];

inline int get_count(int x) {
    int res = 0;
    while (x) res += x & 1, x >>= 1;
    return res;
}

inline int get(int x) {
    return x / len;
}

bool cmp(const Query &a, const Query &b) {
    int i = get(a.l), j = get(b.l);
    if (i != j) return i < j;
    return a.r < b.r;
}

void debug() {
    std::cout << "\n";
}

template<class T, class... OtherArgs>
void debug(T &&var, OtherArgs &&... args) {
    std::cout << std::forward<T>(var) << " ";
    debug(std::forward<OtherArgs>(args)...);
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
    vector<int> nums;
    for (int i = 0; i < 1 << 14; i++)
        if (get_count(i) == k)
            nums.push_back(i);
    for (int i = 1; i <= n; i++) {
        for (auto y: nums) ++g[w[i] ^ y];
        f[i] = g[w[i + 1]];
    }
    for (int i = 0; i < m; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        q[i] = {i, l, r};
    }
    len = sqrt(n);
    sort(q, q + m, cmp);

    for (int i = 0, cl = 1, cr = 0; i < m; i++) {
        int L = q[i].l, R = q[i].r;


        if (cl < L) range[cr].push_back({i, cl, L - 1, -1});
        while (cl < L) q[i].res += f[cl - 1] + !k, cl++;
        if (cl > L) range[cr].push_back({i, L, cl - 1, 1});
        while (cl > L) q[i].res -= f[cl - 2] + !k, cl--;
        if (cr > R) range[cl - 1].push_back({i, R + 1, cr, 1});
        while (cr > R) q[i].res -= f[--cr];
        if (cr < R) range[cl - 1].push_back({i, cr + 1, R, -1});
        while (cr < R) q[i].res += f[cr++];
    }

    memset(g, 0, sizeof g);
    for (int i = 1; i <= n; i++) {
        for (auto y: nums) ++g[w[i] ^ y];
        for (auto &rg: range[i]) {
            int id = rg.id, l = rg.l, r = rg.r, t = rg.t;
            debug(i, l, r, t);

            for (int x = l; x <= r; x++)
                q[id].res += g[w[x]] * t;
        }
    }

    for (int i = 1; i < m; i++) q[i].res += q[i - 1].res;
    for (int i = 0; i < m; i++) ans[q[i].id] = q[i].res;
    for (int i = 0; i < m; i++) printf("%lld\n", ans[i]);

    return 0;
}