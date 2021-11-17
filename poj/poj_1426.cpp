// POJ 1426 Find The Multiple
/*
	Ë¼Â·£º
	±©ËÑ£¬bfs 
*/

#include <iostream>
#include <algorithm>
#include <queue>

typedef unsigned long long ull;

using namespace std;

int n;

void bfs() {
	queue<ull> que;
	que.push(1);
	
	while(!que.empty()) {
		ull temp = que.front(); que.pop();
		
		if(temp % n == 0) {
			cout << temp << endl;
			return;
		}
		
		que.push(temp*10);
		que.push(temp*10+1);
	}
}

int main() {
	while(cin >> n && n) {
		bfs();
	}
	
	return 0;
}
