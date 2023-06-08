#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstring>
#include <iomanip>

using namespace std;

const int MAXN = 1005;
const int INF = 0x3f3f3f3f;

int matchScore = 1, dismatchScore = -1, indelScore = -3;

int match(char a, char b) {
	if (a == '\0' || b == '\0') {
		return indelScore;
	}
	else if (a == b) {
		return matchScore;
	}
	else {
		return dismatchScore;
	}
}

struct DPCell {
	int score;
	vector<pair<int, int>> prev; // 存储所有的最优选择
};

void traceback(const vector<vector<DPCell>>& dpMatrix, const string& s1, const string& s2, int i, int j, vector<pair<char, char>>& alignment) {
	if (i == 0 && j == 0) {
		// 输出一条对比序列和得分
		cout << "一种最优对比序列：" << endl;
		reverse(alignment.begin(), alignment.end()); // 反转alignment向量
		for (int k = 0; k < alignment.size(); k++) { // 用一个循环来输出
			cout << alignment[k].first << " ";
		}
		cout << endl;
		for (int k = 0; k < alignment.size(); k++) {
			cout << alignment[k].second << " ";
		}
		cout << endl;
		cout << "得分：" << dpMatrix[i][j].score << endl;
		return;
	}
	for (auto p : dpMatrix[i][j].prev) { // 遍历所有的最优选择
		int prev_i = p.first;
		int prev_j = p.second;
		if (prev_i == i - 1 && prev_j == j - 1) {
			alignment.push_back({ s1[i - 1], s2[j - 1] });
			traceback(dpMatrix, s1, s2, prev_i, prev_j, alignment);
			alignment.pop_back();
		}
		else if (prev_i == i - 1) {
			alignment.push_back({ s1[i - 1], '-' });
			traceback(dpMatrix, s1, s2, prev_i, prev_j, alignment);
			alignment.pop_back();
		}
		else {
			alignment.push_back({ '-', s2[j - 1] });
			traceback(dpMatrix, s1, s2, prev_i, prev_j, alignment);
			alignment.pop_back();
		}
	}
}

void printMatrix(const vector<vector<DPCell>>& dpMatrix, int n, int m) {
	cout << "DP矩阵:" << endl;
	cout << setw(5) << "" << "|";
	for (int j = 0; j <= m; j++) {
		cout << setw(5) << j << "|";
	}
	cout << endl;
	for (int i = 0; i <= n; i++) {
		cout << setw(5) << i << "|";
		for (int j = 0; j <= m; j++) {
			cout << setw(5) << dpMatrix[i][j].score << "|";
		}
		cout << endl;
	}
}

int needlemanWunsch(const string& s1, const string& s2) {
	int n = s1.length(), m = s2.length();
	vector<vector<DPCell>> dpMatrix(n + 1, vector<DPCell>(m + 1));

	// 初始化第一行和第一列
	for (int i = 0; i <= n; i++) {
		dpMatrix[i][0] = { indelScore * i };
		dpMatrix[i][0].prev.push_back({ i - 1, 0 });
	}
	for (int j = 0; j <= m; j++) {
		dpMatrix[0][j] = { indelScore * j };
		dpMatrix[0][j].prev.push_back({ 0, j - 1 });
	}

	// DP过程
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			int matchScore = dpMatrix[i - 1][j - 1].score + match(s1[i - 1], s2[j - 1]);
			int deleteScore = dpMatrix[i - 1][j].score + indelScore;
			int insertScore = dpMatrix[i][j - 1].score + indelScore;
			int maxScore = max(matchScore, max(deleteScore, insertScore));
			dpMatrix[i][j].score = maxScore;
			// 记录所有的最优选择
			if (maxScore == matchScore) {
				dpMatrix[i][j].prev.push_back({ i - 1, j - 1 });
			}
			if (maxScore == deleteScore) {
				dpMatrix[i][j].prev.push_back({ i - 1, j });
			}
			if (maxScore == insertScore) {
				dpMatrix[i][j].prev.push_back({ i , j - 1 });
			}
		}
	}

	// 输出DP矩阵
	printMatrix(dpMatrix, n, m);

	// 回溯输出所有的最优对比序列
	vector<pair<char, char>> alignment; // 存储当前的对比序列
	traceback(dpMatrix, s1, s2, n, m, alignment);

	return dpMatrix[n][m].score;
}

int main() {
	string s1, s2;
	cout << "Please enter the first sequence: ";
	cin >> s1;
	cout << "Please enter the second sequence: ";
	cin >> s2;

	cout << "Please enter the match score: ";
	cin >> matchScore;
	cout << "Please enter the dismatch score: ";
	cin >> dismatchScore;
	cout << "Please enter the indel score: ";
	cin >> indelScore;

	needlemanWunsch(s1, s2);

	return 0;
}
