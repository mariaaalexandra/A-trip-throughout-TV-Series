#include "hunt.h"
#include <stdio.h>

/* Task 1 - Axii */

uint16_t find_spell(uint64_t memory)
{
    /*
     * The spell is 16 bits and they are in the memory exactly after 5
     * consecutive bits of 1:
     *
     *            high                                             low
     *                [][][x]...[x][x][x][1][1][1][1][1][]...[][][]
     *                    |----16bits---|
     *                          Spell
     *
     * There is only 1 group of 5 consecutive bits of 1 and the other groups
     * have less than consecutive bits of 1
     * Steps:
     * - find 5 consecutive bits of 1
     * - the NEXT 16 bits == spell
     */

    uint16_t res = -1;

    /* TODO */
    int i, j, k;
    uint64_t var, mask1, mask2, mask3, mask4, mask5, mask, mask0;
    res = 0;
    k = 0;
    // Parcurg memory
    for (i = 0; i <= 63; i++) {
        var = 1;
        mask1 = var << i;
        mask2 = var << (i + 1);
        mask3 = var << (i + 2);
        mask4 = var << (i + 3);
        mask5 = var << (i + 4);
        /* Verific daca sunt 5 biti consecutivi de 1. 
        Cum gasesc 5 biti consecutivi urmatorii 16 sunt vraja 
        si folosesc un for prin care parcurg spell*/
        if ((memory & mask1) != 0 && 
        (memory & mask2) != 0 && 
        (memory & mask3) != 0  &&  
        (memory & mask4) != 0 && (memory & mask5) != 0) {
            for (j = i + 5; j <= i + 20; j++) {
                mask = var << j;
                if ((memory & mask) != 0) {
                    mask0 = (var << k);
                    res = (res | mask0);
                }
                // k este variabila auxiliara care ma ajuta sa setez bitii din res
                k = k + 1;
            }
            break;
        }
    }
    return res;
}


uint16_t find_key(uint64_t memory)
{
    /*
     * The key is 16 bits and they are in the memory exactly before 3
     * consecutive bits of 1:
     *
     *                high                                           low
     *                     [][][][1][1][1][x][x]...[x][x][]...[][][]
     *                                    |----16bits---|
     *                                           Key
     * Steps:
     * - find 3 consecutive bits of 1
     * - the PREVIOUS 16 bits == key
     */

    uint16_t res = -1;
   
    /* TODO */
    int i, j, k;
    uint64_t var, mask1, mask2, mask3, mask, mask0;
    k = 0;
    res = 0;
    // Parcurg invers memory cu un for
    for (i = 63; i >= 0; i--) {
        var = 1;
        mask1 = var << i;
        mask2 = var << (i - 1);
        mask3 = var << (i - 2);
        /*In momentul in care gagsec 3 biti consecutivi 
        parcurg cu un for cei 16 biti anteriori*/
        if ( (memory & mask1) != 0 &&
            (memory & mask2) != 0 &&
            (memory & mask3) != 0) { 
            for (j = i - 18; j <= i - 3; j++) {
                mask = var << j;
                if ((memory & mask) != 0) {
                    mask0 = (var << k);
                    res = (res | mask0);
                }
                // k este variabila auxiliara care ma ajuta sa setez bitii din res
                k = k + 1;    
            }
        break;
        }
    }
    return res;
}


uint16_t decrypt_spell(uint16_t spell, uint16_t key)
{
    /*
     * Find the spell knowing that
     * spell_encrypted = spell_plaintext ^ key
     */

    uint16_t res = -1;
    res = spell ^ key;

    /* TODO */

    return res;
}


/* Task 2 - Sword Play */

