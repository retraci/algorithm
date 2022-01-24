// 蓝桥杯2018B 防御力
/*
	思路： 
	排序 贪心 
*/

#include <bits/stdc++.h>

using namespace std;

struct Node {
	int idx, val;
	Node(int i_, int v_) {
		idx = i_, val = v_;
	}
	bool operator < (const Node& n1) const {
		return idx > n1.val;
	}
};

int na, nb;
vector<Node> va, vb;
string ord;

void solve() {
	sort(va.begin(), va.end());
	sort(vb.begin(), vb.end());
	int pa = 0, pb = 0;
	
	for(int i = 0; i < ord.size(); i++) {
		if(ord[i] == '0') {
			cout << 'A' << va[pa++].idx << endl;
		} else {
			cout << 'B' << vb[pb++].idx << endl;
		}
	}
	cout << 'E' << endl;
}

int main() {
	cin >> na >> nb;
	
	int temp;
	for(int i = 1; i <= na; i++) {
		scanf("%d", &temp);
		va.push_back(Node(i, temp));
	}
	for(int i = 1; i <= nb; i++) {
		scanf("%d", &temp);
		vb.push_back(Node(i, temp));
	}
	cin >> ord;
	solve();
	
	return 0;
}
