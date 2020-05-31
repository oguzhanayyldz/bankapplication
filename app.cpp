// build by O�uzhan Ayy�ld�z
#include <iostream>
#include<iomanip>
#include <string>
using  namespace std;

class Account{
	protected:
		int numberOfAccount = 0; // Account Say�s�n� Tutuyor
		int numberOfDeposit = 0; // Hesaplar aras�ndaki transferlerin adetini tutuyor
		int numberOfConfirm = 0; // Onaylanan transferleri tutuyor
		int numberOfFunds = 0; // Fon hesaplar�n say�s�n� tutuyor
		string account_number; // Ba�nald���m�z accountun numaras� 
		string pin;	// Ba�land���m�z accountun �ifresi
		double balance; // Ba�land���m�z accountun bakiyesi
		double balancePending; // Ba�land���m�z accountun beklenilen hesap bakiyesi
		string account_numbers[20]; // T�m accountlar�n hesap numaralar� dizisi
		string pins[20];	// T�m �ifreler dizisi
		double  balances[20];	// T�m bakiyeler dizisi
		double  balancePendings[20]; // T�m bekleyen bakiyeler dizisi
		string perhapsDeposits[20][2]; //Bekleyen t�m transferleri tutuyoru
		double amountOfperhaps[20];	// Bekleyen t�m transferleri bakiyelerini tutuyor.
		string confirmDeposits[20][2]; // Onaylanan t�m transferleri tutuyor.
		double amountOfconfirm[20];	// Onaylanan t�m transferlerin bakiyelerini tutuyor.
		string savingAccount[20];	// Fon hesaplar�n�n bilgileri tutuyor
		double savingAccountAmount[20];	// Fon hesaplar�n�n bakiyelerini tutuyor
		
	public:
		Account(){}
		~Account(){	}
		string getAccountNumber(){
			return account_number;	// Ba�land���m�z accountun numaras�n� d�nderiyor.
		}
		bool connectedControl(){ // Herhangi bir accounta ba�land�k m� bunu kontrol ediyor.
			if(account_number.empty() != true  && pin.empty() != true){
				return true;
			}else{
				return false;
			}
		}
		bool accountControl(string n){ // Account numaran�n uniq olmas� i�in bir kontrol ger�ekle�tiriyor.
			bool r = false;
			for(int i = 0 ; i < numberOfAccount ;i++){
				if (account_numbers[i] == n){
					r = true;
				}
			}
			return r;
		}
		void setAccount(string n,string p, double b){ //Yeni account olu�turma fonksiyonu.
			account_numbers[numberOfAccount] = n;
			pins[numberOfAccount] = p;
			balances[numberOfAccount] = b;
			balancePendings[numberOfAccount] =  0;
			numberOfAccount += 1;
			cout<< "Your account has been opened, please click 2 on the menu to log in."<< endl;
		}
		void  getAccount(string an  , string p){ //Bir hesaba ba�lanmak i�in yap�lan kontrol fonksiyonu
			for(int i = 0;  i < numberOfAccount; i++){
				if(account_numbers[i] == an && pins[i] == p){
					account_number = an;
					pin = p;
					balance = balances[i];
					balancePending = balancePendings[i];
					cout<< "It was connected to your account."<< endl;
				}	
			}
		}
		void deposit(){	//Hesap bilgilerini ve bakiyesini getiriyor.
			if(account_number.empty() != true  && pin.empty() != true){
				cout<< "Account Number : " <<account_number << endl;
				cout<< "Balance of deposit : $" << balance << endl;
				cout<< "Balance of perhaps deposit : $"  << balancePending<<endl;	
			}else{
				cout<< "Please login to your account from the 2nd menu."<<endl;
			}
		}
			
