#include<iostream>
#include<ctime>
#include<stdlib.h>
#include<cstring>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <unistd.h>
#include<vector>

using namespace std;
string first_name,middle_name,last_name;
class customer {
  public :
  

 // capcha verification 
  int cus_access=0;
 
  void  capcha(){

   srand(static_cast<unsigned int>(time(nullptr)));
    string define = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";
    char system_capcha[7], user_capcha[7]; 

    for (int i = 0; i < 6; i++) { 
        int random = rand() % define.length(); 
        system_capcha[i] = define[random];
    }
    system_capcha[6] = '\0'; // Null-terminate the string.
   cout<<"!!prove you are human !!"<<endl;
   cout << "Your captcha is: " << system_capcha << endl;

    cout << "Enter your captcha: ";
    for (int j = 0; j < 6; j++) {
        cin >> user_capcha[j];
    }
    user_capcha[6] = '\0'; // Null-terminate the user's input.

   //condition chck
    if (strcmp(user_capcha,system_capcha)==0) { 
        
        cus_access=1;
        cout << "Verification successful." << endl;
        cout<<endl<<"--------------------------------------------------------------"<<endl;

    } else {
        cout << "Verification failed." << endl;
        cout<<endl<<"--------------------------------------------------------------"<<endl;
  }





 }
};

class owner  
 {
 private:
    string system_id="B"; //testing id & password
    string system_password="B";
    string user_id ,user_password;
    public:
    int own_access=0;
    void getdata (){
        cout<<"Enter user name : ";
        cin>>user_id;
        cout<<"Enter password : ";
        cin>>user_password;
    }
    
    void login (){
        if (  system_id == user_id && system_password == user_password)
        {   own_access=1;
            // system("cls");
            cout<<"ADMIN LOGIN SUCCESSFUL !!"<<endl;
            cout<<endl<<"--------------------------------------------------------------"<<endl;
            
        }
        else
       {  // system("cls");
            cout<<"ADMIN LOGIN FAILED !!"<<endl;
            cout<<endl<<"--------------------------------------------------------------"<<endl;
            
        }
        
    }
};

class Bill{
 private:
 string Item;
 int Rate, Quantity;
 public:
 Bill():Item(""), Rate(0), Quantity(0){ }
 
 void setItem(string item){
 Item = item;
 }
 
 void setRate(int rate){
 Rate = rate;
  }

 void setQuant(int quant){
 Quantity = quant;
 }

 string getItem(){
 return Item;
 }

 int getRate(){
 return Rate;
 }

 int getQuant(){
 return Quantity;
 }

};

void addItem(Bill b){
 bool close = false;
 while(!close){
 system("cls");
 int choice;
 cout<<"\t1.Add."<<endl;
 cout<<"\t2.close."<<endl;
 cout<<"\tEnter Choice: ";
 cin>>choice;

 if(choice==1){
 system("cls");
 string item;
 int rate, quant;

 cout<<"\tEnter Item Name:(allcaps): ";
 cin>>item;
 b.setItem(item);

 cout<<"\tEnter Rate Of Item: ";
 cin>>rate;
 b.setRate(rate);

 cout<<"\tEnter Quantity Of Item: ";
 cin>>quant;
 b.setQuant(quant);









 ofstream out("Bill.txt", ios::app);
 if(!out){
	cout<<"\tError: File Can't Open!"<<endl;
 }
 else{
 out<<b.getItem()<<" : "<<b.getRate()<<" : "<<b.getQuant()<<endl;
 
 out.close();

 }
 cout<<"\tItem Added Successfuly"<<endl;
 sleep(2);
 }

 else if(choice == 2){
	
 close = true;
 cout<<"back to customer menu"<<endl;
 sleep(2);

 }
 
 }
} 

