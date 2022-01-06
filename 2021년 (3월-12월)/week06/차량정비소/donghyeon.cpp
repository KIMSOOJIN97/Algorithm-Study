#include <iostream>
#include <string.h>
#include <queue>
using namespace std;

// �������� ���� ����ü
typedef struct _customer {
	int arriveTime; // ó�� �����ð�
	int receptionNum; // �̿��ߴ� ����ó ��ȣ
	int repairNum; // �̿��ߴ� ����� ��ȣ
	int processTime; // ���� ��ó�� �ð�
	int receptionFinishTime; // ����ó���� ���� �ð�
}Customer;
Customer customer[1002];

// ����� ����ο� ���ı���
// ����ҿ� ���� �� ����(= ����ó���� ���� �ð�) �������� -> �̿��ߴ� ����ó ��ȣ ��������
struct cmp {
	bool operator()(int a, int b) {
		if (customer[a].receptionFinishTime != customer[b].receptionFinishTime) {
			return customer[a].receptionFinishTime > customer[b].receptionFinishTime;
		}
		else {
			return customer[a].receptionNum > customer[b].receptionNum;
		}
	}
};

int N;
int M;
int K;
int A;
int B;
int receptionDesk[11]; // �� ����ó�� ó���ϴ� ����ȣ
int repairDesk[11]; // �� ����Ұ� ó���ϴ� ����ȣ
int receptionTime[11]; // �� ����ó ó���ð�
int repairTime[11]; // �� ����� ó���ð�
queue<int> notArrive; // ���� �������� ���� ����ȣ
queue<int> waitingReception; // ����ó�� ���� ���� ����ϴ� ����ȣ
priority_queue<int, vector<int>, cmp> waitingRepair; // ����ҿ� ���� ���� ����ϴ� ����ȣ
int times; // ���� �ð�
int completeCnt; // ��� ó���� ��ģ �� ��
int answer;

// ����ó ��ó��
void processReception() {
	for (int i = 1; i <= N; i++) {
		if (receptionDesk[i] != 0) { // i�� ����ó�� ���� �ִٸ�
			int cm = receptionDesk[i];
			customer[cm].processTime--; // �ش� ����ó�� ���� ���� ��ó�� �ð��� ����
			if (customer[cm].processTime == 0) { // ���� ���´ٸ�
				customer[cm].receptionFinishTime = times; // ����ó���� ���� ���� �ð� ����
				waitingRepair.push(cm); // ����� ��� ������ ����
				receptionDesk[i] = 0; // �ش� ����ó�� �ð� �ִ� �� ǥ�ø� ����
			}
		}
	}
}

// ����ִ� ����ó �� ���� ��ȣ�� ���� ���� ������
int isEmptyReception() {
	for (int i = 1; i <= N; i++) {
		if (receptionDesk[i] == 0) {
			return i;
		}
	}
	return 0;
}

// ����ó ��� �� -> ����ó�� ��Ī�ϴ� �Լ�
void matchReception() {
	while (!waitingReception.empty()) { // ����ó ��� ���� �ִ� ��쿡��
		int receptionNum = isEmptyReception(); // �� ����ó�� ������
		if (receptionNum == 0) { // �� ����ó�� ���ٸ� ����
			return;
		}

		int cm = waitingReception.front(); // ��� �� �� ���� ������ ���� ������
		waitingReception.pop();
		receptionDesk[receptionNum] = cm; // �� ����ó�� ��Ī
		customer[cm].processTime = receptionTime[receptionNum]; // ��Ī�� ���� ��ó�� �ð� = �ش� ����ó ó���ð�
		customer[cm].receptionNum = receptionNum; // ��Ī�� �� ����ó ��ȣ = �ش� ����ó ��ȣ
	}
}

// ����� ��ó��
void processRepair() {
	for (int i = 1; i <= M; i++) {
		if (repairDesk[i] != 0) { // i�� ����ҿ� ���� �ִٸ�
			int cm = repairDesk[i];
			customer[cm].processTime--; // �ش� ������� ���� ���� ��ó�� �ð��� ����
			if (customer[cm].processTime == 0) {  // ���� ���´ٸ�
				repairDesk[i] = 0; // �ش� ���� �ð� �ִ� �� ǥ�ø� ����
				completeCnt++; // ��� ���� ���� �� �� ����
				if (customer[cm].receptionNum == A && customer[cm].repairNum == B) {
					answer += cm; // �ش� ���� ����ó ��ȣ�� ����� ��ȣ�� ã������ ���� ��ġ�ϸ� �� ��ȣ ����
				}
			}
		}
	}
}

// ����ִ� ����� �� ���� ��ȣ�� ���� ���� ������
int isEmptyRepair() {
	for (int i = 1; i <= M; i++) {
		if (repairDesk[i] == 0) {
			return i;
		}
	}
	return 0;
}

// ����� ��� �� -> ����ҿ� ��Ī�ϴ� �Լ�
void matchRepair() {
	while (!waitingRepair.empty()) { // ����� ��� ���� �ִ� ��쿡��
		int repairNum = isEmptyRepair(); // �� ����Ҹ� ������
		if (repairNum == 0) { // // �� ����Ұ� ���ٸ� ����
			return;
		}
		// ��� �� �� ���� �켱������ ���� ���� ������(���� �� ���� -> ����ó ��ȣ�� ���� ����)
		int cm = waitingRepair.top();
		waitingRepair.pop();
		repairDesk[repairNum] = cm; // �� ����ҿ� ��Ī
		customer[cm].processTime = repairTime[repairNum]; // ��Ī�� ���� ��ó�� �ð� = �ش� ����� ó���ð�
		customer[cm].repairNum = repairNum; // ��Ī�� �� ����� ��ȣ = �ش� ����� ��ȣ
	}
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		/*************** �ʱ�ȭ ***************/
		cin >> N >> M >> K >> A >> B;

		for (int i = 1; i <= N; i++) {
			cin >> receptionTime[i];
		}
		for (int i = 1; i <= M; i++) {
			cin >> repairTime[i];
		}
		for (int i = 1; i <= K; i++) {
			cin >> customer[i].arriveTime;
		}

		memset(receptionDesk, 0, sizeof(receptionDesk));
		memset(repairDesk, 0, sizeof(repairDesk));
		times = 0;
		completeCnt = 0;
		answer = 0;
		/*************** �ʱ�ȭ ***************/

		for (int i = 1; i <= K; i++) { // ���� �������� ���� ������ ����
			notArrive.push(i);
		}

		while (completeCnt < K) { // ��� ���� ó���� ������
			while (!notArrive.empty()) { // ���� �������� ���� ������ �ִٸ�
				// �ش� ������ �����ð��� ����ð� ���� �ռ���
				// ����ó ��� ������ ����
				if (customer[notArrive.front()].arriveTime <= times) {
					waitingReception.push(notArrive.front());
					notArrive.pop();
				}
				else {
					break;
				}
			}

			processReception(); // ����ó ��ó��
			matchReception(); // ����ó ��Ī
			processRepair(); // ����� ��ó��
			matchRepair(); // ����� ��Ī

			times++; // �ð� ����
		}

		if (answer == 0) {
			answer = -1;
		}
		cout << "#" << test_case << " " << answer << endl;
	}
	return 0;
}