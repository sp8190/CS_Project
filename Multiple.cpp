#include <iostream>

using namespace std;
int num1_arr[32], num2_arr[32], A[32] = { 0 };
int num_1 = 0, num_2 = 0;

void return1(int nums,int size);
void return2(int nums,int size);
void returnA(int nums, int size);
void reverse(int arr[], int start, int end);
void shiftRight(int arr[], int d, int n);
void shiftLeft(int arr[], int d, int n);
void multiply();
void division();
int main() {

	
	cout << "첫번째 숫자(피승수)를 입력하세요" << endl;
	cin >> num_1;
	cout << "두번째 숫자(승수)를 입력하세요" << endl;
	cin >> num_2;


	
	return1(num_1,32);
	cout << "첫번째 숫자의 이진수는 ";
	for (int i = 0; i < 32; i++) {
		cout << num1_arr[i] << " ";
	}
	cout << endl;
	return2(num_2,32);
	cout << "두번째 숫자의 이진수는 ";
	for (int i = 0; i < 32; i++) {
		cout << num2_arr[i] <<" ";
	}
	cout << endl;
	multiply();
	


	return 0;
}


void return1(int nums, int size) {
	int aaa = size;
	int check=0;
	if (nums < 0) {
		check = 1;
	}
	int a;
	while (true) {
		if(nums<0)nums = nums - 2 * nums;
		a = nums % 2;
		nums = nums / 2;
		num1_arr[--size] = a;
		if (nums == 1) {
			num1_arr[--size] = 1;
			break;
		}

	}

	if (check==1) {
		int temp;
		
		for (int i = aaa - 1; i >= 0; i--) {
			switch (num1_arr[i]) {
			case 0:
				num1_arr[i] = 1;
				if (i == aaa - 1) {
					num1_arr[i] = 0;
					temp = 1;
					
				}
				if (temp == 1) {
					temp = 1;
					num1_arr[i] = 0;
				}
				break;
			case 1:
				num1_arr[i] = 0;
				if (i == aaa - 1) {
					num1_arr[i] = 1;
					temp = 0;
					
				}
				if (temp == 1) {
					temp = 0;
					num1_arr[i] = 1;
				}
				break;
			}
		}
	}
}


void return2(int nums,int size) {
	int aaa = size;
	int check=0;
	if (nums < 0) {
		check = 1;
	}
	int a;
	while (true) {
		if(nums<0)nums = nums - 2 * nums;
		
		a = nums % 2;
		nums = nums / 2;
		num2_arr[--size]=a;

		if (nums == 1) {
			num2_arr[--size] = 1;
			break;
		}
	}
	if (check==1) {
		int temp;
		
		for (int i = aaa-1; i >=0; i--) {
			switch (num2_arr[i]) {
			case 0:
				num2_arr[i] = 1;
				if (i == aaa - 1) {
					num2_arr[i] = 0;
					temp = 1;
				}
				if (temp == 1) {
					temp = 1;
					num2_arr[i] = 0;
				}
				break;
			case 1:
				num2_arr[i] = 0;
				if (i == aaa - 1) {
					num2_arr[i] = 1;
					temp = 0;
				}
				if (temp == 1) {
					temp = 0;
					num2_arr[i] = 1;
				}
				break;
			}
			
		}
	}	
}

void returnA(int nums, int size) {
	int aaa = size;
	int check = 0;
	if (nums < 0) {
		check = 1;
	}
	int a;
		
		for (int i = 0; i < 32; i++)  A[i] = 0;
	while (true) {
		
		if (nums < 0)nums = nums - 2 * nums;
		
		a = nums % 2;
		nums = nums / 2;
		A[--size] = a;
		
		if (nums <= 1) {
			A[--size] = 1;
			break;
		}
	}

	
	if (check == 1) {
		int temp;
		for (int i = aaa - 1; i >= 0; i--) {
			switch (A[i]) {
			case 0:
				A[i] = 1;
				if (i == aaa - 1) {
					A[i] = 0;
					temp = 1;
				}
				if (temp == 1) {
					temp = 1;
					A[i] = 0;
				}
				break;
			case 1:
				A[i] = 0;
				if (i == aaa - 1) {
					A[i] = 1;
					temp = 0;
				}
				if (temp == 1) {
					temp = 0;
					A[i] = 1;
				}
				break;
				
			}

		}
	}
}

