//#include<stdio.h>
///*
//	2016-02-23
//	배열과 포인터 프로그램
//*/
//
//int main()
//{
//	int arr[3] = { 0, 1, 2 };
//	// 배열의 이름을 통해서 포인터 접근 및 연산이 가능
//	// 배열의 이름이 가리키는곳은 첫 번째 요소의 주소(arr[0]의 주소와 동일)
//	printf("배열의 이름 : %p \n", arr);
//
//	// 각 요소에 대하여 주소값을 출력
//	printf("첫 번째 요소: %p \n", &arr[0]);
//	printf("두 번째 요소: %p \n", &arr[1]);
//	printf("세 번째 요소: %p \n", &arr[2]);
//
//	// 아래의 문장은 컴파일 에러를 일으킨다.
//	// arr = & arr[i]; 
//	
//	return 0;
//}