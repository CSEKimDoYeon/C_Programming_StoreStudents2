#include "AppController.h"
#include <stdio.h>

int main(void)
{
	AppController* appController = AppController_new();
	// ���� ������ AppController�� �����ϱ� ������ �� ��ü�� ������ش�.
	AppContorller_run(appController);
	// ������ AppController�� �������ش�.
	AppController_delete(appController);
	// �۾��� �Ϸ��� AppController�� �������ش�.
	system("pause");
	// ���α׷� ���� �� �ٷ� ����Ǵ� ���� ���´�.
	return 0;
} // end of main()