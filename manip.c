#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHAR_SIZE 255
#define CHARACTERS_NUM 25

// https://stackoverflow.com/questions/3536153/c-dynamically-growing-array

typedef struct {
    int *array;
    size_t used;
    size_t size;
} Array;

void initArray(Array *a, size_t initialSize) {
    a->array = (uint32_t *)malloc(initialSize * sizeof(uint32_t));
    a->used = 0;
    a->size = initialSize;
}

void insertArray(Array *a, uint32_t element) {
    // a->used is the number of used entries, because a->array[a->used++]
    //updates a->used only *after* the array has been accessed.
    // Therefore a->used can go up to a->size 
    if (a->used == a->size) {
        a->size *= 2;
        a->array = (uint32_t *)realloc(a->array, a->size * sizeof(uint32_t));
    }
    a->array[a->used++] = element;
}

void freeArray(Array *a) {
    free(a->array);
    a->array = NULL;
    a->used = a->size = 0;
}

typedef struct {
    uint8_t match;
    uint32_t start;
    uint32_t end;
} Match;

typedef struct {
    Match *array;
    size_t used;
    size_t size;
} MatchArray;

void initMatchArray(MatchArray *a, size_t initialSize) {
    a->array = (Match *)malloc(initialSize * sizeof(Match));
    a->used = 0;
    a->size = initialSize;
}

void insertMatchArray(MatchArray *a, Match element) {
    // a->used is the number of used entries, because a->array[a->used++]
    //updates a->used only *after* the array has been accessed.
    // Therefore a->used can go up to a->size 
    if (a->used == a->size) {
        a->size *= 2;
        a->array = (Match *)realloc(a->array, a->size * sizeof(Match));
    }
    a->array[a->used++] = element;
}

void freeMatchArray(MatchArray *a) {
    free(a->array);
    a->array = NULL;
    a->used = a->size = 0;
}


// ----------------------------------------------------------------------
static const char *CHARACTERS[CHARACTERS_NUM] = {
    "drmario",
    "mario",
    "luigi",
    "bowser",
    "peach",
    "yoshi",
    "dk",
    "cfalcon",
    "ganondorf",
    "falco",
    "fox",
    "ness",
    "ics",
    "kirby",
    "samus",
    "zelda",
    "link",
    "ylink",
    "pichu",
    "pikachu",
    "jigglypuff",
    "mewtwo",
    "gnw",
    "marth",
    "roy"
};

int reverse_character_lookup(char *s) {
    int i;
    for (i=0; i<CHARACTERS_NUM; i++) {
        int cmp = strcmp(CHARACTERS[i], s);
        if (!cmp) return i;
    }
    return -1;
}

void character_lookup(char *s, size_t size, uint32_t character){
    char *char_string;
    switch(character) {
        case 0:
            char_string = "Dr. Mario";
            break;
        case 1:
            char_string = "Mario";
            break;
        case 2:
            char_string = "Luigi";
            break;
        case 3:
            char_string = "Bowser";
            break;
        case 4:
            char_string = "Peach";
            break;
        case 5:
            char_string = "Yoshi";
            break;
        case 6:
            char_string = "DK";
            break;
        case 7:
            char_string = "C. Falcon";
            break;
        case 8:
            char_string = "Ganondorf";
            break;
        case 9:
            char_string = "Falco";
            break;
        case 10:
            char_string = "Fox";
            break;
        case 11:
            char_string = "Ness";
            break;
        case 12:
            char_string = "Ice Climbers";
            break;
        case 13:
            char_string = "Kirby";
            break;
        case 14:
            char_string = "Samus";
            break;
        case 15:
            char_string = "Zelda";
            break;
        case 16:
            char_string = "Link";
            break;
        case 17:
            char_string = "Young Link";
            break;
        case 18:
            char_string = "Pichu";
            break;
        case 19:
            char_string = "Pikachu";
            break;
        case 20:
            char_string = "Jigglypuff";
            break;
        case 21:
            char_string = "Mewtwo";
            break;
        case 22:
            char_string = "Mr. Game & Watch";
            break;
        case 23:
            char_string = "Marth";
            break;
        case 24:
            char_string = "Roy";
            break;
        default:
            char_string = "Unknown ???";
    }
    strncpy(s, char_string, size-1);
    s[size-1] = '\0';
}