void shop_products(){
  
	int Total_Bill=0;
 bool close = false;
 while(!close){
 system("cls");
 int choice;
 cout<<"\t1.Add Bill."<<endl;
 cout<<"\t2.Close Session."<<endl;
 cout<<"\tEnter Choice : ";
 cin>>choice;
 ofstream out_print("Print.txt" , ios::app);

 if(choice==1){
  
 string item;
 int quant;
 cout<<"\tEnter Item: ";
 cin>>item;
 cout<<"\tEnter Quantity: ";
 cin>>quant;

 ifstream in("Bill.txt");
 ofstream out("Billtemp.txt");
 ofstream out_print("Print.txt" , ios::app);


 string line;
 bool found = false;

 while(getline(in, line)){
 stringstream ss;
 ss<<line;
 string itemName;
 int itemRate, itemQuant;
 char delimiter;
 ss>>itemName>>delimiter>>itemRate>>delimiter>>itemQuant;

 if(item == itemName){
 found = true;
 if(quant <= itemQuant){
 int amount = itemRate * quant;
  Total_Bill+=amount ;
 cout<<"\t Item | Rate | Quantity | Amount |total bill"<<endl;
 cout<<"\t"<<itemName<<"\t "<<itemRate<<"\t "<<quant<<"\t "<<amount<<"\t "<<Total_Bill<<endl;
 int newQuant = itemQuant - quant; 
 itemQuant = newQuant;
 

 out<<itemName<<" : "<<itemRate<<" : "<<itemQuant<<endl;
 out_print<<itemName<<" : "<<itemRate<<" : "<<quant<<" : "<<amount<<endl;
 
 sleep(5);
 }
 else{
 cout<<"\tSorry, "<<item<<" is not sufficient!"<<endl;
 sleep(2);
 }
 }

 else{
 out<<line<<endl;
 }	
 }

 out.close();
 in.close();
 out_print.close();
 remove("Bill.txt");
 rename("Billtemp.txt","Bill.txt");
 
 if(!found){
 cout<<"\tItem Not Available!"<<endl;
 sleep(2);
 }
 

 }


 else if(choice ==2){ 
 system("cls");
 close = true;

 cout<<"return to customer menu"<<endl;
 sleep(2);

 }

 }
}

void showProducts(){
 system("cls");
 ifstream in("Bill.txt");

 string line;
 bool found = false;
 cout<<"\t|        PRODUCTS NAME         |   RATE   | QUANTITY |"<<endl;
 cout<<"\t------------------------------------------------------"<<endl;

 while(getline(in, line)){
 stringstream ss;
 ss<<line;
 string itemName;
 int itemRate, itemQuant;
 char delimiter;
 ss>>itemName>>delimiter>>itemRate>>delimiter>>itemQuant;
 
 string str_ItemName = itemName + string(30 - itemName.length(), ' ');
 string str_Rate = to_string(itemRate) + string(10 - to_string(itemRate).length(), ' ');
  string str_Quant = to_string(itemQuant) + string(10 - to_string(itemQuant).length(), ' ');


 cout<<"\t|"<<str_ItemName<<"|"<<str_Rate<<"|"<<str_Quant<<"|"<<endl;
 
 
 }
  cout<<"\t------------------------------------------------------"<<endl;

 char e;
 while(e!='E')
 {cout<<"press 'E' to exit ";
 cin>>e;
 }
 in.close(); 

}

void printBill(){
 
 string fullName = first_name +" "+ middle_name +" "+ last_name;
 fullName= fullName + string(46 - fullName.length(), ' ');

 system("cls");
 
 ifstream in("Print.txt");
 string line;
 bool found = false;
 cout<<"\t-----------------------------------------------------------------"<<endl;
 cout<<"\t|                                                               |"<<endl;
 cout<<"\t|                        * APNA BAZAAR *                        |"<<endl;
 cout<<"\t|                                                               |"<<endl;
 cout<<"\t|---------------------------------------------------------------|"<<endl;
 cout<<"\t| OWNER NAME : BHAVESH MOHAN PATIL                              |"<<endl;
 cout<<"\t|---------------------------------------------------------------|"<<endl;
 cout<<"\t| CUSTOMER NAME : ";cout<<fullName<<"|"<<endl;
 cout<<"\t|---------------------------------------------------------------|"<<endl;
 cout<<"\t|                        * YOUR ORDER *                         |"<<endl;
 cout<<"\t|---------------------------------------------------------------|"<<endl;
 cout<<"\t|        PRODUCTS NAME         |   RATE   | QUANTITY |  AMOUNT  |"<<endl;
 cout<<"\t|---------------------------------------------------------------|"<<endl;
 int Total_Bill=0;
 while(getline(in, line)){
 stringstream ss;
 ss<<line;
 string itemName;
 int itemRate, itemQuant,Amount;
 char delimiter;
 ss>>itemName>>delimiter>>itemRate>>delimiter>>itemQuant>>delimiter>>Amount;
 
 
 
 Total_Bill+=Amount ;
 string str_ItemName = itemName + string(30 - itemName.length(), ' ');
 string str_Rate = to_string(itemRate) + string(10 - to_string(itemRate).length(), ' ');
 string str_Quant = to_string(itemQuant) + string(10 - to_string(itemQuant).length(), ' ');
 string str_Amount = to_string(Amount) + string(10 - to_string(Amount).length(), ' ');
 //string str_Total_Bill = to_string(Total_Bill) + string(10 - to_string(Total_Bill).length(), ' ');
 
 cout<<"\t|"<<str_ItemName<<"|"<<str_Rate<<"|"<<str_Quant<<"|"<<str_Amount<<"|"<<endl;
 
 
 }
 string str_Total_Bill = to_string(Total_Bill) + string(10 - to_string(Total_Bill).length(), ' ');
  cout<<"\t|---------------------------------------------------------------|"<<endl;
  cout<<"\t|                  TOTAL BILL  =                     |";cout<<str_Total_Bill<<"|"<<endl;
  cout<<"\t|---------------------------------------------------------------|"<<endl;
  cout<<"\t|        THANKS FOR SHOPPING !!  PLEASE VISIT AGAIN !!          |"<<endl;
  cout<<"\t-----------------------------------------------------------------"<<endl;



 char e;
 while(e!='E')
 {cout<<"press 'E' to exit ";
 cin>>e;
 }
 in.close(); 


}

