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

const int N = 1e5 + 10;

int n, m;
ll va[N];
vector<ll> vb[N];

const int MAX_LEN = 2e5 + 1;
int seg_tree[MAX_LEN << 2];
int Lazy[MAX_LEN << 2];
int arr[MAX_LEN];

//从下往上更新 节点
void push_up(int root) {
    seg_tree[root] = min(seg_tree[root << 1], seg_tree[root << 1 | 1]);    //最小值改min
}

//从上向下更新，左右孩子
void push_down(int root, int L, int R) {
    if (Lazy[root]) {
        Lazy[root << 1] += Lazy[root];
        Lazy[root << 1 | 1] += Lazy[root];
        int mid = (L + R) >> 1;
        seg_tree[root << 1] += Lazy[root] * (mid - L + 1);
        seg_tree[root << 1 | 1] += Lazy[root] * (R - mid);
        Lazy[root] = 0;
    }
}

//建树
void build(int root, int L, int R) {
    Lazy[root] = 0;
    if (L == R) {
        seg_tree[root] = arr[L];
        return;
    }
    int mid = (L + R) >> 1;
    build(root << 1, L, mid);
    build(root << 1 | 1, mid + 1, R);
    push_up(root);
}

//区间查询
int query(int root, int L, int R, int LL, int RR) {
    if (LL <= L && R <= RR) return seg_tree[root];
    push_down(root, L, R);    //每次访问都去检查Lazy 标记
    int Ans = 0;
    int mid = (L + R) >> 1;
    if (LL <= mid) Ans = min(Ans, query(root << 1, L, mid, LL, RR));    //最小值改min
    if (RR > mid) Ans = min(Ans, query(root << 1 | 1, mid + 1, R, LL, RR)); //最小值改min
    return Ans;
}

//区间修改 +-某值
void update_Interval(int root, int L, int R, int LL, int RR, int val) {
    if (LL <= L && R <= RR) {
        Lazy[root] += val;
        seg_tree[root] += val * (R - L + 1);
        return;
    }
    push_down(root, L, R);
    int mid = (L + R) >> 1;
    if (LL <= mid) update_Interval(root << 1, L, mid, LL, RR, val);
    if (RR > mid) update_Interval(root << 1 | 1, mid + 1, R, LL, RR, val);
    push_up(root);
}

//单点修改 可以改为某值，或者+-某值
void update(int root, int L, int R, int pos, int val) {
    if (L == R) {
        seg_tree[root] = val;    //点直接变为某值
        return;
    }
    int mid = (L + R) >> 1;
    if (pos <= mid) update(root << 1, L, mid, pos, val);
    else update(root << 1 | 1, mid + 1, R, pos, val);
    push_up(root);
}

void solve() {
    int K = 0;
    for (int i = 1; i <= m; i++) K += vb[i].size();

    ll vc[m + 1];
    for (int i = 1; i <= m; i++) {
        vc[i] = accumulate(vb[i].begin(), vb[i].end(), 0LL);
    }

    int tt = n + m;
    pll vd[tt + 1];
    for (int i = 1; i <= n; i++) vd[i] = {va[i], 2};
    for (int i = 1; i <= m; i++) {
        ll avg = (vc[i] + vb[i].size() - 1) / vb[i].size();
        vd[n + i] = {avg, 1};
    }
    sort(vd + 1, vd + tt + 1);

    ll suf[tt + 2];
    suf[tt + 1] = 0;
    for (int i = tt; i >= 1; i--) {
        suf[i] = suf[i + 1] + (vd[i].se == 2 ? 1 : -1);
    }

    for (int i = 1; i <= tt + 1; i++) arr[i] = suf[i];
    build(1, 1, tt + 1);

    string ans(K, '0');
    int idx = 0;
    for (int i = 1; i <= m; i++) {
        for (int x: vb[i]) {
            ll sz = vb[i].size() - 1;
            ll s = (vc[i] + vb[i].size() - 1) / vb[i].size();
            ll ns = ((vc[i] - x + sz - 1) / sz);
            ll id1 = lower_bound(vd + 1, vd + 1 + tt, (pll) {s, 1}) - vd;
            ll id2 = lower_bound(vd + 1, vd + 1 + tt, (pll) {ns, 1}) - vd;

            if (id1 < id2) {
                update_Interval(1, 1, tt + 1, id1 + 1, id2, -1);
                ll cur = query(1, 1, tt + 1, 1, tt + 1);
                if (cur >= 0) ans[idx++] = '1';
                else ans[idx++] = '0';
                update_Interval(1, 1, tt + 1, id1 + 1, id2, 1);
            } else {
                update_Interval(1, 1, tt + 1, id2 + 1, id1, 1);
                ll cur = query(1, 1, tt + 1, 1, tt + 1);
                if (cur >= 0) ans[idx++] = '1';
                else ans[idx++] = '0';
                update_Interval(1, 1, tt + 1, id2 + 1, id1, -1);
            }
        }
    }

    cout << ans << "\n";
}


int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    auto prework = [&]() -> void {
    };
    prework();

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    {
        cout << 1;
    }
    [&]() -> void {
        cout << 1;
    }();

    int T = 1;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> va[i];
        for (int i = 1; i <= m; i++) {
            int k;
            cin >> k;
            vb[i] = {};
            while (k--) {
                int b;
                cin >> b;
                vb[i].push_back(b);
            }
        }
        solve();
    }

    return 0;
}