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
const int N = 2e5 + 10;

int n, m;
pii a[N], b[N];

void solve() {
    vector<ai3> v;
    for (int i = 1; i <= n; i++) {
        auto [w, h] = a[i];
        v.push_back({w, h, 0});
    }
    for (int i = 1; i <= m; i++) {
        auto [w, h] = b[i];
        v.push_back({w, h, 1});
    }

    sort(v.begin(), v.end(), [](auto &a, auto &b) {
        if (a[0] != b[0]) return a[0] > b[0];
        return a[2] > b[2];
    });

    multiset<int> st;
    for (auto [w, h, ty] : v) {
        if (ty) {
            st.insert(h);
            continue;
        }

        auto it = st.lower_bound(h);
        if (it == st.end()) {
            cout << "No" << "\n";
            return;
        }
        st.erase(it);
    }

    cout << "Yes" << "\n";
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
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> a[i].fi;
        for (int i = 1; i <= n; i++) cin >> a[i].se;
        for (int i = 1; i <= m; i++) cin >> b[i].fi;
        for (int i = 1; i <= m; i++) cin >> b[i].se;
        solve();
    }

    return 0;
}