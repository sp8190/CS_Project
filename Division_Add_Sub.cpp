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

bool detobi(int num, bool biArr[]) {	// 10진수를 2진수로 바꾸는 함수
										// biArr : 이진수로 바꾼 결과를 저장함. 레지스터 역할을 하는 배열이므로 길이가 32.
	if (num >= 0) {	// positive num
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

	bool Z = true;		// zero flag
	for (int i = 0; i < LENGTH; i++) {
		if (biArr[i] != 0)
			Z = false;
	}
	return Z;	// 리턴값 : 0인지 아닌지
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
	int oneIdx = LENGTH;	// 피젯수(Q)에서 1이 가장 먼저 나오는 인덱스. 이게 필요한 이유는 맨 아래쪽 주석에서 설명하겠음.
	bool A[LENGTH];
	if (signQ == 0) {	// Q < 0
		for (int i = 0; i < LENGTH; i++)
			A[i] = 0;
	}
	else {	// Q > 0
		for (int i = 0; i < LENGTH; i++)
			A[i] = 1;
		for (int i = 0; i < LENGTH; i++) {
			if (Q[i] == 1) {
				oneIdx = i;
				break;
			}
		}
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
		if (A[LENGTH - 1] == tempA[LENGTH - 1]) {	// caculation success
			Q[0] = 1;
			printAQ(A, Q);
			cout << "Q0 = 1" << endl;
		}
		else {
			if (Z && n - 1 <= oneIdx) {
				Q[0] = 1;
				printAQ(A, Q);
				cout << "Q0 = 1" << endl;
			}
			else {
				Q[0] = 0;
				for (int i = 0; i < LENGTH; i++)	// Array copy ( tempA -> A )
					A[i] = tempA[i];
				printAQ(A, Q);
				cout << "복원" << endl;
			}
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

void devisionZero() {	// 0으로 나눌 때
	cout << "몫 : NaN" << endl << "나머지 : NaN" << endl;
}


void flag(bool result[], bool Carry[]) { // 플래그 출력하는 함수
													// result[] -> 연산 후 결과값 배열
													// Carry[] -> 연산 하면서 나온 캐리 배열
	bool carry = 0; // C
	bool Sign = 0; // S
	bool Vflag = 0; // V
	bool Zero = 1; // Z

	// C 플래그 확인   Carry[] 마지막 확인
	carry = Carry[LENGTH - 1];

	// S 플래그 확인	result[] 마지막 부호비트
	if (result[LENGTH - 1] == 1) Sign = 1;

	// V 플래그 확인	Carry[] 마지막과 그 전의 값 XOR연산
	Vflag = Carry[LENGTH - 1] ^ Carry[LENGTH - 2];

	// Z 플래그 확인	result[] 모두 확인 후 0이 아닌 값이 존재하면 zero flag off
	for (int i = 0; i < LENGTH; i++) {
		if (result[i] != 0) {
			Zero = 0;
		}
	}

	/* 출력 */
	cout << "상태 레지스터 값" << endl;
	cout << "C S V Z" << endl;
	cout << carry << " " << Sign << " " << Vflag << " " << Zero << endl;

}


void add_sub(bool Q[], bool M[], bool Add0_Sub1) { // A ,B ,덧셈뺄셈 여부( 0이면 덧셈, 1이면 뺄셈)

	bool Carry = 0; // 이전 자리올림 위치
	bool Carry1[LENGTH] = { 0, }; // 자리올림
	bool add_result[LENGTH]; // 덧셈 결과를 저장

	if (Add0_Sub1 == 1) { /* 뺄셈의 경우 M을 비트 반전 후 1더하기(2의 보수 처리하기) */

		for (int i = 0; i < LENGTH; i++) {
			M[i] = M[i] ^ 1;	// 비트 반전
		}
		bool one[LENGTH] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
		biSum(M, one, M, 0);	// 비트 반전 후 1을 더함
	}


		for (int i = 0; i <= LENGTH - 1; i++) /* 32비트 반복 */
		{
			switch (Carry)
			{ /* Carry가 발생하지 않았을 때 */
				case 0:
				{
					if ((Q[i] == 1) && (M[i] == 1)) // A 1  B 1  c 0  S 0  C 1
					{
						add_result[i] = 0;
						Carry = 1; /* Carry발생 */
						Carry1[i] = 1;
					}
					else if ((Q[i] == 0) && (M[i] == 0)) // A 0  B 0  c 0  S 0  C 0
						add_result[i] = 0;
					else
						add_result[i] = 1;
					break;
				}

				/* Carry가 발생했을 때 */

				case 1:/* 캐리 발생 */
				{
					if ((Q[i] == 1) && (M[i] == 1)) { // A 1  B 1  c 1  S 1  C 1
						add_result[i] = 1;
						Carry1[i] = 1;
					}
					else if ((Q[i] == 0) && (M[i] == 0)) // A 0  B 0  c 1  S 1  C 0
					{
						add_result[i] = 1;
						Carry = 0;
					}
					else /* Carry발생 */ {
						add_result[i] = 0;
						Carry1[i] = 1;
					}
					break;
				}
			}
		}


		/* 출력 */
		if (Add0_Sub1 == 0)
			cout << "덧셈" << endl;
		else if (Add0_Sub1 == 1)
			cout << "뺄셈" << endl;

		cout << "A : "; // A 2진수 출력
		for (int i = LENGTH - 1; i >= 0; i--)
			cout << Q[i];
		cout << endl;

		cout << "B : "; // B 2진수 출력
		for (int i = LENGTH - 1; i >= 0; i--)
			cout << M[i];
		cout << endl;

		if (Add0_Sub1 == 0) {
		cout << "+ : "; // 덧셈 결과 출력
		for (int i = LENGTH - 1; i >= 0; i--)
			cout << add_result[i];
		cout << endl;
		}
		else if(Add0_Sub1 == 1) {
		cout << "- : "; // 뺼셈 결과 출력
		for (int i = LENGTH - 1; i >= 0; i--)
			cout << add_result[i];
		cout << endl;
		}

		cout << "C : "; // 캐리 출력
		for (int i = LENGTH - 1; i >= 0; i--)
			cout << Carry1[i];
		cout << endl;

		int quotient = bitode(add_result); // 2진수를 10진수로 바꾸는 함수,  2진수 결과를 int 10진수로 변환
		flag(add_result, Carry1); // 플래그 출력
		cout << "몫 : " << quotient << endl; // 몫 출력
	

}






int main() {
	bool Q[LENGTH] = { 0, };	// 피젯수 2진수
	bool M[LENGTH] = { 0, };	// 젯수 2진수
	int d, v;	// D : 피젯수 10진수, V : 젯수 10진수

	while (true) {

		cout << "프로그램 종료는 Ctrl + C 로 함을 전제로 하며" << endl;
		cout << "입력값에 대해 반복적으로 수행하도록 하였습니다." << endl;
		cout << endl;

		cout << "정수를 순서대로 입력해주세요." << endl;
		cout << "A : ";
		cin >> d;
		cout << "B : ";
		cin >> v;
		system("cls");

		cout << "A :" << d << endl;
		cout << "B :" << v << endl;
		cout << endl;


		detobi(d, Q);	// 입력받은 10진수를 2진수로 바꿈
		bool Z = detobi(v, M);	// v(=M)가 0인지 아닌지 검사

		/* 덧셈 */
		add_sub(Q, M, 0);
	

		/* 초기화 */
		cout << endl;
		for (int i = 0; i <= LENGTH - 1; i++) {
			Q[i] = 0;
			M[i] = 0;
		}
		detobi(d, Q);	// 입력받은 10진수를 2진수로 바꿈
		Z = detobi(v, M);	// v(=M)가 0인지 아닌지 검사


		/* 뺄셈 */
		add_sub(Q, M, 1);


		/* 초기화 */
		cout << endl;
		for (int i = 0; i <= LENGTH - 1; i++) {
			Q[i] = 0;
			M[i] = 0;
		}
		detobi(d, Q);	// 입력받은 10진수를 2진수로 바꿈
		Z = detobi(v, M);	// v(=M)가 0인지 아닌지 검사


		/* 나눗셈 */
		cout << "나눗셈" << endl;
		if (Z) {	// 0으로 나눌 때
			devisionZero();
			return 0;
		}
		devision(Q, M);

		/* 초기화 */
		cout << endl;
		for (int i = 0; i <= LENGTH - 1; i++) {
			Q[i] = 0;
			M[i] = 0;
		}
		detobi(d, Q);	// 입력받은 10진수를 2진수로 바꿈
		Z = detobi(v, M);	// v(=M)가 0인지 아닌지 검사

	}



	return 0;
}

/* oneIdx를 둔 이유
	: 나눗셈을 하며 <<를 하는 과정에서, 예를 들어 0101(=5)의 경우 두 번째 시프트가 끝났을 때 0...01이 A로 오게 되는데
	  이의 실제 값은 1*2*2 = 4로, 시프트가 모두 끝났어도 원래의 성분을 그대로 유지한다.
	  그러나, 1011(=-5)의 경우 두 번째 시프트가 끝나면 A에 1...110이 오게 되는데
	  이의 실제 값은 -2*2*2 = -8로, 시프트하기 전과 후의 성분이 달라진다.

	  이러한 원인은 음수에 대해 2의 보수를 취하는 과정에서 비트 반전을 한 후 1을 더하면서,
	  1의 올림수가 발생하지 않거나 1의 올림수가 전 비트에 영향을 미치지 않은 경우
	  올림수의 영향을 받지 않은 특정 비트까지 위에서 자르면 (여기서는 시프트를 통해 잘림)
	  실제로는 2의 보수를 취하였지만 이 부분은 1의 보수를 취한 것과 다름없게 된다. (비트 반전만 일어났다는 뜻)
	  따라서, 젯수와 피젯수의 시프트 된 부분을 더해서 0이 되어 연산 성공한 것처럼 보여도
	  사실은 젯수의 절댓값이 더 크므로 연산은 실패다. 그러므로 이런 경우는 더해서 A가 0이 되어도 연산 성공이라고 치지 않는다.

	  따라서 2의 보수를 취하는 과정에서 1을 더할 때 올림수가 어디까지 영향을 미쳤는지 찾고,
	  올림수가 영향을 미치지 않은 부분은 A가 0이 되었을 때도 연산 실패,
	  올림수가 영향을 미친 부분은 A가 0이 되었을 때 연산 성공 판정을 내리게 한다.
	  oneIdx는 올림수가 영향을 미친 비트의 자릿수 중 가장 높은 자릿수이다. */