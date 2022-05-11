//                   HEADER FILE USED IN PROJECT


#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream.h>
#include<string.h>

//                   CLASS USED IN PROJECT


class product
{
 int pno;
 char name[50];
 float price,qty,tax,dis;
 public:
	void create_product()
	{
	 cout<<"\n* Please Enter The Product No. of The Product: ";
	 cin>>pno;
	 cout<<"\n\n* Please Enter The Name of The Product:";
	 gets(name);
	 cout<<"\n* Please Enter The Price of The Product: ";
	 cin>>price;
	 cout<<"\n* Please Enter The Discount (%): ";
	 cin>>dis;
	 }

	void show_product()
	{
	 cout<<"\n* The Product No. of The Product : "<<pno;
	 cout<<"\n* The Name of The Product : ";
	 puts(name);
	 cout<<"\n* The Price of The Product : "<<price;
	 cout<<"\n* Discount : "<<dis;
	 }

  int  retpno()
  {return pno;}

  float retprice()
  {return price;}

  char* retname()
  {return name;}

  int retdis()
  {return dis;}

};         //class ends here




//    	global declaration for stream object, object


 fstream fp;
 product pr;



//    	function to write in file


void write_product()
   {
    fp.open("Shop.dat",ios::out|ios::app);
    pr.create_product();
    fp.write((char*)&pr,sizeof(product));
    fp.close();
    cout<<"\n\n*** The Product Has Been Created *** ";
    getch();
   }



//    	function to read all records from file


void display_all()
{
    clrscr();
    cout<<"\n\n\n\t\t*** DISPLAY ALL RECORD !!!\n\n";
    fp.open("Shop.dat",ios::in);
    while(fp.read((char*)&pr,sizeof(product)))
	{
	 pr.show_product();
	 cout<<"\n\n====================================\n";
	 getch();
	 }
    fp.close();
    getch();
}



//    	function to read specific record from file



void display_sp(int n)
{
    int flag=0;
    fp.open("Shop.dat",ios::in);
    while(fp.read((char*)&pr,sizeof(product)))
	{
	 if(pr.retpno()==n)
		{
		 clrscr();
		 pr.show_product();
		 flag=1;
		}
	}
    fp.close();
if(flag==0)
 cout<<"\n\n***record not exist***";
    getch();
}



//    	function to modify record of file


void modify_product()
{
    int no,found=0;
    clrscr();
    cout<<"\n\n\t***To Modify ";
    cout<<"\n\n\t* Please Enter The Product No. of The Product:";
    cin>>no;
    fp.open("Shop.dat",ios::in|ios::out);
    while(fp.read((char*)&pr,sizeof(product)) && found==0)
	   {
	    if(pr.retpno()==no)
		   {
		    pr.show_product();
		    cout<<"\n* Please Enter The New Details of Product:"<<endl;
		    pr.create_product();
		    int pos=-1*sizeof(pr);
		    fp.seekp(pos,ios::cur);
		    fp.write((char*)&pr,sizeof(product));

		    cout<<"\n\n\t***Record Updated***";
		    found=1;
		   }
	     }
    fp.close();
    if(found==0)
    cout<<"\n\n*** Record Not Found *** ";
    getch();
}



//    	function to delete record of product


