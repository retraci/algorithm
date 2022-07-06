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
const int N = 2e5 + 10;

int n, m;
int a[N];
pii b[N];
int lb[N], pmx[N];
int pre[N];

void init() {
    fill(pmx + 1, pmx + n + 1, 0);
    for (int i = 1; i <= m; i++) {
        auto [L, R] = b[i];
        pmx[L] = max(pmx[L], R);
    }
    for (int i = 1; i <= n; i++) pmx[i] = max(pmx[i], pmx[i - 1]);

    fill(lb + 1, lb + n + 1, 0);
    set<int> st;
    int L = n;
    for (int R = n; R >= 1; R--) {
        while (L >= 1 && !st.count(a[L])) st.insert(a[L--]);

        lb[R] = L + 1;
        st.erase(a[R]);
    }

    map<int, int> lst;
    for (int i = 1; i <= n; i++) {
        int t = lst.count(a[i]) ? lst[a[i]] : 0;
        pre[i] = t;
        lst[a[i]] = i;
    }
}

void solve() {
    init();

    int mxr = 0;
    for (int i = 1; i <= m; i++) {
        auto [L, R] = b[i];

        if (L >= lb[R]) continue;
        mxr = max(mxr, lb[R] - 1);
    }

    map<int, vector<int>> mp;
    for (int i = mxr + 1; i <= n; i++) mp[a[i]].push_back(i);

    int ans = mxr;
    int R = mxr;
    for (int L = 1; L <= n; L++) {
        int pr = pre[L];
        if (pr != 0) {
            if (pmx[pr] >= L) break;
        }

        auto it = upper_bound(mp[a[L]].begin(), mp[a[L]].end(), R);
        if (it != mp[a[L]].end()) {
            int ne = *it;
            if (pmx[L] >= ne) R = ne;
        }

        R = max(R, L + 1);
        ans = min(ans, R - L);
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
    cin >> _;
    while (_--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= m; i++) {
            int L, R;
            cin >> L >> R;
            b[i] = {L, R};
        }
        solve();
    }

    return 0;
}