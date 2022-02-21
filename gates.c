#include "gates.h"

#include <stdio.h>
#include <assert.h>

/* Task 1 - Bit by Bit */

uint8_t get_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint8_t res = -1;

    /* TODO
     *
     * "res" should be 1 if the bit is active, else 0
     */

    uint64_t var = 1;
    uint64_t mask = var << i;
    if (nr & mask) {
        res = 1;
    }
    else {
        res = 0;
    }


    return res;
}


uint64_t flip_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = -1;

    /* TODO
     *
     * Return the "nr" with the ith bit flipped
     */
    
    uint64_t var = 1;
    uint64_t mask = (var << i);
    if ( nr & mask ) {
        mask = ~ (var << i);
        nr = (nr & mask);
        res = nr;
    }
    else {
        mask = (var << i);
        res = (nr | mask);
    }
    return res;
}


uint64_t activate_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = 0xFF;

    /* TODO
     *
     * Return the "nr" with the ith bit "1"
     */
    uint64_t var = 1;
    uint64_t mask = (var << i);
    res = (nr | mask);
    return res;
}


uint64_t clear_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = -1;

    /* TODO
     *
     * Return the "nr" with the ith bit "0"
     */
    uint64_t var = 1;
    uint64_t mask = ~ (var << i);
    nr = nr & mask;
    res = nr;
    return res;
}


/* Task 2 - One Gate to Rule Them All */

uint8_t nand_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    return !(a & b);
}


uint8_t and_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    /* TODO - Use the nand gate to implement the and gate */
    res = nand_gate(nand_gate(a, b), nand_gate(a,b));
    return res;
}


uint8_t not_gate(uint8_t a)
{
    assert (a == 0 || a == 1);

    uint8_t res = -1;

    /* TODO - Use the nand gate to implement the not gate */
    res = nand_gate(a, a);
    return res;
}


uint8_t or_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    /* TODO - Use the previously defined gates to implement the or gate */
    res = nand_gate(nand_gate(a, a), nand_gate(b, b));
    return res;
}


uint8_t xor_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    /* TODO - Use the previously defined gates to implement the xor gate */
    res = nand_gate(nand_gate(nand_gate(a,b), a), nand_gate(nand_gate(a,b), b));
    return res;
}


/* Task 3 - Just Carry the Bit */

uint8_t full_adder(uint8_t a, uint8_t b, uint8_t c)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);
    assert (c == 0 || c == 1);

    uint8_t res = -1;

    /* TODO - implement the full_adder using the previous gates
     * Since the full_adder needs to provide 2 results, you should
     * encode the sum bit and the carry bit in one byte - you can encode
     * it in whatever way you like
     */
    uint8_t S, C;
    S = xor_gate(xor_gate(a, b), c);
    C = or_gate(and_gate(a, b), and_gate(c, xor_gate(a, b)));
    res = 0;
    // Pe primul bit din res pastrez c si pe al doilea bit  pastrez s
    if (S) {
        res = activate_bit(res, 1);
    }
    if (C) {
        res = activate_bit(res, 0);
    }
    return res;
}


uint64_t ripple_carry_adder(uint64_t a, uint64_t b)
{
    uint64_t res = 0;

    /* TODO
     * Use the full_adder to implement the ripple carry adder
     * If there is ANY overflow while adding "a" and "b" then the
     * result should be 0
     */
    int i;
    uint8_t C = 0;
    uint8_t A;
    for(i = 0; i <= 63; i++) {
       A = full_adder(get_bit(a, i), get_bit(b, i), C);
       C = get_bit(A, 0);
       if (get_bit(A, 1)) {
           res = activate_bit(res, i);
       }
    }
    /* Daca variabila C este diferita de 0,
    atunci are loc overflow si returnez 0 */
    if (C) {
        res = 0;
    }

    return res;
}
