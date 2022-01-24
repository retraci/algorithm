// 减数游戏
/*

*/

#include <bits/stdc++.h>

using namespace std;

int n, x, y;

int main() {
	cin >> n >> x >> y;
	if (n <= x) {
		cout << "Monody wins!" << endl;
		return 0;
	}
	
	if (x > y) cout << "Monody wins!" << endl;
	else if (y > x) cout << "LXHing wins!" << endl;
	else cout << ((n%(x+1)) ? "Monody wins!":"LXHing wins!") << endl;
	
	return 0;
}
