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

int n, q;
int a[N];
ai3 qs[N];
int cnt[N], c[N], bl;
int bl2;

int get(int i) {
    return (i - 1) / bl + 1;
}

int get2(int x) {
    return x / bl2 + 1;
}

void add(int i) {
    if (++cnt[a[i]] == 1) {
        int bid2 = get2(a[i]);
        c[bid2]++;
    }
}

void del(int i) {
    if (--cnt[a[i]] == 0) {
        int bid2 = get2(a[i]);
        c[bid2]--;
    }
}

int qr() {
    int mxbid2 = get2(2e5 + 1);
    for (int bid2 = 1; bid2 <= mxbid2; bid2++) {
        if (c[bid2] == bl2) continue;

        int lb = bl2 * (bid2 - 1), rb = min((int) 2e5 + 1, bl2 * bid2 - 1);
        for (int j = lb; j <= rb; j++) {
            if (cnt[j] == 0) return j;
        }
    }

    assert(false);
    return -1;
}

void solve() {
    bl = sqrt(n), bl2 = sqrt(2e5 + 1);
    sort(qs + 1, qs + q + 1, [](auto &a, auto &b) {
        int bid1 = get(a[1]), bid2 = get(b[1]);
        if (bid1 != bid2) return bid1 < bid2;
        return bid1 & 1 ? a[2] < b[2] : a[2] > b[2];
    });

    int cl = 1, cr = 0;
    vector<int> ans(q + 1);
    for (int i = 1; i <= q; i++) {
        auto [qid, L, R] = qs[i];

        while (cl < L) del(cl++);
        while (cl > L) add(--cl);
        while (cr > R) del(cr--);
        while (cr < R) add(++cr);

        ans[qid] = qr();
    }

    for (int i = 1; i <= q; i++) cout << ans[i] << "\n";
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
        cin >> n >> q;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= q; i++) {
            int L, R;
            cin >> L >> R;
            qs[i] = {i, L, R};
        }
        solve();
    }

    return 0;
}