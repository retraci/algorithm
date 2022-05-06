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

// region prufer
template<int N>
struct Prufer {
    int deg[N];

    Prufer() {}

    vector<int> tree2prufer(int fa[], int n) {
        fill(deg, deg + n + 1, 0);
        for (int i = 1; i <= n - 1; i++) deg[fa[i]]++;

        vector<int> p(n + 1);
        int i = 0, j = 1;
        while (i + 1 <= n - 2) {
            while (deg[j]) j++;
            p[++i] = fa[j];
            while (i + 1 <= n - 2 && --deg[p[i]] == 0 && p[i] < j) p[i + 1] = fa[p[i]], i++;
            j++;
        }

        return p;
    }

    vector<int> prufer2tree(int p[], int n) {
        fill(deg, deg + n + 1, 0);
        p[n - 1] = n;
        for (int i = 1; i <= n - 1; i++) deg[p[i]]++;

        vector<int> fa(n + 1);
        int i = 1, j = 1;
        while (i <= n - 1) {
            while (deg[j]) j++;
            fa[j] = p[i];
            while (i + 1 <= n - 1 && --deg[p[i]] == 0 && p[i] < j) fa[p[i]] = p[i + 1], i++;
            i++, j++;
        }

        return fa;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 100010;

int n, op;
int a[N];
Prufer<N> pf;

void solve() {
    if (op == 1) {
        auto p = pf.tree2prufer(a, n);
        for (int i = 1; i <= n - 2; i++) cout << p[i] << " ";
        cout << "\n";
    } else {
        auto fa = pf.prufer2tree(a, n);
        for (int i = 1; i <= n - 1; i++) cout << fa[i] << " ";
        cout << "\n";
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
        cin >> n >> op;
        for (int i = 1; i <= (op == 1 ? n - 1 : n - 2); i++) cin >> a[i];
        solve();
    }

    return 0;
}