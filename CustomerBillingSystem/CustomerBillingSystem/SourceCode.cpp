#include <iostream>
 #include<conio.h>
#include <string>
#include "SourceCode.h"

using namespace std;

SourceCode::SourceCode(void)
{
}

SourceCode::~SourceCode(void)
{
}
 struct date
 {
	   int month;
	   int day;
	   int year;
 };

  struct account 
  {
	int number;
	char name[100];
	int acct_no;
	float mobile_no;
	char street[100];
	char city[100];
	char acct_type;
	float oldbalance;
	float newbalance;
	float payment;
	struct date lastpayment;
  }customer;

    int tl,sl,ts;

   void input()
	{
	  FILE *fp=fopen("bidur.dat","rb");
	  fseek (fp,0,SEEK_END);
	  tl=ftell(fp);  /// Application crashes here !!!!!!!!!!!!!!!!
	  sl=sizeof(customer);
	  ts=tl/sl;
	  fseek(fp,(ts-1)*sl,SEEK_SET);
	  fread(&customer,sizeof(customer),1,fp);
	  cout << "\ncustomer no:%d\n",++customer.number;
	  fclose(fp);
	  cout << "         Account number:";
	  scanf("%d",&customer.acct_no);
	  cout << "\n       Name:";
	  scanf("%s",customer.name);
	  cout << "\n       mobile no:";
	  scanf("%f",&customer.mobile_no);
	  cout << "         Street:";
	  scanf("%s",customer.street);
	  cout << "         City:";
	  scanf("%s",customer.city);
	  cout << "         Previous balance:";
	  scanf("%f",&customer.oldbalance);
	  cout << "         Current payment:";
	  scanf("%f",&customer.payment);
	  cout << "         Payment date(mm/dd/yyyy):";
	  scanf("%d/%d/%d",&customer.lastpayment.month,&customer.lastpayment.day,&customer.lastpayment.year);
	  return;
   }

   void writefile()
   {
	  FILE *fp;
	  fp=fopen("bidur.dat","ab");
	  fwrite(&customer,sizeof(customer),1,fp);
	  fclose(fp);
	  return;
   }
   
   void output()
	 {
	   cout << "\n\n    Customer no    :%d\n",customer.number;
	   cout << "    Name 	   :%s\n",customer.name;
	   cout << "    Mobile no      :%.f\n",customer.mobile_no;
	   cout << "    Account number :%d\n",customer.acct_no;
	   cout << "    Street         :%s\n",customer.street;
	   cout << "    City           :%s\n",customer.city;
	   cout << "    Old balance    :%.2f\n",customer.oldbalance;
	   cout << "    Current payment:%.2f\n",customer.payment;
	   cout << "    New balance    :%.2f\n",customer.newbalance;
	   cout << "    Payment date   :%d/%d/%d\n\n",customer.lastpayment.month,customer.lastpayment.day,customer.lastpayment.year;
	   cout << "    Account status :";
	  /* textcolor(128+RED);*/
	   switch(customer.acct_type)
	      {
	      case 'C':
		 cout << "CURRENT\n\n";
		 break;
	      case 'O':
		 cout << "OVERDUE\n\n";
		 break;
	      case 'D':
		 cout << "DELINQUENT\n\n";
		 break;
	      default:
		 cout << "ERROR\\n\n";
	      }
	      /*textcolor(WHITE);*/
	      return;
	
   }


   void search()
   {
	 char ch;
	 char nam[100];
	 int n,i,m=1;
	 FILE *fp;
	 fp=fopen("bidur.dat","rb");
	 do
	 {
		cout << "\nenter your choice:";
		ch=getche();
	 }while(ch!='1' && ch!='2');

	 switch(ch)
	 {
	      case '1':
		    fseek(fp,0,SEEK_END);
		    tl=ftell(fp);
		    sl=sizeof(customer);
		    ts=tl/sl;
		    do
			{
			cout << "\nchoose customer number:";
			scanf("%d",&n);
			if(n<=0 || n>ts)
			cout << "\nenter correct\n";
			else{
			    fseek(fp,(n-1)*sl,SEEK_SET);
			    fread(&customer,sl,1,fp);
			    output();
			}
			cout << "\n\nagain?(y/n)";
			ch=getche();
		    }while(ch=='y');

		    fclose(fp);
		    break;
	      case '2':
		    fseek(fp,0,SEEK_END);
		    tl=ftell(fp);
		    sl=sizeof(customer);
		    ts=tl/sl;
		    fseek(fp,(ts-1)*sl,SEEK_SET);
		    fread(&customer,sizeof(customer),1,fp);
		    n=customer.number;

		    do
			{
			cout << "\nenter the name:";
			scanf("%s",nam);
			fseek(fp,0,SEEK_SET);
			for(i=1;i<=n;i++)
			{
			     fread(&customer,sizeof(customer),1,fp);
			     if(strcmp(customer.name,nam)==0)
			     {
				output();
				m=0;
				break;
			     }
			}
			if(m!=0)
			cout << "\n\ndoesn't exist\n";
			cout << "\nanother?(y/n)";
			ch=getche();
		    }while(ch=='y');
		    fclose(fp);
	      }
	      return;
	 }

  void main()
	{
	  int i,n;
	  char ch;
	  system("cls");//clrscr();

	 // _setcursortype(_NOCURSOR);
	  cout << "   CUSTOMER BILLING SYSTEM:\n\n" ;
	  cout << "===============================\n";
	  cout << "\n1:    to add account on list\n";
	  cout << "2:    to search customer account\n";
	  cout << "3:    exit\n";
	  cout << "\n================================\n";
	  do{
	       cout << "\nselect what do you want to do?";
	       ch=getche();
	  }while(ch<='0' || ch>'3');
	  switch(ch){
		case '1':
			system("cls");//clrscr();
			cout << "\nhow many customer accounts?";
			scanf("%d",&n);
			for(i=0;i<n;i++){
				input();
				if(customer.payment>0)
					customer.acct_type=(customer.payment<0.1*customer.oldbalance)? 'O': 'D';
				else
					customer.acct_type=(customer.oldbalance>0)?'D' : 'C';
				customer.newbalance=customer.oldbalance - customer.payment;
				writefile();
			}
			main();
		case '2':
			system("cls");//clrscr();
			cout << "search by what?\n";
			cout << "\n1 --- search by customer number\n";
			cout << "2 --- search by customer name\n";
			search();
			ch=getche();
			main();
		case '3':
			system("cls");//clrscr();
			/*delay(700);
			textcolor(RED);
			gotoxy(25,25);*/
			cout << "\nA PROJECT BY BIDUR & SUJAN";
			/*delay(1500);*/
			exit(1);
	  }
 }

  