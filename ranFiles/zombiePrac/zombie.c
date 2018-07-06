#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	int pid;
	pid = fork();
	if(!pid){
		exit(0);
	}
	printf("Please, press Enter after looking at the zombie process");
	(void)getchar();

}

