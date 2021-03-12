#include <stdio.h>
#include <windows.h>

int main(int fname, char* name[]){

	for(int i = 1; i <= 20; i++){
		printf("%s(My parent is %s) (Number)=%d\n", name[0], name[1], i);
		Sleep(1200);
	}
	return 0;
}