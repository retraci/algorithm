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
#define SZ(x) (int)(x).size()
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef vector<int> VI;
typedef vector<VI> VII;
typedef vector<ll> VL;
typedef vector<vector<ll>> VLL;
constexpr int mod = 1e9 + 7;
constexpr int KINF = 0x3f3f3f3f;
constexpr int INF = 0x7f7f7f7f;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int _;
    cin >> _;
    while (_--) {
        int n, k;
        ll x;
        cin >> n >> k >> x;
        string s;
        cin >> s;
        VI cnt;
        rep(i, 0, n) {
            int j = i;
            while (j < n && s[j] != 'a') ++j;
            cnt.eb(j - i);
            i = j;
        }
        if (s.back() != '*') cnt.eb(0);
        int m = SZ(cnt);
        VI ans(m);
        VL tt(m);
        VL sum(m);
        if (s.back() == '*') {
            tt[m - 1] = 1;
            sum[m - 1] = 1ll * k * cnt[m - 1];
        } else {
            tt[m - 2] = 1;
            sum[m - 2] = 1ll * k * cnt[m - 2];
        }
        _rep(i, m - 2, -1) {
            tt[i] = sum[i + 1] + 1;
            sum[i] = 1ll * k * tt[i] * cnt[i] + sum[i + 1];
        }
        --x;
        rep(i, 0, m) {
            int c = 0;
            while (c < cnt[i] * k && tt[i] <= x) {
                ans[i] += 1;
                x -= tt[i];
                ++c;
            }
        }
        //ans[m + 1] = 0;
        string res;
        rep(i, 0, ans[0]) res += 'b';
        // if(m == 1) res += 'a';
        rep(i, 1, m) {
            res += 'a';
            rep(j, 0, ans[i]) {
                // rep(j, 0, k)
                res += 'b';
            }

        }
        if (x) {
            rep(i, 0, x) {
                res += 'b';
            }
        }
        cout << res << "\n";
    }
    return 0;
}
// 小心左移运算符导致的int溢出
// dp记得处理非法状态
// resize并不会初始化数组
// 全局函数一定要记得inline
// 带空格字符串不能直接cin,要用getline
// 最好用"\n"代替endl


