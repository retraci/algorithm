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
const int N = 300010;

int n, q;
int a[N];
ai3 qs[N];
int cnt[N], cntb[N], c[N], bl, bl2;

int get2(int x) {
    return (x - 1) / bl2 + 1;
}

int get(int i) {
    return (i - 1) / bl + 1;
}

void add(int i) {
    cnt[a[i]]++, cntb[get2(a[i])]++;
    if (cnt[a[i]] == 1) {
        int bid2 = get2(a[i]);
        c[bid2]++;
    }
}

void del(int i) {
    cnt[a[i]]--, cntb[get2(a[i])]--;
    if (cnt[a[i]] == 0) {
        int bid2 = get2(a[i]);
        c[bid2]--;
    }
}

int qr(int sz) {
    int mxbid2 = get2(300002), sum = 0;
    for (int bid = 1; bid <= mxbid2; bid++) {
        if (c[bid] == bl2) {
            sum += cntb[bid];
            continue;
        }

        int L = bl2 * (bid - 1) + 1, R = min(300002, bl2 * bid);
        for (int j = L; j <= R; j++) {
            sum += cnt[j];
            if (cnt[j] == 0) return sz - sum;
        }
    }

    assert(false);
    return -1;
}

void solve() {
    for (int i = 1; i <= n; i++) {
        if (a[i] > 300002) a[i] = 300002;
    }

    bl = sqrt(n), bl2 = sqrt(300002);
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

        ans[qid] = qr(R - L + 1);
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
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        cin >> q;
        for (int i = 1; i <= q; i++) {
            int L, R;
            cin >> L >> R;
            qs[i] = {i, L, R};
        }
        solve();
    }

    return 0;
}