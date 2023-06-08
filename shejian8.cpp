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

    outFile << "�������: " << bowType << "������: " << distance << "��" << endl;
    outFile << "����: " << groupCount << "��ÿ�����: " << arrowCountPerGroup << endl;
    for (int i = 0; i < groupCount; ++i) {
        outFile << "�� " << i + 1 << " ���ܼƻ���: " << groupScores[i] << endl;
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
        cout << "�޷����ļ���" << endl;
    }

    inFile.close();
}

int main() {
    int groupCount, arrowCountPerGroup;
    string bowType;
    int distance;
    cout <<"���а������ΪX"<<endl;
    cout << "���������������: ";
    cin >> groupCount;

    cout << "������ÿ����ļ���: ";
    cin >> arrowCountPerGroup;

    cout << "������������� (������/���Ϲ�/��ͳ��): ";
    cin >> bowType;

    cout << "������������� (8/10/18/30/40/50): ";
    cin >> distance;

    int totalArrows = groupCount * arrowCountPerGroup;
    vector<int> groupScores(groupCount, 0);
    int totalScore = 0;

    for (int i = 0; i < groupCount; ++i) {
        cout << "������� " << i + 1 << " ��Ļ���: ";
        for (int j = 0; j < arrowCountPerGroup; ++j) {
            char arrowScore;
            cin >> arrowScore;
            int arrowScoreInt = charToScore(arrowScore);

            // �������Ļ����Ƿ��� 0 �� 10 ֮��
            while (arrowScoreInt < 0 || arrowScoreInt > 10) {
                cout << "������������� 0 �� 10 ֮������ֻ� X (����10): ";
                cin >> arrowScore;
                arrowScoreInt = charToScore(arrowScore);
            }

            groupScores[i] += arrowScoreInt;
            totalScore += arrowScoreInt;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "�������: " << bowType << "������: " << distance << "��" << endl;
    cout << "�ܼ���: " << totalArrows << endl;
    for (int i = 0; i < groupCount; ++i) {
        double averageScore = (double)groupScores[i] / arrowCountPerGroup;
        cout << "�� " << i + 1 << " ���ܼƻ���: " << groupScores[i] << "��ƽ������: " << averageScore << endl;

        // �����������ʽ��ƽ���������ӻ�
        cout << "ƽ���������ӻ�: [";
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
    cout << "���м�����ƽ��ֵ: " << (double)totalScore / totalArrows << endl;

    // ������д���ļ�
    writeToFile(bowType, distance, groupCount, arrowCountPerGroup, groupScores);

    // ���ļ��ж�ȡ����
    cout << "��ȡ�ļ��е�������ݣ�" << endl;
    readFromFile();

    return 0;
}
