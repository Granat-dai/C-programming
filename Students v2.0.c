//2016.12.10 ѧ����Ϣϵͳ Made by Dai  -��2016.12.13  
#include<stdio.h>
#include<stdlib.h> 
#include<string.h>
#include<malloc.h>
#include<windows.h>
#define LEN sizeof(struct student) 
int n=0; //ȫ�ֱ���ͳ�Ƹ��� 
struct student{    //����student�ṹ�嵥Ԫ 
	long id;
	char name[10];
	int age;
	int dor; 
	char sex; //����C99 boolֵ��Ϊ���ʣ�
    struct student *next; 
	//���ٳ�����������Ϊ���ӣ�����������֮���� 
}*head,*pthis;
typedef struct student STU; 
//����Ϊ�����õ��ĺ���
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
 //��������
 void cls(){ 
	system("CLS");
 } 
 //��ɫ���� 
  void color(const unsigned short color1){    
    if(color1>=0&&color1<=15)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color1);
    else
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
 //UI�Ż�bar
 void bar(int a){  
    if (a==0)  
	{
	    printf("    ------------------------------    -----------------------------") ;//�˵����� 
	    puts("");
    }
    else printf("-------------------------------------------------------------------\n");//�Ӳ˵����� 
 } 
 //��������
STU *prepare(void){   
    STU *head=NULL;
	STU *p1,*p2;
	FILE *fp;
	if((fp=fopen("Student","rb"))==NULL)
	{
		printf("���ļ�����\n");
		return 0;
	}
	n=1;
	while(!feof(fp)) {
		if((p1=(STU*)malloc(LEN))==NULL){
			printf("�ڴ��������\n");
			fclose(fp);
			return 0;
		}
		if(fread(p1,LEN,1,fp)!=1){
			free(p1);  //��ֵ���� 
			break;
		}  
		if(head==NULL)
		head=p2=p1;//���뵽ĩβ 
		else{
			p2->next=p1;
			p2=p1;
			n++; 
		}
	}
	fclose(fp);
	return (head);
}    
 //��������
 void input(){ 
    struct student *tmp;//��ʱ���� 
	cls();
	color(15);printf("*0����ѧ����Ϣ\n");color(7); 
    bar(1);
	do{ 
	 	if((tmp=(struct student *)malloc(sizeof(struct student)))==NULL){
	 	    printf("\n Error!�޿ɷ����ڴ棡\n");
	 	    exit(0);//�޷������ڴ�ʱ�˳� 
			}
		printf("���������%d��ѧ����Ϣ\n",n+1);
		printf("�����ѧ��ѧ��\n");scanf("%d",&tmp->id);while(getchar()!='\n');
		if (tmp->id==0) break; 
		printf("�����ѧ������\n");scanf("%s",&tmp->name);while(getchar()!='\n');
		printf("�����ѧ������\n");scanf("%d",&tmp->age);while(getchar()!='\n');
		printf("�����ѧ��������루��λ���֣�\n");scanf("%d",&tmp->dor);while(getchar()!='\n');
		while(1){
		printf("�����ѧ���Ա�M/F\n");scanf("%c",&tmp->sex);while(getchar()!='\n');
		if(tmp->sex=='M'||tmp->sex=='F') break;
		printf("������M��F ע���Сд��\n\n");
        }
		n++;   //¼������ 
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
		printf("\n\n�ɹ�����ѧ����Ϣ!\n");
		printf("��������룬������¼����ɣ�����ѧ��Ϊ0����¼�롣\n\n");
		bar(1);
		} 
	}while (tmp->id!=0);
	free(tmp);
	printf("����¼����ɣ�");
	system("pause"); 
	cls(); 
 } 
