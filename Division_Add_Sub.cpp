#include <iostream>
using namespace std;
#define LENGTH 32

/*  ����! 
	�� ���α׷�(������ ��Ʈ)���� �����ϴ� bool Ÿ�� �迭��
	�迭�� ù��° �ε����� ���������� 32bit° �ڸ��� ����.
	ex : +3 ===> 00...011 ������ { 1, 1, 0, ... ,0 } ���� ��Ÿ��.
	����� �迭�� �� �ε������� �������� �����. ==> 00...011 */

bool FA(bool A, bool B, bool C[], int i) {	// ������� �ϳ�. A, B = ���ϴ� ��, C = Carry, i : ���� Carry�� ��ġ
	C[i + 1] = A & B | (A ^ B) & C[i];	// Carry �߻�
	return A ^ B ^ C[i];	// S return
}

bool biSum(bool biArr1[], bool biArr2[], bool Sum[], bool S) {	// ���� ��(��)��� : �� 2������ ǥ���� ���ڳ��� ���ϴ�(����) ������ �ϴ� �Լ�
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

bool detobi(int num, bool biArr[]) {	// 10������ 2������ �ٲٴ� �Լ�
										// biArr : �������� �ٲ� ����� ������. �������� ������ �ϴ� �迭�̹Ƿ� ���̰� 32.
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
			biArr[i] = biArr[i] ^ 1;	// ��Ʈ ����
			num /= 2;
		}
		bool one[LENGTH] = { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };	// 1 ----> ó���� �򰥷��� {0, 0, ..., 1 } �̶�� �Ԥ� �����ؾ߰ڴ�
		biSum(biArr, one, biArr, 0);	// ��Ʈ ���� �� 1�� ����
	}

	bool Z = true;		// zero flag
	for (int i = 0; i < LENGTH; i++) {
		if (biArr[i] != 0)
			Z = false;
	}
	return Z;	// ���ϰ� : 0���� �ƴ���
}

int bitode(bool biArr[]) {	// 2������ 10������ �ٲٴ� �Լ�
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
	// biArr2[0]�� �������ִ� ������ �ʿ����?
}

void printAQ(bool A[], bool Q[]) {	// A�� Q���������� ���� ����ϴ� �Լ�
	for (int i = LENGTH - 1; i >= 0; i--)
		cout << A[i];
	cout << "\t";
	for (int i = LENGTH - 1; i >= 0; i--)
		cout << Q[i];
	cout << "\t";
}

////// *** ������ ���� *** //////
void devision(bool Q[], bool M[]) {
	bool signQ = Q[LENGTH - 1];		// Q�� ��ȣ --> A�� �� ����, ���߿� ���� ��ȣ ����
	int oneIdx = LENGTH;	// ������(Q)���� 1�� ���� ���� ������ �ε���. �̰� �ʿ��� ������ �� �Ʒ��� �ּ����� �����ϰ���.
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
	int n = LENGTH;		// Q�� ��Ʈ �ڸ� ���� ǥ��
	bool tempA[LENGTH];		// ���� �� A���� �����ϴ� �迭

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
		cout << "�̵�" << endl;

		for (int i = 0; i < LENGTH; i++)	// Array copy ( A -> tempA )
			tempA[i] = A[i];

		// Cycle 2. A-M or A+M
		bool Z = false;		//	zero flag
		if (A[LENGTH - 1] == M[LENGTH - 1]) {	// A�� M�� ��ȣ ����?
			Z = biSum(A, M, A, 1);	// A <- A-M
			printAQ(A, Q);
			cout << "����" << endl;
		}
		else {
			Z = biSum(A, M, A, 0);	// A <- A+M
			printAQ(A, Q);
			cout << "����" << endl;
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
				cout << "����" << endl;
			}
		}

		n -= 1;
		cout << "-----------------------------------------------------------------------------------------" << endl;
	}

	// ��� ������ �Ǵ�
	if (signQ != M[LENGTH - 1]) {	// ������ �������� ��ȣ �ٸ�
		for (int i = 0; i < LENGTH; i++)	// ���� ���ؾ��ϳ�? �ƴ� �ٷ� ��ȣ��?
			Q[i] = Q[i] ^ 1;	// ��Ʈ ����
		bool one[LENGTH] = { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };	// 1
		biSum(Q, one, Q, 0);	// ��Ʈ ���� �� 1�� ����
	}
	int quotient = bitode(Q);
	cout << "�� : ";
	for (int i = LENGTH - 1; i >= 0; i--)
		cout << Q[i];
	cout << "(2) ---> " << quotient << endl;
	int remainder = bitode(A);
	cout << "������ : ";
	for (int i = LENGTH - 1; i >= 0; i--)
		cout << A[i];
	cout << "(2) ---> " << remainder << endl;
}

