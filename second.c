#include <stdio.h>
#include <windows.h>

int main(){
	
	char* data, result[6];
	HANDLE hmem;
	HANDLE hSemaphore = OpenSemaphore(SYNCHRONIZE, TRUE, "GENERAL_SEMAPHORE");

	hmem = OpenFileMapping(FILE_MAP_READ, FALSE, "SHARE_HMEM");
	data = MapViewOfFile(hmem, FILE_MAP_READ, 0, 0, 0);

	printf("Address=%p\n", hmem);
	WaitForSingleObject(hSemaphore, INFINITE);	//ждёт освобождения семафора
	strncpy(result, data, 6);
	printf("%s\n", data);
	printf("Address data=%p\n", data);
	//Sleep(4000);

	UnmapViewOfFile(data);
	CloseHandle(hSemaphore);
	CloseHandle(hmem);
	return 0;
}