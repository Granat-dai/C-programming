//2016.12.10 学生信息系统 Made by Dai  -改2016.12.13  
#include<stdio.h>
#include<stdlib.h> 
#include<string.h>
#include<malloc.h>
#include<windows.h>
#define LEN sizeof(struct student) 
int n=0; //全局变量统计个数 
struct student{    //定义student结构体单元 
	long id;
	char name[10];
	int age;
	int dor; 
	char sex; //或许C99 bool值更为合适？
    struct student *next; 
	//仅举出几类数据作为例子，其余数据与之相似 
}*head,*pthis;
typedef struct student STU; 
//以下为所有用到的函数
void color(const unsigned short color1);
void bar(int a);
void input();
void insert();
void show();
void del();
void search_menu();
void search_id();
void search_name();
void search_dor();
void search_sex();
void save(STU *head); 
void cls();
void menu_inquire(void); 
STU *prepare(void);
 //清屏函数
 void cls(){ 
	system("CLS");
 } 
 //颜色函数 
  void color(const unsigned short color1){    
    if(color1>=0&&color1<=15)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color1);
    else
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
 //UI优化bar
 void bar(int a){  
    if (a==0)  
	{
	    printf("    ------------------------------    -----------------------------") ;//菜单界面 
	    puts("");
    }
    else printf("-------------------------------------------------------------------\n");//子菜单界面 
 } 
 //读入数据
STU *prepare(void){   
    STU *head=NULL;
	STU *p1,*p2;
	FILE *fp;
	if((fp=fopen("Student","rb"))==NULL)
	{
		printf("打开文件出错\n");
		return 0;
	}
	n=1;
	while(!feof(fp)) {
		if((p1=(STU*)malloc(LEN))==NULL){
			printf("内存申请出错\n");
			fclose(fp);
			return 0;
		}
		if(fread(p1,LEN,1,fp)!=1){
			free(p1);  //将值读入 
			break;
		}  
		if(head==NULL)
		head=p2=p1;//读入到末尾 
		else{
			p2->next=p1;
			p2=p1;
			n++; 
		}
	}
	fclose(fp);
	return (head);
}    
 //输入数据
 void input(){ 
    struct student *tmp;//临时变量 
	cls();
	color(15);printf("*0创建学生信息\n");color(7); 
    bar(1);
	do{ 
	 	if((tmp=(struct student *)malloc(sizeof(struct student)))==NULL){
	 	    printf("\n Error!无可访问内存！\n");
	 	    exit(0);//无法访问内存时退出 
			}
		printf("下面输入第%d个学生信息\n",n+1);
		printf("请给出学生学号\n");scanf("%d",&tmp->id);while(getchar()!='\n');
		if (tmp->id==0) break; 
		printf("请给出学生姓名\n");scanf("%s",&tmp->name);while(getchar()!='\n');
		printf("请给出学生年龄\n");scanf("%d",&tmp->age);while(getchar()!='\n');
		printf("请给出学生宿舍号码（三位数字）\n");scanf("%d",&tmp->dor);while(getchar()!='\n');
		while(1){
		printf("请给出学生性别M/F\n");scanf("%c",&tmp->sex);while(getchar()!='\n');
		if(tmp->sex=='M'||tmp->sex=='F') break;
		printf("请输入M或F 注意大小写！\n\n");
        }
		n++;   //录入数据 
		tmp->next=NULL;
		if(tmp->id!=0){
			if(head==NULL){
				head=tmp;
				pthis=head;
			}else{
				pthis->next=tmp;
				pthis=pthis->next;
			}
		cls();
		printf("\n\n成功创建学生信息!\n");
		printf("请继续输入，如数据录入完成，输入学号为0结束录入。\n\n");
		bar(1);
		} 
	}while (tmp->id!=0);
	free(tmp);
	printf("数据录入完成！");
	system("pause"); 
	cls(); 
 } 
