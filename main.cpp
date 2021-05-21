#include<fstream>
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<dos.h>
#include<windows.h>
using namespace std;

class Directory{
    char name[20];
    long long int num;
    char address[50];
    public:
    void enter(){
        cout<<"Enter name: "<<endl;
        cin>>name;
        cout<<"Enter number: "<<endl;
        cin>>num;
        cout<<"Enter address: "<<endl;
        cin>>address;
    }
    void show(){
        cout<<"Name: "<<name<<endl;
        cout<<"Number: "<<num<<endl;
        cout<<"Address: "<<address<<endl;
    }
    char *rname(){
        return name;
    }
};

void display(){
    ifstream fin;
    fin.open("phonedir.dat",ios::binary|ios::in);
    Directory r;
    while(fin.read((char*)&r,sizeof(r))){
        r.show();
    }
    fin.close();
}

void searchn(){ //name search
    ifstream fin;
    Directory r;
    char name[20];
    int found=0;
    fin.open("phonedir.dat",ios::binary|ios::in);
    cout<<"Enter name to be searched: ";
    cin>>name;
    while(fin.read((char*)&r,sizeof(r))){
        if(strcmp(name, r.rname())==0){
            cout<<"Record Found"<<endl<<endl;
            r.show();
            found++;
        }
    }
    if(!found){
        cout<<name<<endl<< "Not found "<<endl;
    }
    fin.close();
}


void insrec(){
    char choice;
    ofstream fout;
    fout.open("phonedir.dat",ios::binary|ios::app);
    Directory r;
    do{
        cout<<"Enter the details for new record"<<endl;
        r.enter();
        fout.write((char*)&r,sizeof(r));
        cout<<"Do you want to enter more records(y/n): "<<endl;
        cin>>choice;
    }while(tolower(choice)=='y');
    fout.close();
}

void delrec(){
    char delname[30];            
    ifstream fin;
    ofstream fout;
    fin.open("phonedir.dat",ios::binary|ios::in);
    fout.open("temp.dat",ios::binary|ios::app);
    Directory r;
    int del=0;
    cout<<"Enter the name of the record you want to delete: ";
    cin>>delname;
    while(fin.read((char*)&r,sizeof(r))){

        if((strcmp(delname,r.rname()))!=0){
            fout.write((char*)&r,sizeof(r));
        }else{
            del++;
        }
        if(del)
            cout<<"The record has been deleted";
        fin.close();
        fout.close();
        remove("phonedir.dat");
        rename("temp.dat","phonedir.dat");
    }
}

int main(){
    int ch;
    int opt;
    char pass[20];
    cout<<"********* TELEPHONE DIRECTORY *********"<<endl;
    cout<<endl<<endl;
    cout<<"SELECT YOUR IDENTITY"<<endl;
    cout<<"1.VIEWER"<<endl;
    cout<<"2.ADMINISTRATOR"<<endl;
    cout<<"CHOICE:  ";
    cin>>opt;
    if(opt==1){
        do{
            cout<<endl<<endl;
            cout<<"What would you like to do"<<endl;
            cout<<"1. Search record\n2. Display record\n3. Exit"<<endl;
            cout<<"Enter choice: ";
            cin>>ch;
            switch(ch){
            case 1:
                searchn();
                break;
            case 2:
                display();
                cout<<endl;
                break;
            default:
                exit(0);
            }
        }while(ch!=3);
    }

    if(opt==2){
        do{
            cout<<"What would you like to do"<<endl;
            cout<<"1. Add\n2. Delete\n3. Search\n4. Display\n5. Exit"<<endl;
            cout<<"Enter choice: ";
            cin>>ch;
            switch(ch){
            case 1:
                insrec();
                break;
            case 2:
                delrec();
                cout<<endl;
                break;
            case 3:
                searchn();
                cout<<endl;
                break;
            case 4:
                display();
                cout<<endl;
                break;
            default:
                exit(0);
            }
        }while(ch!=5);
    }
}
