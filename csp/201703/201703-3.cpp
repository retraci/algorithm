// 201703-3 Markdown
/*
	思路：
	find 函数 
	replace 函数 
	substr 函数 
*/

#include <bits/stdc++.h>

using namespace std;

string text, line;
string ss;

void solve() {
	// 1.
	int pos = text.find("_");
	while(pos != string::npos) {
		text.replace(pos, 1, "<em>");
		int nex = text.find("_", pos);
		text.replace(nex, 1, "</em>");
		pos = text.find("_", nex);
	}

	// 2.
	pos = text.find("[");
	while(pos != string::npos) {
		int nex = text.find("]", pos);
		int left = text.find("(", nex);
		int right = text.find(")", left);
		string Text = text.substr(pos+1, nex-1-pos);
		string Link = text.substr(left+1, right-1-left);
		text.replace(text.begin()+pos, text.begin()+right+1, "<a href=\""+Link+"\">"+Text+"</a>");
		pos = text.find("[", right);
	}

	// 3.
	if(text[0] == '#') {
		int i = 0;
		while(text[i] == '#') i++;
		string temp(1, i+'0');
		text = text.substr(i+1);
		text = "<h"+temp+">" + text;
		text.insert(text.size()-1, "</h"+temp+">");

	} else if(text[0] == '*') {
		text = "<ul>\n" + text;
		text = text + "</ul>\n";

		pos = text.find("*");
		while(pos != string::npos) {
			text.replace(pos, 2, "<li>");
			int nex = text.find("\n", pos);
			text.insert(nex, "</li>");
			pos = text.find("*", nex);
		}

	} else {
		text = "<p>" + text;
		text.insert(text.size()-1, "</p>");
	}

	cout << text;
	text = "";
}

int main() {
	while(getline(cin, line)) {
		if(line.length() > 0) {
			text += line+"\n";
			continue;
		}
		if(text.length() > 0)
			solve();
	}
	if(text.length() > 0)
		solve();
	
//	cout << endl << ss;

	return 0;
}

