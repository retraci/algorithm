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

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int N = 110;

int n;
int a[N], b[N];

void solve() {
    vector<pii> ans;
    for (int i = 1; i <= n; i++) {
        int id = min_element(a + i, a + n + 1) - a;
        if (id == i) continue;

        swap(a[id], a[i]);
        swap(b[id], b[i]);
        ans.push_back({id, i});
    }

    for (int i = 1; i <= n; i++) {
        int id = min_element(b + i, b + n + 1) - b;
        if (id == i) continue;

        if (a[i] != a[id]) {
            cout << -1 << "\n";
            return;
        }

        swap(b[id], b[i]);
        ans.push_back({id, i});
    }

    cout << ans.size() << "\n";
    for (auto [i, j] : ans) cout << i << " " << j << "\n";
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
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];
        solve();
    }

    return 0;
}