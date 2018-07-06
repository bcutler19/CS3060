//Brayden Cutler
//CS-3060


#include<stdio.h> 
#include<pthread.h>
#include<dirent.h> 
#include<sys/stat.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

void do_ls (char[], int, int*);
int main(int ac, char *av[]) {
    if (ac == 1)
	{
		int mem = 0;
       		 do_ls(".",0,&mem);
	}
    else
    {
        while(--ac)
        {
            int mem = 0;
	    printf("%s:\n", *++av);
            do_ls (*av,0,&mem);
	   printf("\nTotal Space Used: %d\n", mem);
        }// while
    }//end else
    
}//end main
void do_ls(char dirname[],int tabs,int * memC) {
    DIR *dir_ptr;
    struct dirent *direntp;
    struct stat info;

    if((dir_ptr = opendir(dirname))==NULL)
        fprintf(stderr,"|so|: cannot open %s\n", dirname);
    else
    {
        while((direntp = readdir(dir_ptr)) != NULL)
        {
          if(strcmp("..",direntp->d_name) !=0 && strcmp(".",direntp->d_name) !=0)
	  {
		char *fileLoc;
		//allocate memory
		fileLoc = malloc(strlen(dirname)+ 22 + strlen(direntp->d_name));
		strcpy(fileLoc, dirname);
		strcat(fileLoc,"/");
		strcat(fileLoc,direntp->d_name);
		stat (fileLoc, &info);

		if(S_ISDIR (info.st_mode))//if it is a directory
           	{
		tabs++;
               	 do_ls(fileLoc,tabs,memC);
            	}
           	else //if it is a file
            	{
                 for(int i = 0; i < tabs; i++)
		{
		printf("   ");
		}
		printf("%d %s\n", (int) info.st_size, direntp->d_name);
		*memC += (int)info.st_size;
           	}
	}
        }//end while
        closedir(dir_ptr);
    }//end else
}//end main
