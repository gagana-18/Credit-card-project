#include <iostream>
#include <string>
using namespace std;

class CreditCard {
   protected:
      string cardNumber;
      string expirationDate;
      int securityCode;
   public:
      CreditCard() { }
      virtual bool validate() {
         cout << "Credit card validation: " << endl;
         // add validation logic here
         return true;
      }
      void setCardDetails() {
         cout << "Enter card number: ";
         cin >> cardNumber;
         cout << "Enter expiration date (MM/YY): ";
         cin >> expirationDate;
         cout << "Enter security code: ";
         cin >> securityCode;
      }
};

class VisaCard: public CreditCard {
   public:
      VisaCard() { }
      bool validate () {
        if (cardNumber.length() != 16) {
            return false;
        }
        if (cardNumber.substr(0, 1) != "4") {
            return false;
        }
         cout << "Visa card validation: " << endl;
         // add validation logic specific to Visa cards here
         int sum = 0;
        for (int i = 0; i < 16; i++) {
            int digit = cardNumber[i] - '0';
            if (i % 2 == 0) {
                digit *= 2;
                if (digit > 9) {
                    digit -= 9;
                }
            }
            sum += digit;
        }
        return (sum % 10 == 0);
    }
};
      


class MasterCard: public CreditCard {
   public:
      MasterCard() { }
      bool validate () {
        
           // Check if the card number starts with 5 and has 16 digits
        if (cardNumber[0] != '5' || cardNumber.length() != 16) {
            return false;
        }
        
        cout << "MasterCard validation: " << endl;
           // Use Luhn algorithm to validate the card number
        int sum = 0;
        bool doubleDigit = false;
        for (int i = cardNumber.length() - 1; i >= 0; i--) {
            int digit = cardNumber[i] - '0';
            if (doubleDigit) {
                digit *= 2;
                if (digit > 9) {
                    digit = digit % 10 + digit / 10;
                }
            }
            sum += digit;
            doubleDigit = !doubleDigit;
        }
        return sum % 10 == 0;
    }
};

int main() {
   CreditCard *card;
   int choice;

   // ask the user to choose card type
   cout << "Enter card type (1 for Visa, 2 for MasterCard): ";
   cin >> choice;

   // create object based on user choice
   if (choice == 1) {
      card = new VisaCard();
   } else if (choice == 2) {
      card = new MasterCard();
   } else {
      cout << "Invalid choice" << endl;
      return 0;
   }

   // ask the user to enter card details
   card->setCardDetails();

   // validate the card
   if (card->validate()) {
      cout << "Card is valid" << endl;
   } else {
      cout << "Card is invalid" << endl;
   }

   delete card;

   return 0;
}
   