void delete_product()
   {
    int no;
    clrscr();
    cout<<"\n\n\n\t**Delete Record**";
    cout<<"\n\n* Please Enter The product no. of The Product You Want To Delete:";
    cin>>no;
    fp.open("Shop.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&pr,sizeof(product)))
	{
	 if(pr.retpno()!=no)
		{
		 fp2.write((char*)&pr,sizeof(product));
		 }
	 }
    fp2.close();
    fp.close();
    remove("Shop.dat");
    rename("Temp.dat","Shop.dat");
    cout<<"\n\n\t**Record Deleted ..";
    getch();
    }



//    	function to display all products price list

    void menu()
    {

     clrscr();
     fp.open("Shop.dat",ios::in);
     if(!fp)
     {
       cout<<"\n\nERROR!!! FILE COULD NOT BE OPEN\n\n\n*** Go To Admin Menu to create File ***";
       cout<<"\n\n\n* Program is closing ....";
       getch();
       exit(0);
     }

     cout<<"\n\n\t\t***Product MENU***\n\n";
	  cout<<"====================================================\n";
	  cout<<"P.NO.\t\tNAME\t\t\t PRICE\n";
	  cout<<"====================================================\n";

      while(fp.read((char*)&pr,sizeof(product)))
	 {
	   cout<<pr.retpno()<<"\t\t"<<pr.retname()<<"\t "<<pr.retprice()<<endl;
	}
     fp.close();
}

//    	function to place order and generating bill for Products

   void place_order()
   {
    int  order_arr[50],quan[50],c=0;
    float amt,damt,total=0;
    char ch='Y';
    menu();
    cout<<"\n============================";
    cout<<"\n    PLACE YOUR ORDER";
    cout<<"\n============================\n";
    do{
	 cout<<"\n\n* Enter The Product No. Of The Product : ";
	 cin>>order_arr[c];
	 cout<<"\n* Quantity in number : ";
	 cin>>quan[c];
	 c++;
	 cout<<"\n* Do You Want To Order Another Product ? (y/n):";
	 cin>>ch;
    }while(ch=='y' ||ch=='Y');
    cout<<"\n\n**Thank You For Placing The Order...........";getch();clrscr();
      cout<<"\n\n\t****RECIEPT******\n";
      cout<<"\nPr No.\tName  \t\t   Quantity\tPrice\t Amount\t Discounted amount\n";
      for(int x=0;x<=c;x++)

	{
		 fp.open("Shop.dat",ios::in);
		 fp.read((char*)&pr,sizeof(product));
		  while(!fp.eof())
			{
			if(pr.retpno()==order_arr[x])
				{
				 amt=pr.retprice()*quan[x];
				 damt=amt-(amt*pr.retdis()/100);
				 cout<<"\n"<<order_arr[x]<<"\t"<<pr.retname()<<"\t  "<<quan[x]<<"\t "<<pr.retprice()<<"\t "<<amt<<"\t  "<<damt;
				 total+=damt;
				}
			fp.read((char*)&pr,sizeof(product));
			}

		 fp.close();
	 }
       cout<<"\n\n\t* TOTAL = "<<total;
    getch();
    }


//    	INTRODUCTION FUNCTION

void intro()
{
 clrscr();
       cout<<"\t%%      %%      ";
       cout<<"\n\t%%      %% %%%%%%% %%      %%%%%%  %%%%%% %%%%  %%%% %%%%%%%";
       cout<<"\n\t%%      %% %%      %%      %%      %%  %% %%  %%% %% %%       ";
       cout<<"\n\t%%  %%  %% %%%%%   %%      %%      %%  %% %%  %%% %% %%%%%      ";
       cout<<"\n\t%%  %%  %% %%      %%      %%      %%  %% %%      %% %%           ";
       cout<<"\n\t%%%%%%%%%% %%%%%%% %%%%%%% %%%%%%% %%%%%% %%      %% %%%%%%%     ";
       cout<<"\n\n\t\t\t        $$$$$$$$  $$$$$        ";
       cout<<"\n\t\t\t           $$     $   $      ";
       cout<<"\n\t\t\t           $$     $$$$$    ";

       cout<<"\n\n\n\t\t******** SHOP MANAGEMENT SYSTEM  *******";
       cout<<"\n\n\t\t\tBY  :-";
       
       cout<<"\n\n\t\t\t* Ashish Kudiyal"<<" (DELHI TECHNOLOGICAL UNIVERSITY)";
       cout<<" \n\n\n\t\t!!!!press 'ENTER' to continue:!!!! ";

       getch();

}
struct administrator     //structure used for verifying password
{
	char user_name[10];
	char password[10];
}admin;

void	assign_user()
{
	 clrscr();
	strcpy(admin.user_name, "ShopM");
	strcpy(admin.password, "12345");
}
int verify_password()
{       clrscr();
	char u_name[10];
	char u_pwd[10],temp[2];
	int x=1;
	cout<<"\n\n\n\n\n\n";
	cout<<"\n\t\t  *   Enter user name :";
	cin>>u_name;
	cout<<"\n\n\t\t  *   Enter Password : ";
	cin>>u_pwd;
	x=strcmp(admin.user_name,u_name);
	if (x==0)
	{
		x=strcmp(admin.password,u_pwd);
	}
	cin.getline(temp,2);
	return(x);

}

//    	ADMINSTRATOR MENU FUNCTION

void admin_menu()
{
  clrscr();
  char ch2;
  cout<<"\n\n\n";
  cout<<"\t\t%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
  cout<<"\t\t%            ***ADMIN MENU***              %"<<endl;
  cout<<"\t\t%                                          %"<<endl;
  cout<<"\t\t%    1.CREATE PRODUCT                      %"<<endl;

  cout<<"\t\t%                                          %"<<endl;
  cout<<"\t\t%    2.DISPLAY ALL PRODUCTS                %"<<endl;
  cout<<"\t\t%                                          %"<<endl;
  cout<<"\t\t%    3.QUERY                               %"<<endl;
  cout<<"\t\t%                                          %"<<endl;
  cout<<"\t\t%    4.MODIFY PRODUCT                      %"<<endl;
  cout<<"\t\t%                                          %"<<endl;
  cout<<"\t\t%    5.DELETE PRODUCT                      %"<<endl;
  cout<<"\t\t%                                          %"<<endl;
  cout<<"\t\t%    6.VIEW PRODUCT MENU                   %"<<endl;
  cout<<"\t\t%                                          %"<<endl;
  cout<<"\t\t%    7.BACK TO MAIN MENU                   %"<<endl;
  cout<<"\t\t%                                          %"<<endl;
  cout<<"\t\t%    *Please Enter Your Choice (1-7)       %"<<endl;
  cout<<"\t\t%                                          %"<<endl;
  cout<<"\t\t%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
  ch2=getche();
  switch(ch2)
  {
    case '1': clrscr();
	      write_product();
	      break;
    case '2': display_all();break;
    case '3':
	       int num;
	       clrscr();
	       cout<<"\n\n\t* Please Enter The Product No.: ";
	       cin>>num;
	       display_sp(num);
	       break;
      case '4': modify_product();break;
      case '5': delete_product();break;
      case '6': menu();
		getch();
      case '7': break;
      default:cout<<"\a";
   }
}

//    	THE MAIN FUNCTION OF PROGRAM

void main()
{
  char ch;
  intro();
  do

    {
	  clrscr();
	  cout<<"\n\n\n";
	  cout<<"\t\t  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
	  cout<<"\t\t  %                                  %"<<endl;
	  cout<<"\t\t  %                                  %"<<endl;
	  cout<<"\t\t  %          ***MAIN MENU***         %"<<endl;
	  cout<<"\t\t  %                                  %"<<endl;
	  cout<<"\t\t  %                                  %"<<endl;
	  cout<<"\t\t  %       01. CUSTOMER               %"<<endl;
	  cout<<"\t\t  %                                  %"<<endl;
	  cout<<"\t\t  %                                  %"<<endl;
	  cout<<"\t\t  %       02. ADMINISTRATOR          %"<<endl;
	  cout<<"\t\t  %                                  %"<<endl;
	  cout<<"\t\t  %                                  %"<<endl;
	  cout<<"\t\t  %       03. EXIT                   %"<<endl;
	  cout<<"\t\t  %                                  %"<<endl;
	  cout<<"\t\t  %                                  %"<<endl;
	  cout<<"\t\t  % Please Select Your Option (1-3): %"<<endl;
	  cout<<"\t\t  %                                  %"<<endl;
	  cout<<"\t\t  %                                  %"<<endl;
	  cout<<"\t\t  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
	  ch=getche();
	  switch(ch)
	  {
		 case '1': clrscr();
			   place_order();
			   getch();
			   break;
		  case '2':  int p;
			     assign_user();
			     p=verify_password();
			    if(p==0)
			    {
			     admin_menu();
			     }
			     else
			    {
			     cout<<"\n\n\n\t\t***!!! You are Not a Valid User !!!***";
			     getch();
			    }
			    break;
		  case '3':exit(0);
		  default :cout<<"\a";
	}
    }while(ch!='3');

}

//    			END OF PROJECT


