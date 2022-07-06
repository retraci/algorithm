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

int n;
int a[N];

void solve() {
    sort(a + 1, a + n + 1);
    vector<int> ans(n + 1);
    int j = 1;
    for (int i = 1; i <= n; i += 2) ans[i] = a[j++];
    for (int i = 2; i <= n; i += 2) ans[i] = a[j++];

    int flag = 0;
    for (int i = 1; i <= n; i++) {
        int pr = ((i - 1) - 1 + n) % n + 1;
        int ne = ((i - 1) + 1) % n + 1;

        if (i & 1) {
            if (!(ans[i] < ans[pr] && ans[i] < ans[ne])) flag = 1;
        } else {
            if (!(ans[i] > ans[pr] && ans[i] > ans[ne])) flag = 1;
        }
    }

    if (flag) {
        cout << "No" << "\n";
        return;
    }

    cout << "Yes" << "\n";
    for (int i = 1; i <= n; i++) cout << ans[i] << " \n"[i == n];
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
        solve();
    }

    return 0;
}