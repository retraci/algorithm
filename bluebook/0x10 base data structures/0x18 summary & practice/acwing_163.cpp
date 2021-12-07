#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {0, 0, -1, 1, -1, -1, 1, 1, 0};
const int dy[9] = {-1, 1, 0, 0, -1, 1, -1, 1, 0};

const int N = 1e5 + 10;

int n, m;
int va[N];
int vb[N], tt;

int ls[N], rs[N];

void init() {
    for (int i = 1; i <= n; i++) {
        if (tt == 0 || 1LL * vb[tt] * va[i] < 0) tt++;
        vb[tt] += va[i];
    }

    for (int i = 1; i <= tt; i++) {
        ls[i] = i - 1;
        rs[i] = i + 1;
    }
}

void remove(int id) {
    rs[ls[id]] = rs[id];
    ls[rs[id]] = ls[id];
}

void solve() {
    init();

    int ans = 0, cnt = 0;
    for (int i = 1; i <= tt; i++) {
        if (vb[i] > 0) ans += vb[i], cnt++;
    }
    set<pii> st;
    for (int i = 1; i <= tt; i++) st.insert({abs(vb[i]), i});

    while (cnt > m) {
        auto [w, id] = *st.begin(); st.erase(st.begin());

        if (ls[id] != 0 && rs[id] != tt + 1 || vb[id] > 0) {
            ans -= w, cnt--;

            int left = ls[id], right = rs[id];
            vb[id] += vb[left] + vb[right];
            st.insert({abs(vb[id]), id});

            remove(left), remove(right);
            st.erase({abs(vb[left]), left}), st.erase({abs(vb[right]), right});
        }
    }

    cout << ans << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> va[i];
    solve();

    return 0;
}