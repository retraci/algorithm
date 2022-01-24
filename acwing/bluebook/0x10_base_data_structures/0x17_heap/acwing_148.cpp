#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 10010;

int n;
int va[N];

void solve() {
    priority_queue<int> que;
    for (int i = 0; i < n; i++) que.push(-va[i]);

    int ans = 0;
    while (que.size() > 1) {
        int a = que.top(); que.pop(); a = -a;
        int b = que.top(); que.pop(); b = -b;
        ans += a + b;
        que.push(-(a + b));
    }

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> va[i];
    solve();

    return 0;
}