		void perhapsDeposit(){ //Bekleyen bakiye transferlerini getiriyor.
			if(account_number.empty() != true  && pin.empty() != true){
				int counter = 0;
				cout<< "Perhaps Deposits"<< endl<<endl;
				for(int i = 0;  i < numberOfDeposit; i++){	
					if(perhapsDeposits[i][0] == account_number){
						cout<< i << "   -   " <<"To : "  <<perhapsDeposits[i][0] << " From : " << perhapsDeposits[i][1] << " Amount : $" << amountOfperhaps[i] << endl;
						counter++;
					}				
				}
				if(counter != 0){
					int y = 0;
					cout<< "if you can do confirm any perhaps enter the 1 : ";
					cin>>y;
					
					if(y == 1){
						y = 0;
						confirmToDeposit();
					}
				
					cin.ignore();
	            	cin.get();	
					
				}else{
					cout<< "No pending perhaps right now !!"<< endl<< endl;
				}
			}else{
				cout<< "Please login to your account from the 2nd menu."<<endl;
			}
		}
			
		
		void confirmToDeposit(){// Bekleyen para transferlerini onaylamak i�in olu�turulan fonksiyon
			if(account_number.empty() != true  && pin.empty() != true){
				int a;
				cout<< endl;
				cout<< "Select the perhaps you want to confirm:  ";
				cin>>a;
				if(perhapsDeposits[a][0] == account_number){
					numberOfDeposit -= 1;
					for(int i=0; i<numberOfAccount; i++){
						if(account_numbers[i] == account_number){
							balance += amountOfperhaps[a]; 
							balancePending -= amountOfperhaps[a]; 
							balances[i] += amountOfperhaps[a];
							balancePendings[i] -= amountOfperhaps[a];
							setConfirm(perhapsDeposits[a][1],perhapsDeposits[a][0],amountOfperhaps[a]);
							perhapsDeposits[a][0] = " ";
							perhapsDeposits[a][1] = " ";
							amountOfperhaps[a]= 0;
							cout<<endl;
							
						}
					}
					perhapsDeposit();	
				}
				cin.ignore();
	
	            cin.get();	
			}else{
				cout<< "Please login to your account from the 2nd menu."<<endl;
			}	
		}
		
		void confirmDeposit(){ //Onaylanan transferleri listeliyor.
			if(account_number.empty() != true  && pin.empty() != true){
				cout<< "Confirm Deposits"<< endl;
				for(int i = 0;  i < numberOfConfirm; i++){	
					if(confirmDeposits[i][0] == account_number){
						cout<< "To : "  <<confirmDeposits[i][0] << " From : " << confirmDeposits[i][1] << " Amount : $" << amountOfconfirm[i]  << endl;
					}				
				}
			}else{
				cout<< "Please login to your account from the 2nd menu."<<endl;
			}
		}
		
		void setFunds(double amount){ // Fon hesab�na para yat�rma.
			if(account_number.empty() != true  && pin.empty() != true){
				savingAccount[numberOfFunds] = account_number;
				savingAccountAmount[numberOfFunds] = amount;
				balance -= amount;
				for(int i= 0 ; i< numberOfAccount ; i++){
					if(account_numbers[i] == account_number){
						balances[i] -= amount;
					}
				}
				numberOfFunds++;
				cout<< "Your submission has been completed."<<endl;
			}else{
				cout<< "Please login to your account from the 2nd menu."<<endl;
			}
		}
		
		void checkFunds(){ //Fon hesab�ndaki bakiyeyi g�r�nt�l�yor.
			if(account_number.empty() != true  && pin.empty() != true){
				int counter = 0;
				double sum = 0;
				for(int i = 0; i < numberOfFunds; i++ ){
					if (savingAccount[i] == account_number ){
						counter++;
						sum += savingAccountAmount[i];	
					}
				}
				cout<< "There is $" << sum << " in saving account";
				if(counter == 0 ){
					cout<< "You have invested money in any mutual fund. "<<endl;
				}
			}else{
				cout<< "Please login to your account from the 2nd menu."<<endl;
			}
		}
		
