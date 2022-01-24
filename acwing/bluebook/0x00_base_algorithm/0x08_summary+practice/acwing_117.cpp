#include <bits/stdc++.h>

using namespace std;

struct Node {
    char ch;
    int status;
};

const int N = 15;

deque<Node> qs[N];
int cnt[N];
int life;

void doo() {
    int num = 13;

    Node cur = qs[num].front(); qs[num].pop_front();

    if (cur.ch == 'A') num = 1;
    else if (cur.ch == 'J') num = 11;
    else if (cur.ch == 'Q') num = 12;
    else if (cur.ch == 'K') num = 13;
    else if (cur.ch == '0') num = 10;
    else num = cur.ch - '0';

    if (num == 13) return;

    cur.status = 1;
//    cout << num << " ";
    qs[num].push_front(cur);

    while (1) {
        Node cur = qs[num].back(); qs[num].pop_back();

        if (cur.ch == 'A') num = 1;
        else if (cur.ch == 'J') num = 11;
        else if (cur.ch == 'Q') num = 12;
        else if (cur.ch == 'K') num = 13;
        else if (cur.ch == '0') num = 10;
        else num = cur.ch - '0';

        if (num == 13) return;

        cur.status = 1;
//        cout << num << " ";
        qs[num].push_front(cur);
    }
}

void solve() {
    life = 4;
    while (life--) {
        doo();
//        cout << endl;
    }

    int ans = 0;
    for (int i = 1; i <= 13; i++) {
        while (!qs[i].empty()) {
            Node cur = qs[i].front(); qs[i].pop_front();

            int num;
            if (cur.ch == 'J') num = 11;
            else if (cur.ch == 'Q') num = 12;
            else if (cur.ch == '0') num = 10;
            else num = cur.ch - '0';

            if (cur.status) cnt[num]++;
            if (cnt[num] == 4) ans++;
        }
    }

    cout << ans << endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    for (int i = 1; i <= 13; i++) {
        for (int j = 0; j < 4; j++) {
            char a;
            cin >> a;
            qs[i].push_back({a, 0});
        }
    }
    solve();

    return 0;
}