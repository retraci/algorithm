// POJ 3278 Catch That Cow
/*
    bfs
*/

#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct Node {
	int num, cnt;
	Node(int n_, int c_) {
		num = n_; cnt = c_;
	}
};

const int maxn = 100010;

int n, k, ans;
int vis[maxn];

void bfs() {
	queue<Node> que;
	que.push(Node(n, 0));
	vis[n] = 1;
	
	while(!que.empty()) {
		Node node = que.front(); que.pop();
//		cout << node.num << endl;
		if(node.num == k) {
			cout << node.cnt << endl;
			return;
		}
		
		if(node.num-1 >= 0 && !vis[node.num-1]) {
			vis[node.num-1] = 1;
			que.push(Node(node.num-1, node.cnt+1));
		} 
		if(node.num+1 < maxn && !vis[node.num+1]) {
			vis[node.num+1] = 1;
			que.push(Node(node.num+1, node.cnt+1));	
		} 
		if(node.num*2 < maxn && !vis[node.num*2]) {
			vis[node.num*2] = 1;
			que.push(Node(node.num*2, node.cnt+1));
		}
	}
}

int main() {
	cin >> n >> k;
	
	bfs();
	
	return 0;
}