//显示所有项
void show(){
	cls();
	color(15);printf("*1显示所有数据\n");color(7);
	bar(1);
	printf("以下为所有已录入的数据\n\n");
    printf("学号\t姓名\t年龄\t宿舍\t性别\n");
    bar(1);
    if (head==NULL) {
    	cls();
        printf("错误,没有数据!按任意键返回\n\n\n");
        system("pause");
        while(getchar()!='\n');
        cls();
        return;
    }
    
    pthis=head;
    while (pthis!=NULL) {
        printf("%d\t%s\t%d\t%d\t%c\n",pthis->id,pthis->name,pthis->age,pthis->dor,pthis->sex);
        pthis=pthis->next;
    }
    system("pause");
    while(getchar()!='\n');
    cls(); 
} 
//查询数据菜单 
void search_menu() {
	int choice; 
	cls();
	while(getchar()!='\n'); 
    if (head==NULL) {
        printf("\n错误!没有数据!\n");
        system("pause");
        cls();
        while(getchar()!='\n');
        return;
    }
    do{
    color(15);printf("*2查询指定数据\n");color(7);
    bar(1); 
    bar(0);
	puts("         *  0.按学号查找                   *  1.按姓名查找         ");
	puts("");
	puts("         *  2.按宿舍查找                   *  3.按性别查找         ");
	bar(0);
	printf("输入9退出查找系统\n") ;
    printf("\n 请选择菜单编号:");
	choice=getchar()-48;
    while(getchar()!='\n');
    switch(choice){
    	case 0 : search_id();break;
    	case 1 : search_name();break;
        case 2 : search_dor();break;
		case 3 : search_sex();break; 
		case 9 :  cls();
		          return;
				  while(getchar()!='\n'); 
        default : cls(); 
		          printf("输入指令有误!请重新输入\n");
	}
	}while (choice!=9);
    
    
}
//姓名搜索
void search_name(){
	char name[10];
    cls(); 
    color(15);printf("姓名查询功能\n");color(7);
    bar(1);
    printf("请输入需要查询的姓名\n");
	gets(name); 
    pthis=head;
    while (pthis!=NULL) {
        if (strcmp(name,pthis->name)==0) {    //指向所查询的值
		    printf("您所查询的学号对应的信息为\n\n");
		    printf("学号\t姓名\t年龄\t宿舍\t性别\n");
            printf("%d\t%s\t%d\t%d\t%c\n",pthis->id,pthis->name,pthis->age,pthis->dor,pthis->sex);
            system("pause");
            cls();
            return;
        } else {
            pthis=pthis->next;
        }  
    }
    printf("\n无此记录!，按任意键返回\n");
    system("pause");
    cls();
} 
//id搜索 
void search_id(){
    int id;
    cls(); 
    color(15);printf("学号查询功能\n");color(7);
    bar(1);
    printf("请输入需要查询的学号\n");
	scanf("%d",&id); 
    pthis=head;
    while (pthis!=NULL) {
        if (pthis->id==id) {    //指向所查询的值
		    printf("您所查询的学号对应的信息为\n\n");
		    printf("学号\t姓名\t年龄\t宿舍\t性别\n");
            printf("%d\t%s\t%d\t%d\t%c\n",pthis->id,pthis->name,pthis->age,pthis->dor,pthis->sex);
            system("pause");
            cls();
            while(getchar()!='\n');
            return;
        } else {
            pthis=pthis->next;
        }  
    }
    printf("\n无此记录!，按任意键返回\n");
    system("pause");
    cls();
}
//宿舍搜索 
void search_dor(){
    int dor;
    int flag=0;
    cls(); 
    color(15);printf("宿舍查询功能\n");color(7);
    bar(1);
    printf("请输入需要查询的宿舍号码\n");
	scanf("%d",&dor);

    for(pthis=head;pthis!=NULL;pthis=pthis->next) {
    	    if (pthis->dor==dor) {
    	    printf("您所查询的宿舍号码对应的信息为\n\n");
	        printf("学号\t姓名\t年龄\t宿舍\t性别\n"); 	
            printf("%d\t%s\t%d\t%d\t%c\n",pthis->id,pthis->name,pthis->age,pthis->dor,pthis->sex);
            flag=1;
        }
    }
            if(flag==0) printf("\n无此记录!，按任意键返回\n");
		    system("pause");
            cls();
            while(getchar()!='\n');
            return;  
}
//性别搜索
void search_sex(){
	char sex;
    cls(); 
    color(15);printf("性别查询功能\n");color(7);
    bar(1);
    printf("请输入需要查询的性别M/F\n");
	sex=getchar();
	if (sex!='M' && sex!='F') {
	printf("请检查输入的性别与大小写！");
	system("pause");
    cls();
    while(getchar()!='\n');
    return;
    }
	printf("您所查询的性别对应的信息为\n\n");
	printf("学号\t姓名\t年龄\t宿舍\t性别\n"); 
    for(pthis=head;pthis!=NULL;pthis=pthis->next) {
    	    if (pthis->sex==sex) {
            printf("%d\t%s\t%d\t%d\t%c\n",pthis->id,pthis->name,pthis->age,pthis->dor,pthis->sex);
        }
    }
		    system("pause");
            cls();
            while(getchar()!='\n');
            return;  
    printf("\n无此记录!，按任意键返回\n");
    system("pause");
    cls();
}
//删除学生信息
void del() {
    int number;
    struct student *temp,*p;//临时数据 
    cls();
	color(15);printf("*3删除指定数据\n");color(7);
	bar(1); 
    if (head==NULL) {
        printf("\n错误！没有数据，无法删除!\n");//缺少数据
		system("pause");
		while(getchar()!='\n');
        cls(); 
        return;
    }
    printf("\n请输入要删除的学号:\n");
    scanf("%d",&number);
    temp=head;
    while (((temp->id)!=number)&&((temp->next)!=NULL))
    {
        p=temp;
        temp=temp->next;
    }
    if ((temp->id)==number)
        {
        if (temp==head)
            {
            head=head->next;
            }
        else
       {
            p->next=temp->next;           
            free (temp);
       }
       printf ("删除学号为%d的数据完毕\n\n",number);
       n--;
        }
    else printf ("无该数据!\n");
    system("pause");
    while(getchar()!='\n');
    cls();
 }
