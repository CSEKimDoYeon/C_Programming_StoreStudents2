#include "Common.h"
#include "Ban.h"
#include "GradeCounter.h"
#include "AppController.h"
#include "AppIO.h"
#include "Student.h"


#define MAX_NUMBER_OF_STUDENTS 100 // �л��� �ִ� ��

AppController* AppController_new(void)
// ���ο� AppController ��ü�� �����Ѵ�. 
{
	AppController* _this = (AppController*)malloc(sizeof(AppController));
	// �� ��ü�� �޸𸮸� �Ҵ����ش�.
	_this->_ban = Ban_newWithCapacity(MAX_NUMBER_OF_STUDENTS);
	//AppController ��ü�� Ban ��ü�� �־��ش�.
	return _this;
}

void AppController_delete(AppController* _this)
// AppController ��ü�� �޸𸮿��� �����Ѵ�.
{
	Ban_delete(_this->_ban);
	// AppController ������ Ban ��ü�� �������ش�.
	free(_this);
	// ����ִ� �޸� ������ free���ش�.
}

void AppContorller_run(AppController* _this)
{
	AppIO_out("<<< ���� ó���� �����մϴ� >>>\n");
	// (1) ������ �Է� �޴´�
	Boolean inputAndStoreWasSuccessful;
	inputAndStoreWasSuccessful = AppController_inputAndStoreStudents(_this);
	// ����ڷκ��� ������ �Է¹޴´�, ���������� ������ True.
	if (inputAndStoreWasSuccessful) {
		if (Ban_isEmpty(_this->_ban)) {
			AppIO_out("\n[����] �л� ������ ���� �Էµ��� �ʾҽ��ϴ�.\n");
		}
		else {
			// (2) ��հ� ��� �̻��� �л���, �ְ���, �������� ����Ѵ�. 
			AppController_showStatistics(_this);
			// (3) ���������� ����, �׸��� �Է� ���� �л� ������ ����Ѵ�. 
			Ban_sortStudentsByScore(_this->_ban);
			AppController_showStudentsSortedByScore(_this);
		}
	}
	else {
		AppIO_out("[����] ������ ���������� ������� �ʾҽ��ϴ�.");
	}
	AppIO_out("\n<<< ���� ó���� �����մϴ� >>>\n");
}


Boolean AppController_inputIsValid(AppController* _this, char* aStudentID, int aScore)
{ // �Է¹��� �������� ��ȿ���� �˻��ϴ� �Լ�.
	Boolean inputIsValid = TRUE;
	if (!Student_studentIDIsValid(aStudentID)) {
		AppIO_out_msg_invalidStudentID(aStudentID, MAX_STUDENT_ID_LENGTH);
		inputIsValid = FALSE;
	}
	if (!Student_scoreIsValid(aScore)) {
		//AppIO_out_msg_invalidScore(aScore);
		printf("������ �߸� �Է��Ͽ����ϴ�.");
		inputIsValid = FALSE;
	}
	return inputIsValid;
}
Boolean AppController_inputAndStoreStudents(AppController* _this)
{ // �л����� ������ �Է��ϴ� �޼ҵ�.
	int score;
	Boolean storingAStudentWasSuccessful = TRUE;
	char studentID[10];
	Student* student;
	while (storingAStudentWasSuccessful &&
		AppIO_in_doesContinueToInputNextStudent())
	{
		AppIO_in_studentID(studentID);
		score = AppIO_in_score();
		if (AppController_inputIsValid(_this, studentID, score)) {
			student = Student_new(studentID, score);
			storingAStudentWasSuccessful = Ban_add(_this->_ban, student);
		}
	}
	return storingAStudentWasSuccessful;
}

void AppController_showStatistics(AppController* _this)
{
	//������ ó���� ����� ȭ�鿡 ����Ѵ�.
	// �� ������ ���� ó���� ����� Ban ��ü�� ������ �ִ�
	AppIO_out_averageScore(Ban_averageScore(_this->_ban));
	AppIO_out_numberOfStudentsAboveAverage(Ban_numberOfStudentsAboveAverage(_this->_ban));
	AppIO_out_maxScore(Ban_maxScore(_this->_ban));
	AppIO_out_minScore(Ban_minScore(_this->_ban));
	// ���� �� �л����� Ban ��ü�κ��� GradeCounter ��ü ���·� ��´�
	GradeCounter* gradeCounter = Ban_countGrades(_this->_ban);
	AppIO_out_gradeCountFor('A', GradeCounter_numberOfA(gradeCounter));
	AppIO_out_gradeCountFor('B', GradeCounter_numberOfB(gradeCounter));
	AppIO_out_gradeCountFor('C', GradeCounter_numberOfC(gradeCounter));
	AppIO_out_gradeCountFor('D', GradeCounter_numberOfD(gradeCounter));
	AppIO_out_gradeCountFor('F', GradeCounter_numberOfF(gradeCounter));
	GradeCounter_delete(gradeCounter); // �� �̻� �ʿ� �����Ƿ� �Ҹ��Ų��
}

void AppController_showStudentsSortedByScore(AppController* _this)
{
	Student* student;
	//AppIO_out_titleForSortedStudentList();
	printf("\n�л����� ������ ����Դϴ�.\n\n");

	for (int i = 0; i < Ban_size(_this->_ban); i++) {
		student = Ban_elementAt(_this->_ban, i);
		int score = Student_score(student);

		//printf("zzzzz\n");
		AppIO_out_studentInfo(Student_studentID(student),score,	Ban_scoreToGrade(score));
	}
}