uint32_t choose_sword(uint16_t enemy)
{
    /*
     * Help Geralt construct a sword that will give him an advantage in battle.
     * The steps we will follow:
     * - choose the corect sword
     * - brand the sword with the correct runes such that the equation
     * for that specific enemy type is true
     *
     * How does the sword look (Sword template):
     *  [][][][] [0][0][0]...[0][0][0] [][][][][][][][][][][][][][][][]
     *  -------- --------------------- --------------------------------
     *     Type    Does not matter      The "Value" such that the equation
     *                               from 2 holds depending on the enemy type
     *    4 bits      12 bits                     16 bits
     *
     * 1. Type of the sword:
     * - 1001 - Silver Sword - for monsters
     * - 0110 - Steel Sword - for humans
     *
     *  If the number of active bits from variable "enemy" is even == Monster
     *  else == Human
     *
     * 2.
     * Monster Equation:
     *    Value ^ (Enemy & (1 - Enemy)) = 0
     *
     * Human Equation:
     *    Value + Enemy = 0
     */

    uint32_t res = -1;

    /* TODO */
    res = 0;
    int contor = 0;
    int i;
    uint16_t var = 1; 
    uint16_t mask; 
    uint32_t mask0, mask1;
    //Calculez numarul de biti activi
    for (i = 0; i <= 15; i++) {
        mask = var << i;
        if ( enemy & mask) {
            contor = contor + 1;
        }
    }
    /*Daca contor este par, atunci activez bitii 28 si 31, 
    altfel activez bitii 30 si 29*/
    if (contor % 2 == 0) {
        mask0 = (var << 28);
        res = (res | mask0);
        mask1 = (var << 31);
        res = (res | mask1);
    }
    //Daca contor este impar, atunci activez bitii 30 si 29
    else {
        mask0 = (var << 30);
        res = (res | mask0 );
        mask1 = (var << 29);
        res = (res | mask1);
    }
    /*Daca este Monster, atunci parcurgem cu un for
    bitii din (enemy & (var - enemy))
    si verificam daca sunt setati, 
    in caz afirmativ setam si bitii i din res */
    if (contor % 2 == 0) {
        for (i = 0; i <= 15; i++) {
            if ((enemy & (var - enemy)) & (var << i)) {
                res = (res | (var << i));
            }
        }
    }
    /*Daca este Human, atunci parcurgem cu un for 
    bitii din (0 - enemy) si verificam daca sunt setati,
    in caz afirmativ setam si bitii i din res*/
    else {
        for (i = 0; i <= 15; i++) {
            if ((0 - enemy) & (var << i)) {
                res = (res | (var << i));
            }
        }
    }
    return res;
}


/* Task 3 - The Witcher Trials */

uint32_t trial_of_the_grasses(uint16_t cocktail)
{
    /*
     * To become a witcher one must survive a cocktail of different
     * herbs. The body should generate the correct antibodies to
     * neutralize the given cocktail.
     *
     *
     * The antibodies need to respect the following properties:
     *   (antibodies_high & cocktail) ^ (antibodies_low | cocktail) = 0
     *   antibodies_low & antibodies_high = 0
     *   antibodies_low | antibodies_high = cocktail
     *
     * Where:
     *  [][][]...[][][] | [][][]...[][][]
     *  ---------------   ---------------
     *  antibodies_high    antibodies_low
     *      16 bits           16 bits
     *      -------------------------
     *              antibodies
     */

    uint32_t res = 0;
    int i;
    uint16_t var = 1;
    /*Parcurg cu un for bitii. 
    Daca bitul i din cocktail este setat, 
    atunci activez bitul i + 16 din res*/
    for (i = 0; i <= 15; i ++) {
        if (cocktail & (var << i)) {
            res = (res | (var << (i + 16)));
        }
    }

    /* TODO */

    return res;
}


