#include <iostream>

using namespace std;
int num1_arr[32], num2_arr[32], num3_arr[32] = { 0 }, A[32] = { 0 };
int num_1 = 0, num_2 = 0, checkzero = 0;
int Mc = 0, Mv = 0, Ms = 0;
int* returnarr(int nums,int size, int arr[]);
void returnA(int nums, int size);
void checkVM(int arr1[], int arr2[]);
void reverse(int arr[], int start, int end);
void shiftRight(int arr[], int d, int n);
void shiftLeft(int arr[], int d, int n);
void multiply();
int main() {

   
   cout << "첫번째 숫자(피승수)를 입력하세요" << endl;
   cin >> num_1;
   cout << "두번째 숫자(승수)를 입력하세요" << endl;
   cin >> num_2;


   
   returnarr(num_1,32,num1_arr);
   cout << "첫번째 숫자의 이진수는 ";
   for (int i = 0; i < 32; i++) {
      cout << num1_arr[i] << " ";
   }
   cout << endl;
   returnarr(num_2,32,num2_arr);
   cout << "두번째 숫자의 이진수는 ";
   for (int i = 0; i < 32; i++) {
      cout << num2_arr[i] <<" ";
   }
   cout << endl << endl;
   multiply();
   


   return 0;
}


int* returnarr(int nums,int size,int arr[]) {
   int aaa = size;
   int check=0;
   if (nums < 0) {
      check = 1;
   }
   int a;
   while (true) {
      if(nums<0)nums = nums - 2 * nums;
      if (nums == 0) {
         for (int i = 0; i < 32; i++) {
            arr[i] = 0;
         }
         break;
      }
      if (nums == 1) {
         arr[--size] = 1;
         break;
      }
      a = nums % 2;
      nums = nums / 2;
      arr[--size]=a;

   }
   if (check==1) {
      int temp;
      
      for (int i = aaa-1; i >=0; i--) {
         switch (arr[i]) {
         case 0:
            arr[i] = 1;
            if (i == aaa - 1) {
               arr[i] = 0;
               temp = 1;
            }
            if (temp == 1) {
               temp = 1;
               arr[i] = 0;
            }
            break;
         case 1:
            arr[i] = 0;
            if (i == aaa - 1) {
               arr[i] = 1;
               temp = 0;
            }
            if (temp == 1) {
               temp = 0;
               arr[i] = 1;
            }
            break;
         }
         
      }
   }
   return arr;
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
      if (nums == 0) {
         for (int i = 0; i < 32; i++) {
            A[i] = 0;
         }
         checkzero = 1;
         break;
      }
      if (nums == 1) {
         A[--size] = 1;
         break;
      }
      
      a = nums % 2;
      nums = nums / 2;
      A[--size] = a;
      
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
         cout <<count<<"번째 계산 : 10이므로 A-Q연산 진행 ("<<a<<" - "<<num_1<<")" << endl;
         
         returnarr(a, 32,num3_arr);
         
         checkVM(num3_arr, num1_arr);
         a = a - num_1;         
         returnA(a, 32);
         
      }
      else if (num2_arr[31] == 0 && Q0 == 1) {
         cout << count << "번째 계산 : 01이므로 A+Q연산 진행 (" << a << " + " << num_1 << ")" << endl;
         
         returnarr(a, 32,num3_arr);
         checkVM(num3_arr, num1_arr);
         a = a + num_1;
         returnA(a, 32);      
         
      }
      cout << endl << count << "번째 계산 shift후" << endl;
      int temp1 = A[0];
      int temp2 = A[31];
         shiftRight(A, 1, 32);
         A[0] = temp1;
         Q0 = num2_arr[31];
         shiftRight(num2_arr, 1, 32);
         num2_arr[0] = temp2;
         cout <<"shift전 A값 : "<< a << " - > ";
         for (int i = 0; i < 32; i++) {
            cout << A[i] << " ";
         }
         cout << "ㅣ";
         for (int i = 0; i < 32; i++) {
            cout << num2_arr[i] << " ";
         }
         cout <<"l"<< Q0;
         cout << endl << endl;
      
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
   long long temps = 1;
   long long answer = 0;
   for (int i = 0; i < 64; i++) {
      if (ansarr[i] == 1) {
         for (int k = 0; k < 63 - i; k++) {
            temps = temps * 2;
            
         }
         answer = answer + temps;
         temps = 1;
      }
   }
   if (answer < 0) {
      Ms = 1;
   }
   
   cout << endl << num_1 << " x " << num_2 << " = " << answer << "입니다" << endl;
   cout << "<상태 레지스터 값>" << endl << "c  s  v  z" << endl << Mc << "  " << Ms << "  " << Mv << "  " << checkzero << "  " << endl;
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


void checkVM(int arr1[], int arr2[]) {
   int temp = 0;
   int temps[2] = { 0 };
   int ACE[32] = { 0 };
   
   int t;
   if (arr2[0] == 1) {
      for (int i = 31; i >= 0; i--) {
         switch (arr2[i]) {
         case 0:
            arr2[i] = 1;
            if (i == 31) {
               arr2[i] = 0;
               t = 1;
            }
            if (t == 1) {
               t = 1;
               arr2[i] = 0;
            }
            break;
         case 1:
            arr2[i] = 0;
            if (i == 31) {
               arr2[i] = 1;
               t = 0;
            }
            if (t == 1) {
               t = 0;
               arr2[i] = 1;
            }
            break;

         }
      }
   }
   for (int i = 31; i > 1; i--) {
      if (arr1[i] == 1 && arr2[i] == 1) {
         if (temp == 0) {
            ACE[i] = 0;
            temp = 1;
         }
         else {
            ACE[i] = 1;
            temp = 1;
         }
      }
      else if ((arr1[i] == 1 && arr2[i] == 0) || (arr1[i] == 0 && arr2[i] == 1)) {
         if (temp == 0) {
            ACE[i] = 1;
            temp = 0;
         }
         else {
            ACE[i] = 0;
            temp = 1;
         }
      }
      else if (arr1[i] == 0 && arr2[i] == 0) {
         if (temp == 0) {
            ACE[i] = 0;
            temp = 0;
         }
         else {
            ACE[i] = 1;
            temp = 0;
         }
      }
   }
   for (int i = 1; i > -1; i--) {
      if (arr1[i] == 1 && arr2[i] == 1) {
         if (temp == 0) {
            ACE[i] = 0;
            temp = 1;
            temps[i] = 1;
         }
         else {
            ACE[i] = 1;
            temp = 1;
            temps[i] = 1;
         }
      }
      else if ((arr1[i] == 1 && arr2[i] == 0) || (arr1[i] == 0 && arr2[i] == 1)) {
         if (temp == 0) {
            ACE[i] = 1;
            temp = 0;
            temps[i] = 0;
         }
         else {
            ACE[i] = 0;
            temp = 1;
            temps[i] = 1;
         }
      }
      else if (arr1[i] == 0 && arr2[i] == 0) {
         if (temp == 0) {
            ACE[i] = 0;
            temp = 0;
            temps[i] = 0;
         }
         else {
            ACE[i] = 1;
            temp = 0;
            temps[i] = 0;
         }
      }
   }
   if (temps[0] != temps[1]) {
      Mv = 1;
   }
}