//��ʾ������
void show(){
	cls();
	color(15);printf("*1��ʾ��������\n");color(7);
	bar(1);
	printf("����Ϊ������¼�������\n\n");
    printf("ѧ��\t����\t����\t����\t�Ա�\n");
    bar(1);
    if (head==NULL) {
    	cls();
        printf("����,û������!�����������\n\n\n");
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
//��ѯ���ݲ˵� 
void search_menu() {
	int choice; 
	cls();
	while(getchar()!='\n'); 
    if (head==NULL) {
        printf("\n����!û������!\n");
        system("pause");
        cls();
        while(getchar()!='\n');
        return;
    }
    do{
    color(15);printf("*2��ѯָ������\n");color(7);
    bar(1); 
    bar(0);
	puts("         *  0.��ѧ�Ų���                   *  1.����������         ");
	puts("");
	puts("         *  2.���������                   *  3.���Ա����         ");
	bar(0);
	printf("����9�˳�����ϵͳ\n") ;
    printf("\n ��ѡ��˵����:");
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
		          printf("����ָ������!����������\n");
	}
	}while (choice!=9);
    
    
}
//��������
void search_name(){
	char name[10];
    cls(); 
    color(15);printf("������ѯ����\n");color(7);
    bar(1);
    printf("��������Ҫ��ѯ������\n");
	gets(name); 
    pthis=head;
    while (pthis!=NULL) {
        if (strcmp(name,pthis->name)==0) {    //ָ������ѯ��ֵ
		    printf("������ѯ��ѧ�Ŷ�Ӧ����ϢΪ\n\n");
		    printf("ѧ��\t����\t����\t����\t�Ա�\n");
            printf("%d\t%s\t%d\t%d\t%c\n",pthis->id,pthis->name,pthis->age,pthis->dor,pthis->sex);
            system("pause");
            cls();
            return;
        } else {
            pthis=pthis->next;
        }  
    }
    printf("\n�޴˼�¼!�������������\n");
    system("pause");
    cls();
} 
//id���� 
void search_id(){
    int id;
    cls(); 
    color(15);printf("ѧ�Ų�ѯ����\n");color(7);
    bar(1);
    printf("��������Ҫ��ѯ��ѧ��\n");
	scanf("%d",&id); 
    pthis=head;
    while (pthis!=NULL) {
        if (pthis->id==id) {    //ָ������ѯ��ֵ
		    printf("������ѯ��ѧ�Ŷ�Ӧ����ϢΪ\n\n");
		    printf("ѧ��\t����\t����\t����\t�Ա�\n");
            printf("%d\t%s\t%d\t%d\t%c\n",pthis->id,pthis->name,pthis->age,pthis->dor,pthis->sex);
            system("pause");
            cls();
            while(getchar()!='\n');
            return;
        } else {
            pthis=pthis->next;
        }  
    }
    printf("\n�޴˼�¼!�������������\n");
    system("pause");
    cls();
}
//�������� 
void search_dor(){
    int dor;
    int flag=0;
    cls(); 
    color(15);printf("�����ѯ����\n");color(7);
    bar(1);
    printf("��������Ҫ��ѯ���������\n");
	scanf("%d",&dor);

    for(pthis=head;pthis!=NULL;pthis=pthis->next) {
    	    if (pthis->dor==dor) {
    	    printf("������ѯ����������Ӧ����ϢΪ\n\n");
	        printf("ѧ��\t����\t����\t����\t�Ա�\n"); 	
            printf("%d\t%s\t%d\t%d\t%c\n",pthis->id,pthis->name,pthis->age,pthis->dor,pthis->sex);
            flag=1;
        }
    }
            if(flag==0) printf("\n�޴˼�¼!�������������\n");
		    system("pause");
            cls();
            while(getchar()!='\n');
            return;  
}
//�Ա�����
void search_sex(){
	char sex;
    cls(); 
    color(15);printf("�Ա��ѯ����\n");color(7);
    bar(1);
    printf("��������Ҫ��ѯ���Ա�M/F\n");
	sex=getchar();
	if (sex!='M' && sex!='F') {
	printf("����������Ա����Сд��");
	system("pause");
    cls();
    while(getchar()!='\n');
    return;
    }
	printf("������ѯ���Ա��Ӧ����ϢΪ\n\n");
	printf("ѧ��\t����\t����\t����\t�Ա�\n"); 
    for(pthis=head;pthis!=NULL;pthis=pthis->next) {
    	    if (pthis->sex==sex) {
            printf("%d\t%s\t%d\t%d\t%c\n",pthis->id,pthis->name,pthis->age,pthis->dor,pthis->sex);
        }
    }
		    system("pause");
            cls();
            while(getchar()!='\n');
            return;  
    printf("\n�޴˼�¼!�������������\n");
    system("pause");
    cls();
}
//ɾ��ѧ����Ϣ
void del() {
    int number;
    struct student *temp,*p;//��ʱ���� 
    cls();
	color(15);printf("*3ɾ��ָ������\n");color(7);
	bar(1); 
    if (head==NULL) {
        printf("\n����û�����ݣ��޷�ɾ��!\n");//ȱ������
		system("pause");
		while(getchar()!='\n');
        cls(); 
        return;
    }
    printf("\n������Ҫɾ����ѧ��:\n");
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
       printf ("ɾ��ѧ��Ϊ%d���������\n\n",number);
       n--;
        }
    else printf ("�޸�����!\n");
    system("pause");
    while(getchar()!='\n');
    cls();
 }
