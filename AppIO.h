#include "Common.h"

Boolean AppIO_in_doesContinueToInputNextStudent();
char getcharDirectlyFromKeyboard(void);
int AppIO_in_score();
void AppIO_out(char* aString);
void AppIO_out_averageScore(float anAverageScore);
void AppIO_out_numberOfStudentsAboveAverage(int aNumber);
void AppIO_out_maxScore(int aMaxScore);
void AppIO_out_minScore(int aMinScore);
void AppIO_out_gradeCountFor(char aGrade, int aCount);
void AppIO_out_studentInfo(char aStudentID, int aScore, char aGrade);
void AppIO_out_msg_invalidStudentID(char* aStudentID, int maxLength);
void AppIO_in_studentID(char* aStudentID);
