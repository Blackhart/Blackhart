#define _CRT_SECURE_NO_WARNINGS

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

// ~~~~~ Dcl(INTERNAL) ~~~~~

static void generate_data(void);
static void serialize(void* buffer, size_t buffer_length, int ra, int dec);

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
    size_t buffer_length = sizeof(size_t) + STARS_PER_SOLID_ANGLE * 3 * sizeof(double);
    void* buffer = malloc(buffer_length * sizeof(char));
    if (buffer == NULL)
        return;

    ((size_t*)buffer)[0] = STARS_PER_SOLID_ANGLE;

    double* coords = (double*)(((char*)buffer) + sizeof(size_t));

    for (int right_ascension = RIGHT_ASCENSION_MIN; right_ascension <= RIGHT_ASCENSION_MAX; ++right_ascension)
    {
        for (int declinaison = DECLINAISON_MIN; declinaison <= DECLINAISON_MAX; ++declinaison)
        {
            for (int star_count = 0; star_count < STARS_PER_SOLID_ANGLE; ++star_count)
            {
                // generate random RA, Dec, Dist
                coords[star_count] = (rand() / (double)RAND_MAX) * ((right_ascension + 1) - right_ascension) + right_ascension;
                coords[star_count + 1] = (rand() / (double)RAND_MAX) * ((declinaison + 1) - declinaison) + declinaison;
                coords[star_count + 2] = (rand() / (double)RAND_MAX) * (DISTANCE_MAX - DISTANCE_MIN) + DISTANCE_MIN;
            }

            // serialize stars coords on the disk
            serialize(buffer, buffer_length, right_ascension, declinaison);
        }
    }

    free(buffer);
}

void    serialize(void* buffer, size_t buffer_length, int ra, int dec)
{
    char filename[100];
    memset(filename, '\0', 100);
    sprintf(filename, "%s/Stars_%d_%d", BK_DEFAULT_DATA_PATH, ra, dec);

    FILE* flux = fopen(filename, "w");
    fwrite(buffer, sizeof(char), buffer_length, flux);
    fclose(flux);
}
