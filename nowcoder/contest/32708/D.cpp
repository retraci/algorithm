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
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ai3 = array<int, 3>;
mt19937 mrnd(time(0));
mt19937_64 mrnd64(time(0));

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};

int n;
string s, sa, sb;

bool check(const string &ss, int flag) {
    if (ss.size() == 0) return true;

    if (flag) {
        for (int i = 1; i < ss.size(); i++) {
            if (ss[i] < ss[i - 1]) return false;
        }
    } else {
        for (int i = 1; i < ss.size(); i++) {
            if (ss[i] > ss[i - 1]) return false;
        }
    }

    return true;
}

void work() {
    int ans = 0;
    int n = s.size();
    int lim = 1 << n;
    for (int mask = 0; mask < lim; mask++) {
        sa = "", sb = "";
        for (int i = 0; i < n; i++) {
            if (mask >> i & 1) sa += s[i] + '0';
            else sb += s[i] + '0';
        }
        ans += check(sa, 1) && check(sb, 0);
    }

    cout << ans << "\n";
}

void solve() {
    if (n == 0) {
        cout << "6" << "\n";
        cout << "5 1 3 6 2 4" << "\n";
        return;
    }
    if (n == 1) {
        cout << 6 << "\n";
        cout << "1 1 4 5 1 4" << "\n";
        return;
    }

    for (int i = 0; i <= 365; i++) {
        for (int k0 = 0; k0 <= 30; k0++) {
            int t = n + i - (1 << k0);
            if (t < 0) break;

            int cnt = __builtin_popcount(t);
            if (cnt == i) {
                vector<int> c;
                for (int k = 0; k <= __lg(t); k++) {
                    if (t >> k & 1) c.push_back(k);
                }
                reverse(c.begin(), c.end());

                vector<int> ans;
                for (int q = 0; q < k0; q++) ans.push_back(1);
                int y = 2;
                int tmp = (1 << k0) - i;
                for (int x : c) {
                    tmp += 1 << x;
                    while (x--) ans.push_back(y);
                    y++;
                }

                if (tmp != n) debug("sb");
                if (ans.size() > 365) break;

                cout << ans.size() << "\n";
                for (int x : ans) cout << x << " ";
                cout << "\n";

//                s = string(ans.begin(), ans.end());
//                work();

                return;
            }
        }
    }

    cout << -1 << "\n";
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
        cin >> n;
        solve();
    }

    return 0;
}