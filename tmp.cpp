// #pragma GCC optimize(2)
// #pragma GCC optimize(3)
// #pragma GCC optimize("Ofast")
#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
#include<utility>
#include<cstring>
#include<iomanip>
#include<unordered_set>
#include<unordered_map>
#include<set>
#include<map>
#include<queue>
#include<numeric>
using namespace std;
#define rep(i, x, y) for(int i = (int)x; i < (int)y; ++ i)
#define _rep(i, x, y) for(int i = (int)x; i > (int)y; -- i)
#define PII pair<int,int>
#define eb emplace_back
#define pb push_back
#define fi first
#define se second
#define PQ priority_queue
#define lb lower_bound
#define ub upper_bound
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef vector<int> VI;
typedef vector<VI> VII;
typedef vector<ll> VL;
typedef vector<vector<ll>> VLL;
constexpr int mod = 20211121;
constexpr int KINF = 0x3f3f3f3f;
constexpr int INF = 0x7f7f7f7f;
template <int N> struct mat {
    ll a[N][N];
    inline mat() { memset(a, 0, sizeof a); }
    inline mat operator-(const mat& T) const {
        mat res;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j) {
                res.a[i][j] = (a[i][j] - T.a[i][j]) % mod;
            }
        return res;
    }
    inline mat operator+(const mat& T) const {
        mat res;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j) {
                res.a[i][j] = (a[i][j] + T.a[i][j]) % mod;
            }
        return res;
    }
    inline mat operator*(const mat& T) const {
        mat res;
        int r;
        for (int i = 0; i < N; ++i)
            for (int k = 0; k < N; ++k) {
                r = a[i][k];
                for (int j = 0; j < N; ++j)
                    res.a[i][j] += T.a[k][j] * r, res.a[i][j] %= mod;
            }
        return res;
    }
    inline mat operator^(ll x) const {
        mat res, bas;
        for (int i = 0; i < N; ++i) res.a[i][i] = 1;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j) bas.a[i][j] = a[i][j];
        while (x) {
            if (x & 1) res = res * bas;
            bas = bas * bas;
            x >>= 1;
        }
        return res;
    }
    bool operator == (const mat& T) const {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (a[i][j] != T.a[i][j]) return false;
        return true;
    }
};
mat<26> A, B;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr), cout.tie(nullptr);
    ll m;
    cin >> m;
    rep(i, 0, 26){
        rep(j, i, 26) A.a[i][j] = 1;
    }
    B = A ^ m;
    ll res = 0;
    rep(i, 0, 26) (res += B.a[i][25]) %= mod;
    cout << res << "\n";
    return 0;

}
// 小心左移运算符导致的int溢出
// dp记得处理非法状态
// resize并不会初始化数组
// 全局函数一定要记得inline
// 带空格字符串不能直接cin,要用getline
// 最好用"\n"代替endl