void multiply() {
	int a = 0;
	int Q0 = 0;
	int A2[32] = { 0 };
	int count = 0;
	while (count<32) {
		count++;
		for (int i = 0; i < 32; i++) {
			A2[i] = A[i];
		}
		if (A2[0] == 0) {
			int temps = 1;
				a = 0;
			for (int i = 0; i < 32; i++) {
				if (A2[i] == 1) {
					for (int k = 0; k < 31 - i; k++) {
						temps = temps * 2;
					}
					a = a + temps;
					temps = 1;
				}
			}
			
		}
		else {
			int temp;

			for (int i = 32 - 1; i >= 0; i--) {
				switch (A2[i]) {
				case 0:
					A2[i] = 1;
					if (i == 32 - 1) {
						A2[i] = 0;
						temp = 1;
					}
					if (temp == 1) {
						temp = 1;
						A2[i] = 0;
					}
					break;
				case 1:
					A2[i] = 0;
					if (i == 32 - 1) {
						A2[i] = 1;
						temp = 0;
					}
					if (temp == 1) {
						temp = 0;
						A2[i] = 1;
					}
					break;
				}
			}
			int temps = 1;
			a= 0;
			for (int i = 0; i < 32; i++) {
				if (A2[i] == 1) {
					for (int k = 0; k < 31 - i; k++) {
						temps = temps * 2;
					}
					a = a + temps;
					temps = 1;
				}
			}
			
			a = a - 2 * a;
			
		}


		if (num2_arr[31] == 1 && Q0 == 0) {		
			cout << "10이므로 -연산 진행 ("<<a<<" - "<<num_1<<")" << endl;
			a = a - num_1;			
			returnA(a, 32);
			
		}
		else if (num2_arr[31] == 0 && Q0 == 1) {
			cout << "01이므로 +연산 진행 (" << a << " + " << num_1 << ")" << endl;
			a = a + num_1;
			returnA(a, 32);			
		}
		cout << "shift전" << endl;
		cout << a << " :: ";
		for (int i = 0; i < 32; i++) {
			cout << A[i] << " ";
		}
		cout << "ㅣ";
		for (int i = 0; i < 32; i++) {
			cout << num2_arr[i] << " ";
		}
		cout << "l" << Q0;
		cout << endl << "shift후" << endl;
		int temp1 = A[0];
		int temp2 = A[31];
			shiftRight(A, 1, 32);
			A[0] = temp1;
			Q0 = num2_arr[31];
			shiftRight(num2_arr, 1, 32);
			num2_arr[0] = temp2;
			cout << a << " :: ";
			for (int i = 0; i < 32; i++) {
				cout << A[i] << " ";
			}
			cout << "ㅣ";
			for (int i = 0; i < 32; i++) {
				cout << num2_arr[i] << " ";
			}
			cout <<"l"<< Q0;
			cout << endl;
		
	}
	
	
	int ansarr[64];
	for(int i = 0; i < 32; i++) {
		ansarr[i] = A[i];
	}
	for (int i = 32; i < 64; i++) {
		ansarr[i] = num2_arr[i - 32];
	}
	for (int i = 0; i < 64; i++) {
		cout << ansarr[i] << " ";
	}
	cout << endl;
	int temps = 1, answer = 0;
	for (int i = 0; i < 64; i++) {
		if (ansarr[i] == 1) {
			for (int k = 0; k < 63 - i; k++) {
				temps = temps * 2;
				
			}
			answer = answer + temps;
			cout << answer<<endl;
			temps = 1;
		}
	}
	cout <<endl<< answer;
}

void division() {

}

void shiftRight(int arr[], int d, int n) {
	reverse(arr, 0, n - d);
	reverse(arr, n - d, n);
	reverse(arr, 0, n);
}

void shiftLeft(int arr[], int d, int n) {
	reverse(arr, 0, d);
	reverse(arr, d, n);
	reverse(arr, 0, n);
}
void reverse(int arr[], int start, int end) {
    int temp;
    end = end - 1;
    while (start < end) {
        temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}