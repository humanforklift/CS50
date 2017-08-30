/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(int n);
void draw(int size);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init(d);
    
    draw(d);

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw(d);

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(int n)
{
    int counter = 1, x = 0, z;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            x += (n * n) - counter;
            board[i][j] = x;
            counter++; 
            x = 0;
        }    
    }
    //swaps last 2 digits around if there are an odd number of tiles
    if (n % 2 == 0) {
        z = board[n - 1][n - 2];
        board[n - 1][n - 2] = board[n - 1][n - 3];
        board[n - 1][n - 3] = z;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(int size)
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] < 10) {
                printf(" ");
            }
            printf(" %d", board[i][j]);
            if (j == size - 1) {
                printf("\n");
            }
        }
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    int e = 0;
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            if (board[i][j] == e && board[i - 1][j] == tile) {
                board[i - 1][j] = e;
                board[i][j] = tile;
                return true;
            } else if (board[i][j] == e && board[i + 1][j] == tile) {
                board[i + 1][j] = e;
                board[i][j] = tile;
                return true;
            } else if (board[i][j] == e && board[i][j - 1] == tile) {
                board[i][j - 1] = e;
                board[i][j] = tile;
                return true;
            } else if (board[i][j] == e && board[i][j + 1] == tile) {
                board[i][j + 1] = e;
                board[i][j] = tile;
                return true; 
            }
        }    
    }
    return false;
}
/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int arr[d][d], z = 1;
    for (int x = 0; x < d; x++) {
        for (int y = 0; y < d; y++) {
            if (z == d * d) {
                arr[x][y] = 0;
            } else {
                arr[x][y] = z;
                z++;
            }
        }
    }
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            while (board[i][j] != arr[i][j]) {
                return false;
            }
        }
    }
    return true;
}
