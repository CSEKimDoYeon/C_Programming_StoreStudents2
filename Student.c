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
	// 학번 (문자열)의 길이가 최대 길이인 9 보다 짧거나 같아야 한다.
}
Boolean Student_scoreIsValid(int aScore)
{
	return (aScore >= 0 && aScore <= 100);
	// 점수가 0과 100 사이 이어야 한다.
}