#include<stdio.h>
#include<string.h>

char *arr[] = {"Ananth Chandrasekharan","Divya Chandrasekharan","Thangamani Chandrasekharan","T.R. Chandrasekharan"};
char *arr_relation[] = { "Son","Daughter","Amma","Appa"};
char *arr_combined[255];

int main()
{
	/*
	int i,j;
	for (i=0,j=0;arr[i]!='\0',arr_relation[j]!='\0';i++,j++)
	{
		printf("%s : %s\n",*(arr_relation+j),*(arr+i));
	}
	*/

	/*
	int i;
	for (i=0;arr_relation[i]!='\0';i++)
	{
		printf("%s\n", *(arr_relation + i));
	}
	*/

	int i;
	i = 0;
	while (arr_relation[i] != '\0')
	{
		printf("%s", *(arr_relation + i));
		i++;
	}
	printf("\n");

	/*
	int i;
	i = 0;
	while (arr_relation[i]!='\0')
	{
		printf("%s and its length is %d\n", *(arr_relation + i),strlen(*(arr_relation + i)));
		i++;
	}
	printf("\n");
	*/

	return 0;
}


