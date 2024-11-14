#include <stdio.h>

int main() {
    // Initial balance and transactions array
    int initial_balance = 1000;
    int transactions[] = {500, -200, -300, 100, -50, 600, -2000};
    int tobeprocessed[sizeof(transactions) / sizeof(transactions[0])];  // To store unprocessed transactions
    int balance = initial_balance;
    int tobeprocessed_count = 0;  // To track how many transactions are unprocessed

    // Processing each transaction
    for (int i = 0; i < sizeof(transactions) / sizeof(transactions[0]); i++) {
        // Check if withdrawal exceeds the current balance
        if (transactions[i] < 0 && balance + transactions[i] < 0) {
            printf("Transaction %d (amount: %d) is invalid due to insufficient funds.\n", i + 1, transactions[i]);
            tobeprocessed[tobeprocessed_count++] = transactions[i];  // Store unprocessed transaction
        }
        // Check if balance reaches 0
        else if (balance == 0) {
            printf("Balance is 0. No further transactions will be processed.\n");
            tobeprocessed[tobeprocessed_count++] = transactions[i];  // Store unprocessed transaction
        }
        else {
            balance += transactions[i];  // Valid transaction, update balance
        }
    }

    // Final output
    printf("Final balance: %d AED\n", balance);
    printf("Unprocessed transactions: ");
    for (int i = 0; i < tobeprocessed_count; i++) {
        printf("%d ", tobeprocessed[i]);
    }
    printf("\n");

    return 0;
}

