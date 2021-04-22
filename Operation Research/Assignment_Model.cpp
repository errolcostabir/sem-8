#include<iostream>
#include<conio.h>
#include<vector>
#include<algorithm>
using namespace std;

void compute(vector<vector<bool> >& assigned1, vector<bool>& row_complete1, vector<bool>& col_complete1, vector<vector<int> > mat) {
	int check_row_zeros1[4] = { 0,0,0,0 };
	int check_col_zeros1[4] = { 0,0,0,0 };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (mat[i][j] == 0) {
				check_row_zeros1[i]++;
				check_col_zeros1[j]++;
			}
		}
	}
	int runs = 4;
	while (runs > 0) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (check_row_zeros1[i] == 1 && mat[i][j] == 0 && !col_complete1[j]) {
					col_complete1[j] = true;
					check_col_zeros1[j] = 0;
					assigned1[i][j] = true;
					for (int k = 0; k < 4; k++) {
						if (mat[k][j] == 0) {
							check_row_zeros1[k]--;
						}
					}
				}
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (check_col_zeros1[j] == 1 && mat[i][j] == 0 && !row_complete1[i]) {
					row_complete1[i] = true;
					check_row_zeros1[i] = 0;
					assigned1[i][j] = true;
					for (int k = 0; k < 4; k++) {
						if (mat[i][k] == 0) {
							check_col_zeros1[i]--;
						}
					}
				}
			}
		}
		runs--;
	}
}

int main() {
	vector<vector<int> > mat(4, vector<int>(4));
	vector<vector<int> > temp_mat(4, vector<int>(4));
	//input matrix
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cin >> mat[i][j];
			temp_mat[i][j] = mat[i][j];
		}
	}
	//minimum of row
	for (int i = 0; i < 4; i++) {
		int mini = mat[i][0];
		for (int j = 0; j < 4; j++) {
			if (mat[i][j] < mini) {
				mini = mat[i][j];
			}
		}
		for (int j = 0; j < 4; j++) {
			mat[i][j] = mat[i][j] - mini;
		}
	}
	//minimum of column
	for (int i = 0; i < 4; i++) {
		int mini = mat[0][i];
		for (int j = 0; j < 4; j++) {
			if (mat[j][i] < mini) {
				mini = mat[j][i];
			}
		}
		for (int j = 0; j < 4; j++) {
			mat[j][i] = mat[j][i] - mini;
		}
	}

	vector<vector<bool> > assigned(4, vector<bool>(4,false));
	vector<bool> row_complete(4, false);
	vector<bool> col_complete(4, false);

	compute(assigned, row_complete, col_complete, mat);

	int min = 10000;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (!row_complete[i] && !col_complete[j]) {
				if (mat[i][j] < min) {
					min = mat[i][j];
				}
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (!row_complete[i] && !col_complete[j]) {
				mat[i][j] = mat[i][j] - min;
			}

			if (row_complete[i] && col_complete[j]) {
				mat[i][j] = mat[i][j] + min;
			}
		}
	}

	vector<vector<bool> > assigned1(4, vector<bool>(4,false));
	vector<bool> row_complete1(4, false);
	vector<bool> col_complete1(4, false);

	compute(assigned1, row_complete1, col_complete1, mat);
	int minimum_cost = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (assigned1[i][j] == true) {
				cout << "Worker " << i + 1 << " is assigned job " << j + 1 << endl;
				minimum_cost += temp_mat[i][j];
			}
		}
		cout << endl;
	}
	cout << "MINIMUM COST: " << minimum_cost;
}
