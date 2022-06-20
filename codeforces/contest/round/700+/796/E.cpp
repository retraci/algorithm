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
mt19937 mrnd(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};

int n, m;

int ask(const string &s) {
    cout << "? " << s << "\n";
    cout.flush();
    int ret;
    cin >> ret;
    return ret;
}

void solve() {
    string s(m, '0');
    vector<pii> es;
    for (int i = 0; i < m; i++) {
        s[i] = '1';
        int ret = ask(s);
        es.push_back({ret, i});
        s[i] = '0';
    }

    sort(es.begin(), es.end());
    int lst = 0;
    for (auto [cost, eid] : es) {
        s[eid] = '1';
        int cur = ask(s);
        if (cur == lst + cost) lst += cost;
        else s[eid] = '0';
    }

    cout << "! " << lst << "\n";
    cout.flush();
}

void prework() {
}

int main() {
#ifdef LOCAL
//    freopen("../in.txt", "r", stdin);
//    freopen("../out.txt", "w", stdout);
#endif

    prework();
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _ = 1;
//    cin >> _;
    while (_--) {
        cin >> n >> m;
        solve();
    }

    return 0;
}