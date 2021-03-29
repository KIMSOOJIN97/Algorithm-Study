#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

typedef struct _bc {
	int x;
	int y;
	int c;
	int p;
}BC;
BC bcList[10];

int aPath[101]; // a�� ��θ� ����
int bPath[101]; // b�� ��θ� ����
int dx[] = { 0,0,1,0,-1 };
int dy[] = { 0,-1,0,1,0 };

int M, A;

// ������ BC���� ��ȣ�� ������
vector<int> checkBC(int x, int y) {
	vector<int> bc;

	for (int i = 0; i < A; i++) {
		if (abs(x - bcList[i].x) + abs(y - bcList[i].y) <= bcList[i].c) { // ���� �����ȿ� �ִٸ�
			bc.push_back(i); // �ش� BC�� ��ȣ�� ����
		}
	}

	return bc;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		// �ʱ�ȭ
		pair<int, int> aPos = { 1,1 };
		pair<int, int> bPos = { 10,10 };
		int totalP = 0;

		cin >> M >> A;

		for (int i = 0; i < M; i++) {
			cin >> aPath[i];
		}
		for (int i = 0; i < M; i++) {
			cin >> bPath[i];
		}
		for (int i = 0; i < A; i++) {
			cin >> bcList[i].x >> bcList[i].y >> bcList[i].c >> bcList[i].p;
		}

		for (int i = -1; i < M; i++) {
			if (i >= 0) { // a�� b�� ���� ��ġ�� ����(�� ó���� ��ġ�� ����x)
				aPos.first += dx[aPath[i]];
				aPos.second += dy[aPath[i]];
				bPos.first += dx[bPath[i]];
				bPos.second += dy[bPath[i]];
			}

			// ������ BC�� ������
			vector<int> aBC = checkBC(aPos.first, aPos.second);
			vector<int> bBC = checkBC(bPos.first, bPos.second);

			if (aBC.size() == 0 && bBC.size() == 0) { // ������ BC�� ���ٸ� �Ѿ
				continue;
			}
			else if (aBC.size() == 0) { // a�� ������ BC�� ���ٸ�
				int maxP = 0;
				for (int j = 0; j < bBC.size(); j++) { // b�� ������ BC �߿� �ִ뷮�� ����
					maxP = max(maxP, bcList[bBC[j]].p);
				}
				totalP += maxP;
			}
			else if (bBC.size() == 0) { // b�� ������ BC�� ���ٸ�
				int maxP = 0;
				for (int j = 0; j < aBC.size(); j++) { // a�� ������ BC �߿� �ִ뷮�� ����
					maxP = max(maxP, bcList[aBC[j]].p);
				}
				totalP += maxP;
			}
			else { // �� �� ������ BC�� �ִٸ�
				int maxP = 0;
				// a�� b�� ������ BC ���� �� 
				for (int j = 0; j < aBC.size(); j++) {
					for (int k = 0; k < bBC.size(); k++) {
						int sumP;
						if (aBC[j] == bBC[k]) { // ���� BC�� �����ߴٸ�
							sumP = bcList[aBC[j]].p; // �յ�� �й��ϹǷ� ��ü �������� �ش� BC�� ������
						}
						else { // �ٸ� BC�� ���� �����ߴٸ�
							sumP = bcList[aBC[j]].p + bcList[bBC[k]].p; // ��ü �������� ������ �������� �ջ�
						}
						maxP = max(maxP, sumP); // ���� �ִ뷮�� ��� ������ ��
					}
				}
				totalP += maxP;
			}
		}

		cout << "#" << test_case << " " << totalP << endl;
	}
	return 0;
}