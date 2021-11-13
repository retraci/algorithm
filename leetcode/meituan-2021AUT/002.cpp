#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
#include <unordered_map>

using namespace std;

const int N = 5e4 + 10;

int n;
int va[N], vb[N];
int fa[N];
multiset<int> st;
unordered_map<int, int> mp;
int ans[N];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void solve() {
    for (int i = 0; i < n; i++) {
        fa[i] = i;
    }
    for (int i = n - 1; i >= 0; i--) {
        int tmp = vb[i] - 1;
        ans[i] = st.empty() ? 0 : *st.rbegin();

        if (tmp - 1 >= 0 && mp[tmp - 1]) {
            int tx = find(tmp - 1);
            fa[tx] = tmp;
            va[tmp] += va[tx];

            st.erase(st.lower_bound(va[tx]));
        }
        if (tmp + 1 < n && mp[tmp + 1]) {
            int tx = find(tmp + 1);
            fa[tx] = tmp;
            va[tmp] += va[tx];

            st.erase(st.lower_bound(va[tx]));
        }
        st.insert(va[tmp]);
        mp[tmp] = 1;
    }

    for (int i = 0; i < n; i++) {
        printf("%d\n", ans[i]);
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif
    cin >> n;
    for (int i = 0; i < n; i++) {
        scanf("%d", &va[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &vb[i]);
    }
    solve();

    return 0;
}