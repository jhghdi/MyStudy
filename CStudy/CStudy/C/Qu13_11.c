//#include<stdio.h>
///*
//	2016-02-23
//	����1(Qu13-11.c)
//	���̰�5�� int�� �迭 arr�� �����ϰ� �̸� 1,2,3,4,5�� �ʱ�ȭ�� ����,
//	�� �迭�� ù��° ��Ҹ� ����Ű�� ������ ���� ptr�� �����Ѵ�.
//	�� ���� ������ ���� ptr�� ����� ���� ������Ű�� ������ ����(��������)��
//	������� �迭��ҿ� �����ϸ鼭 ��� �迭����� ���� 2�� ������Ű��
//	���������� ������ �̷������� Ȯ���ϴ� ���α׷��� �ۼ��Ͻÿ�.
//	-������ :
//	�ʱⰪ : 1 2 3 4 5
//	�迭�� ��Ҹ� 2���������Ѽ� ����
//	����� : 3 4 5 6 7
//*/
//
//void main()
//{
//	// �迭 �� ������ �ʱ�ȭ
//	int arr[] = { 1,2,3,4,5 };
//	int * ptr = arr;
//
//	printf("�ʱⰪ : ");
//
//	for (int i = 0; i < 5; i++)
//		printf("%d ", arr[i]);
//
//	printf("\n����� : ");
//
//	for (int i = 0; i < 5; i++)
//	{ 
//		// ���� �����Ͽ� ������Ų��.
//		ptr[i] += 2;
//		printf("%d ", arr[i]);
//	}
//
//	printf("\n");
//}