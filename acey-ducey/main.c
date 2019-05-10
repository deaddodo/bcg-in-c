#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    bool running;
    int cash;
} gamestate_t;

typedef struct {
    int card1, card2;
} hand_t;

char FACE_CARD_TABLE[4][6];
void init_face_card_table() {
    strcpy(FACE_CARD_TABLE[0], "JACK");
    strcpy(FACE_CARD_TABLE[1], "QUEEN");
    strcpy(FACE_CARD_TABLE[2], "KING");
    strcpy(FACE_CARD_TABLE[3], "ACE");
}

void print_intro() {
    printf("%40s%s\n", "", "ACEY DUCEY CARD GAME");
    printf("%26s%s\n\n\n", "", "CREATIVE COMPUTING  MORRISTOWN, NEW JERSEY");

    printf("ACEY-DUCEY IS PLAYED IN THE FOLLOWING MANNER \n");
    printf("THE DEALER (COMPUTER) DEALS TWO CARDS FACE UP\n");
    printf("YOU HAVE AN OPTION TO BET OR NOT BET DEPENDING\n");
    printf("ON WHETHER OR NOT YOU FEEL THE CARD WILL HAVE\n");
    printf("A VALUE BETWEEN THE FIRST TWO.\n");
    printf("IF YOU DO NOT WANT TO BET, INPUT A 0\n");
}

int draw_card() {
    int card = (int)((random() % ((14 - 2) + 1)) + 2);
    if(card > 10) {
        printf("%s\n", FACE_CARD_TABLE[card - 11]);
    } else {
        printf("%i\n", card);
    }
    return card;
}

// Always guarantee that the cards are in order from least to most, so
// we can do a single check
void order_cards(hand_t *hand) {
    if(hand->card1 > hand->card2) {
        int temp = hand->card2;
        hand->card2 = hand->card1;
        hand->card1 = temp;
    }
}

void draw_hand(hand_t *hand) {
    printf("HERE ARE YOUR NEXT TWO CARDS: \n");
    hand->card1 = draw_card();
    hand->card2 = draw_card();
    order_cards(hand);
    printf("\n");
}

int take_bet(gamestate_t *state) {
    int bet = 0;
    bool valid = false;

    while(!valid) {
        printf("WHAT IS YOUR BET ");
        scanf("%i", &bet);

        if (bet < 0) {
            printf("THAT'S NOT A VALID BET!\n");
        } else if (bet > state->cash) {
            printf("SORRY, MY FRIEND, BUT YOU BET TOO MUCH.\n");
            printf("YOU HAVE ONLY %i DOLLARS TO BET.\n", state->cash);
        } else {
            if (bet == 0) {
                printf("CHICKEN!!\n");
            }

            valid = true;
        }
    }

    return bet;
}

bool compare_cards(hand_t *hand) {
    int card3 = draw_card();
    return (hand->card1 < card3) && (card3 < hand->card2);
}

bool try_again(gamestate_t *state) {
    char retry[4];

    if(state->cash < 1) {
        printf("SORRY, FRIEND, BUT YOU BLEW YOUR WAD.\n");
    } else {
        printf("TRY AGAIN (YES OR NO) ");
        scanf("%s", retry);
        if(strcmp("YES", retry) == 0) return true;
    }

    return false;
}

int main(int argc, char *argv[]) {
    // initialize the program state
    srandom((unsigned int)time(NULL)); // we have to seed random in C
    init_face_card_table();
    gamestate_t state = {
            .running = true,
            .cash = 100
    };

    print_intro();

    // run the game
    while(state.running) {
        hand_t hand = {
                .card1 = 0,
                .card2 = 0
        };
        int bet=0;
        bool win;

        printf("YOU NOW HAVE %i DOLLARS.\n\n", state.cash);
        draw_hand(&hand);

        bet = take_bet(&state);
        win = compare_cards(&hand);

        if(win) {
            printf("YOU WIN!!\n");
            state.cash += bet;
        } else {
            printf("SORRY, YOU LOSE\n");
            state.cash -= bet;
        }

        state.running = try_again(&state);
    }

    printf("O.K., HOPE YOU HAD FUN!\n");

    return 0;
}