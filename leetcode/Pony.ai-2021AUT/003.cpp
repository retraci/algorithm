#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <stack>

using namespace std;

const int N = 2e6 + 10;

int n;
double h;
double vh[N];
int ans[N];

double get(int idx) {
    return (h - vh[idx]) / idx;
}

void solve() {
    memset(ans, 0, sizeof ans);
    stack<int> stk;
    for (int i = 1; i <= n; i++) {
        while (!stk.empty() && get(stk.top()) > get(i)) {
            stk.pop();
        }
        if (stk.empty()) ans[i] = 0;
        else ans[i] = stk.top();

        stk.push(i);
    }

    for (int i = 1; i <= n; i++) {
        printf("%d\n", ans[i]);
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n >> h;
    for (int i = 1; i <= n; i++) {
        scanf("%lf", &vh[i]);
    }
    solve();

    return 0;
}