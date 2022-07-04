#include <bits/stdc++.h>

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
mt19937 mrnd(std::random_device{}());

int rnd(int mod) {
    return mrnd() % mod;
}

template<int SZ>
struct Manacher {
    int p[2 * SZ + 10];
    string ns;

    Manacher() {}

    // 下标 0 开始
    void init(const string &s) {
        int m = s.size();
        ns.resize(m * 2 + 3);
        ns[0] = '$', ns.back() = '^';
        ns[1] = '#';
        for (int i = 0; i < m; i++) ns[i * 2 + 2] = s[i], ns[i * 2 + 3] = '#';

        int mr = 0, mid = 0;
        for (int i = 1; i < ns.size(); i++) {
            if (i < mr) p[i] = min(p[mid * 2 - i], mr - i);
            else p[i] = 1;
            while (ns[i - p[i]] == ns[i + p[i]]) p[i]++;
            if (mr < i + p[i]) {
                mr = i + p[i];
                mid = i;
            }
        }
    }
};

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1e7 + 10;

string s;
Manacher<N> mc;

void solve() {
    mc.init(s);

    int ans = *max_element(mc.p, mc.p + s.size() * 2 + 3) - 1;
    cout << ans << "\n";
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
        cin >> s;
        solve();
    }

    return 0;
}