#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <set>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 1e3 + 10;

int n, m;
int fa[N];
int sz[N];
multiset<int> st;
int ans[N];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

int get(int cnt) {
    auto it = prev(st.end());
    int res = 0;
    for (int i = 0; i <= cnt; i++) {
        res += *it;
        if (it == st.begin()) {
            res += cnt - i;
            break;
        }
        it = prev(it);
    }

    return res;
}

void solve() {
    for (int i = 1; i <= n; i++) fa[i] = i, sz[i] = 1;

    int cnt = 0, res = 0;
    for (int k = 1; k <= m; k++) {
        int a, b;
        cin >> a >> b;

        int tx = find(a), ty = find(b);
        if (tx != ty) {
            if (st.find(sz[tx]) != st.end()) st.erase(st.find(sz[tx]));
            if (st.find(sz[ty]) != st.end()) st.erase(st.find(sz[ty]));
            fa[ty] = tx;
            sz[tx] += sz[ty];
            sz[ty] = 0;
            st.insert(sz[tx]);

            res = max(res, get(cnt));
            ans[k] = res - 1;
        } else {
            cnt++;
            res = max(res, get(cnt));
            ans[k] = res - 1;
        }
    }

    for (int k = 1; k <= m; k++) cout << ans[k] << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    solve();

    return 0;
}