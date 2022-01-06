#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// ����� ���� ���� : ������ ���� ��������, �������� ��ȣ ���� ��������
bool cmp(pair<double, int> f1, pair<double, int> f2) {
	return (f1.first == f2.first) ? (f1.second < f2.second) : (f1.first > f2.first);
}

vector<int> solution(int N, vector<int> stages) {
	vector<int> answer;
	vector<pair<double, int>> failRate; // <������, �������� ��ȣ>
	int notClearCnt; // ���������� Ŭ���� ���� �÷��̾� ��
	int reachCnt; // ������ �÷��̾� ��

	for (int i = 1; i <= N; i++) { // ��� �������� ��ȣ�� üũ
		// �÷��̾� �� �ʱ�ȭ
		notClearCnt = 0;
		reachCnt = 0;
		for (int j = 0; j < stages.size(); j++) { // ��� ����� �������� ��ȣ�� Ž���ϸ�
			if (stages[j] >= i) { // ���� ���������� Ŭ�����ϰų� �����ߴٸ�
				reachCnt++; // ������ �÷��̾� �� ����
				if (stages[j] == i) { // ���� ���������� ���޸��ߴٸ�
					notClearCnt++; // Ŭ���� ���� �÷��̾� �� ����
				}
			}
		}
		if (reachCnt == 0) { // �ƹ��� �������� ��������
			failRate.push_back(make_pair(0.0, i)); // ������ 0 ����
		}
		else {
			failRate.push_back(make_pair((double)notClearCnt / reachCnt, i)); // �������� �������� ��ȣ ����
		}
	}

	sort(failRate.begin(), failRate.end(), cmp);

	for (int i = 0; i < failRate.size(); i++) {
		answer.push_back(failRate[i].second);
	}

	return answer;
}