#include"Contact.h"
#include"SeqList.h"

//初始化
void ContactInit(Contact* Con)
{
	assert(Con);
	SLInit(Con);
}


//展示通讯录数据
void ContactShow(Contact* con)
{
	//表头：姓名  性别 年龄 电话  地址
	printf("%s %s %s %s %s\n", "姓名", "性别", "年龄", "电话", "地址");
	//遍历通讯录，按照格式打印每个联系人数据
	for (int i = 0; i < con->size; i++)
	{
		printf("%3s %3s %3d %3s %3s\n", //手动调整一下格式
			con->arr[i].name,
			con->arr[i].gender,
			con->arr[i].age,
			con->arr[i].tel,
			con->arr[i].addr
		);
	}
}
//增
void ContactPush(Contact* Con)
{
	struct personInfo per;

	printf("输入增加联系人姓名：\n");	//提示
	scanf("%s", per.name);	//接收

	printf("输入增加联系人性别：\n");
	scanf("%s", per.gender);
	
	printf("输入增加联系人年龄：\n");
	scanf("%d", &per.age);

	printf("输入增加联系人电话：\n");
	scanf("%s", per.tel);

	printf("输入增加联系人住址：\n");
	scanf("%s", per.addr);

	SLPushBack(Con, per);//插入通讯录数据

}
int ConFind(Contact* Con, char* name)
{
	for (int i = 0; i < Con->size; i++)
	{
		if (0 == strcmp(Con->arr[i].name, name))
		{
			return i;
		}
	}
	return -1;
}
//删
void ContactPop(Contact* Con)
{
	struct personInfo per;

	printf("输入删除联系人姓名：\n");	//提示
	scanf("%s", per.name);	//接收

	int ret = ConFind(Con, &per);
	if (ret < 0)
	{
		printf("要删除的联系人不存在！\n");
		return;
	}
	SLErase(Con, ret);//删除
	printf("%s联系人删除成功！\n", per.name);
}
void Conprint(Contact* Con, int pos)
{

	printf("姓名 性别 年龄 电话 地址\n");

	printf("%4s %4s %4d %4s %4s\n",
		Con->arr[pos].name,
		Con->arr[pos].gender, 
		Con->arr[pos].age, 
		Con->arr[pos].tel, 
		Con->arr[pos].addr);

}

//查
void ContactFind(Contact* Con)
{
	//查
	struct personInfo per;

	printf("输入查找联系人的姓名：\n");	//提示
	scanf("%s", per.name);	//接收

	int ret = ConFind(Con, &per);

	//查不到提示
	if (ret < 0)
	{
		printf("要查找的联系人不存在！\n");
		return;
	}

	//查到了打印
	Conprint(Con,ret);

}

//改
void ContactModify(Contact* Con)
{
	//查
	struct personInfo per;

	printf("输入修改联系人的姓名：\n");	//提示
	scanf("%s", per.name);	//接收

	int ret = ConFind(Con, &per);

	//查不到提示
	if (ret < 0)
	{
		printf("要修改的联系人不存在！\n");
		return;
	}

	printf("找到了！请修改：\n");
	//查到了修改
	printf("输入修改联系人的性姓名：\n");	//提示
	scanf("%s", Con->arr[ret].name);	//接收

	printf("输入修改联系人的性别：\n");	//提示
	scanf("%s", Con->arr[ret].gender);	//接收

	printf("输入修改联系人的年龄：\n");	//提示
	scanf("%d", &Con->arr[ret].age);	//接收

	printf("输入修改联系人的电话：\n");	//提示
	scanf("%s", Con->arr[ret].tel);	//接收

	printf("输入修改联系人的住址：\n");	//提示
	scanf("%s", Con->arr[ret].addr);	//接收

	printf("修改成功\n");
}

//销毁
void ContactDestroy(Contact* Con)
{
	assert(Con);
	SLDestroy(Con);
}
