#include <stdio.h>
#include <string.h>

void getZarr(char *str, int Z[]);

// Function to search for all occurrences of pattern in text using Z algorithm
void search(char *text, char *pattern)
{
    // Create concatenated string "P$T"
    int patternLen = strlen(pattern);
    int textLen = strlen(text);
    char concat[patternLen + 1 + textLen + 1]; // +1 for '$', +1 for null terminator
    strcpy(concat, pattern);
    concat[patternLen] = '$';
    strcpy(concat + patternLen + 1, text);
    int l = patternLen + 1 + textLen;

    // Construct Z array
    int Z[l];
    getZarr(concat, Z);

    // Now looping through Z array for matching condition
    int i;
	int c=0;
    for (i = patternLen + 1; i < l; ++i)
    {
        // If Z[i] (matched region) is equal to pattern length, we found a match
        if (Z[i] == patternLen){
            printf("Pattern found at index %d\n", i - patternLen - 1);
            c=1;
        }
    }
    if(c==0){
    	printf("Pattern not found\n");
	}
}

// Function to fill Z array for given string str[]
void getZarr(char *str, int Z[])
{
    int n = strlen(str);
    int L, R, k;

    // [L,R] make a window which matches with prefix of s
    L = R = 0;
    int i;
    for (i = 1; i < n; ++i)
    {
        // If i>R, nothing matches, so calculate Z[i] using naive way
        if (i > R)
        {
            L = R = i;

            // R-L = 0 in starting, so it will start checking from 0'th index
            while (R < n && str[R - L] == str[R])
                R++;
            Z[i] = R - L;
            R--;
        }
        else
        {
            // k = i-L, so k corresponds to number which matches in [L,R] interval
            k = i - L;

            // If Z[k] is less than remaining interval, then Z[i] will be equal to Z[k]
            if (Z[k] < R - i + 1)
                Z[i] = Z[k];
            else
            {
                // Start from R and check manually
                L = i;
                while (R < n && str[R - L] == str[R])
                    R++;
                Z[i] = R - L;
                R--;
            }
        }
    }
}

// Driver program
int main()
{
    FILE *fp;
    char text[1000];   // Assuming max length of text is 1000 characters
    char pattern[100]; // Assuming max length of pattern is 100 characters

    // Open the file for reading
    fp = fopen("input-C.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    int i;
    for (i = 1; i <= 4; i++)
    {
        printf("Input %d:\n", i);

        // Read text and pattern from the file
        if (fgets(text, sizeof(text), fp) == NULL)
        {
            printf("Error reading text from file.\n");
            break;
        }

        if (fgets(pattern, sizeof(pattern), fp) == NULL)
        {
            printf("Error reading pattern from file.\n");
            break;
        }

        // Remove newline characters if present
        text[strcspn(text, "\n")] = '\0';
        pattern[strcspn(pattern, "\n")] = '\0';

        // Perform pattern search
        search(text, pattern);
        printf("\n");
    }

    fclose(fp);
    return 0;
}

