#include "Common.h"
#include "GradeCounter.h"
#include "Ban.h"
#include "Student.h"

Boolean Ban_scoreIsValid(int aScore) {
	// ������ 0~100 �������� �˻��Ѵ�.
	return (aScore >= 0 && aScore <= 100);
}

char Ban_scoreToGrade(int aScore) {
	// ������ ���� ������ return�Ѵ� (Char)
	if (aScore >= 90) {
		return 'A';
	}
	else if (aScore >= 80) {
		return 'B';
	}
	else if (aScore >= 70) {
		return 'C';
	}
	else if (aScore >= 60) {
		return 'D';
	}
	else
	{
		return 'F';
	}
}

Ban* Ban_new(void)
{
	// ���ο� Ban ��ü�� �޸𸮿� �Ҵ��Ѵ�.
	Ban* _this = (Ban*)malloc(sizeof(Ban));
	_this->_capacity = DEFAULT_CAPACITY; // �ִ� �л� �� ����
	_this->_size = 0; // ��ü�� ������ ������ �л����� 0 ��
	_this->_elements = NewVector(Student*, _this->_capacity);
	// ������ ������ �迭 ���� (NewVector)
	return _this;
}

Ban* Ban_newWithCapacity(int givenCapacity)
{
	// givenCapacity�� ���� Ban ��ü�� �����Ѵ�.
	Ban* _this = (Ban*)malloc(sizeof(Ban));
	_this->_capacity = givenCapacity; // �ִ� �л� �� ����
	_this->_size = 0;// ��ü�� ������ ������ �л����� 0 ��
	_this->_elements = NewVector(Student*, _this->_capacity); // ������ ������ �迭
	return _this;
}

void Ban_delete(Ban* _this)
{ // Ban ��ü�� �����Ѵ�. elements ���� �����ؼ� free�����ش�.
	free(_this->_elements);
	free(_this);
}

int Ban_capacity(Ban* _this)
{
	// Ban�� Capacity�� return�Ѵ�.
	return (_this->_capacity);
}
int Ban_size(Ban* _this)
{
	// Ban�� size�� return�Ѵ�.
	return (_this->_size);
}

Boolean Ban_isEmpty(Ban* _this)
{
	// Ban �� ����ִ��� �˻��Ѵ�.
	return (_this->_size == 0);
}

Boolean Ban_isFull(Ban* _this)
{
	// Ban �� ���ִ��� �˻��Ѵ�.
	return (_this->_size >= _this->_capacity);
}

Boolean Ban_add(Ban* _this, Student* aStudent)
{
	// ������ �迭�� ����
	if (Ban_isFull(_this)) {
		return FALSE; // ���� ������ ����
	}
	else {
		// �迭�� �� ������ ��ġ�� �ִ´�.
		_this->_elements[_this->_size] = aStudent;
		_this->_size++;
		return TRUE;
	}
}

Student* Ban_elementAt(Ban* _this, int anOrder)
{
	if (anOrder >= _this->_size) {
		// �־��� ��ġ�� ���Ұ� �������� �ʴ´�
		return NULL; // NULL�� �������� ������ ǥ���ϱ�� �Ѵ�
	}
	else {
		// ���Ұ� ���������� �����Ѵ�
		return (_this->_elements[anOrder]);
	}
}

void Ban_sortStudentsByScore(Ban* _this)
{
	Ban_quickSort(_this);
}

void Ban_quickSort(Ban* _this) // Quick Sort�� ���� ����� �Լ�
{
	int size = Ban_size(_this);
	// ������ �����ʹ� _this->_elements[0] ���� _this->_elements[size-1] ���� �̴�
	// �� ������ �����Ѵ�
	if (size >= 2) { // ������ 2 �̻��̸�
					 // �ּҰ��� ��ġ�� ã�´�
		int minPosition = 0;
		for (int i = 1; i < size; i++) {
			if (Student_score(_this->_elements[i]) <
				Student_score(_this->_elements[minPosition]))
			{
				minPosition = i;
			}
		}
		// �ּҰ��� ���� ������ �� ������ �ű��.
		SWAP(Student*, _this->_elements[minPosition], _this->_elements[size - 1]);
		// ������ �����Ѵ�
		Ban_quickSortRecursively(_this, 0, size - 2);
	}
}

void Ban_quickSortRecursively(Ban* _this, int left, int right)
{ // �л����� ������ QuickSort ����Լ��� �����Ѵ�.
	int mid;
	if (left < right) {
		mid = Ban_partition(_this, left, right);
		Ban_quickSortRecursively(_this, left, mid - 1);
		Ban_quickSortRecursively(_this, mid + 1, right);
	}
}

