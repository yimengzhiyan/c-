#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>

using namespace std;

int charToScore(char arrowScore) {
    if (arrowScore == 'X' || arrowScore == 'x') {
        return 10;
    } else {
        return arrowScore - '0';
    }
}

void writeToFile(const string& bowType, int distance, int groupCount, int arrowCountPerGroup, const vector<int>& groupScores) {
    ofstream outFile("archery_data.txt", ios::app);

    outFile << "射箭类型: " << bowType << "，距离: " << distance << "米" << endl;
    outFile << "组数: " << groupCount << "，每组箭数: " << arrowCountPerGroup << endl;
    for (int i = 0; i < groupCount; ++i) {
        outFile << "第 " << i + 1 << " 组总计环数: " << groupScores[i] << endl;
    }
    outFile << endl;

    outFile.close();
}

void readFromFile() {
    ifstream inFile("archery_data.txt");

    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            cout << line << endl;
        }
    } else {
        cout << "无法打开文件。" << endl;
    }

    inFile.close();
}

int main() {
    int groupCount, arrowCountPerGroup;
    string bowType;
    int distance;
    cout <<"射中靶心请记为X"<<endl;
    cout << "请输入射箭的组数: ";
    cin >> groupCount;

    cout << "请输入每组箭的箭数: ";
    cin >> arrowCountPerGroup;

    cout << "请输入射箭类型 (反曲弓/复合弓/传统弓): ";
    cin >> bowType;

    cout << "请输入射箭距离 (8/10/18/30/40/50): ";
    cin >> distance;

    int totalArrows = groupCount * arrowCountPerGroup;
    vector<int> groupScores(groupCount, 0);
    int totalScore = 0;

    for (int i = 0; i < groupCount; ++i) {
        cout << "请输入第 " << i + 1 << " 组的环数: ";
        for (int j = 0; j < arrowCountPerGroup; ++j) {
            char arrowScore;
            cin >> arrowScore;
            int arrowScoreInt = charToScore(arrowScore);

            // 检查输入的环数是否在 0 到 10 之间
            while (arrowScoreInt < 0 || arrowScoreInt > 10) {
                cout << "输入错误，请输入 0 到 10 之间的数字或 X (代表10): ";
                cin >> arrowScore;
                arrowScoreInt = charToScore(arrowScore);
            }

            groupScores[i] += arrowScoreInt;
            totalScore += arrowScoreInt;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "射箭类型: " << bowType << "，距离: " << distance << "米" << endl;
    cout << "总箭数: " << totalArrows << endl;
    for (int i = 0; i < groupCount; ++i) {
        double averageScore = (double)groupScores[i] / arrowCountPerGroup;
        cout << "第 " << i + 1 << " 组总计环数: " << groupScores[i] << "，平均环数: " << averageScore << endl;

        // 输出进度条形式的平均环数可视化
        cout << "平均环数可视化: [";
        int progressBarWidth = 50;
        int progress = (int)(averageScore * progressBarWidth / 10.0);
        for (int j = 0; j < progressBarWidth; ++j) {
            if (j < progress) {
                cout << '=';
            } else {
                cout << ' ';
            }
        }
        cout << "]" << endl;
    }
    cout << "所有箭环数平均值: " << (double)totalScore / totalArrows << endl;

    // 将数据写入文件
    writeToFile(bowType, distance, groupCount, arrowCountPerGroup, groupScores);

    // 从文件中读取数据
    cout << "读取文件中的射箭数据：" << endl;
    readFromFile();

    return 0;
}
