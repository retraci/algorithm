// POJ 2484 A Funny Game
/*
	思路：
	只要第二个人把链分成两条一样的，并且学着第一个人来拿硬币，则第二人必胜 
*/

#include <iostream> 
#include <cstdio>

using namespace std;

int main() {
	int n;
	while(cin >> n && n) {
		if(n > 2) puts("Bob");
		else puts("Alice");
	}
	
	return 0;
} 
