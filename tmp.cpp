#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <bitset>

// region hash_func
template<typename TT>
struct tuple_hash {
    size_t operator()(TT const &tt) const {
        return std::hash<TT>()(tt);
    }
};

template<class T>
inline void hash_combine(std::size_t &seed, T const &v) {
    seed ^= tuple_hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template<class Tuple, size_t Index = std::tuple_size<Tuple>::value - 1>
struct HashValueImpl {
    void operator()(size_t &seed, Tuple const &tuple) const {
        HashValueImpl<Tuple, Index - 1>{}(seed, tuple);
        hash_combine(seed, std::get<Index>(tuple));
    }
};

template<class Tuple>
struct HashValueImpl<Tuple, 0> {
    void operator()(size_t &seed, Tuple const &tuple) const {
        hash_combine(seed, std::get<0>(tuple));
    }
};

template<typename... TT>
struct tuple_hash<std::tuple<TT...>> {
    size_t operator()(std::tuple<TT...> const &tt) const {
        size_t seed = 0;
        HashValueImpl<std::tuple<TT...>>{}(seed, tt);
        return seed;
    }
};

template<typename T>
inline void hash_val(std::size_t &seed, const T &val) {
    hash_combine(seed, val);
}

template<typename T, typename... Types>
inline void hash_val(std::size_t &seed, const T &val, const Types &... args) {
    hash_combine(seed, val);
    hash_val(seed, args...);
}

template<typename... Types>
inline std::size_t hash_val(const Types &... args) {
    std::size_t seed = 0;
    hash_val(seed, args...);
    return seed;
}

struct pair_hash {
    template<class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &p) const {
        return hash_val(p.first, p.second);
    }
};
// endregion
// region general
#define ll long long
#define ld long double
#define ull unsigned long long
#define fi first
#define se second

typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
typedef std::tuple<int, int, int> ti3;
typedef std::tuple<ll, ll, ll> tl3;
typedef std::tuple<int, int, int, int> ti4;
typedef std::tuple<ll, ll, ll, ll> tl4;
// endregion
// region grid_delta
namespace grid_delta {
    // 上, 右, 下, 左  |  左上, 右上, 左下, 右下
    const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
    const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};
}
// endregion

using namespace std;
using namespace grid_delta;

#define mid (l+r>>1)
#define il inline
typedef set<int>::iterator IT;
int n, m;
const int N = 1e5 + 10, M = 5e6 + 10;

il int read() {
    int w = 0, x = 0;
    char c = 0;
    while (c > '9' || c < '0') w |= c == '-', c = getchar();
    while (c <= '9' && c >= '0') x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    return w ? -x : x;
}

int ls[M], rs[M], s[M], tot, op[N], rt[N], mem[M], ct;
set<int> srt;

il int newnode() {
    return ct ? mem[ct--] : ++tot;
}

il void del(int x) {
    mem[++ct] = x;
    s[x] = ls[x] = rs[x] = 0;
}

void update(int &x, int l, int r, int pos) {
    if (!x) x = newnode();
    s[x] = 1;
    if (l == r) return;
    if (pos <= mid) update(ls[x], l, mid, pos);
    else update(rs[x], mid + 1, r, pos);
}

int merge(int x, int y) {
    if (!x || !y) return x + y;
    s[x] += s[y];
    ls[x] = merge(ls[x], ls[y]);
    rs[x] = merge(rs[x], rs[y]);
    del(y);
    return x;
}

int query(int x, int l, int r) {
    if (l == r) return l;
    if (ls[x]) return query(ls[x], l, mid);
    else return query(rs[x], mid + 1, r);
}

void split(int x, int &y, int k, int op) {
    if (s[x] == k) return;
    s[y = newnode()] = s[x] - k, s[x] = k;
    if (op) {
        if (k <= s[rs[x]]) split(rs[x], rs[y], k, op), swap(ls[x], ls[y]);
        else split(ls[x], ls[y], k - s[rs[x]], op);
    } else {
        if (k <= s[ls[x]]) split(ls[x], ls[y], k, op), swap(rs[x], rs[y]);
        else split(rs[x], rs[y], k - s[ls[x]], op);
    }
}

il IT spl(int x) {
    IT w = srt.lower_bound(x);
    if (*w == x) return w;
    --w;
    split(rt[*w], rt[x], x - *w, op[x] = op[*w]);
    return srt.insert(x).first;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    n = read(), m = read();
    srt.insert(n + 1);
    for (int i = 1; i <= n; i++) {
        int g;
        g = read();
        update(rt[i], 1, n, g);
        srt.insert(i);
    }
    for (int i = 1; i <= m; i++) {
        int o, l, r;
        o = read(), l = read(), r = read();
        IT IL = spl(l), IR = spl(r + 1);
        for (IT i = ++IL; i != IR; i++) rt[l] = merge(rt[l], rt[*i]);
        op[l] = o;
        srt.erase(IL, IR);
    }

    int qp;
    qp = read();
    spl(qp), spl(qp + 1);
    printf("%d\n", query(rt[qp], 1, n));
    return 0;
}
