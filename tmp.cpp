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
#define rep(i, x, y) for(int i = x; i < y; ++ i)
#define _rep(i, x, y) for(int i = x; i > y; -- i)
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
constexpr int mod = 1e9 + 7;
constexpr int KINF = 0x3f3f3f3f;
constexpr int INF = 0x7f7f7f7f;

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int _;
    cin >> _;
    unordered_map<char, string> mp;
    mp['0'] = "0000";
    mp['1'] = "0001";
    mp['2'] = "0010";
    mp['3'] = "0011";
    mp['4'] = "0100";
    mp['5'] = "0101";
    mp['6'] = "0110";
    mp['7'] = "0111";
    mp['8'] = "1000";
    mp['9'] = "1001";
    mp['A'] = "1010";
    mp['B'] = "1011";
    mp['C'] = "1100";
    mp['D'] = "1101";
    mp['E'] = "1110";
    mp['F'] = "1111";
    while (_--) {
        string p;
        cin >> p;
        string tmp;
        cin >> tmp;
        string s;
        for (char &c: tmp) s += mp[c];

        cout << s << endl;

        int i = 0;
        while (s[i] == '0') i++;
        s = s.substr(i, s.size() - i);
        int k = p.size();
        string ans;
        auto del = [&](string f) {
            for (int i = 0; i < f.size(); i++) {
                if (f[i] == p[i]) f[i] = '0';
                else f[i] = '1';
            }
            int i = 0;
            while (i < f.size() && f[i] == '0') i++;
            return f.substr(i, f.size() - i);
        };
        string cur = s.substr(0, k);
        int j = k;
        while (ans.size() < s.size() - 1) {
            if (cur.size() < k) {
                if (j < s.size()) {
                    cur += s[j];
                    ++j;
                } else {
                    cur += '0';
                }
                ans += '0';
                continue;
            }
            //cout << cur << "#\n";
            cur = del(cur);
            //cout << cur << "-#\n";
            ans += '1';
            //if(ans.size() == s.size()) break;
            if (j < s.size()) {
                cur += s[j];
                ++j;
            } else {
                cur += '0';
            }
            //cout << ans << "\n";
        }
        //cout << k << "\n";
        //cout << cur << "\n";
        while (cur.size() < k - 1) cur = "0" + cur;
        if (cur.size() > k - 1) cur = cur.substr(0, k - 1);
        cout << cur << "\n";
    }
    return 0;
}
// 小心左移运算符导致的int溢出
// dp记得处理非法状态
// resize并不会初始化数组
// 全局函数一定要记得inline
// 带空格字符串不能直接cin,要用getline
// 最好用"\n"代替endl


