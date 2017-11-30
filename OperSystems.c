#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct record{
	char selida[10];
	char symbol;
};
int main(int argc,char* argv[])
{
	int end1=0,end2=0;
	int found=0;
	int counter;//it counts how many places isnt empty for do flushing  
	int i,j,c;
	int k,plaisia,q;
	k=atoi(argv[1]);
	plaisia=atoi(argv[2]);
	q=atoi(argv[3]);
	int max=atoi(argv[4]);
	if(plaisia>2*k)
		return 0;
	FILE* arxeio1;
	FILE* arxeio2;
	char sel[15],t;
	int flush;
	int* place;
	place=malloc(2*k*sizeof(int));
	for(i=0;i<2*k;i++)
		place[i]=0;
	struct record* table;
	table=malloc((2*k)*sizeof(struct record));
	int hits=0,PFs=0,WBs=0;
	int size;
	int sum=0;//count how many records checked
	for(i=0;i<2*k;i++)
	{
		table[i].symbol='\0';
		strcpy(table[i].selida,"");
	}
	arxeio1=fopen("gcc.trace","r");
	arxeio2=fopen("bzip.trace","r");
	while(1)
	{
		for(j=0;j<q;j++)
		{
			if(feof(arxeio1))
			{
				end1=1;
				break;
			}
			fscanf(arxeio1,"%s %c",sel,&t); sum++;
			found=0;
			for(i=0;i<k;i++)
			{
				if(strncmp(sel,table[i].selida,5)==0)
				{
					hits++;
					table[i].symbol=t;
					found=1;
				}
			}
			if(found==0)
			{
				flush=0;
				PFs++;
				for(i=0;i<k;i++)
				{
					if(place[i]==0)
					{
						place[i]=1;
						strcpy(table[i].selida,sel);
						table[i].symbol=t;
						flush=1;
						break;
					}
				}
				if(flush==0)
				{
					//FLUSH////////////////
					for(i=0;i<k;i++)
					{
						place[i]=0;
						if(table[i].symbol=='W')
							WBs++;
						strcpy(table[i].selida,"");
						table[i].symbol='\0';
					}
					place[0]=1;
					strcpy(table[0].selida,sel);
					table[0].symbol=t;
				}
			}
		}
		if(sum==max||sum+q>max)
			break;
		if(end1==1&&end2==1)
			break;
		for(j=0;j<q;j++)
		{
			if(feof(arxeio2))
			{
				end2=1;
				break;
			}
			fscanf(arxeio2,"%s %c",sel,&t);sum++;
			found=0;
			for(i=k;i<2*k;i++)
			{
				if(strncmp(sel,table[i].selida,5)==0)
				{
					found=1;
					hits++;
					table[i].symbol=t;
				}
			}
			if(found==0)
			{
				PFs++;
				flush=0;
				for(i=k;i<2*k;i++)
				{
					if(place[i]==0)
					{
						place[i]=1;
						strcpy(table[i].selida,sel);
						table[i].symbol=t;
						flush=1;
						break;
					}
				}
				if(flush==0)
				{
					//FLUSH/////////////////////////////////////////////////
					for(i=k;i<2*k;i++)
					{
						place[i]=0;
						if(table[i].symbol=='W')
							WBs++;
						strcpy(table[i].selida,"");
						table[i].symbol='\0';
					}
					place[k]=1;
					strcpy(table[k].selida,sel);
					table[k].symbol=t;
				}
			}
		}
		if(sum==max||sum+q>max)
			break;
		if(end1==1&&end2==1)
			break;
	}
	printf("Totally i checked %d references of which  %d was hits,",sum,hits);
	printf("%d was PFs and %d was WBs\n",PFs,WBs);
	printf("The number of memory modules is %d\n",plaisia);
	free(table);
	free(place);
	fclose(arxeio1);
	fclose(arxeio2);
	return 0;
}
