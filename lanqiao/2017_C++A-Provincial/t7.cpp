// 正则问题

#include <bits/stdc++.h>

using namespace std;

string reg;
int idx;

int calc() {
    int num = 0, res = 0;
    while (idx < reg.size()) {
        if (reg[idx] == 'x') {
            num++, idx++;
        } else if (reg[idx] == '|') {
            idx++;
            res = max(res, num);
            num = 0;
        } else if (reg[idx] == '(') {
            idx++;
            num += calc();
        } else if (reg[idx] == ')') {
            idx++;
            break;
        }
    }

    res = max(res, num);
    return res;
}

void solve() {
    idx = 0;
    int ans = calc();

    cout << ans << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> reg;
    solve();

    return 0;
}