void devisionZero() {	// 0���� ���� ��
	cout << "�� : NaN" << endl << "������ : NaN" << endl;
}


void flag(bool result[], bool Carry[]) { // �÷��� ����ϴ� �Լ�
													// result[] -> ���� �� ����� �迭
													// Carry[] -> ���� �ϸ鼭 ���� ĳ�� �迭
	bool carry = 0; // C
	bool Sign = 0; // S
	bool Vflag = 0; // V
	bool Zero = 1; // Z

	// C �÷��� Ȯ��   Carry[] ������ Ȯ��
	carry = Carry[LENGTH - 1];

	// S �÷��� Ȯ��	result[] ������ ��ȣ��Ʈ
	if (result[LENGTH - 1] == 1) Sign = 1;

	// V �÷��� Ȯ��	Carry[] �������� �� ���� �� XOR����
	Vflag = Carry[LENGTH - 1] ^ Carry[LENGTH - 2];

	// Z �÷��� Ȯ��	result[] ��� Ȯ�� �� 0�� �ƴ� ���� �����ϸ� zero flag off
	for (int i = 0; i < LENGTH; i++) {
		if (result[i] != 0) {
			Zero = 0;
		}
	}

	/* ��� */
	cout << "���� �������� ��" << endl;
	cout << "C S V Z" << endl;
	cout << carry << " " << Sign << " " << Vflag << " " << Zero << endl;

}


void add_sub(bool Q[], bool M[], bool Add0_Sub1) { // A ,B ,�������� ����( 0�̸� ����, 1�̸� ����)

	bool Carry = 0; // ���� �ڸ��ø� ��ġ
	bool Carry1[LENGTH] = { 0, }; // �ڸ��ø�
	bool add_result[LENGTH]; // ���� ����� ����

	if (Add0_Sub1 == 1) { /* ������ ��� M�� ��Ʈ ���� �� 1���ϱ�(2�� ���� ó���ϱ�) */

		for (int i = 0; i < LENGTH; i++) {
			M[i] = M[i] ^ 1;	// ��Ʈ ����
		}
		bool one[LENGTH] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
		biSum(M, one, M, 0);	// ��Ʈ ���� �� 1�� ����
	}


		for (int i = 0; i <= LENGTH - 1; i++) /* 32��Ʈ �ݺ� */
		{
			switch (Carry)
			{ /* Carry�� �߻����� �ʾ��� �� */
				case 0:
				{
					if ((Q[i] == 1) && (M[i] == 1)) // A 1  B 1  c 0  S 0  C 1
					{
						add_result[i] = 0;
						Carry = 1; /* Carry�߻� */
						Carry1[i] = 1;
					}
					else if ((Q[i] == 0) && (M[i] == 0)) // A 0  B 0  c 0  S 0  C 0
						add_result[i] = 0;
					else
						add_result[i] = 1;
					break;
				}

				/* Carry�� �߻����� �� */

				case 1:/* ĳ�� �߻� */
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
					else /* Carry�߻� */ {
						add_result[i] = 0;
						Carry1[i] = 1;
					}
					break;
				}
			}
		}


		/* ��� */
		if (Add0_Sub1 == 0)
			cout << "����" << endl;
		else if (Add0_Sub1 == 1)
			cout << "����" << endl;

		cout << "A : "; // A 2���� ���
		for (int i = LENGTH - 1; i >= 0; i--)
			cout << Q[i];
		cout << endl;

		cout << "B : "; // B 2���� ���
		for (int i = LENGTH - 1; i >= 0; i--)
			cout << M[i];
		cout << endl;

		if (Add0_Sub1 == 0) {
		cout << "+ : "; // ���� ��� ���
		for (int i = LENGTH - 1; i >= 0; i--)
			cout << add_result[i];
		cout << endl;
		}
		else if(Add0_Sub1 == 1) {
		cout << "- : "; // �E�� ��� ���
		for (int i = LENGTH - 1; i >= 0; i--)
			cout << add_result[i];
		cout << endl;
		}

		cout << "C : "; // ĳ�� ���
		for (int i = LENGTH - 1; i >= 0; i--)
			cout << Carry1[i];
		cout << endl;

		int quotient = bitode(add_result); // 2������ 10������ �ٲٴ� �Լ�,  2���� ����� int 10������ ��ȯ
		flag(add_result, Carry1); // �÷��� ���
		cout << "�� : " << quotient << endl; // �� ���
	

}






