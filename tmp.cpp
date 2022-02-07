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

inline void debug() {
    std::cout << "\n";
}

template<class T, class... OtherArgs>
inline void debug(T &&var, OtherArgs &&... args) {
    std::cout << std::forward<T>(var) << " ";
    debug(std::forward<OtherArgs>(args)...);
}
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

struct dsu{
    dsu(int n){p.resize(n+1); for(int i=1;i<=n;i++) p[i] = i;}
    vector<int> p;
    int find(int x){if(p[x]!=x) p[x] = find(p[x]); return p[x];}
    void merge(int x, int y){p[find(x)] = find(y);}
};

int main()
{
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int n, m; cin>>n>>m;
    array<int, 3> e[m];
    for(int i=0, s, t, w;i<m;i++)
    {
        cin>>s>>t>>w;
        e[i] = {w, s, t};
    }

    set<int> s; // 分界点
    for(int i=0;i<m;i++) for(int j=i+1;j<m;j++)
            s.insert((e[i][0] + e[j][0]) / 2 + 1);

    for(int i=0;i<m;i++) s.insert(e[i][0]);

    ll p, k, a, b, c; cin>>p>>k>>a>>b>>c;

    vector<int> query(k); // 这里用map存询问会超时
    ll t;
    for(int i=0;i<p;i++)
    {
        cin>>t; query[i] = t;
    }
    for(int i=p;i<k;i++)
    {
        t = (t * a + b) % c;
        query[i] = t;
    }
    sort(query.begin(), query.end());


    s.insert(0); //s是需要更新的分界点，而初始x=0处必须重新求最小生成树。
    int num1 = 0, num2 = 0; //记录在x以上的边的数量和x以下边的数量，以便O(1)更新
    ll ans = 0, cost = 0, pre_x = -999;

    int id = 0;
    for(auto x: query)
    {
        id++;
        if(!s.empty() && *s.begin() <= x)
        {
            while(!s.empty() && *s.begin() <= x) s.erase(s.begin());
            //kruskal算法重新求最小生成树
            sort(e,e+m, [&](auto e1, auto e2){return abs(e1[0]-x) < abs(e2[0]-x);});
            //按照边权排序
            dsu g(n);
            cost = 0; num1 = num2 = 0;
            int tmp = 0; // kruskal记录边数
            for(auto [w, s, t]: e)
            {
                if(tmp == n-1) break;
                if(g.find(s) != g.find(t))
                {
                    tmp++;
                    g.merge(s, t);
                    if(w <= x) num1++;
                    else num2++;
                    cost += abs(w-x);

                    debug(id, x, s, t, w, cost, num1, num2);
                }
            }
        }
        else cost += (x - pre_x) * (num1 - num2);

        ans ^= cost;
        pre_x = x;
    }

    cout<<ans;
    return 0;
}

void prework() {

}