uint8_t trial_of_forrest_eyes(uint64_t map)
{
    /*
     * For the next trail, the candidate is tied up and blindfolded.
     * They are also taken to a forest and they should return until
     * the next morning.
     *
     * The candidate knows that there are 4 possibilities for the forest:
     * Brokilon, Hindar, Wolven Glade and Caed Dhu.
     *
     * The candidate also knows those forests by heart, but first you
     * need to identify the forest.
     *
     * The characteristics for 3 of the forests are as follows:
     * - Brokilon - has ONLY groups of 4 trees (or a forest without any tree)
     *   Ex: a group of 4 trees: "...00111100..."
     * - Hindar - has ONLY 2 trees in the MIDDLE
     * - Wolven Glade - FULL of trees
     *
     * The "map" variable encodes the following information:
     * - 1 tree
     * - 0 patch of grass
     *
     * You should put in the "res" variable the index for the identified
     * forrest.
     * - Brokilon - index 0
     * - Hindar - index 1
     * - Wolven Glade - index 2
     * - Caed Dhu - index 3
     */

    uint8_t res = 5;
    uint64_t var = 1;
    int i, logic, contor, logic0;
    logic = 1;
    logic0 = 1;
    //Cu variabila logic0 verific daca padurea nu contine copaci
    for ( i = 0; i <=  63; i++) {
        if ((map & (var << i)) != 0) {
            logic0 = 0;
            break;
        }
    }
    if (logic0 == 1) {
        res = 0;
    }
    /*Verific daca bitul  nu este setat, atunci sar peste el, altfel
    verific daca si urmatorii 3 biti sunt setati. In caz contrar 
    aplic break si variabila logic devine 0.*/

    else {
        for (i = 0 ; i <= 59; i++) {
            if ((map & (var << i)) == 0) {
                continue;
            
            }
            else {
                if ( (map & (var << (i + 1))) == 0) {
                    logic = 0;
                    break;
                }
        
                else {
                    if ( (map & (var << (i + 2))) == 0) {
                        logic = 0;
                        break;
                    }
                    else {
                        if ((map & (var << (i + 3))) == 0) {
                            logic = 0;
                            break;
                        }
                        /*Daca al cincilea element este pom, 
                        atunci nu se respecta regula de 4 pomi
                        consecutivi, pentru ca am avea 5*/
                        else {
                            if ( (map & (var << (i + 4))) != 0) {
                                logic = 0;
                                break;
                            }
                        }
                    }
                }
            }
            /*daca variabila logic a ramas 1 inseamna ca am gasit
            o grupare de 4 pomi si sarim peste 3 elemente
            */
        if ( logic == 1) {
            i = i + 3;
        }
        }
    }
    if (logic == 1) {
        res = 0;
    }
    //cu variabila contor numar cati pomi am in map
    contor = 0;
    for (i = 0; i <= 63; i ++) {
        if ((map & (var << i)) != 0) {
            contor = contor + 1;
        }
    }
    logic = 0;
    //Cu variabila logic verific daca elementele din mijloc sunt pomi
    if ((map & (var << 31)) != 0 && (map & (var << 32)) != 0) {
        logic = 1;
    }
    //daca variabila logic e 1 si am 2 pomi atunci este padurea Hindar
    if ((logic == 1) && (contor == 2)) {
        res = 1;
    }
    logic = 1;
    //verific daca padurea este plina de copaci
    for (i = 0; i <= 63; i++) {
        if ((map & (var << i)) == 0) {
            logic = 0;
            break;
        }
    }
    //daca variabila logic a ramas 1 inseamna ca este padurea Wolven Glade
    if (logic == 1) {
        res = 2;
    }
    /*Daca res a ramas 5 (valoarea cu care
    l-am initializat la inceputul problemei),
    inseamna ca este ultima padure*/
    if (res == 5) {
        res = 3;
    }
    /* TODO */

    return res;
}


uint8_t trial_of_the_dreams(uint32_t map)
{
    /*
     * For this final trial, the candidates go into a trance and when
     * they woke up they would be a fully fledged witcher.
     *
     * For this task, you need to help the witcher find the number
     * of steps that would take the candidate from the dream realm to
     * the real world.
     *
     * The "map" variable would have only 2 bits of 1:
     * - candidate location
     * - portal location
     *
     * You should put in the "res" variable the distance from the
     * candidate position to the portal.
     *
     *  Ex:
     *  [0][0][0][0][0][0]....[1][0][0][0][0][1][0]....[0][0][0]
     *
     *  res = 5
     */

    uint8_t res = 0;

    /* TODO */
    int i, poz1, poz2, d;
    uint32_t var = 1;
    /* Parcurg bitii din map si caut primul bit egal 1 
    si pastrez in variabila poz1 pozitia bitului.*/
    for (i = 0; i <= 31; i++) {
        if ((map & (var << i)) != 0) {
            poz1 = i;
            break;
        }
    }
    /* Parcurg bitii din map in sens invers si caut 
    ultimul bit egal 1 si pastrez in variabila poz2 pozitia bitului.*/
    for (i = 31; i >= 0; i--) {
        if ((map & (var << i)) != 0) {
            poz2 = i;
            break;
        }
    }
    // Aflu in variabila d distanta dintre pozitiile celor doi biti.
    d = poz2 - poz1;
    res = d;
    return res;
}
