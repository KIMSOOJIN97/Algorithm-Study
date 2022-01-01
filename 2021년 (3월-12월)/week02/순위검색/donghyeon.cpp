#include <string>
#include <vector>
#include <map>

using namespace std;

// applicants[���][����][���][�ҿ�Ǫ��] = {����1,����2,����3...} ���·� ����
map<string, map<string, map<string, map<string, vector<int>>>>> applicants;

// delimeter �������� ���ڿ� �и�
vector<string> split(string info, char delimeter) {
	vector<string> result;
	string tmp = "";

	for (int i = 0; i < info.size(); i++) {
		if (info[i] == delimeter) {
			if (tmp != "and") { // "and" ���ڿ��� ������
				result.push_back(tmp);
			}
			tmp = "";
		}
		else {
			tmp += info[i];
		}
	}
	result.push_back(tmp);

	return result;
}

vector<int> solution(vector<string> info, vector<string> query) {
	vector<int> answer;

	for (int i = 0; i < info.size(); i++) {
		vector<string> splitInfo = split(info[i], ' '); // ���� ���� ���ڿ� �и�

		// ��������� �˾Ƴ� �� �̿ܿ� ��� ��찡 �����ϰ� ���� ���� �����ص�
		// ���� �� cpp�� ��� -> ���� �� '-'�� ��� �� ������ ��� �������� ���� ����
		applicants[splitInfo[0]][splitInfo[1]][splitInfo[2]][splitInfo[3]].push_back(stoi(splitInfo[4]));
		applicants["-"][splitInfo[1]][splitInfo[2]][splitInfo[3]].push_back(stoi(splitInfo[4]));
		applicants[splitInfo[0]]["-"][splitInfo[2]][splitInfo[3]].push_back(stoi(splitInfo[4]));
		applicants[splitInfo[0]][splitInfo[1]]["-"][splitInfo[3]].push_back(stoi(splitInfo[4]));
		applicants[splitInfo[0]][splitInfo[1]][splitInfo[2]]["-"].push_back(stoi(splitInfo[4]));
		applicants["-"]["-"][splitInfo[2]][splitInfo[3]].push_back(stoi(splitInfo[4]));
		applicants["-"][splitInfo[1]]["-"][splitInfo[3]].push_back(stoi(splitInfo[4]));
		applicants["-"][splitInfo[1]][splitInfo[2]]["-"].push_back(stoi(splitInfo[4]));
		applicants[splitInfo[0]]["-"]["-"][splitInfo[3]].push_back(stoi(splitInfo[4]));
		applicants[splitInfo[0]]["-"][splitInfo[2]]["-"].push_back(stoi(splitInfo[4]));
		applicants[splitInfo[0]][splitInfo[1]]["-"]["-"].push_back(stoi(splitInfo[4]));
		applicants["-"]["-"]["-"][splitInfo[3]].push_back(stoi(splitInfo[4]));
		applicants["-"]["-"][splitInfo[2]]["-"].push_back(stoi(splitInfo[4]));
		applicants["-"][splitInfo[1]]["-"]["-"].push_back(stoi(splitInfo[4]));
		applicants[splitInfo[0]]["-"]["-"]["-"].push_back(stoi(splitInfo[4]));
		applicants["-"]["-"]["-"]["-"].push_back(stoi(splitInfo[4]));
	}

	for (int i = 0; i < query.size(); i++) {
		vector<string> splitQuery = split(query[i], ' ');
		// �˾Ƴ����� �������� Ư���� ������
		vector<int> applicant = applicants[splitQuery[0]][splitQuery[1]][splitQuery[2]][splitQuery[3]];
		// ���������� ������
		int X = stoi(splitQuery[4]);
		int cnt = 0;

		// �����ڵ� �� �������� �̻��� ��� count
		for (int j = 0; j < applicant.size(); j++) {
			if (applicant[j] >= X) {
				cnt++;
			}
		}
		answer.push_back(cnt);
	}

	return answer;
}