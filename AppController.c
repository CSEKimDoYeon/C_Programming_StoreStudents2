#include "Common.h"
#include "Ban.h"
#include "GradeCounter.h"
#include "AppController.h"
#include "AppIO.h"
#include "Student.h"


#define MAX_NUMBER_OF_STUDENTS 100 // 학생의 최대 수

AppController* AppController_new(void)
// 새로운 AppController 객체를 생성한다. 
{
	AppController* _this = (AppController*)malloc(sizeof(AppController));
	// 새 객체에 메모리를 할당해준다.
	_this->_ban = Ban_newWithCapacity(MAX_NUMBER_OF_STUDENTS);
	//AppController 객체에 Ban 객체를 넣어준다.
	return _this;
}

void AppController_delete(AppController* _this)
// AppController 객체를 메모리에서 삭제한다.
{
	Ban_delete(_this->_ban);
	// AppController 내부의 Ban 객체를 삭제해준다.
	free(_this);
	// 비어있는 메모리 영역을 free해준다.
}

void AppContorller_run(AppController* _this)
{
	AppIO_out("<<< 성적 처리를 시작합니다 >>>\n");
	// (1) 성적을 입력 받는다
	Boolean inputAndStoreWasSuccessful;
	inputAndStoreWasSuccessful = AppController_inputAndStoreStudents(_this);
	// 사용자로부터 성적을 입력받는다, 정상적으로 받으면 True.
	if (inputAndStoreWasSuccessful) {
		if (Ban_isEmpty(_this->_ban)) {
			AppIO_out("\n[오류] 학생 정보가 전혀 입력되지 않았습니다.\n");
		}
		else {
			// (2) 평균과 평균 이상인 학생수, 최고점, 최저점을 출력한다. 
			AppController_showStatistics(_this);
			// (3) 성적순으로 정렬, 그리고 입력 받은 학생 정보를 출력한다. 
			Ban_sortStudentsByScore(_this->_ban);
			AppController_showStudentsSortedByScore(_this);
		}
	}
	else {
		AppIO_out("[오류] 성적이 정상적으로 저장되지 않았습니다.");
	}
	AppIO_out("\n<<< 성적 처리를 종료합니다 >>>\n");
}


Boolean AppController_inputIsValid(AppController* _this, char* aStudentID, int aScore)
{ // 입력받은 정보들이 유효한지 검사하는 함수.
	Boolean inputIsValid = TRUE;
	if (!Student_studentIDIsValid(aStudentID)) {
		AppIO_out_msg_invalidStudentID(aStudentID, MAX_STUDENT_ID_LENGTH);
		inputIsValid = FALSE;
	}
	if (!Student_scoreIsValid(aScore)) {
		//AppIO_out_msg_invalidScore(aScore);
		printf("점수를 잘못 입력하였습니다.");
		inputIsValid = FALSE;
	}
	return inputIsValid;
}
Boolean AppController_inputAndStoreStudents(AppController* _this)
{ // 학생들의 정보를 입력하는 메소드.
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
	//성적을 처리한 결과를 화면에 출력한다.
	// 이 시점에 성적 처리된 결과를 Ban 객체가 가지고 있다
	AppIO_out_averageScore(Ban_averageScore(_this->_ban));
	AppIO_out_numberOfStudentsAboveAverage(Ban_numberOfStudentsAboveAverage(_this->_ban));
	AppIO_out_maxScore(Ban_maxScore(_this->_ban));
	AppIO_out_minScore(Ban_minScore(_this->_ban));
	// 학점 별 학생수는 Ban 객체로부터 GradeCounter 객체 형태로 얻는다
	GradeCounter* gradeCounter = Ban_countGrades(_this->_ban);
	AppIO_out_gradeCountFor('A', GradeCounter_numberOfA(gradeCounter));
	AppIO_out_gradeCountFor('B', GradeCounter_numberOfB(gradeCounter));
	AppIO_out_gradeCountFor('C', GradeCounter_numberOfC(gradeCounter));
	AppIO_out_gradeCountFor('D', GradeCounter_numberOfD(gradeCounter));
	AppIO_out_gradeCountFor('F', GradeCounter_numberOfF(gradeCounter));
	GradeCounter_delete(gradeCounter); // 더 이상 필요 없으므로 소멸시킨다
}

void AppController_showStudentsSortedByScore(AppController* _this)
{
	Student* student;
	//AppIO_out_titleForSortedStudentList();
	printf("\n학생들의 성적순 목록입니다.\n\n");

	for (int i = 0; i < Ban_size(_this->_ban); i++) {
		student = Ban_elementAt(_this->_ban, i);
		int score = Student_score(student);

		//printf("zzzzz\n");
		AppIO_out_studentInfo(Student_studentID(student),score,	Ban_scoreToGrade(score));
	}
}