void deleteProducts(){
  
  struct Product {
    string name;
    int quantity;
    double price;
   };

   
    string file_path = "Bill.txt";
    vector<Product> products;

    // Read the file and store product data in a vector
    ifstream file(file_path);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            Product product;
            char delimitor;
            ss >> product.name >>delimitor>> product.price >>delimitor>> product.quantity;
            if (product.quantity > 0) {
                products.push_back(product);
            }
        }
        file.close();
       } else {
        cerr << "Unable to open file." << endl;
        sleep(3);
    }

    // Write the updated product data back to the file
    ofstream outfile(file_path);
    if (outfile.is_open()) {
        for (const Product& product : products) {
            outfile << product.name << " : " << product.price << " : " << product.quantity << endl;
        }
        outfile.close();
        cout << "Rows with zero quantity removed successfully." << endl;
        sleep(3);
    } else {
        cerr << "Unable to write to file." << endl;
        sleep(2);
    }

  
}
 
void printBillFile(){
 
 string fullName = first_name +" "+ middle_name +" "+ last_name;
 fullName= fullName + string(46 - fullName.length(), ' ');


 ifstream in("Print.txt");
 ofstream out(fullName, ios::out);
 string line;
 bool found = false;
  out<<"\t-----------------------------------------------------------------"<<endl;
  out<<"\t|                                                               |"<<endl;
  out<<"\t|                        * APNA BAZAAR *                        |"<<endl;
  out<<"\t|                                                               |"<<endl;
  out<<"\t|---------------------------------------------------------------|"<<endl;
  out<<"\t| OWNER NAME : BHAVESH MOHAN PATIL                              |"<<endl;
  out<<"\t|---------------------------------------------------------------|"<<endl;
  out<<"\t| CUSTOMER NAME : ";cout<<fullName<<"|"<<endl;
  out<<"\t|---------------------------------------------------------------|"<<endl;
  out<<"\t|                        * YOUR ORDER *                         |"<<endl;
  out<<"\t|---------------------------------------------------------------|"<<endl;
  out<<"\t|        PRODUCTS NAME         |   RATE   | QUANTITY |  AMOUNT  |"<<endl;
  out<<"\t|---------------------------------------------------------------|"<<endl;
 int Total_Bill=0;
 while(getline(in, line)){
 stringstream ss;
 ss<<line;
 string itemName;
 int itemRate, itemQuant,Amount;
 char delimiter;
 ss>>itemName>>delimiter>>itemRate>>delimiter>>itemQuant>>delimiter>>Amount;
 
 
 
 Total_Bill+=Amount ;
 string str_ItemName = itemName + string(30 - itemName.length(), ' ');
 string str_Rate = to_string(itemRate) + string(10 - to_string(itemRate).length(), ' ');
 string str_Quant = to_string(itemQuant) + string(10 - to_string(itemQuant).length(), ' ');
 string str_Amount = to_string(Amount) + string(10 - to_string(Amount).length(), ' ');
 //string str_Total_Bill = to_string(Total_Bill) + string(10 - to_string(Total_Bill).length(), ' ');
 
 cout<<"\t|"<<str_ItemName<<"|"<<str_Rate<<"|"<<str_Quant<<"|"<<str_Amount<<"|"<<endl;
 
 
 }
 string str_Total_Bill = to_string(Total_Bill) + string(10 - to_string(Total_Bill).length(), ' ');
   out<<"\t|---------------------------------------------------------------|"<<endl;
   out<<"\t|                  TOTAL BILL  =                     |";cout<<str_Total_Bill<<"|"<<endl;
   out<<"\t|---------------------------------------------------------------|"<<endl;
   out<<"\t|        THANKS FOR SHOPPING !!  PLEASE VISIT AGAIN !!          |"<<endl;
   out<<"\t-----------------------------------------------------------------"<<endl;




 in.close(); 


}

