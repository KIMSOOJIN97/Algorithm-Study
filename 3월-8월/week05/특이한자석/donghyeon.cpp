#include <iostream>
#include <vector>

using namespace std;

int mg[4][8]; // mg[i][j] : i�� �ڼ��� j��° ���� ��(N�� - 0, S�� - 1)

// �ڼ��� ȸ��
void rotate(int num, int d) {
	if (d == 1) { // �ð���� ȸ��
		// 0 0 0 1 1 0 0 1 -> 1 0 0 0 1 1 0 0
		int last = mg[num][7]; // ������ ���� �����ص�

		for (int i = 7; i > 0; i--) { // ��� ������ ���������� �̵�
			mg[num][i] = mg[num][i - 1];
		}

		mg[num][0] = last; // ù��° ���� ȸ���ϱ� �� ������ ���� ����
	}
	else { // �ݽð���� ȸ��
		// 1 0 0 0 1 0 1 0 -> 0 0 0 1 0 1 0 1
		int first = mg[num][0]; // ù��° ���� �����ص�

		for (int i = 0; i < 7; i++) { // ��� ������ �������� �̵�
			mg[num][i] = mg[num][i + 1];
		}

		mg[num][7] = first; // ������ ���� ȸ���ϱ� �� ù��° ���� ����
	}

	return;
}

// ���� �ڼ��� �پ��ִ� ���� �ڼ��� ����
int getLeft(int num) {
	return mg[num][6];
}

// ������ �ڼ��� �پ��ִ� ���� �ڼ��� ����
int getRight(int num) {
	return mg[num][2];
}

// 4���� �ڼ��� � �������� ȸ���ϴ��� ����
vector<int> getDir(int num, int d) {
	vector<int> dir(4, 0); // 0���� �ʱ�ȭ -> 0 : ȸ������ ����
	dir[num] = d; // num��° �ڼ��� d�������� ȸ��

	// num�� �ڼ� ���� �ڼ����� ȸ�� ������ ����
	int left = num - 1;
	while (1) {
		// ���� ù��° �ڼ��̰ų� ���� �ڼ��� �پ��ִ� ���� �ڼ��� ���ٸ� ����
		if (left < 0 || (getRight(left) == getLeft(left + 1))) {
			break;
		}

		// �ڼ��� �ٸ��ٸ� ���� �ڼ��� ȸ�������� ���� �ڼ��� ȸ�������� �ݴ�������� ����
		if (dir[left + 1] == 1) {
			dir[left] = -1;
		}
		else {
			dir[left] = 1;
		}
		left--; // ���� �ڼ����� �̵�
	}

	// num�� �ڼ� ������ �ڼ����� ȸ�� ������ ����
	int right = num + 1;
	while (1) {
		// ���� ������ �ڼ��̰ų� ������ �ڼ��� �پ��ִ� ���� �ڼ��� ���ٸ� ����
		if (right >= 4 || (getRight(right - 1) == getLeft(right))) {
			break;
		}

		// �ڼ��� �ٸ��ٸ� ������ �ڼ��� ȸ�������� ���� �ڼ��� ȸ�������� �ݴ�������� ����
		if (dir[right - 1] == 1) {
			dir[right] = -1;
		}
		else {
			dir[right] = 1;
		}
		right++; // ������ �ڼ����� �̵�
	}

	return dir; // ȸ������ �迭�� ����
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		int K;
		int num;
		int d;
		vector<int> dir;

		cin >> K;

		// �ڼ����� �ڼ��� ����
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 8; j++) {
				cin >> mg[i][j];
			}
		}

		for (int i = 0; i < K; i++) {
			cin >> num >> d;

			dir = getDir(num - 1, d); // �ڼ����� ȸ�������� ����

			for (int j = 0; j < 4; j++) { // �ڼ����� Ȯ���ϸ鼭
				if (dir[j] == 0) { // ȸ������ �ʴ� �ڼ����� �Ѿ
					continue;
				}
				rotate(j, dir[j]); // j��° �ڼ��� dir[j]�������� ȸ��
			}
		}

		int sum = 0;
		int score = 1;
		for (int i = 0; i < 4; i++) { // �ڼ����� Ȯ���ϸ鼭
			if (mg[i][0] == 1) { // �� �� �ڼ��� S���̸� ����ȹ��
				sum += score;
			}
			score *= 2;
		}

		cout << "#" << test_case << " " << sum << endl;
	}

	return 0;
}