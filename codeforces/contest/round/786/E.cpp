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

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1e6 + 10;

int n;
int a[N];

void solve() {
    multiset<int> st(a + 1, a + n + 1);
    int mi1 = *st.begin(); st.erase(st.begin());
    int mi2 = *st.begin();

    int ans = (mi1 + 1) / 2 + (mi2 + 1) / 2;
    for (int i = 2; i <= n - 1; i++) {
        if (a[i - 1] & 1 && a[i + 1] & 1) {
            int t = 1 + a[i - 1] / 2 + a[i + 1] / 2;
            ans = min(ans, t);
        }
    }

    for (int i = 2; i <= n; i++) {
        int mi = min(a[i], a[i - 1]);
        int mx = max(a[i], a[i - 1]);

        if (mx > 2 * mi) {
            ans = min(ans, (mx + 1) / 2);
        } else {
            int t = (mx + mi + 2) / 3;
            ans = min(ans, t);
        }
    }

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
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}