#include<iostream>
#include<algorithm>
#include<math.h>
#include<cstring>
#include<fstream>
#define MAX 987654321
using namespace std;
int map[10][10];
bool checked[10];
int ans = MAX, node, pos;
//�÷��̵� �ͼ� �˰����� �̿��Ͽ� �̸� �ּҰ��� ������Ʈ ��Ų��.
//���� DFS ����Ͽ� �༺ 1���� 2���� �ִܰŸ��� ���Ѵ�.

void DFS(int idx, int cnt, int dis)
{
	//ans�� �ּڰ��̸� return
	if (ans < dis)
		return;
	//�༺Ž�簹���� �Է¹���node�� ������ ans�� �ּڰ��� ������Ʈ�ϰ� return
	if (cnt == node)
	{
		ans = min(ans, dis);
		return;
	}
	//�Է¹��� �༺�� ������ŭ ���鼭 �༺�� �ε���, Ž���� �༺��, �ɸ��� �ð��� DFS�� ������.
	//checked �湮���� Ȯ��(�̹� �÷��̵� �ͼ� ����Ͽ� �ִܰŸ� ��������� ������)
	for (int i = 0; i < node; i++)
	{
		if (checked[i])
			continue;
		checked[i] = true;
		DFS(i, cnt + 1, dis + map[idx][i]);
		checked[i] = false;
	}
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	//üũ�迭 �ʱ�ȭ
	memset(checked, false, sizeof(checked));
	cin >> node >> pos;

	for (int i = 0; i < node; i++)
	{
		for (int j = 0; j < node; j++)
		{
			cin >> map[i][j];
		}
	}
	//�߻�Ǵ� �༺ ��ġ �湮üũ
	checked[pos] = true;
	//�÷��̵� �ͼ��� �ִܰŸ� �̸� �������ش�.
	for (int k = 0; k < node; k++)
	{
		for (int i = 0; i < node; i++)
		{
			for (int j = 0; j < node; j++)
			{
				if (map[i][k] + map[k][j] < map[i][j])
					map[i][j] = map[i][k] + map[k][j];
			}
		}
	}
	//DFS���� �߻�Ǵ� �༺��ġ, �༺Ž�簹��, �ɸ��� �ð� �Ű������� �Ѱ��ش�.
	DFS(pos, 1, 0);
	cout << ans << "\n";
	return 0;
}