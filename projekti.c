//
//  main.c
//  Game Shop
//
//  Created by Pyry Satama on 17.4.2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct game {
     char name[20];
    float price;
    float profit;
}game;

//Adds a new game to the database. Parameter i is the number of games in database
 game *add_game(const char *command, game *array, int i, int *test)
{
    char name[20];
    float price;
    if(sscanf(command, "A %s %f", name, &price) < 2) {    // checks if the input is given correctly
        *test = 1;
        printf("Invalid input.\nNext command:\n");
        return array;
    } else {
    game *newgame = realloc(array, sizeof(game) * (i+1));
    if(newgame == NULL) return NULL;
    strcpy(newgame[i].name, name);
    newgame[i].price = price;
    newgame[i].profit = 0;
        *test = 0;
    return newgame;
    }
    return 0;
}

// Buys the game N units. Increases total sales of the game.
void buy_game(const char *command, game *game, int size) {
    char name[20];
    int N;
    int i = 0;
    int k = 0;
    if(sscanf(command, "B %s %d", name, &N) > 1) {   // checks if the input is given correctly
    for(i = 0; i < size; i++) {
        if(strcmp(game[i].name, name) == 0) {
            k = 1;
            break;
           }
        }
     }
    if(k == 0) printf("Invalid input\nNext command:\n");
    if(k == 1) {
        game[i].profit = game[i].profit + N* game[i].price;
        printf("%d games bought\nNext command:\n", N);
    }
}

// compare function for qsort
int cmpfunc(const void *a, const void *b) {
     const game *game_a = a;
     const game *game_b = b;
    return (int)(game_b->profit - game_a->profit);
}


// print all the game in the shop in descending order based on their total sales
void print(game *a, int size) {
    qsort(a, size, sizeof(game), cmpfunc);    // sorts the games to the right order
    for(int i = 0; i < size; i++) {
        printf("%s, price: %.2f, total sales: %.2f\n", a[i].name, a[i].price, a[i].profit); }
}


// saves all game information to a file indicated by the filename
void save_game(const char *command, game *a, int size) {
    char filename[20];
    FILE *f;
    if(sscanf(command, "W %s", filename) < 1) {     // checks if the input is given correctly
        printf("Invalid input\nNext command:\n");
    } else {
        // open file for writing
        f = fopen(filename, "w");
        if(!f) {
            fprintf(stderr, "Opening file failed\nNext command:\n");
        } else {
            for(int i = 0; i < size; i++) {
                fprintf(f, "%s %.2f %.2f\n", a[i].name, a[i].price, a[i].profit);
        }
            printf("Game(s) saved successfully!\nNext command:\n");
    }
        fclose(f);
        }
}


//returns a number of lines (games) in a given file
int line_count(const char *command)
{
    char c;
    int count=0;
    int ch = 0;
    char filename[20];
    if(sscanf(command, "O %s", filename) < 1) {      // checks if the input is given correctly
        return -1;
    } else {
    FILE *p = fopen(filename, "r");
    if(!p) {
        return -1;
    }
    for(c = getc(p); c != EOF; c = getc(p)) {
        if(c == '\n') {
            count++;
            ch = 0;
        } else {
            ch++;
        }
    }
    if(ch>0) count++;
    fclose(p);
    return count;
    }
}


game *load_game(const char *command, game *a, int size) {
    char filename[20];
    FILE *f;
    if(sscanf(command, "O %s", filename) < 1) {
        printf("Invalid input\nNext command:\n");
        return a;
    } else {
        f = fopen(filename, "r");
        if(!f) {
            fprintf(stderr, "Opening file failed\nNext command:\n");
            return a;
        } else {
            int lines = size;
           game *new = calloc(lines, sizeof(game));
            char name[20];
            float price, profit;
            int i = 0;
            char str[100];
           while(i < lines) {
               fgets(str, 100, f);
               sscanf(str, "%s %f %f", name, &price, &profit);
               strcpy(new[i].name, name);
               new[i].price = price;
               new[i].profit = profit;
               i++;
            }
            printf("File opened successfully\nNext command:\n");
            fclose(f);
            return new;
        }
    }
}

void cleanup(struct game *game) {
    free(game);          //releases all allocated memory
}


int main() {
    printf("Welcome to Game Store!\n\nInstructions:\n\nAdd a game to database: A name price\n\nBuy the game that's in the database N units: B name N\n\nPrint game information: L\n\nSave games to the given file: W filename\n\nLoad game information from the given file: O filename\n\nExit program: Q\n\nGive command:\n");
    int continues = 1;
    int i = 0;   // number of games in database
    int test;    // test parameter for add_game
    int lines;   // number of lines in a file you want to open
    game *game = NULL;
    while(continues) {
        char buffer[80];
        char *ret = fgets(buffer, 80, stdin);
        if (ret == NULL) {
            printf("No input\nNext command:\n");
        }
        
        switch(ret[0]) {
            case 'A':
                game = add_game(buffer, game, i, &test);
                
                if(test == 0) {
                printf("Game added successfully\nNext command:\n");
                    i++;
                    }
                break;
                
            case 'B':
                buy_game(buffer, game, i);
                break;
                
            case 'L':
                if(i==0){
                    printf("No games in database\nNext command:\n");
                } else {
                    print(game, i);
                    printf("Next command:\n");
                }
                break;
                
            case 'W':
                save_game(buffer, game, i);
                break;
                
            case 'O':
                 lines = line_count(buffer);
                if(lines != -1) {
                    i = lines;
                  game = load_game(buffer, game, i); }
                else {
                    printf("Invalid input\nNext command:\n");
                }
                break;
                
            case 'Q':
                continues = 0;
                break;
                
            default:
                printf("Unknown command\nNext command:\n");
                break;
        }
    }
    cleanup(game);
    return 0;
}
