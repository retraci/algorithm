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
const int N = 2e5 + 10;

int n;
int a[N];

void solve() {
    multiset<int> mst(a + 1, a + n + 1);

    int cur = 1;
    while (!mst.empty()) {
        if (mst.size() & 1) {
            if (a[cur] != *mst.begin()) {
                cout << "NO" << "\n";
                return;
            }
            mst.erase(mst.begin());
        } else {
            int mi = *mst.begin();
            if (a[cur] != mi && (cur + 1 > n || a[cur + 1] != mi)) {
                cout << "NO" << "\n";
                return;
            }
            if (a[cur] != mi && cur + 1 <= n) a[cur + 1] = a[cur];
            mst.erase(mst.begin());
        }
        cur++;
    }

    cout << "YES" << "\n";
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