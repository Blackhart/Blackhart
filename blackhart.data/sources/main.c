#define _CRT_SECURE_NO_WARNINGS

// ~~~~~ Standard headers ~~~~~

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <omp.h>

// ~~~~~ Constantes ~~~~~

static int const    RIGHT_ASCENSION_MIN = 0;
static int const    RIGHT_ASCENSION_MAX = 360;
static int const    DECLINAISON_MIN = -90;
static int const    DECLINAISON_MAX = 90;
static int const    DISTANCE_MIN = 0;
static int const    DISTANCE_MAX = 1000;
static int const    STARS_PER_SOLID_ANGLE = 1700000000 / (360 * 180);

// ~~~~~ Dcl(INTERNAL) ~~~~~

static void generate_data(void);

// ~~~~~ Def(PUBLIC) ~~~~~

int main(void)
{
    // initialize omp
    omp_set_num_threads(omp_get_max_threads());

    // initialize random seed
    srand((unsigned int)time(NULL));

    // generate stars coordinates
    generate_data();

    return EXIT_SUCCESS;
}

// ~~~~~ Def(INTERNAL) ~~~~~

void    generate_data(void)
{
    char filename[100];
    memset(filename, '\0', 100);
    sprintf(filename, "%s/Stars", BK_DEFAULT_DATA_PATH);

    FILE* flux = fopen(filename, "w");
    if (flux == NULL)
        return;

    size_t ra1_dec1_length = sizeof(size_t) + STARS_PER_SOLID_ANGLE * 3 * sizeof(double);
    size_t ra1_dec180_length = ra1_dec1_length * 180;

    void* buffer = malloc(ra1_dec180_length);
    if (buffer == NULL)
        goto CLOSE_FILE;

    for (int right_ascension = RIGHT_ASCENSION_MIN; right_ascension < RIGHT_ASCENSION_MAX; ++right_ascension)
    {
        for (int declinaison = DECLINAISON_MIN; declinaison < DECLINAISON_MAX; ++declinaison)
        {
            void* offseted_buffer = (char*)buffer + ra1_dec1_length * (declinaison + 90);

            ((size_t*)offseted_buffer)[0] = STARS_PER_SOLID_ANGLE;

            double* coords = (double*)(((char*)offseted_buffer) + sizeof(size_t));

            for (int star_count = 0; star_count < STARS_PER_SOLID_ANGLE * 3; star_count += 3)
            {
                // generate random RA, Dec, Dist
                coords[star_count] = (rand() / (double)RAND_MAX) * ((right_ascension + 1) - right_ascension) + right_ascension;
                coords[star_count + 1] = (rand() / (double)RAND_MAX) * ((declinaison + 1) - declinaison) + declinaison;
                coords[star_count + 2] = (rand() / (double)RAND_MAX) * (DISTANCE_MAX - DISTANCE_MIN) + DISTANCE_MIN;
            }
        }

        // serialize stars coords on the disk
        fwrite(buffer, sizeof(char), ra1_dec180_length, flux);
    }

    free(buffer);

CLOSE_FILE:
    fclose(flux);
}
