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
#include <cassert>
#include <random>
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

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1e5 + 10;

int n, m;
int a[N];
ll lz[355], s[355];
int bl;

int get(int i) {
    return (i - 1) / bl + 1;
}

void upd(int L, int R, ll x) {
    if (get(L) == get(R)) {
        for (int i = L; i <= R; i++) a[i] += x, s[get(i)] += x;
        return;
    }

    int i = L, j = R;
    while (get(i) == get(L)) a[i] += x, s[get(i)] += x, i++;
    while (get(j) == get(R)) a[j] += x, s[get(j)] += x, j--;
    for (int k = get(i); k <= get(j); k++) s[k] += bl * x, lz[k] += x;
}

ll qr(int L, int R) {
    ll res = 0;
    if (get(L) == get(R)) {
        for (int i = L; i <= R; i++) res += a[i] + lz[get(i)];
        return res;
    }

    int i = L, j = R;
    while (get(i) == get(L)) res += a[i] + lz[get(i)], i++;
    while (get(j) == get(R)) res += a[j] + lz[get(j)], j--;
    for (int k = get(i); k <= get(j); k++) res += s[k];

    return res;
}

void solve() {
    bl = sqrt(n);
    for (int i = 1; i <= n; i++) s[get(i)] += a[i];

    while (m--) {
        string op;
        cin >> op;

        if (op[0] == 'C') {
            int L, R, x;
            cin >> L >> R >> x;

            upd(L, R, x);
        } else {
            int L, R;
            cin >> L >> R;

            cout << qr(L, R) << "\n";
        }
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
//    cin >> _;
    while (_--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}