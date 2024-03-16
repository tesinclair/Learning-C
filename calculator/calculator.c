#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int *parseInput(char *input, char token);

int main(){

    char tokens[] = {'*', '+', '/', '-'};
    int running = 1;
    printf("==CALCULATOR==");
    printf("\nUse for *, +, /, -.\n(q, exit) to quit\n");

    while (running){

        printf(">>>");

        char *equation;
        size_t eqnSize = 0; 
        
        getline(&equation, &eqnSize, stdin);

        if (equation == NULL){
            printf("Getline Failed");
            free(equation);
            return 1;
        }
        equation[strlen(equation) - 1] = '\0';
        if (equation[0] == 'q' || strcmp(equation, "exit") == 0){
            running = 0;
            free(equation);
            break;
        }
        for (int i = 0; i < strlen(equation); i++){
            for (int j = 0; j < strlen(tokens); j++){
                if (equation[i] == tokens[j]){
                    int *parsedInput = parseInput(equation, tokens[j]);
                    if (!parsedInput){
                        free(parsedInput);
                        return 1;
                    }

                    int eqa = parsedInput[0];
                    int eqb = parsedInput[1];

                    switch (tokens[j]){
                        case '*':
                            printf("%d\n", eqa * eqb);
                            break;
                        case '+':
                            printf("%d\n", eqa + eqb);
                            break;
                        case '/':
                            if (eqb == 0){
                                printf("Cannot divide by 0\n");
                                break;
                            }
                            printf("%.2f\n", (double) eqa / eqb);
                            break;
                        case '-':
                            printf("%d\n", eqa - eqb);
                            break;
                        default:
                            printf("An unknown situation occurred");
                    }
                    free(parsedInput);
                }
            }
        }
    }
    return 0;
}
int *parseInput(char *input, char token){
    const int len = sizeof(input) / sizeof(char);

    // eqa and eqb are defined such that the equation can be written: eqa token eqb

    int leneqa;
    int leneqb;
    int eqbStart;
    int tokenIndex;

    int *parsedInput = malloc(2 * sizeof(int));
    if (parsedInput == NULL){
        printf("Mem allocation error");
        free(parsedInput);
        return NULL;
    }

    for (int i = 0; i < len; i++){
        if (input[i] == token){
            tokenIndex = i;
            // If there is a space between the token and the operand, set the length of
            // eqa to be before the space, else set it to before the token
            if (input[tokenIndex-1] == ' '){
                leneqa = i - 2;
            }else{
                leneqa = i - 1;
            }
        }

        if (input[i] == '\0'){
            // If there is a space after the token position, ignore it.
            if (input[tokenIndex + 1] == ' '){
                eqbStart = tokenIndex + 2;
            }else{
                eqbStart = tokenIndex + 1;
            }
            leneqb = strlen(input) - eqbStart;
        }
    }
    char *temp = malloc(leneqa * sizeof(char));
    if (temp == NULL){
        printf("error allocating memory");
        free(temp);
        return NULL;
    }

    for (int i = 0; i <= leneqa; i++){
        temp[i] = input[i];
    }
    parsedInput[0] = atoi(temp);
    
    char *newtemp = malloc(leneqb * sizeof(char));
    if (newtemp == NULL){
        printf("Error reallocating memory");
        free(newtemp);
        return NULL;
    }
    int eqbEnd = eqbStart + leneqb;
    for (int i = eqbStart; i < eqbEnd; i++){
        newtemp[i - eqbStart] = input[i];
    }

    parsedInput[1] = atoi(newtemp);
    free(newtemp);
    free(temp);
    free(input);
    return parsedInput;

}