//追加指定点数据
void insert() {
    int i,p;
    struct student *tmp;
    cls();
    color(15);printf("*4添加指定数据\n");color(7);
    bar(1);
	printf("以下为所有已录入的数据\n\n");
    printf("学号\t姓名\t年龄\t宿舍\t性别\n");
    bar(1);
    pthis=head;
    while (pthis!=NULL) {
        printf("%d\t%s\t%d\t%d\t%c\n",pthis->id,pthis->name,pthis->age,pthis->dor,pthis->sex);
        pthis=pthis->next;
    }   
    if (head==NULL) {        
        printf("\n\n数据不存在，无法插入!\n"); //先验
		system("pause");
		while(getchar()!='\n');	
        cls(); 
        return;
    }
    printf("\n请输入插入点的位置:\n");
    printf("请注意，插入点位置指的是插入目标前一个的位置数，如第一个即为0，第二个即为1\n\n");
    scanf("%d",&p);
    
    if (p<0||p>n) {
        printf("输入不合法!请检查输入值与信息总数！按任意键返回\n");
        system("pause");
        cls();
		while(getchar()!='\n'); 
        return;
    }   
    if ((tmp=(STU *)malloc(sizeof(struct student)))==NULL) {
        printf("\n错误!不能申请所需的内存!\n");//分配新的位置存储 
        exit(0);
    }
    printf("请给出学生学号\n");scanf("%d",&tmp->id);while(getchar()!='\n');
    //检验学号重复
      pthis=head;
	  while(pthis!=NULL)  
        {  
            if(pthis->id==tmp->id)  
            {  
                printf("该学号已经存在，无法插入！\n");  
                return ;  
            }  
            pthis=pthis->next;  
        }  
	printf("请给出学生姓名\n");scanf("%s",&tmp->name);while(getchar()!='\n');
	printf("请给出学生年龄\n");scanf("%d",&tmp->age);while(getchar()!='\n');
	printf("请给出学生宿舍号码（三位数字）\n");scanf("%d",&tmp->dor);while(getchar()!='\n');
	while(1){
	printf("请给出学生性别M/F\n");scanf("%c",&tmp->sex);while(getchar()!='\n');
	if(tmp->sex=='M'||tmp->sex=='F') break;
	printf("请输入M或F 注意大小写！\n\n");
    }//输入
    tmp->next=NULL;
    if (tmp->id!=0) {
        pthis=head;
        if (p==0) {
            tmp->next=head;
            head=tmp;
        } else {
            for (i=0; i<p-1; i++) {
                pthis=pthis->next;
            }
            tmp->next=pthis->next;
            pthis->next=tmp;     //将指定值插入 
        }
    printf("数据已插入完毕！\n");
    n++;
    system("pause");
    } 	
	else {
        printf("\n数据无效!\n");
        free(tmp);
    }
    cls();
}
//save函数与保存
void save (STU *head){
   STU *p; 
   FILE *fp1;
   if ((fp1 = fopen("Student", "wb")) == NULL)
    {
        printf("Student文件不存在!\n");
    }
    p=head;
    while (p!= NULL)
    {
        fwrite(p,LEN,1,fp1);
        p = p->next;
    }
    fclose(fp1);
} 
//主函数与菜单 
void main() {
    char choice,k;
 	int id=0;
    cls();
    head=prepare();
 	puts("***欢迎使用学生信息系统***");
	puts("");
	puts("注意：无数据时请先创建学生信息\n");  
 	do{
 	color(15); 
	printf("*****当前数据库中有%d个数据*****\n\n",n); 
	color(7);
 	puts("***系统功能选择***");
 	puts("\n");
 	bar(0);
	puts("         *  0.创建学生信息                 *  1.显示所有学生信息   ");
	puts("");
	puts("         *  2.查询学生信息                 *  3.删除学生信息       ");
	puts("");
	puts("         *  4.添加学生信息                 *  5.退出系统           ");
	bar(0); 
	color(15); printf("\n 请选择菜单编号:");color(7);
	choice=getchar()-48;
//处理菜单 
	switch(choice)
	    {
		    case 0:
		        if(head==NULL)
				{
		        	input();break;
		   		}
		   		else
		   		{   
		   		    cls();
				    printf("已经存在输入数据，如需插入数据请选择插入数据\n");
					system("pause");//判断重复
					while(getchar()!='\n'); 
					cls();
					break;
				

				}
			case 1:show();break;
			case 2:search_menu();break;
			case 3:del();break;
			case 4:insert();break;
			default:cls(); 
		            printf("输入指令有误!请重新输入\n\n\n");
        }
    }while (choice!=5);
   
   while(getchar()!='\n');
   cls();
   puts("");
    do{
        printf("\n您是否要保存录入结果？输入Y/y保存，N/n不保存\n");
        k=getchar(); 
        if(k=='Y'||k=='y'){
            save(head);
            cls();
            bar(1); 
            printf("\t\t感谢您的使用，期待下一次相遇-。-\n\n");
            bar(1);
            exit(0);
            }
        if(k=='N'||k=='n'){
            cls();
            bar(1); 
            printf("\t\t感谢您的使用，期待下一次相遇-。-\n\n");
            bar(1);
            exit(0);             }
        cls();
        printf("输入有误！重新输入");
    }while(k!='y'&&k!='Y'&&k!='n'&&k!='N'); 
}
 
