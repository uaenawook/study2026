#include"Stack.h"



void Stack()
{
	ST s;//别写成*s
	STInit(&s);
	STPush(&s,1);
	STPush(&s,2);
	STPush(&s,3);
	STPush(&s,4);

	printf("%d\n", STTop(&s));
	STPop(&s);
	printf("%d\n", STTop(&s));
	STPop(&s);
	printf("%d\n", STTop(&s));
	STPop(&s);
	printf("%d\n", STTop(&s));
	STPop(&s);


	printf("是非为空%d\n", STEmpty(&s));


	STDestroy(&s);

}
int main()
{

	Stack();
	return 0;
}