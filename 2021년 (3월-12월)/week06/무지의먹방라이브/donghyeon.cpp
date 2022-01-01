#include <string>
#include <vector>

using namespace std;

// ��Ȯ�� : ���
// ȿ���� : ���� ���� �̤���
int solution(vector<int> food_times, long long k) {
	int answer = 0;
	int idx = 0; // ���� �������� ���� ��ȣ
	int cnt = 0; // �� ���� ���� ��

	for (int i = 0; i < k;) { // k�ʱ���
		if (idx >= food_times.size()) { // �ε��� ����(�� ���� �������� �ٽ� ó������)
			idx -= food_times.size();
		}

		if (food_times[idx]) { // ������ �ִٸ�
			food_times[idx]--; // ���� ���� ����
			if (food_times[idx] == 0) { // �� �Ծ��ٸ�
				cnt++; // �� ���� ���� �� ����
			}
			idx++; // ���� ��������
			i++; // �ð� ����
		}
		else { // ������ ���ٸ�
			idx++; // �ð� �������� ���� ���Ĺ�ȣ��
		}

		if (cnt == food_times.size()) { // ��� ������ �� �Ծ��ٸ� ����
			break;
		}
	}

	if (cnt == food_times.size()) { // ��� ������ �� �Ծ��ٸ� -1
		answer = -1;
	}
	else {
		// ��Ʈ��ũ ���� �� ���� ������ ã��
		while (1) {
			if (idx >= food_times.size()) { // �ε��� ����(�� ���� �������� �ٽ� ó������)
				idx -= food_times.size();
			}

			if (food_times[idx]) { // ���� ���� ������ �ִٸ� ����
				break;
			}
			else { // ������ ���� ��������
				idx++;
			}
		}
		answer = idx + 1; // �ε����� ���Ĺ�ȣ ����
	}

	return answer;
}