#include<iostream>
#include<vector>
using namespace std;

class Simplex {

private:

	int variables, slack_variables;
	vector< vector<float> > mat1;
	vector< vector<float> > mat2;

public:

	void setVariables(int variables,int slack_variables) {
		this->variables = variables;
		this->slack_variables = slack_variables;
	}

	void setMatrix() {
		for (int i = 0; i < (slack_variables + 1); i++) {
			vector<float> temp_arr;
			for (int j = 0; j < (slack_variables + variables + 2); j++) {
				float temp;
				cin >> temp;
				temp_arr.push_back(temp);
			}
			mat1.push_back(temp_arr);
		}
	}

	void computeAns() {
		bool flag = false;
		vector<int> basic_variable(slack_variables, 0);
		while (!flag) {
			mat2 = mat1;
			float entering_variable = 1000.0; int  entering_variable_index;
			float leaving_variable = 1000.0; int leaving_variable_index;

			for (int i = 0; i < (slack_variables + variables + 2); i++) {
				if (mat1[0][i] < 0 && mat1[0][i] < entering_variable) {
					entering_variable = mat1[0][i];
					entering_variable_index = i;
				}
			}

			if (entering_variable > 0) {
				flag = true;
				break;
			}

			for (int i = 1; i < (slack_variables + 1); i++) {
				float temp = mat1[i][slack_variables + variables + 1];
				float ans = temp / mat1[i][entering_variable_index];
				if (ans > 0 && ans < leaving_variable) {
					leaving_variable = ans;
					leaving_variable_index = i;
				}
			}

			if (basic_variable[leaving_variable_index] == 0) {
				basic_variable[leaving_variable_index] = entering_variable_index;
			}

			float pivot_element = mat1[leaving_variable_index][entering_variable_index];

			for (int i = 0; i < (slack_variables + variables + 2); i++) {
				mat1[leaving_variable_index][i] = mat2[leaving_variable_index][i] / pivot_element;
			}

			int i = 0;

			while (i < (slack_variables + 1)) {
				if (i == leaving_variable_index) {
					i++;
				}
				else {
					for (int j = 0; j < (slack_variables + variables + 2); j++) {
						mat1[i][j] = mat2[i][j] - (mat2[i][entering_variable_index] * mat1[leaving_variable_index][j]);
					}
					i++;
				}
			}
		}

		vector<float> outputs(variables, 0);

		cout << "Z: " << mat1[0][slack_variables + variables + 1] << endl;
		for (int i = 0; i < slack_variables; i++) {
			if (basic_variable[i] != 0) {
				outputs[basic_variable[i] - 1] = mat1[i][slack_variables + variables + 1];
			}
		}

		for (int i = 0; i < variables; i++) {
			cout << "X" << i + 1 << ": " << outputs[i]<<endl;
		}
	}
};

int main() {
	Simplex s;
	int variables, slack_variables;
	cout << "Enter the number of variables and slack variables" << endl;
	cin >> variables >> slack_variables;
	s.setVariables(variables, slack_variables);
	cout << "Enter the Equations" << endl;
	s.setMatrix();
	cout << endl;
	cout << "The solution is: " << endl;
	s.computeAns();
}

/*
Output:

Enter the number of variables and slack variables
3 3
Enter the Equations
1 -3 -2 -5 0 0 0 0
0 1 2 1 1 0 0 430
0 3 0 2 0 1 0 460
0 1 4 0 0 0 1 420

The solution is:
Z: 1350
X1: 0
X2: 100
X3: 230
*/