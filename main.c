#include <stdio.h>

int main(int argc, char** argv)
{
	unsigned long long AuthID = 0x00;

	if (argc == 1)
	{
		printf("SELF not specified in arg1");
		return 1;
	}
	else
	{
		FILE* fd = fopen(argv[1],"r+");
		if (fd == NULL)
		{
			printf("File not found %s",argv[1]);
			return 1;
		}
		fseek(fd,0x80,SEEK_SET);
		fread(&AuthID, sizeof(unsigned long long), 1, fd);
		printf("Current Authid: %llx\n", AuthID);
		if (AuthID == 0x2f00000000000001)
		{
			AuthID = 0x2f00000000000101;
		}
		else if (AuthID == 0x2f00000000000002)
		{
			AuthID = 0x2f00000000000102;
		}
		else
		{
			printf("Already works on activated dev/test kit.\n");
			return 1;
		}
		fseek(fd, 0x80, SEEK_SET);
		fwrite(&AuthID, sizeof(unsigned long long), 1, fd);
		printf("New Authid: %llx\n", AuthID);
		fclose(fd);
		return 0;
	}
}
