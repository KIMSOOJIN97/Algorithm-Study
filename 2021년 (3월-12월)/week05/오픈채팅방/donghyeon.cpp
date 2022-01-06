#include <string>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

// ������ �������� ���ڿ� �и�
// result[0] : ��ɾ�, result[1] : ���� ���̵�, result[2] : �г���
vector<string> splitString(string str) {
	vector<string> result;
	string tmp = "";

	for (int i = 0; i < str.length(); i++) {
		if (str[i] == ' ') {
			result.push_back(tmp);
			tmp = "";
		}
		else {
			tmp += str[i];
		}
	}
	result.push_back(tmp);

	return result;
}

vector<string> solution(vector<string> record) {
	vector<string> answer;
	map<string, string> nicknames; // <���� ���̵�, �г���>
	vector<pair<string, string>> messages; // <���� ���̵�, �޽���>

	for (int i = 0; i < record.size(); i++) {
		vector<string> info = splitString(record[i]);

		// (���� ���̵�, �޽���) ���·� vector�� ���� 
		if (info[0] == "Leave") {
			messages.push_back(make_pair(info[1], "���� �������ϴ�."));
		}
		else {
			if (info[0] == "Enter") {
				messages.push_back(make_pair(info[1], "���� ���Խ��ϴ�."));
			}
			nicknames[info[1]] = info[2]; // �� ������ �������� ������ �г��� ����
		}
	}

	for (int i = 0; i < messages.size(); i++) { // �޽��� �迭 Ž��
		string userId = messages[i].first; // ���� ���̵� ������
		// <���� ���̵� �ش��ϴ� �г���, �޽���> ���·� �ٽ� ����
		answer.push_back(nicknames[userId] + messages[i].second);
	}

	return answer;
}