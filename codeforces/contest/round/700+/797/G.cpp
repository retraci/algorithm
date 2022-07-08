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
const int N = 1e5 + 10;

int n, q;
int a[N];
map<int, int> mp;

void add(int i, int x) {
    mp[i] = x;

    auto it = mp.find(i);
    if (it != mp.begin() && prev(it)->se <= x) {
        mp.erase(it);
        return;
    }

    it = next(it);
    while (it != mp.end() && it->se >= x) it = mp.erase(it);
}

void solve() {
    mp.clear();
    for (int i = 1; i <= n; i++) add(i, a[i]);

    for (int i = 1; i <= q; i++) {
        int k, x;
        cin >> k >> x;
        a[k] -= x;

        add(k, a[k]);

        cout << mp.size() << " \n"[i == q];
    }
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
        cin >> n >> q;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}