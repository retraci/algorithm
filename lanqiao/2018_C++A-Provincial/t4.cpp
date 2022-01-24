// 第几个幸运数

#include <bits/stdc++.h>

using namespace std;

#define ll long long

ll num = 59084709587505;
int va[] = {3, 5, 7};

void solve() {
    set<ll> sett;
    sett.insert(3);
    sett.insert(5);
    sett.insert(7);

    set<ll>::iterator cur = sett.begin();
    while (*cur < num) {
        for (int i = 0; i < 3; i++) if (*cur * va[i] <= num) sett.insert(*cur * va[i]);
        cur++;
    }

    int ans = sett.size();
    cout << ans << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    solve();

    return 0;
}