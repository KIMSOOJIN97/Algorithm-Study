#include<iostream>
#include<algorithm>
#include<math.h>
#include<cstring>

using namespace std;
//1.�ϳ��� ���� �������� �翷�� Ž���ϸ鼭 ���� �� ���� �ϳ��� ã�´�.
//2.�翷���� ã�� �ΰ��� ���� ���� ������ �ϳ��� ���� ����ŭ ������ ���� �� �ִ�.
//�������� ���
int arr[501];
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int p1, p2, h, w, sum = 0, cnt = 0;
	cin >> h >> w;


	for (int i = 0; i < w; i++)
	{
		cin >> arr[i];
	}

	for (int i = 0; i < w; i++)
	{
		//������ ���̷��� �翷 ���� ���̰� �Է¹޴� ���� ���� ���� Ŀ���ϹǷ�
		//p1, p2�� �Է¹��� ���� ���� �־���
		p1 = p2 = arr[i];
		for (int j = 0; j < i; j++)
		{
			p1 = max(p1, arr[j]);
		}
		for (int k = i + 1; k < w; k++)
		{
			p2 = max(p2, arr[k]);
		}

		//�翷�� �� ���� ������ �Է¹��� ���� �� ��ŭ ������ ���� �� ����
		sum += (min(p1, p2) - arr[i]);

	}
	cout << sum << "\n";
	return 0;
}