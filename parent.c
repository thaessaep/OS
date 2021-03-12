#include <stdio.h>
#include <windows.h>
#include <string.h>

int main(){
	DWORD rc, rc2;
	HANDLE handle2;
	char* name = "Parent";
	STARTUPINFO sti = { 0 }, sti2 = { 0 };
	PROCESS_INFORMATION pi = { 0 }, pi2 = { 0 };

	rc = CreateProcess("child1.exe", "Child1 Parent", NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &sti, &pi);
	rc2 = CreateProcess("child2.exe", "Child2 Parent", NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &sti2, &pi2);
	handle2 = CreateJobObject(NULL, NULL);
	AssignProcessToJobObject(handle2, pi2.hProcess);
	if(!rc && !rc2){
		printf("Error process");
		return -1;
	}
	for(int i = 1; i <= 20; i++){	
		printf("%s (Number)=%d\n", name, i);
		if(i == 7){
				TerminateProcess(pi.hProcess, 0);	//удаляет только дочерний процесс
				printf("Kill child process(ID=%d) with PID=%d\n", pi.hProcess, pi.dwProcessId);
		}
		if(i == 11){				
				TerminateJobObject(handle2, 0);	//удаляет дочерний процесс и всех его потомков
				printf("Kill child process(ID=%d) with PID=%d\n", pi2.hProcess, pi2.dwProcessId);
		}				
		Sleep(2000);
	}
	CloseHandle(pi.hProcess);
	CloseHandle(pi2.hProcess);
	return 0;
}