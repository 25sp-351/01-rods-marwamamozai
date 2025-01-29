#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {


    if (argc < 2) {
        printf("Usage: %s <rod length>\n", argv[0]);
        return 1;
    }

    //Intialization and valid input check 
    int rod_size = atoi(argv[1]);
    if (rod_size <= 0) {
        printf("Invalid rod length. Must be a positive integer.\n");
        return 1;
    }

    // Input: Outputs prompt for rodsize 
    printf("Rod size: %d\n", rod_size);


    //---------
    int lengths[100], prices[100];
    int count = 0;

    //Input : user will input the length and prices 
    printf("Enter lengths and prices (e.g., '32, 10'). Press Return & then Ctrl+D to finish:\n");
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), stdin)) {
        int length, price;
        if (sscanf(buffer, "%d, %d", &length, &price) == 2) {
            lengths[count] = length;
            prices[count] = price;
            count++;
        } else {
            printf("Invalid input: %s", buffer);
        }
    }


    //Orgainizes lengths and prices and displays the amount user put 
    printf("You entered %d length-price pairs.\n", count);
    for (int i = 0; i < count; i++) {
        printf("Length: %d, Price: %d\n", lengths[i], prices[i]);
    }
    int total_value = 0;
    int remainder = rod_size;


    // Processing & Output of Cutting plan : using a while loop to find the best ratio
    // and then outputting the best ratio / pieces that can be cut 
    
    printf("\nCutting plan:\n");
    while (remainder > 0) {
        int best_index = -1;
        double best_ratio = 0;

        for (int i = 0; i < count; i++) {
            if (lengths[i] <= remainder) {
                double ratio = (double)prices[i] / lengths[i];
                if (ratio > best_ratio) {
                    best_ratio = ratio;
                    best_index = i;
                }
            }
        }

        if (best_index == -1) {
            break;
        }

        int num_pieces = remainder / lengths[best_index];
        int total_piece_value = num_pieces * prices[best_index];
        remainder -= num_pieces * lengths[best_index];
        total_value += total_piece_value;

        printf("%d @ %d = %d\n", num_pieces, lengths[best_index], total_piece_value);
    }

    printf("Remainder: %d\n", remainder);
    printf("Value: %d\n", total_value);

    return 0;

} // end program
