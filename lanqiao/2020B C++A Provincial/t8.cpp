// 子串分值

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

const int N = 100010;

char str[N];
int n;
int pre[N], ne[N];
int last[26];

void solve() {
    int len = strlen(str + 1);
    n = len + 1;

    for (int i = 1; i < n; i++) {
        int x = str[i] - 'a';
        pre[i] = last[x];
        last[x] = i;
    }

    for (int i = 0; i < 26; i++) last[i] = n;
    for (int i = n - 1; i >= 1; i--) {
        int x = str[i] - 'a';
        ne[i] = last[x];
        last[x] = i;
    }

    ll ans = 0;
    for (int i = 1; i < n; i++) {
        ans += 1LL * (i - pre[i]) * (ne[i] - i);
    }

    cout << ans << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    scanf("%s", str + 1);
    solve();

    return 0;
}