#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <algorithm>

using namespace std;

int S[17][17]; // �ó��� ����
int N;
int K;
int C[17]; // N�� �� K���� �� ����
vector<int> A; // A������ ������
vector<int> B; // B������ ������
int minDiff; // �� ���İ��� �ּ� ���� ����

// �� ���ĵ��� �ó��� ���� ���ϰ� ���� ���̸� ���ϴ� �Լ�
void makeSynergy() {
	int aSum = 0; // A������ ��
	int bSum = 0; // B������ ��

	// �� ������ �ó������� ����
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A.size(); j++) {
			if (i != j) {
				aSum += S[A[i]][A[j]];
			}
		}
	}

	// �� ������ �ó������� ����
	for (int i = 0; i < B.size(); i++) {
		for (int j = 0; j < B.size(); j++) {
			if (i != j) {
				bSum += S[B[i]][B[j]];
			}
		}
	}

	// �� ������ ���� ���̰� �ּҰ����� ������ ����
	int diff = abs(aSum - bSum);
	minDiff = min(minDiff, diff);

	return;
}

// N���� ��� �� K���� ����
void nCk(int depth, int next) {
	if (depth == K) { // K���� ��� �����ߴٸ�
		// ����Ḧ ���� ���� �ʱ�ȭ
		A.clear();
		B.clear();

		int check[17] = { 0, }; // A������ ������ ������ üũ
		// K���� �� ������ A������ ������ �ְ�
		// ���õ��� ���� ��ҵ��� B������ ����ῡ ����
		for (int i = 0; i < K; i++) {
			A.push_back(C[i]);
			check[C[i]] = 1;

		}
		for (int i = 0; i < N; i++) {
			if (check[i] == 0) {
				B.push_back(i);
			}
		}

		makeSynergy();
	}
	else { // ���� K���� ������ �� ���� �ʾҴٸ�
		for (int i = next; i < N; i++) {
			C[depth] = i; // depth��° ������ i���� ����
			nCk(depth + 1, i + 1); // i�� ���� ������ ������ ���� �̾��
		}
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
		K = N / 2;
		minDiff = INT_MAX;

		// �ó��� �� ����
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> S[i][j];
			}
		}

		nCk(0, 0); // (0�� ����, 0������ ����)

		cout << "#" << test_case << " " << minDiff << endl;
	}
	return 0;
}