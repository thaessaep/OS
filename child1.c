#include <stdio.h>
#include <windows.h>

int main(int fname, char* name[]){
	DWORD rc;
	STARTUPINFO sti = { 0 };
	PROCESS_INFORMATION pi = { 0 };

	rc = CreateProcess("grandchild1.exe", "Grandchild1 Child1", NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &sti, &pi);
	if(!rc){
		printf("Error process");
		return -1;
	}
	for(int i = 1; i <= 20; i++){	
		printf("%s(My parent is %s) (Number)=%d\n", name[0], name[1], i);				
		Sleep(2000);
	}
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return 0;
}