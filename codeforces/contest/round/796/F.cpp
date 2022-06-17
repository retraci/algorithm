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
int a[N], b[N];
pii c[N];

void solve() {
    vector<ll> s(n + 2);
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i] - b[i];

    vector<int> d[n + 1];
    queue<int> que;
    for (int i = 1; i <= m; i++) {
        auto [L, R] = c[i];
        if (s[L - 1] == 0 && s[R] == 0) {
            que.push(i);
        } else {
            d[L - 1].push_back(i);
            d[R].push_back(i);
        }
    }

    set<int> st;
    for (int i = 1; i <= n; i++) {
        if (s[i] == 0) continue;
        st.insert(i);
    }
    while (!que.empty()) {
        auto [L, R] = c[que.front()]; que.pop();

        auto it = st.lower_bound(L);
        while (it != st.end() && *it <= R) {
            s[*it] = 0;
            for (int v : d[*it]) {
                auto [nl, nr] = c[v];
                if (s[nl - 1] == 0 && s[nr] == 0) que.push(v);
            }
            it = st.erase(it);
        }
    }

    cout << (st.empty() ? "YES" : "NO") << "\n";
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
    cin >> _;
    while (_--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];
        for (int i = 1; i <= m; i++) cin >> c[i].fi >> c[i].se;
        solve();
    }

    return 0;
}