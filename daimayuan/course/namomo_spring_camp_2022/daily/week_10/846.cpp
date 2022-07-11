#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <cmath>

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
using ull = unsigned long long;
using pii = pair<int, int>;

const int N = 100010;

int n;
int a[N];

void solve() {
    vector<int> mp(n + 1);
    for (int i = 1; i <= n; i++) mp[a[i]] = i;

    ll ans = 0;
    sort(a + 1, a + n + 1);
    multiset<int> st;
    st.insert(0), st.insert(0), st.insert(n + 1), st.insert(n + 1);
    for (int i = n; i >= 1; i--) {
        int id = mp[a[i]];
        auto it = st.insert(id);

        auto p1 = prev(it), p2 = prev(p1);
        auto n1 = next(it), n2 = next(n1);

        if (*p1 >= 1) ans += 1LL * a[i] * (*p1 - *p2) * (*n1 - id);
        if (*n1 <= n) ans += 1LL * a[i] * (*n2 - *n1) * (id - *p1);
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