#include<iostream>
#include<fstream>
#include<stdio.h>
#include<string.h>
#include<windows.h>

using namespace std;
class Accounts
{
 long accno;
 char accname[25];
 char pass[20];
 long double amount;
 char lasttran[10];
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
  cout<<"Enter account name: ";
  cin.getline(accname,25);
  cin.ignore();
  cout<<"Set a strong password: ";
  cin>>pass;

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
 int c;
 person(){c=0;}
 void getdetail()
 {
  cout<<"Enter name: ";
  cin>>name;
  cout<<"Enter Designation(A/N): ";
  cin>>desig;
  getdata();
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
  if(p.c==0)
  {
  nw.write((char*)&p,sizeof(p));
  p.c+=1;
  }
 }


 }while(acc);
 acc.close();
 nw.close();
 remove("accounts.dat");
 rename("new.dat","accounts.dat");
}int main()
{

ofstream file("accounts.dat",ios::binary|ios::out);
person A;
A.getdetail();
file.write((char*)&A,sizeof(A));
file.close();

 return 0;
}
