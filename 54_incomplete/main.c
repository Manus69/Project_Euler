#include "why.h"

#include <stdio.h>
#include <stdlib.h>

#define _FILE ("p054_poker.txt")
#define CARDS_PER_HAND (5)

enum SCORE
{
    ONE_CARD,
    PAIR, TWO_PAIRS, THREE_CARDS, STRAIGHT, FLUSH, FULL_HOUSE,
    FOUR_CARDS, STRAIGHT_FLUSH, ROYAL_FLUSH,
};

struct Card
{
    char     rank;
    char     suit;
};

typedef struct Card Card;

struct Hand
{
    Card*   cards[CARDS_PER_HAND];
};

typedef struct Hand Hand;

struct Game
{
    Hand* lhs;
    Hand* rhs;
};

typedef struct Game Game;

static Int _compare_letters(char lhs, char rhs)
{
    if (lhs == rhs)
        return 0;
    
    if (lhs == 'A')
        return -1; 
    else if (rhs == 'A')
        return 1;
    
    if (lhs == 'K')
        return -1;
    else if (rhs == 'K')
        return 1;
    
    if (lhs == 'Q')
        return -1;
    else if (rhs == 'Q')
        return 1;
    
    if (lhs == 'J')
        return -1;
    else if (rhs == 'J')
        return 1;
    
    return 0;
}

static Int _compare(const void* lhs, const void* rhs)
{
    char* _lhs;
    char* _rhs;
    Int result;

    _lhs = *(char **)lhs;
    _rhs = *(char **)rhs;

    if (*_lhs >= 'A' && *_rhs >= 'A')
    {
        if ((result = _compare_letters(*_lhs, *_rhs)))
            return result;
    }
    
    return CompareCstr(lhs, rhs);
}

Card* CardCreate(const char* string)
{
    Card* card;

    card = malloc(sizeof(*card));
    WhySavePtr(&card);

    card->rank = *string ++;
    card->suit = *string;

    return card;
}

Hand* HandCreate(const Deck* strings, Uint index)
{
    Hand* hand;
    Card* card;
    Uint n;
    Uint n_cards;
    char* string;

    hand = malloc(sizeof(*hand));
    WhySavePtr(&hand);

    n = 0;
    n_cards = CARDS_PER_HAND;

    while (n_cards)
    {
        string = *(char **)DeckPointAt(strings, n + index);
        card = CardCreate(string);
        hand->cards[n] = card;

        ++ n;
        -- n_cards;
    }

    return hand;
}

Int HandCompare(const Hand* lhs, const Hand* rhs)
{

}

Game* GameCreate(const Deck* strings)
{
    Game* game;
    Hand* lhs;
    Hand* rhs;
    
    game = malloc(sizeof(*game));
    WhySavePtr(&game);

    lhs = HandCreate(strings, 0);
    rhs = HandCreate(strings, CARDS_PER_HAND);
    game->lhs = lhs;
    game->rhs = rhs;

    return game;
}

static Deck* _get_all_games(const Deck* lines)
{
    Uint n;
    char* string;
    Deck* substrings;
    Deck* games;
    Game* game;

    games = DeckCreatePtr(NULL, NULL);
    n = 0;
    while (n < DeckNItems(lines))
    {
        string = *(char **)DeckPointAt(lines, n);
        substrings = StringSplit(string, ' ');

        SortDeckSlice(substrings, 0, CARDS_PER_HAND - 1, _compare);
        SortDeckSlice(substrings, CARDS_PER_HAND, 2 * CARDS_PER_HAND - 1, _compare);
        PrintDeck(substrings, PrintCstrS);

        game = GameCreate(substrings);
        DeckDestroy(substrings);

        DeckPushBack(games, &game);
        ++ n;
    }

    return games;
}

//need to implement hand compare which sounds very boring

int main()
{
    WhyStart();

    Deck* lines;
    Deck* games;
    lines = ReadFileAllLines(_FILE);
    // PrintDeck(lines, PrintCstrN);

    games = _get_all_games(lines);

    DeckDestroy(lines);
    DeckDestroy(games);
    WhyEnd();

    return 0;
}