		void withDraw(string p, double amount){ // Hesab�n�zdan para �ekmeyi sa�layan fonksiyon.
			if(account_number.empty() != true  && pin.empty() != true){
				if( chequeWithDraw(amount) == true && p == pin){
					for(int i = 0 ; i < numberOfAccount;  i++){
				 		if(account_numbers[i] == account_number){
							balances[i] -= amount;
						}
					}
					balance -= amount;
					cout<< "You have successfully withdrawn your money."<<endl;
				}else if(chequeWithDraw(amount) == false){
					cout<< "There is not enough money in your account !!"<<endl;
				}else{
					cout<< "Check your password."<<endl;
				}
			}else{
				cout<< "Please login to your account from the 2nd menu."<<endl;
			}
		} 
		
		void addingBalance(double amount){ //Hesab�n�za para yat�rmak i�in kullan�lan fonksiyon
			if(account_number.empty() != true  && pin.empty() != true){
				for(int i = 0 ; i < numberOfAccount;  i++){
				 	if(account_numbers[i] == account_number){
						balances[i] += amount;
					}
				}
				balance += amount;
				cout<< "Your money upload has been successfully completed. "<<endl;
			}else{
				cout<< "Please login to your account from the 2nd menu."<<endl;
			}
		}
		
		bool chequeWithDraw(double amount){ // Para transferi i�in yeteri kadar bakiyeniz var m� onu kontrol ediyor.
			if(balance >= amount){
				return true;
			}else{
				return false;
			}
		}
		
		void setCheque(string from, string to, double amount){ //Para transferini ger�ekle�tiren fonksiyon
			if(account_number.empty() != true  && pin.empty() != true){
				if(account_number != to){
				 if(chequeWithDraw(amount) == true){
				 	balance = balance - amount;
				 	perhapsDeposits[numberOfDeposit][0] = to;
				 	perhapsDeposits[numberOfDeposit][1] = from;
				 	amountOfperhaps[numberOfDeposit] = amount;
				 	for(int i = 0 ; i < numberOfAccount;  i++){
				 		if(account_numbers[i] == to){
				 			balancePendings[i] += amount;
						 }
						 if(account_numbers[i] == from){
						 	balances[i] -= amount;
						 }
					 }
				 	numberOfDeposit += 1;
				 	cout<< "Your submission has been completed."<<endl;
				 }else{
				 	cout<< "You don't have enough money for this transaction !!"<<endl;
				 }
				}else{
					cout<< "You cannot transfer to your own account !!"<<endl;
				}
			}else{
				cout<< "Please login to your account from the 2nd menu."<<endl;
			}
		}
		
		void setConfirm(string from, string to, double amount){
		 	confirmDeposits[numberOfConfirm][0] = to;
		 	confirmDeposits[numberOfDeposit][1] = from;
		 	amountOfconfirm[numberOfDeposit] = amount;
		 	numberOfConfirm += 1;
		}
		
		void depositCheque(){
			//return true;
		}
		
		
		
};


