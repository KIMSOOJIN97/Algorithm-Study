#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

int N;
int nums[13]; // ���� �迭 ����
int opCnt[4]; // �� �������� ����
int maxSum; // ���� ����� �ִ밪
int minSum; // ���� ����� �ּҰ�

// �����ڰ� �ִٸ� ������ ����� �Ű������� ���
void dfs(int depth, int sum) {
	if (depth == N) { // ��� ����� ���´ٸ� �ִ밪, �ּҰ� ����
		maxSum = max(maxSum, sum);
		minSum = min(minSum, sum);
		return;
	}

	if (opCnt[0]) { // '+'�� �ִٸ� '+'���� ���� �� ���ڸ� ���� ������ �̾��
		opCnt[0]--;
		dfs(depth + 1, sum + nums[depth]);
		opCnt[0]++; // ��͸� �������� �Ŀ� '+' ���� �ٽ� ����
	}
	if (opCnt[1]) { // '-'�� �ִٸ� '-'���� ���� �� ���ڸ� �� ������ �̾��
		opCnt[1]--;
		dfs(depth + 1, sum - nums[depth]);
		opCnt[1]++; // ��͸� �������� �Ŀ� '-' ���� �ٽ� ����
	}
	if (opCnt[2]) { // '*'�� �ִٸ� '*'���� ���� �� ���ڸ� �� ������ �̾��
		opCnt[2]--;
		dfs(depth + 1, sum * nums[depth]);
		opCnt[2]++; // ��͸� �������� �Ŀ� '*' ���� �ٽ� ����
	}
	if (opCnt[3]) { // '/'�� �ִٸ� '/'���� ���� �� ���ڸ� �� ������ �̾��
		opCnt[3]--;
		dfs(depth + 1, sum / nums[depth]);
		opCnt[3]++; // ��͸� �������� �Ŀ� '/' ���� �ٽ� ����
	}

	return;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		// �ʱ�ȭ
		cin >> N;
		maxSum = INT_MIN;
		minSum = INT_MAX;

		for (int i = 0; i < 4; i++) {
			cin >> opCnt[i];
		}
		for (int i = 0; i < N; i++) {
			cin >> nums[i];
		}

		// �ʱⰪ�� �����̹Ƿ� �հ�� ù��° ��, �ι�° ���Һ��� ���
		dfs(1, nums[0]);

		cout << "#" << test_case << " " << maxSum - minSum << endl;

	}
	return 0;
}