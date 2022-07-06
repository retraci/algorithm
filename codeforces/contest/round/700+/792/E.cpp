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

int n, k;
int a[N];

void solve() {
    map<int, int> cnt;
    for (int i = 1; i <= n; i++) cnt[a[i]]++;

    int mex = n, need = 0;
    for (int i = 0; i <= n; i++) {
        if (cnt.count(i)) continue;

        if (++need > k) {
            need--;
            mex = i;
            break;
        }
    }

    int dif = mex;
    vector<int> rem;
    for (auto [x, c] : cnt) {
        if (x < mex) continue;

        dif++;
        rem.push_back(c);
    }

    sort(rem.begin(), rem.end());
    int i = 0;
    while (i < rem.size() && need > 0) {
        while (i < rem.size() && rem[i] == 0) i++;
        if (i == rem.size()) break;

        need--;
        if (--rem[i] == 0) dif--;
    }

    cout << dif - mex << "\n";
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
        cin >> n >> k;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}