void rng_adv(uint32_t *seed) {
    // integer overflow automatically accounted for
    *seed = ((*seed * 214013) + 2531011);
}

uint32_t rng_int(uint32_t *seed, uint32_t max_val) {
    uint32_t top_bits = *seed >> 16;
    return (max_val * top_bits) >> 16;
}

void check_sequence(uint32_t seed, uint32_t prev_seed, Match *m, Array *characters){
    int i;
    m->start = prev_seed;
    m->end = 0;
    m->match = 0;
    for(i=0; i<characters->used-1; i++){
        rng_adv(&seed);
        rng_adv(&seed);
        if (rng_int(&seed, 25) != characters->array[i+1]) {
            return;
        }
    }
    rng_adv(&seed);
    m->match = 1;
    m->end = seed;
}

void seed_find() {
    uint32_t prev_seed = 0x00000001; // init seed
    uint32_t seed = prev_seed;
    rng_adv(&seed);
    char msg[CHAR_SIZE]; // loop messages
    char character[32]; // loop character select
    Array characters; // array of characters entered by user
    initArray(&characters, 16); // array init
    uint32_t i; // loops

    // display characters

    printf("allowed inputs: \n  ");
    for (i=0; i<CHARACTERS_NUM; i++) {
        printf("%s%s", CHARACTERS[i], (i<CHARACTERS_NUM-1) ? ", " : "\n");
        if (!((i+1) % 5) && i<CHARACTERS_NUM-1) printf("\n  ");
    }

    // input loop

    i=1;
    while(1) {
        printf("Character %u -> ", i);
        scanf("%31s", character);
        int character_num = reverse_character_lookup(character);
        if (character_num < 0)
            break;
        insertArray(&characters, character_num);
        character_lookup(msg, CHAR_SIZE, character_num);
        printf("#%u: %s\n", i, msg);
        i++;
    }

    // print out character list

    printf("No more characters. Doing RNG search...\n");
    printf("Final list:\n");
    for (i=0; i<characters.used; i++) {
        character_lookup(msg, CHAR_SIZE, characters.array[i]);
        printf("%s(%u)%s", 
            msg, 
            characters.array[i], 
            (i < characters.used-1) ? ", " : "\n");
    }
    
    // checking sequences 

    MatchArray matches;
    initMatchArray(&matches, 16);
    uint32_t value;
    for (i=0; i<0xFFFFFFFF; i++) {
        if (rng_int(&seed, 25) == characters.array[0]) {
            Match match;
            check_sequence(seed, prev_seed, &match, &characters);
            if (match.match) {
                insertMatchArray(&matches, match);
            }
        }
        if (!(i % 0x1234517))
            printf("Scanning: 0x%08X -> 0x%08X ... %u matches%s\r", 
                i, seed, matches.used, (matches.used > 0) ? "!" : ".");
        prev_seed = seed;
        rng_adv(&seed);
    }

    // printing results

    printf("Scanning: 0x%08X -> 0x%08X ... %u matches%s\n", 
        i, seed, matches.used, (matches.used > 0) ? "!" : ".");

    printf("List of matches:\n");
    for(i=0; i<matches.used; i++) {
        printf("== Match %d ==\n", i);
        uint32_t current_seed = matches.array[i].end;
        printf(" Start:   0x%08X\n", matches.array[i].start);
        printf(" Current: 0x%08X\n", matches.array[i].end);
        printf(" Next 5: ");
        int j;
        for (j=0; j<6; j++) {
            rng_adv(&current_seed);
            character_lookup(msg, CHAR_SIZE, rng_int(&current_seed, 25));
            printf("%s%s", msg, (j<5) ? ", " : "...\n");
            rng_adv(&current_seed);
        }
    }
}

// begin

int main() {
    printf("----------------------------------------\n");
    printf("SSBM RNG Seed Character Checking Program\n");
    printf("Written in C by Savestate\n");
    printf("----------------------------------------\n");
    char answer;
    printf("Locate seed? y/n -> ");
    scanf("%c", &answer);
    if (answer == 'y' || answer == 'Y')
        seed_find();
    
}