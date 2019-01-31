#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<time.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>
#include<string.h>
#define RETURNTIME 15

/********************************************* FUNCTIONS *********************************************************/
char catagories[][20]={"Computer","Electrical","Mechanical","Civil","Electronics"};
void mainmenu();
void office(void);
void Password();
void officedisplay();
void addbooks(void);
void deletebooks(void);
void searchbooks(void);
void viewbooks(void);
void issuebooks(void);
void editbooks(void);
void issuerecord(void);
void students(void);
void viewstudentbooks(void);
int getdata();

/********************************************* OTHER FUNCTIONS ***************************************************/
void printBoxSlowly(void);
void printBox(void);
void clearArea(int,int,int,int);
void gotoxy(short x, short y);
void goodbye(int,int);
int t(void);
void delay (unsigned int mseconds);

/******************************************* GLOBAL VARIABLES ****************************************************/
int s;
char findbook;
char password[10]={"fcit"};
struct date 
{
	int dd,mm,yy;
};
struct books
{
 int id;
 char name[30];
 char bookname[30];
 char author[30];
 char *cat;
 int quantity;
 float price;
 int count;
 int rackno;
 struct date issuedate;
 struct date duedate;
};
struct books x;

FILE *fp,*ft,*fs;

/******************************************* MAIN FUNCTION *******************************************************/
void main(){
 system("mode con: cols=200 lines=80");
 HWND hWnd = GetConsoleWindow();
 ShowWindow(hWnd,SW_SHOWMAXIMIZED);
 mainmenu();
 
}

