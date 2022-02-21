#include "communication.h"
#include "util_comm.h"

#include <stdio.h>


/* Task 1 - The Beginning */

void send_byte_message(void)
{
    /* TODO
     * Send the encoding of the characters: R, I, C, K
     */
    send_squanch(18);
    send_squanch(9);
    send_squanch(3);
    send_squanch(11);
}


void recv_byte_message(void)
{
    /* TODO
     * Receive 5 encoded characters, decode them and print
     * them to the standard output (as characters)
     *
     * ATTENTION!: Use fprintf(stdout, ...)
     */
    int i;
    uint8_t var;
    for (i = 0; i <= 4; i++) {
        var = recv_squanch();
    /* Adun 64 la var pentru a imi afisa caracterul,
    de exemplu pentru A, var este 1 si in codul ASCII 65 */
        fprintf(stdout, "%c", var + 64);
    }
}


void comm_byte(void)
{
    /* TODO
     * Receive 10 encoded characters and send each character (the character is
     * still encoded) 2 times
     */
    int i;
    uint8_t var;
    // Parcurg cele 10 caractere
    for (i = 0; i <= 9; i++) {
        var = recv_squanch();
        send_squanch(var);
        send_squanch(var);
    }
}


/* Task 2 - Waiting for the Message */

void send_message(void)
{
    /* TODO
     * Send the message: HELLOTHERE
     * - send the encoded length
     * - send each character encoded
     */
    int len = 10;
    // Shiftez la stanga prin inmultirea cu 4
    len = 4 * 10;
    send_squanch(len);
    send_squanch(8);
    send_squanch(5);
    send_squanch(12);
    send_squanch(12);
    send_squanch(15);
    send_squanch(20);
    send_squanch(8);
    send_squanch(5);
    send_squanch(18);
    send_squanch(5);
}


void recv_message(void)
{
    /* TODO
     * Receive a message:
     * - the first value is the encoded length
     * - length x encoded characters
     * - print each decoded character
     * 
     * ATTENTION!: Use fprintf(stdout, ...)
     */
    uint8_t  var, len, var1, mask1;
    int i;
    len = recv_squanch();
    // Decodez lungimea prin shiftare la dreapta, adica impart la 4
    len = len / 4;
    // Negam bitii 4 si 5 
    var1 = 1;
    mask1 = ~ (var1 << 4);
    len = len & mask1;
    mask1 = ~ (var1 << 5);
    len = len & mask1;
    fprintf(stdout, "%u", len);
    for (i = 0; i <= len - 1; i++) {
        var = recv_squanch();
        fprintf(stdout, "%c", var + 64);
    }
}


void comm_message(void)
{
    /* TODO
     * Receive a message from Rick and do one of the following depending on the
     * last character from the message:
     * - 'P' - send back PICKLERICK
     * - anything else - send back VINDICATORS
     * You need to send the messages as you did at the previous tasks:
     * - encode the length and send it
     * - encode each character and send them
     */
    uint8_t len, var1, var, mask1;
    int len1, len2, i;
    len = recv_squanch();
    len = len / 4;
    var1 = 1;
    mask1 = ~ (var1 << 4);
    len = len & mask1;
    mask1 = ~ (var1 << 5);
    len = len & mask1;
    for (i = 0; i <= len - 1; i++) {
        var = recv_squanch();
    }
    /* Verific daca ultimul caracter este 'P' si trimit mesajul "PICKLERICK"
    in caz afirmativ sau mesajul "VINDICATORS" in caz contrar*/
    if ( var + 64 == 'P') {
        len1 = 10;
        len1 = 10 * 4;
        send_squanch(len1);
        send_squanch(16);
        send_squanch(9);
        send_squanch(3);
        send_squanch(11);
        send_squanch(12);
        send_squanch(5);
        send_squanch(18);
        send_squanch(9);
        send_squanch(3);
        send_squanch(11);
    }
    else {
        len2 = 11;
        len2 = 11 * 4;
        send_squanch(len2);
        send_squanch(22);
        send_squanch(9);
        send_squanch(14);
        send_squanch(4);
        send_squanch(9);
        send_squanch(3);
        send_squanch(1);
        send_squanch(20);
        send_squanch(15);
        send_squanch(18);
        send_squanch(19);
    }

}


/* Task 3 - In the Zone */

void send_squanch2(uint8_t c1, uint8_t c2)
{
    /* TODO
     * Steps:
     * - "merge" the character encoded in c1 and the character encoded in c2
     * - use send_squanch to send the newly formed byte
     */
    int i;
    uint8_t message = 0;
    uint8_t var2 = 1;
    uint8_t mask2;
    int j = - 1;
    int res;
    for (i = 0; i <= 3; i++) {
    /*Verific daca bitul i din c2 este setat,
    daca bitul i este setat atunci setez bitul j din message*/
        uint8_t var = 1;
        uint8_t mask = var << i;
        j = j + 1;
        if ( c2 & mask ) {
            res = 1;
        }
        else {
            res = 0;
        }
        if (res == 1) {
            var2 = 1;
            mask2 = (var2 << j);
            message = ( message | mask2);
        }
        /*Verific daca bitul i din c1 este setat,
        daca bitul i este setat setez bitul j + 1 din message*/
        j = j + 1;
        if ( c1 & mask) {
            res = 1;
        }
        else {
            res = 0;
        }
        if (res == 1) {
            var2 = 1;
            mask2 = (var2 << j );
            message = (message | mask2);
        }
        
    }

    send_squanch(message);
}


uint8_t decode_squanch2(uint8_t c)
{
    /*
     * Decode the given byte:
     * - split the two characters as in the image from ocw.cs.pub.ro
     */

    uint8_t res = -1;

    /* TODO */
    uint8_t C = 0;
    int i, res1;
    int j;
    uint8_t var2, mask2;
    // Parcurg octetul
    for (i = 0; i <= 7; i++) {
        uint8_t var = 1;
        uint8_t mask = (var << i);
        j = i / 2;
        /* Verific daca bitul i din c este setat si
        in cazul in care este setat si i este par setez bitul j (i / 2),
        altfel daca bitul este setat si
        i este impar setez bitul j (i / 2 + 4) din C */
        if (c & mask) {
            res1 = 1;
        }
        else {
            res1 = 0;
        }
        if (res1 == 1) {
            var2 = 1;
            if (i % 2 == 0) {
                mask2 = (var2 << j);
            }
            else {
                j = i / 2 + 4;
                mask2 = (var2 << j);
            }
            C = ( C | mask2);
        }

    }
    // res devine C
    res = C;
    return res;
}
