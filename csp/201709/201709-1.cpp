// 201709-1 打酱油
/*
	思路：
	模拟 
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	cin >> n;
	int sum = n / 10;
	int discount2 = sum / 5;
	int discount1 = (sum % 5) / 3;
	sum += discount2*2 + discount1;
	cout << sum << endl;
	
	return 0;
}
