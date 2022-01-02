#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <bitset>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

const int N = 33;

int n;
char sa[N], sb[N], sc[N];

int tt;
char seq[N];
int st[N];
int ans[N];

bool check() {
    int t = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (ans[sa[i] - 'A'] != -1 && ans[sb[i] - 'A'] != -1 && ans[sc[i] - 'A'] != -1) {
            int a = ans[sa[i] - 'A'], b = ans[sb[i] - 'A'], c = ans[sc[i] - 'A'];
            if (t == -1) {
                int s0 = a + b + 0, s1 = a + b + 1;
                if (s0 % n != c && s1 % n != c) return false;
                if (i == 0 && s0 / n >= 1) return false;
            } else {
                int s = a + b + t;
                if (s % n != c) return false;
                if (i == 0 && s / n >= 1) return false;
                t = s / n;
            }
        } else {
            t = -1;
        }
    }

    return true;
}

bool dfs(int cur) {
    if (cur == n) return true;

    for (int i = 0; i < n; i++) {
        if (st[i]) continue;

        ans[seq[cur] - 'A'] = i;
        st[i] = 1;
        if (check() && dfs(cur + 1)) return true;
        st[i] = 0;
        ans[seq[cur] - 'A'] = -1;
    }

    return false;
}

void solve() {
    for (int i = n - 1; i >= 0; i--) {
        char a = sa[i], b = sb[i], c = sc[i];
        if (!st[a - 'A']) seq[tt++] = a, st[a - 'A'] = 1;
        if (!st[b - 'A']) seq[tt++] = b, st[b - 'A'] = 1;
        if (!st[c - 'A']) seq[tt++] = c, st[c - 'A'] = 1;
    }

    memset(st, 0, sizeof st);
    memset(ans, -1, sizeof ans);
    dfs(0);

    for (int i = 0; i < n; i++) cout << ans[i] << " ";
    cout << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    cin >> sa >> sb >> sc;
    solve();

    return 0;
}