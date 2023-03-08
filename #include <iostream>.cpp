#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;
//am incercat sa folosesc structul si sa creez o clasa
struct Transaction {
    string transaction_id;
    string transaction_type;
    string customer_id;
    float amount;
    string currency;
};

int main() {
    // Citesc datele din primul fisier 
    vector<Transaction> transactions1;
    ifstream file1("internal.csv");
    string line;
    while (getline(file1, line)) {
        stringstream ss(line);
        Transaction transaction;
        getline(ss, transaction.transaction_id, ',');
        getline(ss, transaction.transaction_type, ',');
        getline(ss, transaction.customer_id, ',');
        ss >> transaction.amount;
        getline(ss, line, ','); // sterge , dupa ultima operatie 
        getline(ss, transaction.currency, ',');
        transactions1.push_back(transaction);
    }

    // Citesc datele din al 2 lea fisier 
    vector<Transaction> transactions2;
    ifstream file2("provider.csv");
    while (getline(file2, line)) {
        stringstream ss(line);
        Transaction transaction;
        getline(ss, transaction.transaction_id, ',');
        getline(ss, transaction.transaction_type, ',');
        getline(ss, transaction.customer_id, ',');
        ss >> transaction.amount;
        getline(ss, line, ','); // Sterg virgula 
        getline(ss, transaction.currency, ',');
        transactions2.push_back(transaction);
    }

    // Compar datele-m-am complicat foarte mult probabil prea mult.    :/
    for (const auto& transaction1 : transactions1) {
        const auto& transaction1Id = transaction1.transaction_id;
        auto transaction2It =find_if(transactions2.begin(), transactions2.end(),
                                           [&transaction1Id](const Transaction& transaction2) {
                                               return transaction2.transaction_id == transaction1Id;
                                           });
        if (transaction2It == transactions2.end()) {
            cout << "Transaction " << transaction1Id << " nu exista in al 2 lea fisier" <<endl;
        } else {
            const auto& transaction2 = *transaction2It;
            if (transaction1.transaction_type != transaction2.transaction_type) {
                cout << "Transaction " << transaction1Id << " diferit trans. type" <<endl;
            }
            if (transaction1.customer_id != transaction2.customer_id) {
                cout << "Transaction " << transaction1Id << "  dif custid" <<endl;
            }
            if (transaction1.amount != transaction2.amount) {
                cout << "Transaction " << transaction1Id << " e dif amount" <<endl;
            }
            if (transaction1.currency != transaction2.currency) {
                cout<<"Transaction"<<transaction1Id<<" dif currency "<<endl;
            }
        }
    }
    file1.close();
    file2.close();
return 0;
}