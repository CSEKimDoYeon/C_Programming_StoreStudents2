#pragma once

#include "Common.h"
#define MAX_STUDENT_ID_LENGTH 9

typedef struct {
	char _studentID[MAX_STUDENT_ID_LENGTH + 1];
	int _score;
}Student;

Student* Student_new(char* givenStudentID, int givenScore);
void Student_delete(Student* _this);
char* Student_studentID(Student* _this);
int Student_score(Student* _this);
Boolean Student_studentIDIsValid(char* aStudentID);
Boolean Student_scoreIsValid(int aScore);