int main() {
	bool Q[LENGTH] = { 0, };	// ������ 2����
	bool M[LENGTH] = { 0, };	// ���� 2����
	int d, v;	// D : ������ 10����, V : ���� 10����

	while (true) {

		cout << "���α׷� ����� Ctrl + C �� ���� ������ �ϸ�" << endl;
		cout << "�Է°��� ���� �ݺ������� �����ϵ��� �Ͽ����ϴ�." << endl;
		cout << endl;

		cout << "������ ������� �Է����ּ���." << endl;
		cout << "A : ";
		cin >> d;
		cout << "B : ";
		cin >> v;
		system("cls");

		cout << "A :" << d << endl;
		cout << "B :" << v << endl;
		cout << endl;


		detobi(d, Q);	// �Է¹��� 10������ 2������ �ٲ�
		bool Z = detobi(v, M);	// v(=M)�� 0���� �ƴ��� �˻�

		/* ���� */
		add_sub(Q, M, 0);
	

		/* �ʱ�ȭ */
		cout << endl;
		for (int i = 0; i <= LENGTH - 1; i++) {
			Q[i] = 0;
			M[i] = 0;
		}
		detobi(d, Q);	// �Է¹��� 10������ 2������ �ٲ�
		Z = detobi(v, M);	// v(=M)�� 0���� �ƴ��� �˻�


		/* ���� */
		add_sub(Q, M, 1);


		/* �ʱ�ȭ */
		cout << endl;
		for (int i = 0; i <= LENGTH - 1; i++) {
			Q[i] = 0;
			M[i] = 0;
		}
		detobi(d, Q);	// �Է¹��� 10������ 2������ �ٲ�
		Z = detobi(v, M);	// v(=M)�� 0���� �ƴ��� �˻�


		/* ������ */
		cout << "������" << endl;
		if (Z) {	// 0���� ���� ��
			devisionZero();
			return 0;
		}
		devision(Q, M);

		/* �ʱ�ȭ */
		cout << endl;
		for (int i = 0; i <= LENGTH - 1; i++) {
			Q[i] = 0;
			M[i] = 0;
		}
		detobi(d, Q);	// �Է¹��� 10������ 2������ �ٲ�
		Z = detobi(v, M);	// v(=M)�� 0���� �ƴ��� �˻�

	}



	return 0;
}

/* oneIdx�� �� ����
	: �������� �ϸ� <<�� �ϴ� ��������, ���� ��� 0101(=5)�� ��� �� ��° ����Ʈ�� ������ �� 0...01�� A�� ���� �Ǵµ�
	  ���� ���� ���� 1*2*2 = 4��, ����Ʈ�� ��� ����� ������ ������ �״�� �����Ѵ�.
	  �׷���, 1011(=-5)�� ��� �� ��° ����Ʈ�� ������ A�� 1...110�� ���� �Ǵµ�
	  ���� ���� ���� -2*2*2 = -8��, ����Ʈ�ϱ� ���� ���� ������ �޶�����.

	  �̷��� ������ ������ ���� 2�� ������ ���ϴ� �������� ��Ʈ ������ �� �� 1�� ���ϸ鼭,
	  1�� �ø����� �߻����� �ʰų� 1�� �ø����� �� ��Ʈ�� ������ ��ġ�� ���� ���
	  �ø����� ������ ���� ���� Ư�� ��Ʈ���� ������ �ڸ��� (���⼭�� ����Ʈ�� ���� �߸�)
	  �����δ� 2�� ������ ���Ͽ����� �� �κ��� 1�� ������ ���� �Ͱ� �ٸ����� �ȴ�. (��Ʈ ������ �Ͼ�ٴ� ��)
	  ����, ������ �������� ����Ʈ �� �κ��� ���ؼ� 0�� �Ǿ� ���� ������ ��ó�� ������
	  ����� ������ ������ �� ũ�Ƿ� ������ ���д�. �׷��Ƿ� �̷� ���� ���ؼ� A�� 0�� �Ǿ ���� �����̶�� ġ�� �ʴ´�.

	  ���� 2�� ������ ���ϴ� �������� 1�� ���� �� �ø����� ������ ������ ���ƴ��� ã��,
	  �ø����� ������ ��ġ�� ���� �κ��� A�� 0�� �Ǿ��� ���� ���� ����,
	  �ø����� ������ ��ģ �κ��� A�� 0�� �Ǿ��� �� ���� ���� ������ ������ �Ѵ�.
	  oneIdx�� �ø����� ������ ��ģ ��Ʈ�� �ڸ��� �� ���� ���� �ڸ����̴�. */