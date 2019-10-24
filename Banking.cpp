#include<iostream>
#include<fstream>
#include<stdio.h>
#include<cstdio>
#include<string.h>
#include<windows.h>

using namespace std;
int check(long accno);
class Accounts
{
 long accno;
 char pass[20];
 long double amount;
 char lasttran[10];
protected:
 char accname[25];
public:
 Accounts()
 {
  amount=0;
  strcpy(lasttran,"none");
 }
 long getacno()
 {
  return accno;
 }
 char* getname()
 {
  return accname;
 }
 char* getpass()
 {
  return pass;
 }
 long double getamt()
 {
  return amount;
 }
 void getdata()
 { ac:
  cout<<"Select account no. : ";
  cin>>accno;
  if(!check(accno))
  {
   goto ac;
  }
  cin.ignore();
  again:
  cout<<"Enter account name: ";
  cin.getline(accname,25);
  if(accname[0]>='0'&&accname[0]<='9')
  {
   cout<<endl<<"Account name can not begin with a digit! "<<endl;
   goto again;
  }
  cin.ignore();
  setp:
  cout<<"Set a strong password: ";
  cin>>pass;
  if(strlen(pass)<8)
  {
   cout<<endl<<"Password too short!"<<endl;
   goto setp;
  }
  char repass[20];
  cout<<"Re enter password: ";
  cin>>repass;
  if(strcmp(repass,pass))
  {
   cout<<endl<<"Passwords do not match! \n please re-Enter \n";
   goto setp;
  }

 }
 void showdet()
 {
  cout<<"Account number: "<<accno<<endl;
  cout<<"Account name: "<<accname<<endl;
  cout<<"Current amount: "<<amount<<endl;

 }
 void withdraw()
 {long amt;
  cout<<"How much amount do you want to withdraw? :";
  cin>>amt;
  if(amount-amt>0)
  {amount-=amt;
  cout<<"Transaction was successful, remaining balance= "<<amount;}
  else{cout<<"Not sufficient balance in the account! ";cout<<endl<<"Amount: "<<amount<<endl;}

 }
 void setpass(char pas[20])
 {
  strcpy(pass,pas);

 }
 void setlas(char state[4])
 {
  strcpy(lasttran,state);
 }
 int cmppass(char pas[20])
 {
  int a=strcmp(pass,pas);
  return !a;
 }
 void welcome()
 {
  cout<<endl<<"Welcome "<<accname<<endl;
 }
 void deposit()
 {long amt;
  cout<<"How much money do you want to deposit? :";
  cin>>amt;
  amount+=amt;
  cout<<"Transaction was successful,balance= "<<amount;

 }
 int cmplasttran(char state[4])
 {
  int r=strcmp(state,lasttran);
  return !r;
 }
};
class person:public Accounts
{
 char name[25];
 char desig;

public:
person()
{
 strcpy(name,accname);
}
 void getdetail()
 {
  getdata();
  des:
  cout<<"Enter Designation(A/N): ";
  cin>>desig;
  if((desig!='A' && desig!='a') && (desig!='N' && desig!='n'))
  {
   cout<<endl<<"please enter A/N "<<endl;
   goto des;
  }

 }
char deg()
{
 return desig;
}
}S;
int check(long accno)
{
 ifstream chek("accounts.dat",ios::binary|ios::in);
   person c;
  do
  {
   chek.read((char*)&c,sizeof(c));
   if(c.getacno()==accno)
   {
    cout<<endl<<"This account no. already exists! please choose another one! \n";
    Sleep(3000);
    return 0;
   }
  }while(chek);
  chek.close();
  return 1;
}

void accdel(long accn)
{
 fstream acc, nw;
 acc.open("accounts.dat",ios::binary|ios::in|ios::out);
 nw.open("new.dat",ios::binary|ios::app|ios::in);
 person p;
 do
 {
 acc.read((char*)&p,sizeof(p));
 if(p.getacno()==accn)
 {
 }
 else
 {

  nw.write((char*)&p,sizeof(p));

 }


 }while(acc);
 acc.close();
 nw.close();
 remo:
 int rem=remove("accounts.dat");
 if(rem!=0){goto remo;}
 rena:
 int ren=rename("new.dat","accounts.dat");
 if(ren!=0){goto rena;}
}
void listup()
 {

person p;
fstream i("accounts.dat",ios::binary|ios::in);
ofstream o("accounts.txt",ios::out);

do
{
 i.read((char*)&p,sizeof(p));
 o<<endl<<"Account no "<<p.getacno()<<endl;
 o<<"Name: "<<p.getname()<<endl;
}while(i);
i.close();
o.close();

 }
