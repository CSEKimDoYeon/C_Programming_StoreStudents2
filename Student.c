#include "Common.h"
#include "Student.h"
#include <string.h>

Student* Student_new(char* givenStudentID, int givenScore)
{
	Student* _this = (Student*)malloc(sizeof(Student));
	
	strcpy(_this->_studentID, givenStudentID);
	_this->_score = givenScore;
	return _this;
}
void Student_delete(Student* _this)
{
	free(_this);
}
char* Student_studentID(Student* _this)
{
	char* copiedStudentID = NewVector(char, 10);
	strcpy(copiedStudentID, _this->_studentID);
	return copiedStudentID;
}
int Student_score(Student* _this)
{
	return _this->_score;
}

Boolean Student_studentIDIsValid(char* aStudentID)
{
	int length = 0;
	while (*aStudentID !='\0') {
		length++;
		aStudentID++;
	}
	return (length <= MAX_STUDENT_ID_LENGTH);
	// �й� (���ڿ�)�� ���̰� �ִ� ������ 9 ���� ª�ų� ���ƾ� �Ѵ�.
}
Boolean Student_scoreIsValid(int aScore)
{
	return (aScore >= 0 && aScore <= 100);
	// ������ 0�� 100 ���� �̾�� �Ѵ�.
}