/***************************************** FUNCTION DEFINITION ***************************************************/
void mainmenu(){
	printBoxSlowly();
    gotoxy(75,31);
    t();
    gotoxy(75,10);
    printf("WELCOME TO NED LIBRARY MANAGEMNET");
    gotoxy(55,12);
    printf("1.STUDENTS USE");
    gotoxy(55,13);
    printf("2.OFFICE USE");
    gotoxy(55,14);
    printf("3.EXIT");
    gotoxy(55,16);
    printf("CHOOSE ONE: ");
    char ch;
    ch = getch();
    	switch(ch){
    		case '1':
    		 students();
    		 break;
    		case '2':
    		 office();
    		 break;
		    case '3':
             goodbye(13,4);
             break;
		}
}
int t(void){  
	time_t t;
	time(&t);
	printf("%s",ctime(&t));
	return 0;
}
void office(void){
	Password();
}
void Password(void){
	clearArea(29,9,120,17);
	printBox();
    gotoxy(75,31);
    t();
    gotoxy(20,10);
   char d[25]="Password Protected";
   char ch,pass[10];
   int i=0,j;
    gotoxy(60,10);
    for(j=0;j<20;j++)
    {
    delay(50);
    printf("|");
    }
    for(j=0;j<20;j++)
   {
   delay(50);
   printf("%c",d[j]);
   }
   for(j=0;j<20;j++)
   {
   delay(50);
   printf("|");
   }
   gotoxy(10,10);
   gotoxy(75,15);
   printf("Enter Password:");
 
   while(ch!=13)
   {
    ch=getch();
 
    if(ch!=13){
    putch('*');
    pass[i] = ch;
    i++;
    }
   }
   pass[i] = '\0';
   if(strcmp(pass,password)==0)
   {
 
    gotoxy(75,17);
    printf("ACCESS GRANTED !");
    gotoxy(75,18);
    printf("Press any key to countinue.....");
    getch();
    officedisplay();
   }
   else
   {
     gotoxy(55,18);
     printf("\aWarning!! Incorrect Password");
     getch();
     Password();
   }
}
void officedisplay(){
 system("cls");
    int i;
    printBox();
    gotoxy(55,12);
    printf("1.ADD BOOKS");
    gotoxy(55,13);
    printf("2.DELETE BOOKS");
    gotoxy(55,14);
    printf("3.SEARCH BOOKS");
	gotoxy(55,15);
	printf("4.ISSUED BOOKS");
	gotoxy(55,16);
	printf("5.VIEW BOOKS");
	gotoxy(55,17);
	printf("6.EDIT BOOKS");
	gotoxy(55,18);
	printf("7.EXIT");
	gotoxy(55,20);
    printf("Enter your choice : ");
	scanf("%d",&i);
    switch(i)
    {
        case 1:
        addbooks();
        break;
        case 2:
        deletebooks();
        break;
        case 3:
        searchbooks();
        break;
        case 4:
        issuebooks();
        break;
        case 5:
        viewbooks();
        break;
        case 6:
        editbooks();
        break;
        case 7:
        goodbye(13,4);
        break;
    default:
    {
        gotoxy(55,22);
        printf("\aWrong Entry!!Please re-entered correct option");
        if(getch())
        officedisplay();
    }
	 }
}
void addbooks(void){
	system("cls");
	int i;
	printBox();
	gotoxy(68,12);
	printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB SELECT CATEGORY \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
	gotoxy(68,13);
	printf("1. Computer");
	gotoxy(68,14);
	printf("2. Electrical");
	gotoxy(68,15);
	printf("3. Mechanical");
	gotoxy(68,16);
	printf("4. Civil");
	gotoxy(68,17);
	printf("5. Electronics");
	gotoxy(68,18);
	printf("6. Back to main menu");
	gotoxy(68,19);
	printf("Enter your choice : ");
	scanf("%d",&i);
	if(i==6)
	officedisplay();
	system("cls"); 
	fp=fopen("Project.dat","ab+"); 
	if(getdata()==1)
	{
		x.cat=catagories[i-1]; 
		fseek(fp,0,SEEK_END); 
		fwrite(&x,sizeof(x),1,fp);
		fclose(fp);
		gotoxy(68,21);
		printf("The record is succesfully saved");		
		gotoxy(68,22);
		printf("Do you want to add more?( Y / N)");
		if(getch()=='n')
		officedisplay();
		else
		addbooks();
	}
}
void deletebooks(void){
	system("cls");
	printBox();
    int id,flag=0;
    char ch;
    fp = fopen("Project.dat","rb+");
    if(fp == NULL){
        printf("File cannot be open");
        exit(2);
    }
    ft = fopen("test.dat","wb");
    gotoxy(68,12);
    printf("Enter Book id : ");
    scanf("%d",&id);
    rewind(fp);
    while(fread(&x,sizeof(x),1,fp)==1){
     if(x.id!=id){
      fwrite(&x,sizeof(x),1,ft);
     }
     else
        flag=1;
    }
    if(flag)
    {
        gotoxy(68,14);
        printf("Record deleted successfully.");
	}
    else
    {
        gotoxy(68,15);
        printf("No record found associated with this book in our database.");
	}
    fclose(fp);
    fclose(ft);
    remove("Project.dat");
    rename("test.dat","Project.dat");
    gotoxy(68,16);
    printf("Want to delete another book record (Y/N) ? : ");
    ch=getche();
    if(ch == 'y')
        deletebooks();
    else {
    	gotoxy(68,17);
        printf("Returning to office menu in 3  seconds.");
        delay(3);
        officedisplay();
    }
}
void students(void){
	int j,d;
	system("cls");
	printBox();
	gotoxy(70,10);
	printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB NED LIBRARY \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
	gotoxy(70,11);
	printf("1.ISSUE A BOOK ");
	gotoxy(70,12);
	printf("2.VIEW AVAILABLE BOOKS");
	gotoxy(70,13);
	printf("3.EXIT");
	gotoxy(70,14);
	printf("Enter your choice : ");
	scanf("%d",&j);
	switch(j){
		case 1:
		{
		 system("cls");
         int c=0;
         char another='y';
         while(another=='y')
        {
         system("cls");
         printBox();
         gotoxy(73,10);
         printf("ISSUE BOOK SECTION");
         gotoxy(68,12);
         printf("Enter the Book Id:");
         scanf("%d",&d);
         fp=fopen("Project.dat","rb");
         fs=fopen("Issue.dat","ab+");
         if(checkid(d)==0)
         {
          gotoxy(68,14);
          printf("The book record is available");
          gotoxy(68,15);
          printf("There are %d unissued books in library ",x.quantity);
          gotoxy(68,16);
          printf("The name of book is %s",x.name);
          gotoxy(68,17);
          fflush(stdin);
		  printf("Enter student name:");
          scanf("%s",x.name);
          fflush(stdin);
          gotoxy(68,18);
		  printf("Enter date in format(dd/mm/yy) :");
          scanf("%d/%d/%d",&x.issuedate.dd,&x.issuedate.mm,&x.issuedate.yy);
          gotoxy(68,19);
          printf("Issued date=%d-%d-%d",x.issuedate.dd,x.issuedate.mm,x.issuedate.yy);
          gotoxy(68,20);
          printf("The BOOK of ID %d is issuedate",x.id);
                 x.duedate.dd=x.issuedate.dd+RETURNTIME;
                 x.duedate.mm=x.issuedate.mm;
                 x.duedate.yy=x.issuedate.yy;
                 if(x.duedate.dd>30)
                 {
                 x.duedate.mm+=x.duedate.dd/30;
                 x.duedate.dd-=30;
 
                 }
                 if(x.duedate.mm>12)
                 {
                  x.duedate.yy+=x.duedate.mm/12;
                  x.duedate.mm-=12;
 
                 }
                 gotoxy(68,21);
                 printf("To be return:%d-%d-%d",x.duedate.dd,x.duedate.mm,x.duedate.yy);
                 fseek(fs,sizeof(x),SEEK_END);
                 fwrite(&x,sizeof(x),1,fs);
                 fclose(fs);
                 c=1;
            }
            if(c==0)
            {
            gotoxy(68,16);
            printf("No record found");
            }
            gotoxy(68,23);
            printf("Issue any more(Y/N):");
            fflush(stdin);
            another=getche();
            fclose(fp);
		}
		students();
		break;
	}
	case 2:
    {
    	char c;
    	viewstudentbooks();
	    getch();
		students();
		break;		
	}		
	case 3:
	{
		goodbye(13,4);
		break;
	}
	default:
    {
        gotoxy(70,16);
        printf("\aWrong Entry!!Please re-entered correct option");
        getch();
        students();
    }
}
}
int getdata(){
	int t;
    printBox();
    gotoxy(68,12);
    printf("Enter the Information Below");
    gotoxy(68,14);
    printf("Book ID : ");
    gotoxy(68,15);
    scanf("%d",&t);
    if(checkid(t) == 0)
    {
        gotoxy(68,17);
        printf("\aThe book id already exists\a");
        getch();
        addbooks();
        return 0;
    }
    x.id=t;
    gotoxy(68,16);
    fflush(stdin);
    printf("Book Name:");
    fflush(stdin);
    gets(x.bookname);
    gotoxy(68,17);
    printf("Author:");
    fflush(stdin);
    gets(x.author);
    gotoxy(68,18);
    printf("Quantity:");
    scanf("%d",&x.quantity);
    gotoxy(68,19);
    fflush(stdin);
    printf("Price:");
    scanf("%f",&x.price);
    gotoxy(68,20);
    fflush(stdin);
	printf("Rack No:");
    scanf("%d",&x.rackno);
    return 1;
}
int checkid(int t)  
{
    rewind(fp);
    while(fread(&x,sizeof(x),1,fp)==1)
    if(x.id==t)
    return 0;  
    return 1;
}
void searchbooks(void){
	int d;
	system("cls");
	printBox();
	gotoxy(58,10);
	printf("SEARCH SECTION");
	gotoxy(55,12);
	printf("1. SEARCH BY ID");
	gotoxy(55,14);
	printf("2. SEARCH BY BOOK NAME");
	gotoxy(55,16);
	printf("3. GO BACK");
	gotoxy(55,18);
	fflush(stdin);
	printf("CHOOSE ONE : ");
	scanf("%d",&d);
	fp=fopen("Project.dat","rb+");
	rewind(fp);
	switch(d)
	{
		case 1:
		{
		system("cls");
		printBox();
		gotoxy(58,10);
		printf("SEARCH BOOKS BY ID");
        gotoxy(55,12);
		fflush(stdin);
        printf("Enter the book id:");
        scanf("%d",&d);
        gotoxy(55,13);
        printf("Searching........");
        delay(10);
        while(fread(&x,sizeof(x),1,fp)==1)
        {
        if(x.id==d)
        {
            delay(2);
            gotoxy(55,15);
            printf("The Book is available");
            gotoxy(55,16);
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
            gotoxy(55,17);
            printf("\xB2 ID:%d",x.id);gotoxy(82,17);printf("\xB2");
            gotoxy(55,18);
            printf("\xB2 Name:%s",x.bookname);gotoxy(82,18);printf("\xB2");
            gotoxy(55,19);
            printf("\xB2 Author:%s ",x.author);gotoxy(82,19);printf("\xB2");
            gotoxy(55,20);
            printf("\xB2 Quantity:%d ",x.quantity);gotoxy(82,20);printf("\xB2"); gotoxy(82,19);printf("\xB2");
            gotoxy(55,21);
            printf("\xB2 Price:Rs %f",x.price);gotoxy(82,21);printf("\xB2");
            gotoxy(55,22);
            printf("\xB2 Rack No:%d ",x.rackno);gotoxy(82,22);printf("\xB2");
            gotoxy(55,23);
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
            findbook='t';
        }
 
        }
        if(findbook!='t')  
        {
        gotoxy(20,8);
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        gotoxy(20,9);printf("\xB2");  gotoxy(38,9);printf("\xB2");
        gotoxy(20,10);
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        gotoxy(22,9);printf("\aNo Record Found");
        }
        gotoxy(55,24);
        printf("Try another search?(Y/N)");
        if(getch()=='y')
        searchbooks();
        else
        officedisplay();
        break;
    }
    case 2:
    {
        char s[15];
        system("cls");
        printBox();
        gotoxy(56,10);
        printf("SEARCH BY NAME OF BOOK");
        gotoxy(55,13);
        printf("Enter Book Name:");
        scanf("%s",s);
        int d=0;
        while(fread(&x,sizeof(x),1,fp)==1)
        {
        if(strcmp(x.bookname,(s))==0) 
        {
            gotoxy(55,15);
            printf("The Book is available");
            gotoxy(55,16);
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
            gotoxy(55,17);
            printf("\xB2 ID:%d",x.id);gotoxy(82,17);printf("\xB2");
            gotoxy(55,18);
            printf("\xB2 Name:%s",x.bookname);gotoxy(82,18);printf("\xB2");
            gotoxy(55,19);
            printf("\xB2 Author:%s",x.author);gotoxy(82,19);printf("\xB2");
            gotoxy(55,20);
            printf("\xB2 Qantity:%d",x.quantity);gotoxy(82,20);printf("\xB2");
            gotoxy(55,21);
            printf("\xB2 Price:Rs %f",x.price);gotoxy(82,21);printf("\xB2");
            gotoxy(55,22);
            printf("\xB2 Rack No:%d ",x.rackno);gotoxy(82,22);printf("\xB2");
            gotoxy(55,23);
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
            d++;
        }
 
        }
        if(d==0)
        {
        gotoxy(53,16);
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        gotoxy(53,17);printf("\xB2");  
		gotoxy(71,17);printf("\xB2");
        gotoxy(53,18);
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        gotoxy(55,17);printf("\aNo Record Found");
        }
        gotoxy(55,24);
        printf("Try another search?(Y/N)");
        if(getch()=='y')
        searchbooks();
        else
        officedisplay();
        break;
    }
    case 3:
    {
    	officedisplay();
    	break;
	}
    default :
    getch();
    searchbooks();
    }
    fclose(fp);
}
void issuebooks(void){
 system("cls");
 printBox();
 int t;
 gotoxy(70,10);
 printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB ISSUE BOOK SECTION \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
 gotoxy(70,12);
 printf("1.View Issued Books");
 gotoxy(70,13);
 printf("2.Search Issued Books");
 gotoxy(70,14);
 printf("3.Remove Issued Books");
 gotoxy(70,15);
 printf("4.Go Back");
 gotoxy(70,17);
 printf("Choose One : ");
 scanf("%d",&t);
 switch(t){
 	case 1:
 	{
 		system("cls");
 		int j=4;
        printf("*******************************Issued book list*******************************\n");
        gotoxy(2,2);
        printf("STUDENT NAME    CATEGORY    ID    BOOK NAME    ISSUED DATE    RETURN DATE");
        fs=fopen("Issue.dat","rb");
        while(fread(&x,sizeof(x),1,fs)==1)
        {
 
            gotoxy(2,j);
            printf("%s",x.name);
            gotoxy(18,j);
            printf("%s",x.cat);
            gotoxy(30,j);
            printf("%d",x.id);
            gotoxy(36,j);
            printf("%s",x.bookname);
            gotoxy(51,j);
            printf("%d-%d-%d",x.issuedate.dd,x.issuedate.mm,x.issuedate.yy );
            gotoxy(65,j);
            printf("%d-%d-%d",x.duedate.dd,x.duedate.mm,x.duedate.yy);
            gotoxy(50,25);
            j++;
 
        }
        fclose(fs);
        getch();
        issuebooks();
        break;
	 }
	 case 2:
	 {
	    system("cls");
	    printBox();
	    gotoxy(58,10);
        printf("Enter Book ID : ");
        int p,c=0;
        char another='y';
        while(another=='y')
        {
			scanf("%d",&p);
            fs=fopen("Issue.dat","rb");
            while(fread(&x,sizeof(x),1,fs)==1)
            {
                if(x.id==p)
                {
                    issuerecord();
                    gotoxy(58,14);
                    printf("Press any key.......");
                    getch();
                    issuerecord();
                    c=1;
                }
 
            }
            fflush(stdin);
            fclose(fs);
            if(c==0)
            {
                gotoxy(58,12);
                printf("No Record Found");
            }
            gotoxy(58,15);
            printf("Try Another Search?(Y/N)");
            another=getch();
        }
		issuebooks();
		break;		
	 }
	 case 3:
	 {
	  system("cls");
	  printBox();
	    int b;
        FILE *fg;  
        char another='y';
        while(another=='y')
        {
            gotoxy(58,10);
            printf("Enter book id to remove:");
            scanf("%d",&b);
            fs=fopen("Issue.dat","rb+");
            while(fread(&x,sizeof(x),1,fs)==1)
            {
                if(x.id==b)
                {
                    issuerecord();
                    findbook='t';
                }
                if(findbook=='t')
                {
                    gotoxy(58,18);
                    printf("Do You Want to Remove it?(Y/N)");
                    if(getch()=='y')
                    {
                        fg=fopen("record.dat","wb+");
                        rewind(fs);
                        while(fread(&x,sizeof(x),1,fs)==1)
                        {
                            if(x.id!=b)
                            {
                            fseek(fs,0,SEEK_CUR);
                            fwrite(&x,sizeof(x),1,fg);
                            }
                        }
                        fclose(fs);
                        fclose(fg);
                        remove("Issue.dat");
                        rename("record.dat","Issue.dat");
                        gotoxy(58,14);
                        printf("The issued book is removed from list");
						}
 
                }
                if(findbook!='t')
                {
                    gotoxy(58,15);
                    printf("No Record Found");
                }
            }
            gotoxy(58,19);
            printf("Delete any more?(Y/N)");
            another=getch();
        }
        issuebooks();
        break;
    }
    case 4:
    {
    	officedisplay();
    	break;
	}
    default:
    gotoxy(70,18);
    printf("\aWrong Entry!!");
    getch();
    issuebooks();
    break;
      }
      gotoxy(1,30);
      officedisplay();	
}	
void viewbooks(void){
	system("cls");
	int i=0,j;
    gotoxy(1,1);
    printf("********************************** BOOK LIST **********************************");
    gotoxy(2,2);
    printf(" CATEGORY     ID     BOOK NAME       AUTHOR         QTY      PRICE      RackNo ");
    j=4;
    fp=fopen("Project.dat","rb");
    while(fread(&x,sizeof(x),1,fp)>0)
    {
    gotoxy(3,j);
    fflush(stdin);
    printf("%s",x.cat);
    gotoxy(16,j);
    fflush(stdin);
    printf("%d",x.id);
    gotoxy(23,j);
    fflush(stdin);
    printf("%s",x.bookname);
    gotoxy(39,j);
    fflush(stdin);
    printf("%s",x.author);
    gotoxy(54,j);
    fflush(stdin);
    printf("%d",x.quantity);
    gotoxy(62,j);
    fflush(stdin);
    printf("%.2f",x.price);
    gotoxy(73,j);
    fflush(stdin);
    printf("%d",x.rackno);
    printf("\n\n");
    j++;
    i=i+x.quantity;
      }
      gotoxy(3,25);
      printf("Total Books =%d",i);
      fclose(fp);
      gotoxy(35,25);
      printf("\nPress any key to return to office menu");
      getch();
      officedisplay();
}
void editbooks(void){
    system("cls");
    int c=0;
    int d,e;
    char another='y';
    while(another=='y')
    {
        system("cls");
        printBox();
        gotoxy(65,10);
        printf("Enter Book Id to be edited : ");
        scanf("%d",&d);
        fp=fopen("Project.dat","rb+");
        while(fread(&x,sizeof(x),1,fp)==1)
        {
            if(checkid(d)==0)
            {
                gotoxy(65,11);
                printf("The book is availble");
                gotoxy(65,12);
                printf("The Book ID:%d",x.id);
                fflush(stdin);
				gotoxy(65,14);
                printf("Enter new name:");
				gets(x.bookname);
				fflush(stdin);
                gotoxy(65,15);
                printf("Enter new Author:");
				gets(x.author);
                gotoxy(65,16);
                fflush(stdin);
                printf("Enter new quantity:");
				scanf("%d",&x.quantity);
				fflush(stdin);
                gotoxy(65,17);
                printf("Enter new price:");
				scanf("%f",&x.price);
				fflush(stdin);
                gotoxy(65,18);
                printf("Enter new rackno:");
				scanf("%d",&x.rackno);
				fflush(stdin);
                gotoxy(65,19);
                printf("The record is modified");
                fseek(fp,ftell(fp)-sizeof(x),0);
                fwrite(&x,sizeof(x),1,fp);
                fclose(fp);
                c=1;
            }
            if(c==0)
            {
                gotoxy(65,15);
                printf("No record found");
            }
        }
        gotoxy(65,21);
        printf("Modify another Record?(Y/N)");
        fflush(stdin);
        another=getch() ;
    }
        officedisplay();
}
void goodbye(int x,int y){
	clearArea(1,1,170,29);
	int i;
	int a = x+6;
	for (i = 1; i <= 5; i++){
		switch(i){
			case 1:
				gotoxy(a,y); printf("    * * * * *");
				break;
			case 2:
				gotoxy(a,y+1); printf("       *    ");
				break;
			case 3:
				gotoxy(a,y+2); printf("      *    ");
				break;
			case 4:
				gotoxy(a,y+3); printf("     *    ");
				break;
			case 5:
				gotoxy(a,y+4); printf("    *    ");
				break;
		}
	}
	for (i = 1; i <= 5; i++){
		switch(i){
			case 1:
				gotoxy(a+13,y); printf("   *       *");
				break;
			case 2:
				gotoxy(a+12,y+1); printf("   *       *");
				break;
			case 3:
				gotoxy(a+12,y+2); printf("  * * * * *");
				break;
			case 4:
				gotoxy(a+12,y+3); printf(" *       *");
				break;
			case 5:
				gotoxy(a+12,y+4); printf("*       *");
				break;
		}
	}
	for (i = 1; i <= 5; i++){
		switch(i){
			case 1:
				gotoxy(a+25,y); printf("   * * * * *");
				break;
			case 2:
				gotoxy(a+24,y+1); printf("   *       *");
				break;
			case 3:
				gotoxy(a+24,y+2); printf("  * * * * *");
				break;
			case 4:
				gotoxy(a+24,y+3); printf(" *       *");
				break;
			case 5:
				gotoxy(a+24,y+4); printf("*       *");
				break;
		}
	}
	for (i = 1; i <= 5; i++){
		switch(i){
			case 1:
				gotoxy(a+37,y); printf("   *       *");
				break;
			case 2:
				gotoxy(a+36,y+1); printf("   * *     *");
				break;
			case 3:
				gotoxy(a+36,y+2); printf("  *   *   *");
				break;
			case 4:
				gotoxy(a+36,y+3); printf(" *     * *");
				break;
			case 5:
				gotoxy(a+36,y+4); printf("*       *");
				break;
		}
	}
	for (i = 1; i <= 5; i++){
		switch(i){
			case 1:
				gotoxy(a+49,y); printf("   *       *");
				break;
			case 2:
				gotoxy(a+48,y+1); printf("   *     *  ");
				break;
			case 3:
				gotoxy(a+48,y+2); printf("  * * *");
				break;
			case 4:
				gotoxy(a+48,y+3); printf(" *     *  ");
				break;
			case 5:
				gotoxy(a+48,y+4); printf("*       *");
				break;
		}
	}
	for (i = 1; i <= 5; i++){
		switch(i){
			case 1:
				gotoxy(a+64,y); printf("   *       *");
				break;
			case 2:
				gotoxy(a+63,y+1); printf("     *   *  ");
				break;
			case 3:
				gotoxy(a+63,y+2); printf("      *    ");
				break;
			case 4:
				gotoxy(a+63,y+3); printf("     *    ");
				break;
			case 5:
				gotoxy(a+63,y+4); printf("    *    ");
				break;
		}
	}
	for (i = 1; i <= 5; i++){
		switch(i){
			case 1:
				gotoxy(a+76,y); printf("   * * * * *");
				break;
			case 2:
				gotoxy(a+75,y+1); printf("   *       *");
				break;
			case 3:
				gotoxy(a+75,y+2); printf("  *       *");
				break;
			case 4:
				gotoxy(a+75,y+3); printf(" *       *");
				break;
			case 5:
				gotoxy(a+75,y+4); printf("* * * * *");
				break;
		}
	}
	for (i = 1; i <= 5; i++){
		switch(i){
			case 1:
				gotoxy(a+88,y); printf("   *       *");
				break;
			case 2:
				gotoxy(a+87,y+1); printf("   *       *");
				break;
			case 3:
				gotoxy(a+87,y+2); printf("  *       *");
				break;
			case 4:
				gotoxy(a+87,y+3); printf(" *       *");
				break;
			case 5:
				gotoxy(a+87,y+4); printf("    *    ");
				break;
		}
	}
}
void printBoxSlowly(void){
	int i,x,a=24,b=5,c;
    for(i=0;i<=30;i++){
    switch(i){
	case 1:
	 gotoxy(a,b);
     for(x=1;x<=130;x++)
     {
     delay(1);
     printf("|"); 
	 }
	 break;
	case 2:
	 gotoxy(a,b+1);
     for(x=1;x<=130;x++)
     {
     delay(1);
     printf("|"); 
	 }
	 break;
    case 3:
     gotoxy(a,b+2);
     for(x=1;x<=130;x++)
     {
     delay(1);
     printf("|"); 
	 }
     break;
	 case 4:
	 gotoxy(a,b+3);
     for(x=1;x<=130;x++)
     {
     delay(1);
     printf("|"); 
	 }	
     break;
	 case 5:
	 gotoxy(a,b+4);
	 for(x=1;x<=5;x++)
	 {
	 	delay(1);
	 	printf("|");
	 }
	 gotoxy(a+125,b+4);
	 for(x=1;x<=5;x++)
	 {
	 	delay(1);
	 	printf("|");
	 }
	 break;
	 case 6:
	gotoxy(a,b+5);
	 for(x=1;x<=5;x++)
	 {
	 	delay(1);
	 	printf("|");
	 }
	 gotoxy(a+125,b+5);
	 for(x=1;x<=5;x++)
	 {
	 	delay(1);
	 	printf("|");
	 }
	 break;
	 case 7:
	  gotoxy(a,b+6);
	  for(x=1;x<=5;x++)
	  {
	   delay(1);
	   printf("|");
	  }
	   gotoxy(a+125,b+6);
	  for(x=1;x<=5;x++)
	  {
	 	delay(1);
	 	printf("|");
	  }
	  break;
	  case 8:
	  	gotoxy(a,b+7);
	 for(x=1;x<=5;x++)
	 {
	 	delay(1);
	 	printf("|");
	 }
	 gotoxy(a+125,b+7);
	 for(x=1;x<=5;x++)
	 {
	 	delay(1);
	 	printf("|");
	 }
	 break;
	 case 9:
	  gotoxy(a,b+8);
	 for(x=1;x<=5;x++)
	 {
	 	delay(1);
	 	printf("|");
	 }
	 gotoxy(a+125,b+8);
	 for(x=1;x<=5;x++)
	 {
	 	delay(1);
	 	printf("|");
	 }
	 break;
	 case 10:
	 gotoxy(a,b+9);
	 for(x=1;x<=5;x++)
	 {
	 	delay(1);
	 	printf("|");
	 }
	 gotoxy(a+125,b+9);
	 for(x=1;x<=5;x++)
	 {
	 	delay(1);
	 	printf("|");
	 }
	 break;
	 case 11:
	 	gotoxy(a,b+10);
	 for(x=1;x<=5;x++)
	 {
	 	delay(1);
	 	printf("|");
	 }
	 gotoxy(a+125,b+10);
	 for(x=1;x<=5;x++)
	 {
	 	delay(1);
	 	printf("|");
	 }
	 break;
	 case 12:
	 	gotoxy(a,b+11);
	 for(x=1;x<=5;x++)
	 {
	 	delay(1);
	 	printf("|");
	 }
	 gotoxy(a+125,b+11);
	 for(x=1;x<=5;x++)
	 {
	 	delay(1);
	 	printf("|");
	 }
	 break;
	 case 13:
	 	gotoxy(a,b+12);
	 for(x=1;x<=5;x++)
	 {
	 	delay(1);
	 	printf("|");
	 }
	 gotoxy(a+125,b+12);
	 for(x=1;x<=5;x++)
	 {
	 	delay(1);
	 	printf("|");
	 }
	 break;
	 case 14:
	 	gotoxy(a,b+13);
	 for(x=1;x<=5;x++)
	 {
	 	delay(1);
	 	printf("|");
	 }
	 gotoxy(a+125,b+13);
	 for(x=1;x<=5;x++)
	 {
	 	delay(1);
	 	printf("|");
	 }
	 break;
	 case 15:
	  gotoxy(a,b+14);
	  for(x=1;x<=5;x++)
	  {
	 	delay(1);
	 	printf("|");
	  } 
	  gotoxy(a+125,b+14);
	  for(x=1;x<=5;x++)
	  {
	 	delay(1);
	 	printf("|");
	  } 
	  break;
	  case 16:
	  	gotoxy(a,b+15);
	  for(x=1;x<=5;x++)
	  {
	 	delay(1);
	 	printf("|");
	  } 
	  gotoxy(a+125,b+15);
	  for(x=1;x<=5;x++)
	  {
	 	delay(1);
	 	printf("|");
	  } 
	  break;
	  case 17:
	  	gotoxy(a,b+16);
	  for(x=1;x<=5;x++)
	  {
	 	delay(1);
	 	printf("|");
	  } 
	  gotoxy(a+125,b+16);
	  for(x=1;x<=5;x++)
	  {
	 	delay(1);
	 	printf("|");
	  } 
	  break;
	  case 18:
	  	gotoxy(a,b+17);
	  for(x=1;x<=5;x++)
	  {
	 	delay(1);
	 	printf("|");
	  } 
	  gotoxy(a+125,b+17);
	  for(x=1;x<=5;x++)
	  {
	 	delay(1);
	 	printf("|");
	  } 
	  break;
	  case 19:
	  	gotoxy(a,b+18);
	  for(x=1;x<=5;x++)
	  {
	 	delay(1);
	 	printf("|");
	  } 
	  gotoxy(a+125,b+18);
	  for(x=1;x<=5;x++)
	  {
	 	delay(1);
	 	printf("|");
	  } 
	  break;
	  case 20:
	  	gotoxy(a,b+19);
	  for(x=1;x<=5;x++)
	  {
	 	delay(1);
	 	printf("|");
	  } 
	  gotoxy(a+125,b+19);
	  for(x=1;x<=5;x++)
	  {
	 	delay(1);
	 	printf("|");
	  } 
	  break;
	  case 21:
	  	gotoxy(a,b+20);
	  for(x=1;x<=5;x++)
	  {
	 	delay(1);
	 	printf("|");
	  } 
	  gotoxy(a+125,b+20);
	  for(x=1;x<=5;x++)
	  {
	 	delay(1);
	 	printf("|");
	  } 
	  break;
	  case 22:
	  	gotoxy(a,b+21);
     for(x=1;x<=130;x++)
     {
     delay(1);
     printf("|"); 
	 }
	 break;
	  case 23:
	 	gotoxy(a,b+22);
        for(x=1;x<=130;x++)
        {
         delay(1);
         printf("|"); 
	    }
	    break;
	 case 24:
	 	gotoxy(a,b+23);
        for(x=1;x<=130;x++)
        {
         delay(1);
         printf("|"); 
	    }
	    break;
	 case 25:
	 	gotoxy(a,b+24);
        for(x=1;x<=130;x++)
        {
         delay(1);
         printf("|"); 
	    }
	    break;
	 }
}
}
void clearArea(int x, int y, int width, int height){
	int x1 = x;
	int i,j;
	for(i = 1; i <= height; i++){
		for (j = 1; j <= width; j++){
			gotoxy(x,y); printf(" ");
			x++;
		}
		x = x1;
		y++;
	}
}
void printBox(void){
	 int i,x,a=24,b=5,c;
    for(i=0;i<=30;i++){
    switch(i){
	case 1:
	 gotoxy(a,b);
     for(x=1;x<=130;x++)
     {
     printf("|"); 
	 }
	 break;
	case 2:
	 gotoxy(a,b+1);
     for(x=1;x<=130;x++)
     {
     printf("|"); 
	 }
	 break;
    case 3:
     gotoxy(a,b+2);
     for(x=1;x<=130;x++)
     {
     printf("|"); 
	 }
     break;
	 case 4:
	 gotoxy(a,b+3);
     for(x=1;x<=130;x++)
     {
     printf("|"); 
	 }	
     break;
	 case 5:
	 gotoxy(a,b+4);
	 for(x=1;x<=5;x++)
	 {
	 	printf("|");
	 }
	 gotoxy(a+125,b+4);
	 for(x=1;x<=5;x++)
	 {
	 	printf("|");
	 }
	 break;
	 case 6:
	gotoxy(a,b+5);
	 for(x=1;x<=5;x++)
	 {
	 	printf("|");
	 }
	 gotoxy(a+125,b+5);
	 for(x=1;x<=5;x++)
	 {
	 	printf("|");
	 }
	 break;
	 case 7:
	  gotoxy(a,b+6);
	  for(x=1;x<=5;x++)
	  {
	   printf("|");
	  }
	   gotoxy(a+125,b+6);
	  for(x=1;x<=5;x++)
	  {
	 	printf("|");
	  }
	  break;
	  case 8:
	  	gotoxy(a,b+7);
	 for(x=1;x<=5;x++)
	 {
	 	printf("|");
	 }
	 gotoxy(a+125,b+7);
	 for(x=1;x<=5;x++)
	 {
	 	printf("|");
	 }
	 break;
	 case 9:
	  gotoxy(a,b+8);
	 for(x=1;x<=5;x++)
	 {
	 	printf("|");
	 }
	 gotoxy(a+125,b+8);
	 for(x=1;x<=5;x++)
	 {
	 	printf("|");
	 }
	 break;
	 case 10:
	 gotoxy(a,b+9);
	 for(x=1;x<=5;x++)
	 {
	 	printf("|");
	 }
	 gotoxy(a+125,b+9);
	 for(x=1;x<=5;x++)
	 {
	 	printf("|");
	 }
	 break;
	 case 11:
	 	gotoxy(a,b+10);
	 for(x=1;x<=5;x++)
	 {
	 	printf("|");
	 }
	 gotoxy(a+125,b+10);
	 for(x=1;x<=5;x++)
	 {
	 	printf("|");
	 }
	 break;
	 case 12:
	 	gotoxy(a,b+11);
	 for(x=1;x<=5;x++)
	 {
	 	printf("|");
	 }
	 gotoxy(a+125,b+11);
	 for(x=1;x<=5;x++)
	 {
	 	printf("|");
	 }
	 break;
	 case 13:
	 	gotoxy(a,b+12);
	 for(x=1;x<=5;x++)
	 {
	 	printf("|");
	 }
	 gotoxy(a+125,b+12);
	 for(x=1;x<=5;x++)
	 {
	 	printf("|");
	 }
	 break;
	 case 14:
	 	gotoxy(a,b+13);
	 for(x=1;x<=5;x++)
	 {
	 	printf("|");
	 }
	 gotoxy(a+125,b+13);
	 for(x=1;x<=5;x++)
	 {
	 	printf("|");
	 }
	 break;
	 case 15:
	  gotoxy(a,b+14);
	  for(x=1;x<=5;x++)
	  {
	 	printf("|");
	  } 
	  gotoxy(a+125,b+14);
	  for(x=1;x<=5;x++)
	  {
	 	printf("|");
	  } 
	  break;
	  case 16:
	  	gotoxy(a,b+15);
	  for(x=1;x<=5;x++)
	  {
	 	printf("|");
	  } 
	  gotoxy(a+125,b+15);
	  for(x=1;x<=5;x++)
	  {
	 	printf("|");
	  } 
	  break;
	  case 17:
	  	gotoxy(a,b+16);
	  for(x=1;x<=5;x++)
	  {
	 	printf("|");
	  } 
	  gotoxy(a+125,b+16);
	  for(x=1;x<=5;x++)
	  {
	 	printf("|");
	  } 
	  break;
	  case 18:
	  	gotoxy(a,b+17);
	  for(x=1;x<=5;x++)
	  {
	 	printf("|");
	  } 
	  gotoxy(a+125,b+17);
	  for(x=1;x<=5;x++)
	  {
	 	printf("|");
	  } 
	  break;
	  case 19:
	  	gotoxy(a,b+18);
	  for(x=1;x<=5;x++)
	  {
	 	printf("|");
	  } 
	  gotoxy(a+125,b+18);
	  for(x=1;x<=5;x++)
	  {
	 	printf("|");
	  } 
	  break;
	  case 20:
	  	gotoxy(a,b+19);
	  for(x=1;x<=5;x++)
	  {
	 	printf("|");
	  } 
	  gotoxy(a+125,b+19);
	  for(x=1;x<=5;x++)
	  {
	 	printf("|");
	  } 
	  break;
	  case 21:
	  	gotoxy(a,b+20);
	  for(x=1;x<=5;x++)
	  {
	 	printf("|");
	  } 
	  gotoxy(a+125,b+20);
	  for(x=1;x<=5;x++)
	  {
	 	printf("|");
	  } 
	  break;
	  case 22:
	  	gotoxy(a,b+21);
     for(x=1;x<=130;x++)
     {	 
      printf("|"); 
	 }
	 break;
	  case 23:
	 	gotoxy(a,b+22);
        for(x=1;x<=130;x++)
        {
         printf("|"); 
	    }
	    break;
	 case 24:
	 	gotoxy(a,b+23);
        for(x=1;x<=130;x++)
        {
         printf("|"); 
	    }
	    break;
	 case 25:
	 	gotoxy(a,b+24);
        for(x=1;x<=130;x++)
        {
         printf("|"); 
	    }
	    break;
	 }
	 }
}
void gotoxy(short x, short y)                                               
{
 COORD pos ={x,y};
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void delay (unsigned int mseconds){
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
void issuerecord(void)
{
         system("cls");
         gotoxy(58,12);
         printf("The Book has taken by %s",x.name);
         gotoxy(58,14);
         printf("Issued Date:%d-%d-%d",x.issuedate.dd,x.issuedate.mm,x.issuedate.yy);
         gotoxy(58,15);
         printf("Returning Date:%d-%d-%d",x.duedate.dd,x.duedate.mm,x.duedate.yy);
}
void viewstudentbooks(void){
	system("cls");
	int i=0,j;
    gotoxy(1,1);
    printf("*********************************Book List*****************************");
    gotoxy(2,2);
    printf(" CATEGORY     ID     BOOK NAME       AUTHOR         QTY      PRICE      RackNo ");
    j=4;
    fp=fopen("Project.dat","rb");
    while(fread(&x,sizeof(x),1,fp)>0)
    {
    gotoxy(3,j);
    fflush(stdin);
    printf("%s",x.cat);
    gotoxy(16,j);
    fflush(stdin);
    printf("%d",x.id);
    gotoxy(23,j);
    fflush(stdin);
    printf("%s",x.bookname);
    gotoxy(39,j);
    fflush(stdin);
    printf("%s",x.author);
    gotoxy(54,j);
    fflush(stdin);
    printf("%d",x.quantity);
    gotoxy(62,j);
    fflush(stdin);
    printf("%.2f",x.price);
    gotoxy(73,j);
    fflush(stdin);
    printf("%d",x.rackno);
    printf("\n\n");
    j++;
    i=i+x.quantity;
      }
      gotoxy(3,25);
      printf("Total Books =%d",i);
      fclose(fp);
      gotoxy(35,25);
      printf("\nPress any key to return to main menu");
      getch();
      students();
}
/* PROJECT BY:
   1.MUHAMMAD ASAD      CT-052
   2.SYED ALI NAQI      CT-045
   3.SHAHEER GHANI IMAM CT-047
   4.TAYYAB             CT-062
*/
