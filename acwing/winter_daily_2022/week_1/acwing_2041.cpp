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

const int N = 1e6 + 10;

int n, m;
int va[N];

void solve() {
    while (m--) {
        int L, R;
        cin >> L >> R;
        va[L]++, va[R + 1]--;
    }

    for (int i = 1; i <= n; i++) va[i] += va[i - 1];
    nth_element(va + 1, va + n / 2 + 1, va + n + 1);
    cout << va[n / 2 + 1] << "\n";
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