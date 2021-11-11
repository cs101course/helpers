#include <stdio.h>
#include <stdbool.h>

/* 
 * Read a line from the provided filePtr
 * and stores the line in string.
 * A maximum of numChars will be read.
 * Returns the number of characters copied to string, including a final \0 character.
 *  (it will be <= numChars + 1)
 */
int readLine(FILE *filePtr, char *string, int numChars);

/* 
 * Read from a file up until the provided delimeter character,
 * or EOF (end of file).
 * A maximum of numChars will be read.
 * Returns the number of characters copied to string, including a final \0 character.
 *  (it will be <= numChars + 1)
 */
int readUntilDelim(FILE *filePtr, char delimeter, char *string, int numChars);

/* 
 * Read a string and attempt to convert it to an integer (in the given base)
 * A maximum of numChars will be read, including the \0 terminator.
 * The conversion will take place in the base provided.
 * The value pointed to by isConverted will be set to true if conversion was successful,
 * and set to false otherwise.
 * Beginning and trailing whitespace is ignored.
 * Returns an integer, or 0 if no value could be converted.
 */
long int intFromString(char *string, int numChars, int base, bool *isConverted);

/* Read a string and attempt to convert it to a double (base 10).
 * A maximum of numChars will be read, including the \0 terminator.
 * The value pointed to by isConverted will be set to true if conversion was successful,
 * and set to false otherwise.
 * Beginning and trailing whitespace is ignored.
 * Returns a double, or 0.0 if no value could be converted
 */
double doubleFromString(char *string, int numChars, bool *isConverted);


/* Strip whitespace from the beginning and end of a string
 * A maximum of numChars will be read, including the \0 terminator.
 * The result will be saved to outputString.
 * Returns the number of characters (including \0 terminator) of outputString
 */
int stripWhitespace(char *inputString, int numChars, char *outputString);

/* Strip whitespace from the beginning of a string
 * A maximum of numChars will be read, including the \0 terminator.
 * The result will be saved to outputString.
 * Returns the number of characters (including \0 terminator) of outputString
 */
int stripBeginningWhitespace(char *inputString, int numChars, char *outputString);

/* Strip whitespace from the end of a string
 * A maximum of numChars will be read, including the \0 terminator.
 * The result will be saved to outputString.
 * Returns the number of characters (including \0 terminator) of outputString
 */
int stripTrailingWhitespace(char *inputString, int numChars, char *outputString);
