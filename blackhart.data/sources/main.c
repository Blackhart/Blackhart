// ~~~~~ Standard headers ~~~~~

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

// ~~~~~ Constantes ~~~~~

static int const    RIGHT_ASCENSION_MIN = 0;
static int const    RIGHT_ASCENSION_MAX = 359; // because 360 degrees = 0 degrees
static int const    DECLINAISON_MIN = -90;
static int const    DECLINAISON_MAX = 90;
static int const    DISTANCE_MIN = 0;
static int const    DISTANCE_MAX = 1000;
static int const    STARS_PER_SOLID_ANGLE = 1700000000 / (360 * 180);

// ~~~~~ Structs ~~~~~

struct EquatorialCoord
{
    double  ra;
    double  dec;
    double  dist;
};

struct Stars
{
    size_t                  count;
    struct EquatorialCoord* coords;
};

// ~~~~~ Dcl(INTERNAL) ~~~~~

static void generate_data(void);
static void serialize(struct Stars const* stars, int ra, int dec);

// ~~~~~ Def(PUBLIC) ~~~~~

int main(void)
{
    // initialize random seed
    srand((unsigned int)time(NULL));

    // generate stars coordinates
    generate_data();

    return EXIT_SUCCESS;
}

// ~~~~~ Def(INTERNAL) ~~~~~

void    generate_data(void)
{
    struct Stars stars;

    stars.count = STARS_PER_SOLID_ANGLE;
    stars.coords = malloc(stars.count * sizeof(struct EquatorialCoord));

    for (int right_ascension = RIGHT_ASCENSION_MIN; right_ascension <= RIGHT_ASCENSION_MAX; ++right_ascension)
    {
        for (int declinaison = DECLINAISON_MIN; declinaison <= DECLINAISON_MAX; ++declinaison)
        {
            for (int star_count = 0; star_count < stars.count; ++star_count)
            {
                // generate random RA, Dec, Dist
                stars.coords[star_count].ra = (rand() / (double)RAND_MAX) * ((right_ascension + 1) - right_ascension) + right_ascension;
                stars.coords[star_count].dec = (rand() / (double)RAND_MAX) * ((declinaison + 1) - declinaison) + declinaison;
                stars.coords[star_count].dist = (rand() / (double)RAND_MAX) * (DISTANCE_MAX - DISTANCE_MIN) + DISTANCE_MIN;
            }

            serialize(&stars, right_ascension, declinaison);
        }
    }

    free(stars.coords);
}

void    serialize(struct Stars const* stars, int ra, int dec)
{
    char filename[14];

    memset(filename, '\0', 14);

    sprintf_s(filename, 14, "Stars_%d_%d", ra, dec);

    printf("%s\n", filename);
}