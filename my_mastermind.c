#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>

bool input_check(char mye_inputval[]) {
    if (strlen(mye_inputval) != 4) {
        printf("Wrong mye_inputval\n");
        return false; }
     int freq[9] = {0};
     for (int i = 0; i < 4; i++) {
     if (!isdigit(mye_inputval[i])) {
            printf("Wrong Input\n");
            return false;}
        int numb = mye_inputval[i] - '0';
        freq[numb]++;

        if (freq[numb] > 1) {
            printf("Duplicate number found\n");
            return false; }
    }
    return true;
    }


int lenh(char mye_inputval[]) {
    int leng = 0;
    while(mye_inputval[leng] != '\n' && mye_inputval[leng] != '\0') {
        leng++;
    }
    return leng;
}


void read_input(char mye_inputval[]) {
    ssize_t bytes_read = read(STDIN_FILENO, mye_inputval, 4);

    if (bytes_read < 0) {
        perror("Read failed");
    }
     if (bytes_read == 0) {
        printf("No mye_inputval provided.\n");
     }
    mye_inputval[bytes_read] = '\0';
}


void commands_for_print() {
   printf("Will you find the secret code?\nPlease enter a valid guess\n");
}

 void dee_masterhhmind(char *hidden_code, int highest_attempts) {
    int no_of_trials = 0; while (no_of_trials < highest_attempts) {
        char guess[5] = {0};printf("---\nRound %d\n>", no_of_trials);
        char c; int index = 0; ssize_t read_bytes; while ((read_bytes = read(STDIN_FILENO, &c, 1)) > 0) {
     if (c == '\n') { guess[index] = '\0';break; }
        if (index < 4) { guess[index++] = c;}
         }if (read_bytes == 0) { printf("\nYou have Exited the game.\n"); return;}
            if (strcmp(guess, hidden_code) == 0) { printf("Congratz! You did it!\n");
         return;}
            int well_placed = 0, misplaced = 0; char t_secrets[5], guesses[5];
         strcpy(t_secrets, hidden_code); strcpy(guesses, guess);
     for (int i = 0; i < 4; i++) {
    if (guesses[i] == t_secrets[i]) {well_placed++; t_secrets[i] = 'X'; guesses[i] = 'Y';  } 
       }for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
              if (guesses[i] == t_secrets[j]) {misplaced++; t_secrets[j] = 'X'; guesses[i] = 'Y'; 
                 break; }} }
        printf("Well placed pieces: %d\n", well_placed);
        printf("Misplaced pieces: %d\n", misplaced);no_of_trials++;}
        printf("Sorry, you've run out of no_of_trials. The secret code was: %s\n", hidden_code);}


int main(int veegc, char *veegz[]) {
    char *hidden_code = NULL; int highest_attempts = 10; 
     int i = 1;
        while (i < veegc) {
            if (strcmp(veegz[i], "-c") == 0) {
                if (++i < veegc) { hidden_code = veegz[i];
                } else {
                    fprintf(stderr, "Error: No code provided after -c flag.\n");
                    return 1;}
            } else if (strcmp(veegz[i], "-t") == 0) {
                if (++i < veegc) { highest_attempts = atoi(veegz[i]);
                } else { fprintf(stderr, "Error: No value provided after -t flag.\n");
                    return 1;}
            } i++;
        } srand(time(NULL));
                if (hidden_code == NULL) { char spontaenouscode[5];
                    for (int i = 0; i < 4; i++) { spontaenouscode[i] = '0' + rand() % 9;}
                    spontaenouscode[4] = '\0'; hidden_code = spontaenouscode; }
                commands_for_print(); dee_masterhhmind(hidden_code, highest_attempts);
                return 0; }