int main()
{
 int choice;
 start:

 cout<<"1.Admin login"<<endl;
 cout<<"2.User login"<<endl;
 cout<<"3.Terminate program "<<endl;
 cout<<"Enter choice: ";cin>>choice;
 if(choice==1)
 {long acc;person A;
 fstream a;
  a.open("accounts.dat",ios::in|ios::binary);
  cout<<endl<<"Enter Account number: ";cin>>acc;
  bool found=true;
  do
  {
   a.read((char*)&A,sizeof(A));
   if(acc==A.getacno()&& (A.deg()=='A' || A.deg()=='a') )
   {
    char p[20];found=false;
    A.welcome();
    cout<<endl<<"Enter password: ";cin>>p;
    if(!strcmp(p,A.getpass()))
    {int choice=0;
    adstart:
      cout<<endl<<"What do you want to do? ";
      cout<<endl<<"1.Add new account "<<endl;
      cout<<"2.Delete an account "<<endl;
      cout<<"3.Show all accounts "<<endl;
      cout<<"4.Exit to main menu "<<endl;
      cin>>choice;
      if(choice==1)
      {
       person P;
       fstream ac("accounts.dat",ios::binary|ios::app);
       P.getdetail();
       ac.write((char*)&P,sizeof(P));
       ac.close();
       listup();
       cout<<endl<<"Account added successfully! "<<endl;
       P.showdet();
       Sleep(3000);
       system("CLS");
      goto adstart;
      }
      else if(choice==2)
      {long acn;bool found=true;person P;a.close();
       cout<<endl<<"Enter account no you want to delete: ";cin>>acn;
       ifstream file("accounts.dat",ios::binary|ios::in);
       do
       {
        file.read((char*)&P,sizeof(P));
        if(acn==P.getacno())
        {found=false;
        P.showdet();
        file.close();
        cout<<endl<<"Are you sure you want to delete this account?(y/n): ";
        char o;
        cin>>o;
        if(o=='y' || o=='Y')
        {
         accdel(acn);
         cout<<endl<<"Account deleted successfully! ";
         listup();
         Sleep(3000);
       system("CLS");
         goto adstart;
        }
         else{cout<<endl<<"Account not deleted! ";Sleep(3000);
       system("CLS");goto adstart;}
        }

       }while(file&&found);

       if(found)
       {cout<<endl<<"No such account could be found! ";Sleep(3000);
       system("CLS");goto adstart;}

      }
      else if(choice==4)
      {
       system("CLS");
       goto start;
      }
      else if(choice==3)
      {char word;
      ifstream lfile("accounts.txt");
      do
      {
       lfile.get(word);
       cout<<word;
      }while(lfile);
      lfile.close();
      }
      Sleep(7000);
      system("CLS");
      goto adstart;
    }
   else{cout<<"Wrong password entered!";Sleep(3000);
       system("CLS");goto start;}
   }
  }while(found&&a);
  a.close();
if(found)
{
  cout<<"No such account could be found! ";
Sleep(3000);
system("CLS");
goto start;}
 }
 else if(choice==2)
 {
  long ac;person A;bool found=true;
  cout<<endl<<"Enter your Account no: ";
  cin>>ac;
  fstream user("accounts.dat",ios::binary|ios::in);
  do
  {
   user.read((char*)&A,sizeof(A));
   if(ac==A.getacno()&&'N'==A.deg())
   {
    user.close();
    found=false;
    char p[20];
    A.welcome();
    cout<<"Enter password: ";
    cin>>p;
    if(!strcmp(p,A.getpass()))
    {int choice=0;
    userstart:
     cout<<endl<<"What would you like to do? "<<endl;
     cout<<"1.Add amount "<<endl;
     cout<<"2.Withdraw amount "<<endl;
     cout<<"3.Show amount "<<endl;
     cout<<"4.Change password "<<endl;
     cout<<"5.Exit to main menu "<<endl;
     cin>>choice;
     if(choice==1)
     {
      A.deposit();
      accdel(ac);
      ofstream newa("accounts.dat",ios::binary|ios::app);
      newa.write((char*)&A,sizeof(A));
      newa.close();
      Sleep(6000);
       system("CLS");
      goto userstart;
     }
     else if(choice==2)
     {
      A.withdraw();
      accdel(ac);
      ofstream newa("accounts.dat",ios::binary|ios::app);
      newa.write((char*)&A,sizeof(A));
      newa.close();
      Sleep(6000);
       system("CLS");
      goto userstart;
     }
     else if(choice==3)
     {
      cout<<"Amount in account is :"<<A.getamt();
      Sleep(3000);
       system("CLS");
      goto userstart;
     }
     else if(choice==4)
     {char oldp[20];char newp[20];
     cout<<endl<<"Enter current password: ";
     cin>>oldp;
     if(A.cmppass(oldp))
     {
      cout<<endl<<"Set New password: ";
      cin>>newp;
      cout<<endl<<"Re- enter new password: :";
      cin>>oldp;
      if(!strcmp(oldp,newp))
      {

       accdel(ac);
       A.setpass(newp);
       ofstream newa("accounts.dat",ios::binary|ios::app);
      newa.write((char*)&A,sizeof(A));
      newa.close();
      cout<<endl<<"Password updated successfully! "<<endl;
      Sleep(6000);
       system("CLS");
      goto userstart;

      }
      else{cout<<endl<<"The password doesn't match! ";
      Sleep(6000);
      system("CLS");
       goto userstart;
      }
     }
      else{
       cout<<endl<<"Incorrect password entered! ";

       Sleep(6000);
       system("CLS");
       goto userstart;
      }

     }
     else if(choice==5)
     {

       system("CLS");
       goto start;
     }
    }
   else{cout<<endl<<"Wrong password entered! "<<endl;Sleep(3000);
       system("CLS");goto start;}
   }
  }while(found&&user);
  if(found)
  {user.close();
   cout<<endl<<"No such user account found! "<<endl;
   Sleep(3000);
       system("CLS");
   goto start;
  }

 }
 else if(choice==3)
 {
  exit(0);
 }
 else{cout<<endl<<"Wrong input!" ;Sleep(2000);system("CLS");goto start;}

 return 0;
}
