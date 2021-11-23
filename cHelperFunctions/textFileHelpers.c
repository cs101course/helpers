#include <ctype.h>
#include <stdlib.h>
#include "textFileHelpers.h"

/* 
 * Read a line from the provided filePtr
 * and stores the line in string.
 * A maximum of maxChars will be read.
 * Returns the number of characters copied to string, including a final \0 character.
 *  (it will be <= maxChars + 1)
 */
int readLine(FILE *filePtr, char *string, int maxChars) {
    return readUntilDelim(filePtr, '\n', string, maxChars);
}

/* 
 * Read from a file up until the provided delimeter character,
 * or EOF (end of file).
 * A maximum of maxChars will be read.
 * Returns the number of characters copied to string, including a final \0 character.
 *  (it will be <= maxChars + 1)
 */
int readUntilDelim(FILE *filePtr, char delimeter, char *string, int maxChars) {
    int characterIndex;
    bool isFinished;
    char currentChar;

    isFinished = false;
    characterIndex = 0;
    currentChar = fgetc(filePtr);
    if (currentChar == EOF) {
        isFinished = true;
    }
    while (characterIndex != maxChars && !isFinished) {
        if (currentChar == EOF || currentChar == delimeter) {
            // The current character is the end of file, or
            // the delimeter has been reached
            isFinished = true;
        } else {
            string[characterIndex] = currentChar;
        }

        characterIndex++;
        if (characterIndex != maxChars && !isFinished) {
            currentChar = fgetc(filePtr);
        }
    }

    // Finish off the string with the final null terminator
    if (characterIndex > 0) {
        string[characterIndex-1] = '\0';
    }

    return characterIndex;
}

/* 
 * Read a string and attempt to convert it to an integer (in the given base)
 * A maximum of maxChars will be read, including the \0 terminator.
 * The conversion will take place in the base provided.
 * The value pointed to by isConverted will be set to true if conversion was successful,
 * and set to false otherwise.
 * Beginning and trailing whitespace is ignored.
 * Returns an integer, or 0 if no value could be converted.
 */
long int intFromString(char *string, int maxChars, int base, bool *isConverted) {
    int convertedValue;
    char strippedString[maxChars + 1];
    char *endPtr;

    stripWhitespace(string, maxChars, strippedString);

    convertedValue = strtol(strippedString, &endPtr, base);
    if (endPtr == strippedString) {
        // nothing was read
        *isConverted = false;
    } else {
        *isConverted = true;
    }

    return convertedValue;
}

/* 
 * Read a string and attempt to convert it to a double (base 10).
 * A maximum of maxChars will be read, including the \0 terminator.
 * The value pointed to by isConverted will be set to true if conversion was successful,
 * and set to false otherwise.
 * Beginning and trailing whitespace is ignored.
 * Returns a double, or 0.0 if no value could be converted
 */
double doubleFromString(char *string, int maxChars, bool *isConverted) {
    double convertedValue;
    char strippedString[maxChars + 1];
    char *endPtr;

    stripWhitespace(string, maxChars, strippedString);

    convertedValue = strtod(strippedString, &endPtr);
    if (endPtr == strippedString) {
        // nothing was read
        *isConverted = false;
    } else {
        *isConverted = true;
    }

    return convertedValue;
}

/* 
 * Strip whitespace from the beginning and end of a string
 * A maximum of maxChars will be read, including the \0 terminator.
 * The result will be saved to outputString.
 * Returns the number of characters (including \0 terminator) of outputString
 */
int stripWhitespace(char *inputString, int maxChars, char *outputString) {
    char frontStrippedString[maxChars + 1];
    
    stripBeginningWhitespace(inputString, maxChars, frontStrippedString);
    return stripTrailingWhitespace(frontStrippedString, maxChars, outputString);
}

/* 
 * Strip whitespace from the beginning of a string
 * A maximum of maxChars will be read, including the \0 terminator.
 * The result will be saved to outputString.
 * Returns the number of characters (including \0 terminator) of outputString
 */
int stripBeginningWhitespace(char *inputString, int maxChars, char *outputString) {
    int firstIndex;
    int inputIndex;
    int outputIndex;

    // skip past all spaces
    firstIndex = 0;
    while (firstIndex != maxChars 
            && inputString[firstIndex] != '\0'
            && isspace(inputString[firstIndex])) {
        firstIndex++;
    }

    // Copy over the rest of the characters
    inputIndex = firstIndex;
    outputIndex = 0;
    while (inputIndex != maxChars && inputString[inputIndex] != '\0') {
        outputString[outputIndex] = inputString[inputIndex];
        outputIndex++;
        inputIndex++;
    }

    outputString[outputIndex] = '\0';

    return outputIndex + 1;
}

/* 
 * Strip whitespace from the end of a string
 * A maximum of maxChars will be read, including the \0 terminator.
 * The result will be saved to outputString.
 * Returns the number of characters (including \0 terminator) of outputString
 */
int stripTrailingWhitespace(char *inputString, int maxChars, char *outputString) {
    int outputIndex;
    int lastIndex;

    // Find the end of the string
    lastIndex = 0;
    while (lastIndex != maxChars && inputString[lastIndex] != '\0') {
        lastIndex++;
    }

    // move back one step, to the previous character
    lastIndex--;

    // Move backwards, skipping spaces
    while (lastIndex != 0 && isspace(inputString[lastIndex])) {
        lastIndex--;
    }

    // Copy over the rest of the characters
    outputIndex = 0;
    while (outputIndex <= lastIndex && inputString[outputIndex] != '\0') {
        outputString[outputIndex] = inputString[outputIndex];
        outputIndex++;
    }

    outputString[outputIndex] = '\0';

    return outputIndex + 1;
}
