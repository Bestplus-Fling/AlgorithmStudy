using namespace std;
#include <iostream>
#include <vector>
#include <algorithm>
int length, treeNum, time;
int dy[8] = { 0, 0, 1, -1, -1, -1, 1, 1 };
int dx[8] = { 1, -1, 0, 0, -1, 1, -1, 1 };

struct treedata
{
	int y, x;
};
int main() {
	cin >> length >> treeNum >> time;
	vector<vector<vector<int>>> arr(length, vector<vector<int>>(length));
	vector<vector<int>> nutrient(length, vector<int>(length, 5));
	vector<vector<int>> addNutrient(length, vector<int>(length));
	for (int i = 0; i < length; ++i) {
		for (int j = 0; j < length; ++j) {
			cin >> addNutrient[i][j];
		}
	}
	int y, x, age;
	for (int i = 0; i < treeNum; ++i) {
		cin >> y >> x >> age;
		arr[y - 1][x - 1].push_back(age);
	}
	for (int year = 0; year < time; ++year) {
		// �� + ����.
		vector<treedata> maketree; // ������ ���� ������ ����
		for (int i = 0; i < length; ++i) {
			for (int j = 0; j < length; ++j) {
				vector<int> temp; // �ӽ� �����.
				vector<int>& cur = arr[i][j];
				sort(cur.begin(), cur.end());
				int size = cur.size();
				if (size == 0) continue;
				int die = 0;
				for (int k = 0; k < size; ++k) {		// i, j ���ִ°� ���� �̾ƺ�. (�켱���� ť�� �����ź���)
					int tree = cur[k];
					if (tree > nutrient[i][j]) {		// ����� �����ϸ�, ������ �װ� ����� ��.
						die += tree / 2;
					}
					else {								// ����� ����ϸ�, ����� ���ҽ�Ű�� �ӽ� �迭�� ����.
						nutrient[i][j] -= tree;
						tree++;
						if (tree % 5 == 0) {			// 5�� ����� ������ ���� �����Ϳ� ����
							maketree.push_back({ i, j });
						}
						temp.push_back(tree);

					}
				}
				size = temp.size();
				swap(cur, temp);	// �ٽ� i, j �� �������


				nutrient[i][j] += die;
			}
		}
		// ����
		int size = maketree.size();
		int tempy, tempx;
		for (auto& makeTree : maketree) {
			for (int j = 0; j < 8; ++j) {
				tempy = makeTree.y + dy[j]; tempx = makeTree.x + dx[j];
				if (tempy < 0 || tempy >= length || tempx < 0 || tempx >= length) continue;
				arr[tempy][tempx].push_back(1);
			}
		}
		// �ܿ�
		// ����� ������.
		for (int i = 0; i < length; ++i) {
			for (int j = 0; j < length; ++j) {
				nutrient[i][j] += addNutrient[i][j];
			}
		}
	}
	int result = 0;
	// ��� ����
	for (int i = 0; i < length; ++i) {
		for (int j = 0; j < length; ++j) {
			result += arr[i][j].size();
		}
	}

	cout << result << '\n';
	return 0;
}