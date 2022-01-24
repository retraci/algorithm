// 蓝桥杯2015B 表格计算 
/*
	思路：
	字符串处理 
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 55;

int n, m;
double data[maxn][maxn];
vector<vector<string> > input;

void dfs(int x, int y);

bool is_digit(string s) {
	for(int i = 0; i < s.size(); i++) {
		if(s[i] >= '0' && s[i] <= '9') continue;
		else return false;
	}
	return true;
}

double s2i(string s) {
	int res = 0;
	for(int i = 0; i < s.size(); i++) {
		res *= 10;
		res += s[i] - '0';
	}
	
	return res;
}

double sum(int x1, int y1, int x2, int y2) {
	double res = 0;
	
	for(int i = x1; i <= x2; i++) {
		for(int j = y1; j <= y2; j++) {
			if(input[i][j] != "") {
				 dfs(i, j);
			}
			res += data[i][j];
		}
	}
	return res;
}

double avg(int x1, int y1, int x2, int y2) {
	double res = 0;
	
	int num = ((x2-x1+1)*(y2-y1+1));
	res = sum(x1, y1, x2, y2);
	return res/num;
}

double st(int x1, int y1, int x2, int y2) {
	double res = 0;
	
	int num = ((x2-x1+1)*(y2-y1+1));
	double av = avg(x1, y1, x2, y2);
	for(int i = x1; i <= x2; i++) {
		for(int j = y1; j <= y2; j++) {
			if(input[i][j] != "") {
				 dfs(i, j);
			}
			res += (data[i][j]-av)*(data[i][j]-av);
		}
	}
	
	return sqrt(res/num);
}

void dfs(int x, int y) {
	//cout << x << " " << y << endl;
	string s = input[x][y];
	
	string op;
	int x1, x2, y1, y2;
	for(int i = 0; i < 3; i++) {
		op += s[i];
	}
	s.erase(s.begin(), s.begin()+4);
	
	s.erase(s.end()-1);
	int pos = s.find(':');
	s[pos] = ' ';
	pos = s.find(',');
	s[pos] = ' ';
	pos = s.find(',');
	s[pos] = ' ';
	
	stringstream ss;
	ss << s;
	
	ss >> x1 >> y1 >> x2 >> y2;
	x1--,y1--,x2--,y2--;
	//printf("%d %d %d %d\n", x1, y1, x2, y2);
	if(op == "SUM") {
		data[x][y] = sum(x1, y1, x2, y2);
	} else if(op == "AVG") {
		data[x][y] = avg(x1, y1, x2, y2);
	} else if(op == "STD") {
		data[x][y] = st(x1, y1, x2, y2);
	}
	
	input[x][y] = "";
}

void solve() {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			if(input[i][j] == "") continue;
			
			dfs(i, j);
		}
	}
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			if(j < m-1)
				printf("%.2llf ", data[i][j]);
			else
				printf("%.2llf\n", data[i][j]);
		}
	}
}

int main() {
	cin >> n >> m;
	input = vector<vector<string> >(n, vector<string>(m, ""));
	
	string temp;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			cin >> temp;
			if(is_digit(temp)) {
				data[i][j] = s2i(temp);
			} else {
				input[i][j] = temp;
			}
		}
	}
	
	solve();
	/*
	cout << endl;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			if(input[i][j] != "")
				cout << input[i][j] << " ";
			else 
				cout << data[i][j] << " ";
		}
		cout << endl;
	}
	*/	
	
	return 0;
}
