#include<iostream>
#include<fstream>
#include<stdio.h>
#include<string.h>
#include<windows.h>

using namespace std;
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
 {
  cout<<"Select account no. : ";
  cin>>accno;
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
 int cmppass(char pas[20])
 {
  int a=strcmp(pas,pass);
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
void accdel(long accn)
{
 fstream acc,nw;
 acc.open("accounts.dat",ios::binary|ios::in);
 nw.open("new.dat",ios::binary|ios::app);
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
 remove("accounts.dat");
 rename("new.dat","accounts.dat");
}

int main()
{

ofstream file("accounts.dat",ios::binary|ios::out);
person A;
A.getdetail();
file.write((char*)&A,sizeof(A));
file.close();

 return 0;
}