int main (){
  
int main_choice =1 , access=0;
while (main_choice!=0 || access!=1)
{
  system("cls");
cout<<" -------------------------------------------"<<endl;
cout<<"|                 WELCOME                   |"<<endl;
cout<<"|                    TO                     |"<<endl;
cout<<"|               APNA BAZAAR                 |"<<endl;
cout<<"---------------------------------------------"<<endl;
cout<<"|               MAIN MENU                   |"<<endl;
cout<<"---------------------------------------------"<<endl;
cout<<"|1- customer                                |"<<endl;
cout<<"|2- owner                                   |"<<endl;
cout<<"|3- exit                                    |"<<endl;
cout<<"|-------------------------------------------|"<<endl;
cout<<"Enter your choice : ";
cin>>main_choice;
cout<<"---------------------------------------------"<<endl;

switch (main_choice)
{
case 1:{//customer
   
    customer obj;
  
   while( obj.cus_access!=1 ){
    obj.capcha();
   }
  
   
   if (obj.cus_access==1)
   { 
    
      cout<<endl<<"--------------------------------------------------------------"<<endl;
      cout<<"|                 Enter Customer name                        |"<<endl;
      cout<<"--------------------------------------------------------------"<<endl;
      
      cout<<"First name : ";
      cin>>first_name ;
      cout<<"Middle name : ";
      cin>>middle_name ;
      cout<<"Last name : ";
      cin>>last_name ;
      
      system("cls");
      cout<<"--------------------------------------------------------------"<<endl;
      cout<<"hii!"<<first_name<<" "<<middle_name<<" "<<last_name<<endl;
      cout<<"welcome to our store . Enjoy your purchase"<<endl;
      cout<<"--------------------------------------------------------------"<<endl;
      sleep(3);

     int cus_choice;
     bool exit=false;
     while(!exit){
        system("cls");
     cout<<"--------------------"<<endl;
     cout<<"|  CUSTOMER MENU   |"<<endl;
     cout<<"--------------------"<<endl;
     cout<<"|1-SHOW PRODUCTS   |"<<endl;
     cout<<"|2-BUY PRODUCTS    |"<<endl;
     cout<<"|3-PRINT BILL      |"<<endl;
     cout<<"|4-DOWNLOAD BILL   |"<<endl;
     cout<<"|5-EXIT            |"<<endl;
     cout<<"--------------------"<<endl;
     cout<<"enter your choice: ";
     cin>>cus_choice;
   
     switch(cus_choice) {
     case 1:
     showProducts();
     break;


     case 2:
     shop_products();
     break;
     
     case 3:
     printBill();
     break;
     case 4 :
     char y;
     cout<<endl;
     cout<<"press 'Y' for dowmload bill : ";
     cin>>y;
     if(y=='Y'){
      printBillFile();
     }
     break;

     case 5:
      system("cls");
      exit = true;
      ifstream in("Print.txt", ios::out | ios::trunc);
      in.close();
      cout<<"\tGood Luck!"<<endl;
     Sleep(3);
     break;
   
   
   
     }
    }
    
    }

     
   break;
   
   
   
   
   }
 
 
 
 
case 2 :{//owner
  
 owner obj;
 Bill b;
 while(obj.own_access!=1){
 obj.getdata();
 obj.login();
 }
    if (obj.own_access==1)
    {
     system("cls");  
     cout<<"--------------------------------------------------------------"<<endl;
     cout<<"hii! BHAVESH MOHAN PATIL"<<endl;
     cout<<"WELCOME TO YOUR STORE. LET'S GROW YOUR BUSINESS"<<endl;
     cout<<"--------------------------------------------------------------"<<endl;
      sleep(2);

     bool exit=false;
     while(!exit){
     int owner_choice;
     
     system("cls");
     cout<<"------------------------"<<endl;
     cout<<"|      ADMIN MENU      |"<<endl;
     cout<<"------------------------"<<endl; 
     cout<<"|1- SHOW PRODUCTS      |"<<endl;
     cout<<"|2- ADD PRODUCTS       |"<<endl;
     cout<<"|3- DELETE PRODUCTS    |"<<endl;
     cout<<"|3- SALES REPORT       |"<<endl;
     cout<<"|4- EXIT               |"<<endl;
     cout<<"------------------------"<<endl;
     cout<<"enter your choice :";
     cin >>owner_choice;

 switch (owner_choice)
   {
   
   case 1:{
    
    showProducts();	
    
    break;
   }


   case 2:{
       
    addItem(b);	
    
    break;
   }
 
   case 3:{
       
    deleteProducts();	
    
    break;
   }
   case 4:{
        
   exit=true;
   cout<<"Back to main menu "<<endl; 
   sleep(2);
   break;
   }
   default:{
   cout<<"INVALID CHOICE TRY AGAIN  "<<endl<<"\t Error 404"<<endl;
   break;}
 }

 
   }


   }
  break;
 }

case 3 : {//EXIT 
  main_choice=0;

    return 0;
    break;
 }



}
}
}