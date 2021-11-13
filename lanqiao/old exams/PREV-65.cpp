// 试题 历届试题 单词分析

#include <bits/stdc++.h>

using namespace std;

string str;
int cnt[26];

void solve() {
    for (int i = 0; i < str.size(); i++) cnt[str[i] - 'a']++;

    int idx = max_element(cnt, cnt+26) - cnt;

    char ch = 'a' + idx;
    cout << ch << endl << cnt[idx] << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> str;
    solve();

    return 0;
}