#include <iostream>
using namespace std;
#include <vector>
#include <deque>

void drop(deque<vector<int>>& conveyor, int down) {
	conveyor[down][0] = 0;
}

int main() {
	int length, limit; cin >> length >> limit;
	deque<vector<int>> conveyor;
	int input_temp;
	for (int i = 0; i < length * 2; i++) {
		cin >> input_temp;
		conveyor.push_back({ 0, input_temp });
	}
	int up = 0, down = length - 1, is_robot = 0, durability = 1, cnt = 0;
	int sycle = 0;
	vector<int> temp;
	// ������ 0�� ���� �̻��� �Ǹ� ����
	while (cnt < limit)
	{
		sycle++;
		// �����̾� ��ĭ �̵�
		temp = conveyor.back(); conveyor.pop_back();
		conveyor.push_front(temp);
		// �κ��� �����°� �����ϸ�
		if (conveyor[down][is_robot]) drop(conveyor, down);

		//�κ� ��ĭ�� �̵�, ������ 1�� ����
		for (int i = length - 2; i >= 0; i--) {
			if (conveyor[i][is_robot] && !conveyor[i + 1][is_robot] && conveyor[i + 1][durability] >= 1) {
				conveyor[i][is_robot] = 0;
				conveyor[i + 1][is_robot] = 1;
				conveyor[i + 1][durability]--;
				if (conveyor[i + 1][durability] == 0) cnt++;
			}
		}
		// �κ��� �����°� �����ϸ�
		if (conveyor[down][is_robot]) drop(conveyor, down);
		// �κ� �ø���
		if (conveyor[up][durability] >= 1) {
			conveyor[up][is_robot] = 1;
			conveyor[up][durability]--;
			if (conveyor[up][durability] == 0) cnt++;
		}
		
	}
	cout << sycle << '\n';
	return 0;
}