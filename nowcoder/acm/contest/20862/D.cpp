#include<bits/stdc++.h>

using namespace std;
const int inf = 100;

template<typename T>
inline void rd(T &x) {
    T ret = 0, sgn = 1;
    char c = getchar();
    while (!isdigit(c)) {
        sgn = (c == '-' ? -1 : 1);
        if (c == 'x') {
            x = inf;
            return;
        }
        c = getchar();
    }
    while (isdigit(c)) ret = (ret << 3) + (ret << 1) + c - '0', c = getchar();
    x = (sgn == -1 ? -ret : ret);
}

int gcd(int a, int b) {
    if (b) return gcd(b, a % b);
    else return a;
}

int T, a, b, c, d, p;

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> T;
    while (T--) {
        rd(a), rd(b), rd(c), rd(d);
        int sgn = 0, sg1 = 0;

        if (a == inf || d == inf) {
            if (a == inf) p = d;
            else p = a;
            if (p == 0) {
                if (b * c >= 0) cout << "E" << endl;
                else cout << 'R' << endl;
            } else {
                if (p < 0) sgn = 1, sg1++;
                if (b * c < 0) sg1++;
                cout << "x";
                if (sgn == 0) cout << '>';
                else cout << '<';
                if (b * c == 0) {
                    cout << 0 << endl;
                } else {
                    int g = gcd(abs(p), abs(b * c));
                    if (sg1 % 2 != 0) cout << '-';
                    if (g == abs(p)) cout << abs(b * c) / g << endl;
                    else cout << abs(b * c) / g << '/' << abs(p) / g << endl;
                }
            }
        } else {
            sgn = 1;
            if (b == inf) p = c;
            else p = b;
            if (p == 0) {
                if (a * d <= 0) cout << 'E' << endl;
                else cout << 'R' << endl;
            } else {
                if (p < 0) sgn = 0, sg1++;
                if (a * d < 0) sg1++;
                cout << "x";
                if (sgn == 0) cout << '>';
                else cout << '<';
                if (a * d == 0) {
                    cout << 0 << endl;
                } else {
                    int g = gcd(abs(p), abs(a * d));
                    if (sg1 % 2 != 0) cout << '-';
                    if (g == abs(p)) cout << abs(a * d) / g << endl;
                    else cout << abs(a * d) / g << '/' << abs(p) / g << endl;
                }
            }
        }
    }
}