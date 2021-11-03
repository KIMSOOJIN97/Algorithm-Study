#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(string s) {
	int answer = s.length(); // ���� ���ڿ��� �ִ� ���� = ���� ���ڿ� ����
	string s1 = "";
	string s2 = "";

	for (int i = 1; i <= s.length() / 2; i++) { // i = ���ڿ��� �ڸ��� ����(1�� ~ ���ڿ�����/2 )
		int idx = 0; // ���ڿ� index
		int length = 0; // ����� ���ڿ��� ��ü ����
		int compact = 0; // ����� ���ڿ� ����

		while (1) {
			// idx�� �������� i�������� �ڸ� 2���� ���ڿ��� ������
			s1 = s.substr(idx, i);
			s2 = s.substr(idx + i, i);

			if (s1 == s2) { // �� ���ڿ��� ���ٸ�
				compact++; // ����� ���ڿ� ���� ����
			}
			else { // �� ���ڿ��� �ٸ���
				if (compact) { // ������ ����� ���ڿ��� �ִٸ�
					// ���� ���� ������ ���̸� ���� �� ��� ���ڿ� ���̿� ������
					// 3�� ���� ���ڿ� ���� 14�� -> length += 3(�� ����) + 2(14�� ����)
					compact++;
					length += i + to_string(compact).length();
					compact = 0; // ���� ���� ���� �ʱ�ȭ
				}
				else { // ������ ����� ���ڿ��� ���ٸ�
					length += i; // ��� ���ڿ��� ���̸� ����
				}
			}

			idx += i; // ���ڿ� ������ŭ index ���� 

			if (idx + i > s.length()) {
				length += s2.length();
				break;
			}
		}

		answer = min(answer, length);
	}

	return answer;
}