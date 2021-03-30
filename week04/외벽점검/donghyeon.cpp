#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int minDepth; // ���� ���� ������ ģ�� ��

void dfs(int n, vector<int>& weak, vector<int>& dist, vector<int> weakChk, int depth, int repairCnt) {
	vector<int> tmpChk; // ��� ���� ���� ǥ�ø� ���� �迭�� �ӽ� ����
	int tmpCnt; // ������� ���˵� �ܺ� ���� ���� ����
	int start; // ���� ���� ��ġ
	int end1; // ������ �� �ִ� �ִ� ����
	int end2 = -1;

	if (depth == dist.size()) { // ��� ģ���� �̹� ���� �����ߴٸ� ����
		return;
	}

	for (int i = 0; i < weak.size(); i++) { // ��� ������ ��ȸ
		if (weakChk[i] == 1) { // �̹� ���˵Ǿ��ִٸ� �Ѿ
			continue;
		}
		tmpChk = weakChk;
		tmpCnt = repairCnt;
		start = weak[i]; // ���� ���� ��ġ = i�� ��� ���� ��ġ
		end1 = weak[i] + dist[depth]; // ���� ���� = i�� ��� ���� ~ (i�� ��� ���� + depth�� ģ���� �̵��Ÿ�)

		if (end1 >= n) { // ���� ������ ��ü �ܺ� ���̸� �ʰ��Ѵٸ� �� ���� ���Ƽ� ���� �������� ����
			end2 = end1 - n; // n = 12, 10~13 �������� ���� ���� -> 10~12, 0~1 ���� ����
		}

		for (int j = 0; j < weak.size(); j++) { // ��� ������ ��ȸ
			if (tmpChk[j] == 0) { // ���� ���˵Ǿ����� ���� ��� ���� �߿�
				if ((weak[j] >= start && weak[j] <= end1) || weak[j] <= end2) { // ���� ���� �����ȿ��� ���� �����ϴٸ�
					tmpChk[j] = 1; // ���� ǥ��
					tmpCnt++; // ������ ������� ���� ����
				}
			}
		}

		if (tmpCnt == weak.size()) { // ���� �����ߴٸ�
			minDepth = min(minDepth, depth); // ���� ���� ģ�� ���� ���� ����
		}

		// ���� ���� ����, ������ ģ�� ��, ������ ��� ���� ������ �������� ���
		dfs(n, weak, dist, tmpChk, depth + 1, tmpCnt);
	}
}

int solution(int n, vector<int> weak, vector<int> dist) {
	int answer = 0;
	vector<int> weakChk(weak.size(), 0); // weakChk[i] = 1 -> weak[i]�� ���� �Ϸ�

	minDepth = dist.size() + 1;

	sort(dist.begin(), dist.end(), greater<int>()); // �� ���� ���� ģ���� �����ϱ� ���� �̵��Ÿ� ���� �������� ����

	dfs(n, weak, dist, weakChk, 0, 0);

	if (minDepth == dist.size() + 1) { // ģ���� ������ ���� ���� �����ؾ� ���� �����̸� -1
		answer = -1;
	}
	else {
		answer = minDepth + 1;
	}

	return answer;
}