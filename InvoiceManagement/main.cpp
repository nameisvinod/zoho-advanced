#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#define c_txt "c.txt"
#define in_txt "in.txt"
#define it_txt "it.txt"
#define init_txt "init.txt"
using namespace std;


//============================== customer ====================================

class Customer{
	int id;
	char name[20];
	public:
		Customer(){};
		void setId(int id){
			this->id = id;
		}
		void setName(char name[]){
			strcpy(this->name, name);
		}
		int getId(){
			return id;
		}
		string getName(){
			return string(name);
		}
};

class CustomerView{
	public:
		void printCustomerDetails(int id,string name){
			cout<<"ID : "<<id<<endl;
			cout<<"Name :"<<name<<endl;
		}
};


class CustomerController
{
	Customer model;
	CustomerView view;
	public:
		CustomerController(){};
		CustomerController(Customer model, CustomerView view):model(model), view(view){};
		void setId(int id){
			model.setId(id);
		}
		void setName(char name[]){
			model.setName(name);
		}
		int getId(){
			return model.getId();
		}
		string getName(){
			return model.getName();
		}
		void printCustomerDetails(){
			view.printCustomerDetails(model.getId(), model.getName());
		}
};

Customer retrieveCustomerDetails(){
	int id;
	char name[20];
	Customer customer;

	cout<<"enter id: ";
	cin>>id;
	cout<<"Enter name : ";
	cin.ignore();
	cin.getline(name, 20);
	customer.setId(id);
	customer.setName(name);
	
	return customer;
}
//============================== customer ====================================

//============================== item ====================================

class Item
{
	int id;
	char name[20];
	public:
		void setId(int id){
			this->id = id;
		}
		void setName(char name[]){
			strcpy(this->name, name);
		}
		int getId(){
			return id;
		}
		string getName(){
			return string(name);
		}
};
class ItemView{
	public:
		void printItemDetails(int id,string name){
			cout<<"----------------Item Details------------"<<endl;
			cout<<"ID : "<<id<<endl;
			cout<<"Name :"<<name<<endl;
		}
};
class ItemController
{
	Item model;
	ItemView view;
public:
	ItemController(){};
	ItemController(Item model, ItemView view):model(model), view(view){}
	void setId(int id){
			model.setId(id);
		}
		void setName(char name[]){
			model.setName(name);
		}
		int getId(){
			return model.getId();
		}
		string getName(){
			return model.getName();
		}
		void printItemDetails(){
			view.printItemDetails(model.getId(), model.getName());
		}
	
};
Item retrieveItemDetails(){
	int id;
	char name[20];
	Item item;

	cout<<"enter id: ";
	cin>>id;
	cout<<"Enter name : ";
	cin.ignore();
	cin.getline(name, 20);
	item.setId(id);
	item.setName(name);
	
	return item;
}
//============================== item ====================================


//============================== invoice ====================================
class Invoice
{
		int id;
		int cId;
		char date[20];
	public:
		void setId(int id){
			this->id = id;
		}
		void setDate(char date[]){
			strcpy(this->date, date);
		}
		void setCId(int cId){
			this->cId = cId;
		}
		int getId(){
			return id;
		}
		string getDate(){
			return string(date);
		}
		int getCId(){
			return cId;
		}
};
class InvoiceView
{
	public:
		void printInvoiceDetails(int id,string date, int Cid){
			cout<<"ID : "<<id<<endl;
			cout<<"CustomerID : "<<Cid<<endl;
			cout<<"Date :"<<date<<endl;
		}
};
class InvoiceController
{
	Invoice model;
	InvoiceView view;
	public:
		InvoiceController(){};
		InvoiceController(Invoice model, InvoiceView view):model(model), view(view){};
		void setId(int id){
			model.setId(id);
		}
		void setName(char* date){
			model.setDate(date);
		}
		void setCId(int id){
			model.setCId(id);
		}
		int getId(){
			return model.getId();
		}
		int getCId(){
			return model.getCId();
		}
		string getDate(){
			return model.getDate();
		}
		void printInvoiceDetails(){
			view.printInvoiceDetails(model.getId(), model.getDate(), model.getCId());
		}
};

Invoice retrieveInvoiceDetails(){
	int id, cid;
	char date[20];
	Invoice invoice;

	cout<<"enter id: ";
	cin>>id;
	cout<<"enter customer id: ";
	cin>>cid;
	cout<<"Enter date : ";
	cin.ignore();
	cin.getline(date, 20);
	invoice.setId(id);
	invoice.setCId(cid);
	invoice.setDate(date);
	
	return invoice;
}
class InvoiceItem{
		int invoiceId;
		int itemId;
	public:
		InvoiceItem(){};
		InvoiceItem(int invoiceId,int itemId):invoiceId(invoiceId), itemId(itemId){};
		int getInvoiceId(){
			return invoiceId;
		}
		int getItemId(){
			return itemId;
		}
};
//============================== invoice ====================================