//׷��ָ��������
void insert() {
    int i,p;
    struct student *tmp;
    cls();
    color(15);printf("*4���ָ������\n");color(7);
    bar(1);
	printf("����Ϊ������¼�������\n\n");
    printf("ѧ��\t����\t����\t����\t�Ա�\n");
    bar(1);
    pthis=head;
    while (pthis!=NULL) {
        printf("%d\t%s\t%d\t%d\t%c\n",pthis->id,pthis->name,pthis->age,pthis->dor,pthis->sex);
        pthis=pthis->next;
    }   
    if (head==NULL) {        
        printf("\n\n���ݲ����ڣ��޷�����!\n"); //����
		system("pause");
		while(getchar()!='\n');	
        cls(); 
        return;
    }
    printf("\n�����������λ��:\n");
    printf("��ע�⣬�����λ��ָ���ǲ���Ŀ��ǰһ����λ���������һ����Ϊ0���ڶ�����Ϊ1\n\n");
    scanf("%d",&p);
    
    if (p<0||p>n) {
        printf("���벻�Ϸ�!��������ֵ����Ϣ�����������������\n");
        system("pause");
        cls();
		while(getchar()!='\n'); 
        return;
    }   
    if ((tmp=(STU *)malloc(sizeof(struct student)))==NULL) {
        printf("\n����!��������������ڴ�!\n");//�����µ�λ�ô洢 
        exit(0);
    }
    printf("�����ѧ��ѧ��\n");scanf("%d",&tmp->id);while(getchar()!='\n');
    //����ѧ���ظ�
      pthis=head;
	  while(pthis!=NULL)  
        {  
            if(pthis->id==tmp->id)  
            {  
                printf("��ѧ���Ѿ����ڣ��޷����룡\n");  
                return ;  
            }  
            pthis=pthis->next;  
        }  
	printf("�����ѧ������\n");scanf("%s",&tmp->name);while(getchar()!='\n');
	printf("�����ѧ������\n");scanf("%d",&tmp->age);while(getchar()!='\n');
	printf("�����ѧ��������루��λ���֣�\n");scanf("%d",&tmp->dor);while(getchar()!='\n');
	while(1){
	printf("�����ѧ���Ա�M/F\n");scanf("%c",&tmp->sex);while(getchar()!='\n');
	if(tmp->sex=='M'||tmp->sex=='F') break;
	printf("������M��F ע���Сд��\n\n");
    }//����
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
            pthis->next=tmp;     //��ָ��ֵ���� 
        }
    printf("�����Ѳ�����ϣ�\n");
    n++;
    system("pause");
    } 	
	else {
        printf("\n������Ч!\n");
        free(tmp);
    }
    cls();
}
//save�����뱣��
void save (STU *head){
   STU *p; 
   FILE *fp1;
   if ((fp1 = fopen("Student", "wb")) == NULL)
    {
        printf("Student�ļ�������!\n");
    }
    p=head;
    while (p!= NULL)
    {
        fwrite(p,LEN,1,fp1);
        p = p->next;
    }
    fclose(fp1);
} 
//��������˵� 
void main() {
    char choice,k;
 	int id=0;
    cls();
    head=prepare();
 	puts("***��ӭʹ��ѧ����Ϣϵͳ***");
	puts("");
	puts("ע�⣺������ʱ���ȴ���ѧ����Ϣ\n");  
 	do{
 	color(15); 
	printf("*****��ǰ���ݿ�����%d������*****\n\n",n); 
	color(7);
 	puts("***ϵͳ����ѡ��***");
 	puts("\n");
 	bar(0);
	puts("         *  0.����ѧ����Ϣ                 *  1.��ʾ����ѧ����Ϣ   ");
	puts("");
	puts("         *  2.��ѯѧ����Ϣ                 *  3.ɾ��ѧ����Ϣ       ");
	puts("");
	puts("         *  4.���ѧ����Ϣ                 *  5.�˳�ϵͳ           ");
	bar(0); 
	color(15); printf("\n ��ѡ��˵����:");color(7);
	choice=getchar()-48;
//����˵� 
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
				    printf("�Ѿ������������ݣ��������������ѡ���������\n");
					system("pause");//�ж��ظ�
					while(getchar()!='\n'); 
					cls();
					break;
				

				}
			case 1:show();break;
			case 2:search_menu();break;
			case 3:del();break;
			case 4:insert();break;
			default:cls(); 
		            printf("����ָ������!����������\n\n\n");
        }
    }while (choice!=5);
   
   while(getchar()!='\n');
   cls();
   puts("");
    do{
        printf("\n���Ƿ�Ҫ����¼����������Y/y���棬N/n������\n");
        k=getchar(); 
        if(k=='Y'||k=='y'){
            save(head);
            cls();
            bar(1); 
            printf("\t\t��л����ʹ�ã��ڴ���һ������-��-\n\n");
            bar(1);
            exit(0);
            }
        if(k=='N'||k=='n'){
            cls();
            bar(1); 
            printf("\t\t��л����ʹ�ã��ڴ���һ������-��-\n\n");
            bar(1);
            exit(0);             }
        cls();
        printf("����������������");
    }while(k!='y'&&k!='Y'&&k!='n'&&k!='N'); 
}
 