int main(){
	
	Account *account = new Account(); // Pointer tan�mlan�yor.
	account->setAccount("1","1",600.0);	// �rnek olarak 2 tane hesap eklendi.
	account->setAccount("2","2",600.0);
	account->getAccount("1","1"); // 1 numaral� hesaba ba�lan�ld�
	account->setCheque("1","2",200.0);	// 1 numaral� hesaptan 2 numaral� hesaba $200 g�nderildi.
	account->getAccount("2","2"); // 2 numaral� hesaba ba�lan�yoruz ��nk� bekleyen para transferini g�rmek i�in
	
	string account_num; // Form i�erisindeki i�lemler i�in s�rekli de�i�en de�i�kenler.
	string pin;
	double  balance;
	
	int opt; // ��lem se�mek i�in olu�turulan de�i�ken

    for (;;) // Sonsuz d�ng� sa�l�yor. Bu sayede program kapanm�yor.

    {

        system("color 0C"); // Renk ve Arkaplan rengi kodu.

        system("cls"); // Case i�indekilerin devaml� yeni sayfada gelmelerini sa�l�yor.
        
        cout<<  " _____________________________________________________"<<endl;
		           																					// Bankam�z�n logosu
		cout << "|     _______    _______      __    __     _______    |"<<"\n"<<
				"|    |   _   |  |  _____|    |  |  |  |   |____  /    |"<<"\n"<<
				"|    |  | |  |  | |  ___     |  |  |  |      /  /     |"<<"\n"<<
				"|    |  | |  |  | | |_  |    |  |  |  |     /  /      |"<<"\n"<<
				"|    |  |_|  |  | |___| |    |  |__|  |    /  /__     |"<<"\n"<<
				"|    |_______|  |_______|    |________|   |______|    |"<<"\n";
				
		cout << "|________________________BANK_________________________|"<<endl<<endl;
				
		
        
        cout << " _____________________________________________________";
        																												//��lem men�s�
				cout<<"\n|                                                     |\n| 1 --> Create New Account ";
				
				cout<<"                           |\n| 2 --> Connect to the Your Account";

                cout<<"                   |\n| 3 --> Deposit";

                cout<<"                                       |\n| 4 --> Perhaps Deposit";

                cout<<"                               |\n| 5 --> Confirm Deposit";

                cout<<"                               |\n| 6 --> Withdraw to Account";
                
                cout<<"                           |\n| 7 --> Adding Balance to the Account";

                cout<<"                 |\n| 8 --> Sending Money to Another Account";

                cout<<"              |\n| 9 --> Funding the Fund";
                
                cout<<"                              |\n| 10 --> Control the Fund";
                
                cout<<"                             |\n| 11 --> Close to the Program                         |";
                
                cout<<"\n|_____________________________________________________|";

 		cout<<"\n _____________________________________________________\n|";

        cout<<"                                                     |\n Option : ";						// ��lem se�icisi.
        cin>>opt;
		
		cout<<"\n|_____________________________________________________|\n";
                

                system("cls");

                switch(opt)
                {
	                case 1:	// Yeni account olu�turma ekran�
						cout<< "Please enter the account number: ";
						cin>> account_num;
						if(account->accountControl(account_num) == false){
							cout<< "Please enter the pin: ";
							cin>> pin;
							cout<< "Please enter the fist balance: ";
							cin>> balance;	
						}else{
							cout<< "There is an account similar to the account number you selected. Please choose another account number." <<endl;
						}		
						account->setAccount(account_num,pin,balance);
	                break;
	                case 2:	// Hesaba giri� ekran�
	                		cout<< "Please enter the account number : ";
							cin>> account_num;
							cout<< "Please enter the pin : ";
							cin>> pin;	
							account->getAccount(account_num,pin);
	                    break;
	                case 3: // Hesap d�k�man� sayfas� ve bakiye
	                        account->deposit();
	                    break;
	                case 4: // Bekleyen i�lemler ekran�
							account->perhapsDeposit();	
	                break;
	                case 5:	// Onaylanan i�lemler ekran�
		                	account->confirmDeposit();
	                	break;
	                case 6: // Para �ekme ekran�
						if(account->connectedControl() == true){
	                		cout<< "Please enter the pin : ";
							cin>> pin;
							cout<< "Enter the balance you want to withdraw : ";
							cin>> balance;
						}	
	                        account->withDraw(pin,balance);
	                	break;
	               case 7:	// Yat�rma ekran�
						if(account->connectedControl() == true){
	                		cout<< "Enter the amount you want to add : ";
							cin>> balance;
						}	
	                        account->addingBalance(balance);
	                	break;
	                case 8:	// Transfer ekran�
							if(account->connectedControl() == true){
		                		cout<< "Enter the account number you want to send : ";
		                		cin>> account_num;
		                		cout<< "Enter the balance you want to send:";
								cin>> balance;
							}
	                		account->setCheque(account->getAccountNumber(),account_num,balance);
	                	break;
	                	
	                case 9:	// Fona para yat�rma ekran�
	                		if(account->connectedControl() == true){
	                			cout<< "Enter the balance amount you wish to deposit in the Fund : ";
								cin>> balance;
							}
	                		account->setFunds(balance);
	                	break;
	                	
	                case 10: // Fon hesab�n�z� kontrol etme ekran�
	                		account->checkFunds();
	                	break;
					case 11: // Program� kapama ekran�
							exit(0);
						break;       	
	                default :cout<<"Invalid Option\n";

                }
				
                cin.ignore();

                cin.get();

    }
	
	return 0;
}




