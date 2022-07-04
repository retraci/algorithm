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

// region 字符串最小表示法
// 下标从 0 开始
string get_min(const string &s) {
    int n = s.size();
    string ns = s + s;
    int i = 0, j = 1;

    while (i < n && j < n) {
        int k = 0;
        while (k < n && ns[i + k] == ns[j + k]) k++;
        if (ns[i + k] > ns[j + k]) i = i + k + 1;
        else j = j + k + 1;
        if (i == j) j++;
    }

    int pos = min(i, j);
    return ns.substr(pos, n);
}
// endregion

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

string s1, s2;

void solve() {
    string mi1 = get_min(s1), mi2 = get_min(s2);

    if (mi1 != mi2) {
        cout << "No" << "\n";
        return;
    }
    cout << "Yes" << "\n";
    cout << mi1 << "\n";
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
        cin >> s1 >> s2;
        solve();
    }

    return 0;
}