int Ban_partition(Ban* _this, int left, int right)
{ // ���� �������� ������.
	{
		int pivot = left;
		int pivotScore = Student_score(_this->_elements[pivot]);
		int toLeft = right + 1;
		int toRight = left;
		do {
			do { toRight++; } while (Student_score(_this->_elements[toRight]) > pivotScore);
			do { toLeft--; } while (Student_score(_this->_elements[toLeft]) < pivotScore);
			if (toRight < toLeft) {
				SWAP(Student*, _this->_elements[toRight], _this->_elements[toLeft]);
			}
		} while (toRight < toLeft);
		SWAP(Student*, _this->_elements[pivot], _this->_elements[toLeft]);
		return toLeft;
	}
}

int Ban_sumOfScoresRecursively(Ban* _this, int left, int right)
{
	// ���� �հ踦 ����Ͽ� return ������ �����ش�.
	// ũ�⸦ (N-1)�� ���̴� ����Լ��� �ۼ��Ͻÿ�.
	if (left > right) {
		return 0;
	}
	else {
		int score = Student_score(_this->_elements[left]);
		return (score + Ban_sumOfScoresRecursively(_this, left + 1, right));
	}
} 

int Ban_maxScoreRecursively(Ban* _this, int left, int right)
{
	int maxOfLeftPart; // ��Ʈ�� ���� ��ġ.
	int maxOfRightPart; // ��Ʈ�� ������ ��ġ.
	int mid; // ��� ��ġ
	if (left == right) { // �¿찡 ���ٸ�
		return _this->_elements[left]->_score; // �ش� ���� �ִ밪. ��ü�� ���ھ� ��ȯ
	}
	else {
		mid = (left + right) / 2;
		// ��, �츣�� ������ ������ mid�� �����Ѵ�.
		maxOfLeftPart = Ban_maxScoreRecursively(_this, left, mid);
		// ���� ���� 1�� ��Ʈ���� �ִ밪�� ���ϰ�
		maxOfRightPart = Ban_maxScoreRecursively(_this, mid + 1, right);
		// ������ ���� 2�� ��Ʈ���� �ִ밪�� ���ؼ�
		if (maxOfLeftPart >= maxOfRightPart)
			// �� �� �� ū ���� return �Ѵ�.
			return maxOfLeftPart;
		else
			return maxOfRightPart;
	}
} 
int Ban_minScoreRecursively(Ban* _this, int left, int right)
{
	int minOfSubPart;
	if (left == right) // �¿찡 ���ٸ�
		return _this->_elements[left]->_score;
	// �ش� ���� �ּҰ��̵ȴ�.
	else {
		minOfSubPart = Ban_minScoreRecursively(_this, left + 1, right);
		// �ƴ϶�� left�� 1�� �÷��� ũ�⸦ �ϳ��� �ٿ����鼭 �ٽ� ���Ѵ�.
		if (_this->_elements[left]->_score < minOfSubPart) {
			return _this->_elements[left]->_score;
		}
		else {
			return minOfSubPart;
		}
		// ũ�� ��� �� return
	}
}

int Ban_numberOfStudentsAboveAverage(Ban* _this)
{ // ����̻��� �л� ���� ����ϴ� �޼ҵ�.
	float average = Ban_averageScore(_this);
	int score;
	int numberOfStudentsAboveAverage = 0;
	for (int i = 0; i < _this->_size; i++) {
		score = Student_score(_this->_elements[i]);
		if ((float)score >= average) {
			numberOfStudentsAboveAverage++;
		}
	}
	return numberOfStudentsAboveAverage;
}

GradeCounter* Ban_countGrades(Ban* _this)
{ // ������ Count �ϴ� �޼ҵ�
	char currentGrade;
	int score;
	GradeCounter* gradeCounter = GradeCounter_new();
	for (int i = 0; i < _this->_size; i++) {
		score = Student_score(_this->_elements[i]);
		currentGrade = Ban_scoreToGrade(score);
		GradeCounter_count(gradeCounter, currentGrade);
	}
	return gradeCounter;
}



float Ban_averageScore(Ban* _this)
{
	// ����� ����Ͽ� return ������ �����ش�.
	float sumOfScores = (float)Ban_sumOfScoresRecursively(_this, 0, _this->_size - 1);
	float average = sumOfScores / (float)_this->_size;
	return average;
}
int Ban_maxScore(Ban* _this)
{
	// �ְ����� ã�Ƽ� return ������ �����ش�.
	return Ban_maxScoreRecursively(_this, 0, _this->_size - 1);
}
int Ban_minScore(Ban* _this)
{
	// �������� ã�Ƽ� return ������ �����ش�.
	return Ban_minScoreRecursively(_this, 0, _this->_size - 1);
}

