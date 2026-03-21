#pragma once

//定义通讯录内容
//姓名 性别 年龄 电话 住址
#define NAME_MAX 20
#define GENDER_MAX 10
#define TEL_MAX 20
#define ADDR_MAX 100
struct personInfo
{
	char name[NAME_MAX];
	char gender[GENDER_MAX];
	int age;
	char tel[TEL_MAX];
	char addr[ADDR_MAX];
};



typedef struct SeqList Contact;

//初始化
void ContactInit(Contact* Con);


//展示通讯录数据
void ContactShow(Contact* con);

//增
void ContactPush(Contact* Con);

//删
void ContactPop(Contact* Con);

//查
void ContactFind(Contact* Con);

//改
void ContactModify(Contact* Con);

//销毁
void ContactDestroy(Contact* Con);
