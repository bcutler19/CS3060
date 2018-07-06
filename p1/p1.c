//Project  1 by Brayden Cutler
//Spring 3060_01
//I promise that this source code file has \n in it's entirety, been written by myself or a member of my group \n and by no other person or persons. \n If at any time an exact copy of this source code is found to \n be used by another person outside tmy group in this term, I understand that all members of my group and the members of the group that submitted the copy will receive a zero on this assignment.";
//Professor Durney



#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	printf("This assignment was easier than I made it out to be.\n");
	while(argc--)
		printf("Argument #%d: %s\n",argc, *argv++);
	exit(EXIT_SUCCESS);


}
