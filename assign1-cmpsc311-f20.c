////////////////////////////////////////////////////////////////////////////////
//
//  File           : cmpsc311-f16-assign1.c
//  Description    : This is the main source code for for the first assignment
//                   of CMPSC311 at Penn State University.  See the related
//                   assignment page for details.
//
//   Author        : Malay Agarwal
//   Last Modified : 09/16/2020 14:45
////////////////////////////////////////////////////////////////////////////////
//   NOTE: CODE MAY SEG FAULT BUT IF IT IS RAN A FEW TIMES THERE WILL BE A 
//   RESULT WITHOUT A SEG FAULT AND PERFECT RESULT
//   IT TAKES UP TO 10 RUNS SOMETIMES TO NOT SEG FAULT.
////////////////////////////////////////////////////////////////////////////////
//

// Include Files
#include <stdio.h>
#include <cmpsc311_util.h>
#include <time.h>

// Defines
#define NUM_CARDS 52
#define MAX_CARDS 11
#define SPADE "\xE2\x99\xA0"
#define CLUB "\xE2\x99\xA3"
#define HEART "\xE2\x99\xA5"
#define DIAMOND "\xE2\x99\xA6"

// Functions

////////////////////////////////////////////////////////////////////////////////
//
// Function     : print_card
// Description  : print the card from the integer value
//
// Inputs       : card - the card to print
// Outputs      : 0 always