void addCustomer(){
	Customer model = retrieveCustomerDetails();
	CustomerView view;
	CustomerController cc(model, view);

	fstream f;
	f.open(c_txt,ios::out |ios::binary| ios::app );
	f.write((char* )(&cc), sizeof(cc));
	f.close();
}
void addInvoice(){
	Invoice model = retrieveInvoiceDetails();
	InvoiceView view;
	InvoiceController ic(model, view);

	fstream f;
	f.open(in_txt,ios::out |ios::binary| ios::app );
	f.write((char* )(&ic), sizeof(ic));
	f.close();
}
int addItem(){
	Item model = retrieveItemDetails();
	ItemView view;
	ItemController cc(model, view);

	fstream f;
	f.open(it_txt,ios::out |ios::binary| ios::app );
	f.write((char* )(&cc), sizeof(cc));
	f.close();
	return cc.getId();
}
void addItemsToInvoice(){
	int invoiceId;
	cout<<"Enter invoice Id : ";
	cin>>invoiceId;
	cout<<"Item details : "<<endl;
	int itemId = addItem();

	// cout<<itemId<<endl;
	InvoiceItem it(invoiceId, itemId);
	fstream f;
	f.open(init_txt,ios::out |ios::binary| ios::app );
	f.write((char* )(&it), sizeof(it));
	f.close();
}
void displayCustomers(){
	fstream f;
	CustomerController cc;
	Customer model;
	cout<<"----------------Customer Details------------"<<endl;

	f.open(c_txt, ios::in|ios::binary);
	while(f.read((char *)&cc, sizeof(cc))){
		cc.printCustomerDetails();
		cout<<endl;
	}
	f.close();
}
void displayInvoices(int getId){
	fstream f;
	InvoiceController cc;
	Invoice model;
	int id;
	cout<<"----------------Invoice Details------------"<<endl;

	if(getId){
		cout<<"Enter Customer Id:"<<endl;
		cin>>id;
		cout<<"Invoice deatils for cutsomer : "<< id <<endl;
	}
	f.open(in_txt, ios::in|ios::binary);
	int done = false;
	while(f.read((char *)&cc, sizeof(cc))){
		if(getId && id==cc.getCId()){
			done = true;
			cc.printInvoiceDetails();
			cout<<endl;
		}
		if(!getId){
			cc.printInvoiceDetails();
			cout<<endl;
		}
	}
	if(getId && !done)
		cout<<"No invoices for given customer"<<endl;
	f.close();
}
void displayInvoiceDetails(){
	InvoiceItem it;
	ItemController ic;
	fstream f1;
	int invoiceId;
	cout<<"Enter invoice Id :";
	cin>>invoiceId;
	f1.open(init_txt, ios::in|ios::binary);
	while(f1.read((char*)&it, sizeof(it))){
		if(invoiceId == it.getInvoiceId()){
			int itemId = it.getItemId();
			fstream f2;
			f2.open(it_txt, ios::in|ios::binary);
			while(f2.read((char*)&ic, sizeof(ic))){
				if(ic.getId()==itemId){
					ic.printItemDetails();
				}
			}
			f2.close();
		}
	}
	f1.close();
}
void displayMenu(){
	int ch;
	cout<<"---------------WELCOME TO INVOICE------------------------"<<endl;
	cout<<"--------------------MAIN MENU--------------------"<<endl;
	cout<<"1.ADD CUSTOMER\n2.ADD INVOICE\n3.ADD ITEMS TO INVOICE\n";
	cout<<"4.LIST CUSTOMERS\n5.LIST ALL INVOICES \n6.LIST INVOICES OF A CUSTOMER\n";
	cout<<"7.DETAILS OF AN INVOICE \n8.EXIT"<<endl;
	do{
		cout<<"\nEnter Chioce : ";
		cin>>ch;
		switch(ch){
			case 1: addCustomer(); break;
			case 2: addInvoice(); break;
			case 3: addItemsToInvoice(); break;
			case 4: displayCustomers(); break;
			case 5: displayInvoices(false); break;
			case 6: displayInvoices(true); break;
			case 7: displayInvoiceDetails(); break;
			// case 8: return;
			default: ch=9;break;	 
		}
	}while(ch<8);
	cout<<"----------------------END OF TRANSACTIONS--------------------"<<endl;
}
//============================== main ====================================

int main(int argc, char const *argv[])
{
	displayMenu();
	return 0;
}