#include <stdio.h>

int min(int a,int b)
{
	return a>b?b:a;
}

int x1,y1,x2,y2;

main()
{
	scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
	printf("%d",min(min(x1,x2-x1),min(y1,y2-y1)));
}