int print_card(int card)
{

    // CODE HERE
    char card_faces[] = "234567891JQKA";
    char *card_suits[] = {SPADE, CLUB, HEART, DIAMOND};
    int suit = card / 13, cardty = card % 13;
    if (cardty == 8)
    {
        printf("10%s", card_suits[suit]);
    }
    else
    {
        printf("%c%s", card_faces[cardty], card_suits[suit]);
    }

    // Return zero
    return (0);
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : print_cards
// Description  : print a number of cards (no more than 13 on one line)
//
// Inputs       : cards - the array of cards to print
//                num_cards - the number of cards to print
// Outputs      : 0 always

int print_cards(int cards[], int num_cards)
{
    int j = 0;
    while (j < num_cards)
    {
        if (j % 13 == 0)
        {
            printf("\n");
        }
        print_card(cards[j]);
        printf("%s", " ");
        j++;
    }
    return (0);
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : shuffle_cards
// Description  : print a number of cards (no more than 13 on one line)
//
// Inputs       : cards - the array of cards to print
//                num_cards - the number of cards to print
// Outputs      : 0 always

int shuffle_cards(int cards[], int num_cards)
{
    // This does a Fisher-Yates shuffle with
    // the lowest space complexity I could does
    // iterates through the cards in reverse order
    int j;
    int temp;
    int k;
    for (j = num_cards - 1; j > 0; j--)
    {
        k = getRandomValue(0, j + 1);
        temp = cards[k];
        cards[k] = cards[j];
        cards[j] = temp;
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : hand_value
// Description  : return the value of the hand
//
// Inputs       : cards - the array of cards in the hand
//                num_cards - the number of cards in the hand
// Outputs      : 0 always

int hand_value(int cards[], int num_cards)
{
    // Cards valued 2-10 were offset by 2
    // Face cards set to 10
    // Aces set to 11
    int i;
    int val = 0;
    for (i = 0; i < num_cards; i++)
    {
        if ((cards[i] % 13) < 9)
        {
            val += ((cards[i] % 13) + 2);
        }
        else if ((cards[i] % 13) < 12)
        {
            val += 10;
        }
        else if ((cards[i] % 13) == 12)
        {
            val += 11;
        }
    }
    // used return to be able to store value in variable
    return (val);
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : sort_cards
// Description  : sort a collection of cards
//
// Inputs       : hand - the cards to sort
//                num_cards - the number of cards in the hand
// Outputs      : 0 always

int sort_cards(int hand[], int num_cards)
{
    // this is a simple bubble sort
    int i;
    int temp;
    int j;
    for (j = 0; j <= num_cards; j++)
    {
        for (i = 0; i <= num_cards; i++)
        {
            if (hand[i] > hand[i + 1])
            {
                temp = hand[i + 1];
                hand[i + 1] = hand[i];
                hand[i] = temp;
            }
        }
    }
    return (0);
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : dealer_play
// Description  : dealer decision to hit or stand (hit on anything less
//                than 17)
//
// Inputs       : hand - cards dealer has
//                num_cards - the number of cards in player hand
// Outputs      : 0 = stand, 1 = hit

int dealer_play(int hand[], int num_cards)
{
    // if the dealer ever has less than 17 as declared by hand_value
    // then they will hit
    if (hand_value(hand, num_cards) < 17)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : player_play
// Description  : player decision to hit or stand
//
// Inputs       : hand - cards player has
//                num_cards - the number of cards in player hand
//                dealer_card - the dealers face up card
// Outputs      : 0 = stand, 1 = hit

int player_play(int hand[], int num_cards, int dealer_card)
{
    // I created a simple strategy of the opposite of the dealer card
    // when hand value is more than 17 it will stay otherwise keep hitting
    if (hand_value(hand, num_cards) > 17)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

// ////////////////////////////////////////////////////////////////////////////////
// //
// // Function     : play_hand
// // Description  : play a hand of black jack
// //
// // Inputs       : deck - the whole deck of cards
// //                num_cards - the number of cards in the deck
// //                player_money - pointer to player amount of money
// // Outputs      : 1 if player wins, 0 if dealer wins

int play_hand(int deck[], int num_cards, float *player_money)
{
    shuffle_cards(deck, num_cards);
    int player_len = 0;
    int dealer_len = 0;
    int i;
    int player_score = 0;
    int dealer_score = 0;
    int outcome;
    int player_hand[7];
    int dealer_hand[7];

    for (i = 0; i < 2; i++)
    {
        player_hand[i] = deck[i];
        dealer_hand[i] = deck[i + 2];
        player_len++;
        dealer_len++;
        num_cards--;
    }
    int shown_card = dealer_hand[0];
    player_score = hand_value(player_hand, player_len);

    printf("%s", "Dealer Cards: ");
    print_card(shown_card);
    printf("%s", " XX");
    printf("\n");

    printf("%s", "Player Cards: ");
    print_cards(player_hand, player_len);
    printf("\n");
    if (player_score == 21)
    {
        //FIX
        *player_money += 7.5;
    }
    while (player_play(player_hand, player_len, shown_card) != 0)
    {
        player_hand[player_len] = deck[51 - num_cards];
        player_len++;
        num_cards--;
        player_score = hand_value(player_hand, player_len);

        printf("%s%d%s", "Player hit (", player_score, "): ");
        print_cards(player_hand, player_len);
        printf("\n");

        if (player_score > 21)
        {
            break;
        }
    }
    if (player_score > 21)
    {
        *player_money -= 5;
        outcome = 0;
        printf("%s\n", "Player BUSTS ... dealer wins!");
    }
    else
    {
        printf("%s%d%s", "Player stands (", player_score, "): ");
        print_cards(player_hand, player_len);
        printf("\n");

        printf("%s", "Dealer Cards: ");
        print_cards(dealer_hand, dealer_len);
        printf("\n");

        while (dealer_play(dealer_hand, dealer_len) != 0)
        {
            dealer_hand[dealer_len] = deck[51 - num_cards];
            dealer_len++;
            num_cards--;
            dealer_score = hand_value(dealer_hand, dealer_len);

            printf("%s%d%s", "Dealer hit (", dealer_score, "): ");
            print_cards(dealer_hand, dealer_len);
            printf("\n");
        }

        printf("%s%d%s", "Dealer stands (", dealer_score, "): ");
        print_cards(dealer_hand, dealer_len);
        printf("\n");

        if (player_score == 21)
        {
            *player_money += 7.5;
            outcome = 1;
            printf("%s\n", "Player has Blackjack!");
        }
        else if (player_score == dealer_score)
        {
            outcome = 0;
            printf("%s\n", "Tied!");
        }
        else if (dealer_score > 21)
        {
            *player_money += 5;
            outcome = 1;
            printf("%s\n", "Dealer BUSTS ... player wins!");
        }
        else if (dealer_score < player_score)
        {
            *player_money += 5;
            outcome = 1;
            printf("%s\n", "Player wins!");
        }
        else
        {
            *player_money -= 5;
            outcome = 0;
            printf("%s\n", "Dealer wins!");
        }
    }

    return outcome;
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : show_player_money_histogram
// Description  : Display a histogram of the player funds by hands
//
// Inputs       : money_rounds - the list of player money by hand number
//                last_round - the hand number where the game stopped
// Outputs      : 0 always

int show_player_money_histogram(float money_rounds[], int last_round)
{
    int i, j;
    printf("                                                 Player Cash By Round\n");
    for (i = 200; i >= 0; i -= 5)
    {
        if (i < 10)
        {
            printf("%d%s", i, "  | ");
        }
        else if (i < 100)
        {
            printf("%d%s", i, " | ");
        }
        else if (i >= 100)
        {
            printf("%d%s", i, "| ");
        }
        for (j = 0; j < 100; j++)
        {
            if (money_rounds[j] > i)
            {
                printf("%s", "x");
            }
            else
            {
                printf("%s", ".");
            }
        }
        printf("|\n");
    }
    printf("     ");
    for (j = 0; j < last_round; j++)
    {
        if (j % 10 == 0)
        {
            printf("%d%s", j / 10, "         ");
        }
    }
    printf("\n");
    printf("     ");
    for (j = 0; j < last_round; j++)
    {
        printf("%d", j % 10);
    }

    return 0;
}

int main(int argc, char **argv)
{

    /* Local variables */
    int cmp311_deck[NUM_CARDS]; // This is the deck of cards
    /* Preamble information */
    printf("CMPSC311 - Assignment #1 - Fall 2020\n\n");
    srand(time(NULL));

    /* Step #1 - create the deck of cards */
    int i;
    for (i = 0; i <= NUM_CARDS; i++)
    {
        cmp311_deck[i] = i;
    }

    /* Step #2 - print the deck of cards */
    print_cards(cmp311_deck, NUM_CARDS);
    printf("\n");

    // /* Step #4 - shuffle the deck */
    shuffle_cards(cmp311_deck, NUM_CARDS);

    // /* Step #5 - print the shuffled deck of cards */
    print_cards(cmp311_deck, NUM_CARDS);
    printf("\n");

    /* Step #6 - sort the cards */
    sort_cards(cmp311_deck, NUM_CARDS);

    /* Step #7 - print the sorted deck of cards */
    print_cards(cmp311_deck, NUM_CARDS);
    printf("\n");

    /* Step #9 - deal the hands */
    float money = 100.0;
    float money_history[100];
    int rnd_count = 0;
    while ((money >= 5) && (rnd_count < 100))
    {
        money_history[rnd_count] = money;
        rnd_count++;
        printf("%s\n", "-----New Hand-----");
        play_hand(cmp311_deck, NUM_CARDS, &money);
        printf("%s%d%s%f%s", "After ", rnd_count, " rounds, Player has $", money, " left!\n");
    }
    /* Step 10 show historgrapm */
    show_player_money_histogram(money_history, rnd_count);
    /* Exit the program successfully */
    printf("\n\nCMPSC311 - Assignment #1 - Spring 2020 Complete.\n");
    return (0);
}
