#include <iostream>
using namespace std;
#define LENGTH 32

/*  주의! 
	이 프로그램(나눗셈 파트)에서 등장하는 bool 타입 배열은
	배열의 첫번째 인덱스가 레지스터의 32bit째 자리를 뜻함.
	ex : +3 ===> 00...011 이지만 { 1, 1, 0, ... ,0 } 으로 나타냄.
	출력은 배열의 끝 인덱스부터 역순으로 출력함. ==> 00...011 */

bool FA(bool A, bool B, bool C[], int i) {	// 전가산기 하나. A, B = 더하는 수, C = Carry, i : 현재 Carry의 위치
	C[i + 1] = A & B | (A ^ B) & C[i];	// Carry 발생
	return A ^ B ^ C[i];	// S return
}

bool biSum(bool biArr1[], bool biArr2[], bool Sum[], bool S) {	// 병렬 가(감)산기 : 두 2진수로 표현된 숫자끼리 더하는(빼는) 연산을 하는 함수
																// biArr1 + biArr2 = Sum, S : sign flag (0: +, 1: -)
	bool Carry[LENGTH + 1] = { 0, };
	Carry[0] = S;
	bool Z = false;	// Zero flag
	for (int i = 0; i < LENGTH; i++) {
		Sum[i] = FA(biArr1[i], biArr2[i] ^ S, Carry, i);
		Z = Z | Sum[i];
	}
	Z = !Z;
	return Z;
}

void detobi(int num, bool biArr[]) {	// 10진수를 2진수로 바꾸는 함수
										// biArr : 이진수로 바꾼 결과를 저장함. 레지스터 역할을 하는 배열이므로 길이가 32.
	if (num >= 0) {	// 0 or positive num
		for (int i = 0; i < LENGTH - 1 && num != 0; i++) {
			biArr[i] = num % 2;
			num /= 2;
		}
	}
	else {	// negative num
		num = -num;
		biArr[LENGTH - 1] = 1;	// MSB == 1
		for (int i = 0; i < LENGTH - 1; i++) {
			biArr[i] = num % 2;
			biArr[i] = biArr[i] ^ 1;	// 비트 반전
			num /= 2;
		}
		bool one[LENGTH] = { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };	// 1 ----> 처음에 헷갈려서 {0, 0, ..., 1 } 이라고 함ㅠ 주의해야겠당
		biSum(biArr, one, biArr, 0);	// 비트 반전 후 1을 더함
	}
}

int bitode(bool biArr[]) {	// 2진수를 10진수로 바꾸는 함수
	int num = 0;
	int bi = 1;
	if (biArr[LENGTH - 1] == 0) {	// 0 or positive num
		for (int i = 0; i < LENGTH - 1; i++) {
			if (biArr[i] == 1)
				num += bi;
			bi *= 2;
		}
	}
	else {	// negative num
		for (int i = 0; i < LENGTH - 1; i++) {
			if (biArr[i] == 1)
				num += bi;
			bi *= 2;
		}
		num -= bi;
	}
	return num;
}

void Lshift(bool biArr1[], bool biArr2[]) {	// 1 Left Shift
	for (int i = LENGTH - 1; i > 0; i--) {
		biArr1[i] = biArr1[i - 1];
	}
	biArr1[0] = biArr2[LENGTH - 1];
	for (int i = LENGTH - 1; i > 0; i--) {
		biArr2[i] = biArr2[i - 1];
	}
	// biArr2[0]를 설정해주는 과정은 필요없나?
}

void printAQ(bool A[], bool Q[]) {	// A와 Q레지스터의 값을 출력하는 함수
	for (int i = LENGTH - 1; i >= 0; i--)
		cout << A[i];
	cout << "\t";
	for (int i = LENGTH - 1; i >= 0; i--)
		cout << Q[i];
	cout << "\t";
}

////// *** 나눗셈 연산 *** //////
void devision(bool Q[], bool M[]) {
	bool signQ = Q[LENGTH - 1];		// Q의 부호 --> A의 값 결정, 나중에 몫의 부호 결정
	bool A[LENGTH];
	if (signQ == 0) {
		for (int i = 0; i < LENGTH; i++)
			A[i] = 0;
	}
	else {
		for (int i = 0; i < LENGTH; i++)
			A[i] = 1;
	}
	int n = LENGTH;		// Q의 비트 자리 수를 표시
	bool tempA[LENGTH];		// 연산 전 A값을 저장하는 배열

	// Print initial state
	cout << "A                                 \tQ                                \tM" << endl;
	cout << "=========================================================================================" << endl;
	printAQ(A, Q);
	for (int i = LENGTH - 1; i >= 0; i--)
		cout << M[i];
	cout << endl;

	while (n != 0) {
		// Cycle 1. Left shift
		Lshift(A, Q);
		printAQ(A, Q);
		cout << "이동" << endl;

		for (int i = 0; i < LENGTH; i++)	// Array copy ( A -> tempA )
			tempA[i] = A[i];

		// Cycle 2. A-M or A+M
		bool Z = false;		//	zero flag
		if (A[LENGTH - 1] == M[LENGTH - 1]) {	// A와 M의 부호 동일?
			Z = biSum(A, M, A, 1);	// A <- A-M
			printAQ(A, Q);
			cout << "뺄셈" << endl;
		}
		else {
			Z = biSum(A, M, A, 0);	// A <- A+M
			printAQ(A, Q);
			cout << "덧셈" << endl;
		}

		// Cycle 3. Caculation determination
		if (A[LENGTH - 1] == tempA[LENGTH - 1] || n == 1 && Z) {	// caculation success or A == 0 (-> 반복문을 마지막으로 돌 때만 적용)
			Q[0] = 1;												// A == 0 일 경우를 반복문을 마지막으로 돌 때만 적용시킨 이유
			printAQ(A, Q);											//	-----> -5 / 2 같은 예외를 방지하기 위해
			cout << "Q0 = 1" << endl;
		}
		else {
			Q[0] = 0;
			for (int i = 0; i < LENGTH; i++)	// Array copy ( tempA -> A )
				A[i] = tempA[i];
			printAQ(A, Q);
			cout << "복원" << endl;
		}

		n -= 1;
		cout << "-----------------------------------------------------------------------------------------" << endl;
	}

	// 몫과 나머지 판단
	if (signQ != M[LENGTH - 1]) {	// 제수와 피젯수의 부호 다름
		for (int i = 0; i < LENGTH; i++)	// 보수 구해야하나? 아님 바로 부호만?
			Q[i] = Q[i] ^ 1;	// 비트 반전
		bool one[LENGTH] = { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };	// 1
		biSum(Q, one, Q, 0);	// 비트 반전 후 1을 더함
	}
	int quotient = bitode(Q);
	cout << "몫 : ";
	for (int i = LENGTH - 1; i >= 0; i--)
		cout << Q[i];
	cout << "(2) ---> " << quotient << endl;
	int remainder = bitode(A);
	cout << "나머지 : ";
	for (int i = LENGTH - 1; i >= 0; i--)
		cout << A[i];
	cout << "(2) ---> " << remainder << endl;
}

int main() {
	bool Q[LENGTH] = { 0, };	// 피젯수 2진수
	bool M[LENGTH] = { 0, };	// 젯수 2진수
	int d, v;	// D : 피젯수 10진수, V : 젯수 10진수

	cout << "A ÷ B" << endl << "A : ";
	cin >> d;
	cout << "B : ";
	cin >> v;
	detobi(d, Q);	// 입력받은 10진수를 2진수로 바꿈
	detobi(v, M);
	
	devision(Q, M);

	return 0;
}