//#include<stdio.h>
///*
//	2016-02-18
//	문제1(Qu08-01.c)
//	1이상 100미만의 정수중에서 7의배수와 9의배수를 출력하는 프로그램을 작성하라.
//	단, 7의 배수이면서 동시에 9의 배수인 정수는 한번만 출력해야 한다.
//*/
//int main(void)
//{
//	for (int i = 1; i < 100; i++)
//	{
//		// 7의 배수 or 9의 배수 or (7의 배수 and 9의 배수)의 조건에 부합하면 출력
//		if (i % 7 == 0 || i % 9 == 0 || (i % 7 == 0 && i % 9 == 0) )
//			printf("%d \n", i);
//	}
//
//	return 0;
//}