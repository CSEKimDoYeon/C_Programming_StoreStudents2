#include "Common.h"
#include "AppIO.h"

#include <stdio.h>
#include <conio.h>

Boolean AppIO_in_doesContinueToInputNextStudent()
{
	//����ڷκ��� ���� �Է� ���θ� �Է¹޴´�.
	printf("\n? ������ �Է��Ϸ��� 'Y'�� , �Է��� �����Ϸ��� �ٸ� �ƹ� Ű�� ġ�ÿ�: ");
	char answer = getcharDirectlyFromKeyboard();
	// ������ ������ ��Keyboard ���� ���� ���� �Է� �ޱ⡱ ������ �����Ͻÿ�.
	if (answer == 'Y' || answer == 'y')
		return TRUE;
	else
		printf("\n�Է��� �����մϴ�.\n");
	return FALSE;
}

char getcharDirectlyFromKeyboard(void)
{ /*���� ���͸� ������ ����� �ƴ� Ű���忡��
  ������ ���� �ٷ� �ν��ϵ��� �ϴ� �Լ�*/
	char charFromKeyboard;
	charFromKeyboard = _getch();
	return charFromKeyboard;
}
int AppIO_in_score()
{
	// �Է¹��� ������ ��ȯ�ϴ� �Լ�.
	int score;
	printf("\n- ������ �Է��Ͻÿ�: ");
	scanf("%d", &score);
	return score;
}

void AppIO_out(char* aString) {
	// �޽��� ��� �Լ�.
	printf(aString);
}
void AppIO_out_averageScore(float anAverageScore) {
	// ��������� �Ҽ��� ù �� ° �ڸ����� �ݿø��Ѵ�.
	printf("\n��������� %.1f �Դϴ�.\n", anAverageScore);
}
/*��Ÿ ����Լ� ���*/
void AppIO_out_numberOfStudentsAboveAverage(int aNumber) {
	printf("��� �̻��� �л��� ��� %d�� �Դϴ�.\n", aNumber);
}
void AppIO_out_maxScore(int aMaxScore) {
	printf("�ְ����� %d �� �Դϴ�.\n", aMaxScore);
}
void AppIO_out_minScore(int aMinScore) {
	printf("�������� %d �� �Դϴ�.\n\n", aMinScore);
}
void AppIO_out_gradeCountFor(char aGrade, int aCount) {
	printf("%c ������ �л��� %d�� �Դϴ�.\n", aGrade, aCount);
}
void AppIO_out_studentInfo(char* aStudentID, int aScore, char aGrade) {
	printf("�й� : %s	���� : %d	���� : %c\n",aStudentID, aScore, aGrade);
}
/*��Ÿ ����Լ� ���*/

void AppIO_out_msg_invalidStudentID(char* aStudentID, int maxLength)
{ // �й��� ���̸� �ʰ����� ��� ����ϴ� �޼ҵ�
	printf("[����] �й� %s �� ���̰� �ʹ� ��ϴ�. �ִ� %d �Դϴ�.\n",
		aStudentID, maxLength);
}
void AppIO_in_studentID(char* aStudentID)
{ // �л��� �й��� �Է¹޴´�.
	printf("\n- �й��� �Է��Ͻÿ�: ");
	scanf("%s", aStudentID);
}