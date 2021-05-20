#include <stdio.h>
#include <windows.h>

#define MEMSIZE 1000

int skip(int k){

	return k + 400;
}


int main(){

	HANDLE hmem;
	HANDLE hSemaphore = CreateSemaphore(NULL, 0, 2, "GENERAL_SEMAPHORE");

	hmem = CreateFileMapping((HANDLE)0xFFFFFFFF, NULL, PAGE_READWRITE, 0, 16000, "SHARE_HMEM");	//создание объекта виртуальной памяти
	char* data = MapViewOfFile(hmem, FILE_MAP_WRITE, 0, 0, 0);	//отображение объекта

	printf("Address=%p\n", hmem);
	Sleep(10000);
	strcpy(data, "Start program");
	ReleaseSemaphore(hSemaphore, 1, NULL);	//освобождение семафора

	char* virtualMem = VirtualAlloc(NULL, MEMSIZE, MEM_COMMIT, PAGE_READWRITE);	//выделяет память в сторону увеличения

	char litter = 'a';
	int k = 0;
	for(int i = 0; i < 15; i++){

		k = skip(k);
		printf("Write litter %c, Address=%d\n", litter, k);
		virtualMem[k] = litter;
		litter += 1;
	}
	//printf("END");

	UnmapViewOfFile(data);
	VirtualFree(virtualMem, 0, MEM_RELEASE);
	CloseHandle(hSemaphore);
	CloseHandle(hmem);
	return 0;
}