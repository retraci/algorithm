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
#include <numeric>
#include <stack>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

const int N = 1e6 + 10;

int n;
string s;
int tag[N];

void solve() {
    n = s.size();
    for (int i = 0; i < n; i++) tag[i] = 0;
    stack<int> stk;
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            stk.push(i);
            continue;
        }
        if (!stk.empty()) stk.pop();
        else tag[i] = 1;
    }
    while (!stk.empty()) {
        tag[stk.top()] = 1;
        stk.pop();
    }

    int ans = 0, cnt = 0;
    for (int i = 0; i < n; i++) {
        if (tag[i]) continue;

        int j = i;
        while (j < n && !tag[j]) j++;
        if (j - i > ans) {
            ans = j - i;
            cnt = 1;
        } else if (j - i == ans) {
            cnt++;
        }

        i = j - 1;
    }

    if (ans == 0) cout << "0 1" << "\n";
    else cout << ans << " " << cnt << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> s;
    solve();

    return 0;
}