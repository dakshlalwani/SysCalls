#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

void checkUsrPerms(struct stat);
void checkGroupPerms(struct stat);
void checkOthersPerms(struct stat);

int source, dest, sy;
char buf;
char r = 'r', w = 'w', x = 'x', d = '-', nl = '\n';
char error1[100] = "Usage : <executable> <source> <destination>\n";
char error2[100] = "Can't open source file.\n";
char error3[100] = "Can't create destination.\n";
char msg1[100] = "symlink not created.\n";
char msg2[100] = "Symlink Created : YES\n";
char msg3[100] = "Task 2.2.1 Symlink Check FAILED\n";
char msg4[100] = "Directory Created\n";
char msg5[100] = "Task 2.2.2 FAILED\n";
char msg6[100]= "Task 2.3.1 (Directory Permissions)";
char msg7[100] = "Task 2.3.2 (File Permissions)";
char msg8[100] = "Task 2.3.2 (Symlink Permissions)";
char msg9[100] = "Task 2.4 Output File Reverse and Case Inversion Check FAILED\n";
char msg10[100] = "Task 2.4 DONE\n";
char own[100] = " : ";
char grp[100] = " ";
char oth[100] = " ";

struct stat a;
off_t filesize, i, j;

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        write(STDERR_FILENO, error1, 59);
        return 0;
    }

    source = open(argv[1], 0400);

    if (source < 0)
    {
        write(STDERR_FILENO, error2, 24);
        return 0;
    }

    char loc[10000] = "Assignment/";
    strcat(loc, argv[2]);

    if ((mkdir("Assignment", 0700)) < 0)
    {
        write(STDERR_FILENO, error3, 26);
        exit(-1);
    }

    dest = creat(loc, 0600);

    if (dest < 0)
    {
        write(STDERR_FILENO, error3, 26);
        return 0;
    }

    filesize = lseek(source, (off_t) 0, SEEK_END);
    for (i = filesize - 1; i >= 0; i--)
    {
        lseek(source, (off_t) i, SEEK_SET);
        read(source, &buf, 1);
        if (buf<=90 && buf>=65)
        {
            buf += 'a'-'A';
        }
        else if (buf>=97 && buf<=122)
            buf -= 'a'-'A';
        write(dest, &buf, 1);
    }
    write(STDOUT_FILENO, "File Reversed\n", 14);
    close(source);
    close(dest);

    sy = symlink(loc,argv[3]); 
    if(sy<0)
    {
        write(STDERR_FILENO, msg1, 21);
        return 0;
    }

    // Task 2.2.1 : Verify the creation of the symlink

    if(lstat(argv[3],&a) == 0)
    {
        if(S_ISLNK(a.st_mode))
        {
            write(STDOUT_FILENO, msg2, 28);
            write(STDOUT_FILENO, "Symlink Verified : YES\n", 23);

        }
        else
        {
            write(STDERR_FILENO, msg3, 32);
            return 0;
        }
    }
    else
    {
        write(STDERR_FILENO, msg3, 32);
        return 0;
    }


    // Task 2.2.2 : Verify the creation of the new file and new directory created in the above part of question

    if(stat("./Assignment",&a) == 0)
    {
        if(S_ISDIR(a.st_mode))
        {
            if(stat(loc,&a) == 0)
            {
                write(STDOUT_FILENO, msg4, 18);
                write(STDOUT_FILENO, "File Created : YES\n", 19);
            }
            else
            {
                write(STDERR_FILENO, msg5, 18);
                return 0;
            }
        }
        else
        {
            write(STDERR_FILENO, msg5, 18);
            return 0;               
        }        
    }
    else
    {
        write(STDERR_FILENO, msg5, 18);
        return 0;
    }


    // Task 2.3 : Check permissions for the three files mentioned in the above point.

    stat("./Assignment",&a);
    write(STDOUT_FILENO, msg6, 34);

    checkUsrPerms(a);
    checkGroupPerms(a);
    checkOthersPerms(a);

    stat(loc,&a);
    write(STDOUT_FILENO, msg7, 29);

    checkUsrPerms(a);
    checkGroupPerms(a);
    checkOthersPerms(a);

    lstat(argv[3],&a);
    write(STDOUT_FILENO, msg8, 32);

    checkUsrPerms(a);
    checkGroupPerms(a);
    checkOthersPerms(a);

    // Task 2.4 : Check if the file created is reversed and case-inverted version of the input file.
    
    source = open(argv[1], 0400);    

    if (source < 0)
    {
        write(STDERR_FILENO, error2, 24);
        return 0;
    }
    dest = open(loc, 0400);

    if (dest < 0)
    {
        write(STDERR_FILENO, error2, 24);
        return 0;
    }
    filesize = lseek(source, (off_t) 0, SEEK_END);
    char buf1, buf2;
    for (i = 0; i <= filesize-1; i++)
    {
        j = filesize - (i + 1);
        lseek(source, (off_t) i, SEEK_SET);
        lseek(dest, (off_t) j, SEEK_SET);
        read(source, &buf1, 1);
        read(dest, &buf2, 1);
       if (buf1 <= 90 && buf1>= 65)
        {
            if (buf2-buf1 != 32;)
            {
                write(STDERR_FILENO, msg9, 61);
                return 0;
            }
        }
        else if (buf1 <= 122 && buf1 >= 97)
        {
            if (buf1-buf2 != 32)
            {
                write(STDERR_FILENO, msg9, 61);
                return 0;
            }
        }
        else if (buf1!=buf2)
        {
            if (buf1-buf2!=0)
            {
                write(STDERR_FILENO, msg9, 61);
                return 0;
            }
        }
    }

    write(STDOUT_FILENO, msg10, 14);
    close(source);
    close(dest);
    return 0;
}

void checkUsrPerms(struct stat a)
{   
    write(STDOUT_FILENO,own,sizeof(own));
    write(STDOUT_FILENO, (a.st_mode & S_IRUSR) ? &r:&d, 1);
    write(STDOUT_FILENO, (a.st_mode & S_IWUSR) ? &w:&d, 1);
    write(STDOUT_FILENO, (a.st_mode & S_IXUSR) ? &x:&d, 1);
}

void checkGroupPerms(struct stat a)
{
    write(STDOUT_FILENO,grp,sizeof(grp));
    write(STDOUT_FILENO, (a.st_mode & S_IRGRP) ? &r:&d, 1);
    write(STDOUT_FILENO, (a.st_mode & S_IWGRP) ? &w:&d, 1);
    write(STDOUT_FILENO, (a.st_mode & S_IXGRP) ? &x:&d, 1);
}

void checkOthersPerms(struct stat a)
{
    write(STDOUT_FILENO,oth,sizeof(oth));
    write(STDOUT_FILENO, (a.st_mode & S_IROTH) ? &r:&d, 1);
    write(STDOUT_FILENO, (a.st_mode & S_IWOTH) ? &w:&d, 1);
    write(STDOUT_FILENO, (a.st_mode & S_IXOTH) ? &x:&d, 1);
    write(STDOUT_FILENO,&nl,1);
}
