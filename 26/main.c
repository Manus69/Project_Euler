// #in lude "why.h"

// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>

// #define SIZE (1000)
// #define N_DIGITS (1000)
// #define BUFF_SIZE (N_DIGITS + 1)
// #define N_DECKS (10)

// struct DigitBuffer
// {
//     char    digits[BUFF_SIZE];
//     Uint    insert_index;
//     Deck*   substrings[N_DECKS];
// };

// typedef struct DigitBuffer DigitBuffer;

// static void _create_decks(Deck* decks[N_DECKS])
// {
//     Uint n;

//     n = 0;
//     while (n < N_DECKS)
//     {
//         decks[n] = DeckCreatePtr(NULL, NULL);
//         ++ n;
//     }
// }

// static void _reset_decks(Deck* decks[N_DECKS])
// {
//     Uint n;

//     n = 0;
//     while (n < N_DECKS)
//     {
//         DeckDestroy(decks[n]);
//         decks[n] = DeckCreatePtr(NULL, NULL);
//         ++ n;
//     }
// }

// static void _destroy_decks(Deck* decks[N_DECKS])
// {
//     Uint n;

//     n = 0;
//     while (n < N_DECKS)
//     {
//         DeckDestroy(decks[n]);
//         ++ n;
//     }
// }

// DigitBuffer* DigitBufferCreate()
// {
//     DigitBuffer* digit_buffer;

//     digit_buffer = malloc(sizeof(*digit_buffer));
//     memset(digit_buffer->digits, 0, BUFF_SIZE);
//     digit_buffer->insert_index = 0;
//     _create_decks(digit_buffer->substrings);

//     return digit_buffer;
// }

// void DigitBufferReset(DigitBuffer* digit_buffer)
// {
//     memset(digit_buffer->digits, 0, BUFF_SIZE);
//     digit_buffer->insert_index = 0;
//     _reset_decks(digit_buffer->substrings);
// }

// char DigitBufferGet(const DigitBuffer* digit_buffer, Uint index)
// {
//     return digit_buffer->digits[index];
// }

// Uint _match_substrings(const char* lhs, const char* rhs)
// {
//     Uint distance;
//     Uint current;

//     distance = rhs - lhs;
//     current = distance;

//     while (true)
//     {
//         if (current == 0)
//             return distance;

//         if (*lhs != *rhs)
//             return 0;

//         ++ lhs;
//         ++ rhs;
//         -- current;
//     }
// }

// Uint _try_match(const DigitBuffer* digit_buffer, Uint index)
// {
//     char* string;
//     char* current;
//     Deck* substrings;
//     Uint n;
//     Uint result;

//     string = (char *)digit_buffer->digits + index;
//     index = DigitBufferGet(digit_buffer, index) - '0';
//     substrings = digit_buffer->substrings[index];
//     n = 0;

//     while (n + 1 < DeckNItems(substrings))
//     {
//         current = *(char **)DeckPointAt(substrings, n);
//         result = _match_substrings(current, string);

//         if (result)
//             return result;

//         ++ n;
//     }

//     return 0;
// }

// void DigitBufferGetNextDigit(DigitBuffer* digit_buffer, Uint* top, Uint bot)
// {
//     *top = *top * 10;

//     if (*top < bot)
//     {
//         digit_buffer->digits[digit_buffer->insert_index] = '0';
//     }
//     else
//     {
//         digit_buffer->digits[digit_buffer->insert_index] = (*top / bot) + '0';
//         *top = *top % bot;

//         printf("%zu\n", *top % bot);
//     }

//     ++ digit_buffer->insert_index;
// }

// void DigitBufferGetNDigits(DigitBuffer* digit_buffer, Uint* top, Uint bot, Uint n)
// {
//     while (n)
//     {
//         DigitBufferGetNextDigit(digit_buffer, top, bot);
//         -- n;
//     }
// }

// void DigitBufferMemorizeLocation(DigitBuffer* digit_buffer, Uint index)
// {
//     Uint digit;
//     Deck* deck;
//     char* current;

//     digit = digit_buffer->digits[index];
//     digit -= '0';
//     deck = digit_buffer->substrings[digit];
//     current = digit_buffer->digits + index;
//     DeckPushBack(deck, &current);
// }

// Uint _get_max_distance(const DigitBuffer* digit_buffer)
// {
//     Uint    index;
//     Uint    diff;
//     Deck*   deck;
//     char*   current;

//     index = digit_buffer->digits[digit_buffer->insert_index - 1] - '0';
//     deck = digit_buffer->substrings[index];

//     if (DeckNItems(deck) == 0)
//         return 0;
    
//     current = *(char **)DeckPointAt(deck, 0);
//     diff = digit_buffer->digits + digit_buffer->insert_index - 1 - current;

//     return diff;
// }

// void _generate_digits(DigitBuffer* digit_buffer, Uint* top, Uint bot)
// {
//     Uint n_digits;

//     n_digits = _get_max_distance(digit_buffer);
//     DigitBufferGetNDigits(digit_buffer, top, bot, n_digits);
// }

// Uint _find_longest_sequence(Uint top, Uint bot, DigitBuffer* digit_buffer)
// {
//     Uint index;
//     Uint result;

//     result = 0;
//     DigitBufferReset(digit_buffer);
//     DigitBufferGetNextDigit(digit_buffer, &top, bot);
//     DigitBufferMemorizeLocation(digit_buffer, 0);
//     index = 1;

//     while (top)
//     {
//         if (index == digit_buffer->insert_index)
//         {
//             DigitBufferGetNextDigit(digit_buffer, &top, bot);
//             _generate_digits(digit_buffer, &top, bot);
//         }
        
//         DigitBufferMemorizeLocation(digit_buffer, index);

//         result = _try_match(digit_buffer, index);

//         // if (result)
//         //     break ;

//         if (index > 20)
//             break;

//         ++ index;
//     }

//     printf("%s\n", digit_buffer->digits);

//     return result;
// }

// // int main()
// // {
// //     DigitBuffer* digit_buffer;
// //     Uint top;
// //     Uint bot;

// //     digit_buffer = DigitBufferCreate();

// //     top = 1;
// //     bot = 100;

// //     Uint result = _find_longest_sequence(top, bot, digit_buffer);
// //     PrintUintN(&result);

// //     _destroy_decks(digit_buffer->substrings);
// //     free(digit_buffer);

// //     return EXIT_SUCCESS;
// // }