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
const int N = 1e5 + 10;
const int M = 3e6 + 10;

int n, L, P;
string a[N];
int s[N];
ld f[N];
ai3 que[N];
int hh, tt;

ld get(int pre, int cur) {
    ld res = 1, x = s[cur] - s[pre - 1] - 1 - L;
    for (int i = 1; i <= P; i++) res *= x;
    return abs(res);
}

ld calc(int pre, int cur) {
    return f[pre - 1] + get(pre, cur);
}

void ins(int i) {
    int pos = n + 1;
    while (hh <= tt && calc(i, que[tt][1]) <= calc(que[tt][0], que[tt][1])) pos = que[tt--][1];
    if (hh <= tt && calc(i, que[tt][2]) <= calc(que[tt][0], que[tt][2])) {
        int left = que[tt][1], right = que[tt][2];
        while (left < right) {
            int md = left + right >> 1;
            if (calc(i, md) <= calc(que[tt][0], md)) right = md;
            else left = md + 1;
        }
        que[tt][2] = left - 1;
        pos = left;
    }
    if (pos <= n) que[++tt] = {i, pos, n};
}

void solve() {
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i].size() + 1;

    hh = 0, tt = -1;
    que[++tt] = {0, 1, n};

    vector<int> pre(n + 1);
    for (int i = 1; i <= n; i++) {
        ins(i);
        pre[i] = que[hh][0];
        f[i] = calc(pre[i], i);
        while (hh <= tt && que[hh][2] <= i) hh++;
        que[hh][1] = i + 1;
    }

    if (f[n] > 1e18) {
        cout << "Too hard to arrange" << "\n";
    } else {
        cout << (ll) f[n] << "\n";
        vector<pii> ans;
        int t = n;
        while (t) {
            ans.push_back({pre[t], t});
            t = pre[t] - 1;
        }
        reverse(ans.begin(), ans.end());
        for (auto [lb, rb] : ans) {
            for (int i = lb; i <= rb; i++) {
                cout << a[i] << " \n"[i == rb];
            }
        }
    }
    cout << "--------------------" << "\n";
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
        cin >> n >> L >> P;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}