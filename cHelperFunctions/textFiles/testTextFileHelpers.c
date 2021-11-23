#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "textFileHelpers.h"

#define LINE_SIZE 1024

void testReadLine(void) {
    char line[LINE_SIZE];
    int charsRead;
    FILE *filePtr = fopen("testFile.txt", "r");

    charsRead = readLine(filePtr, line, LINE_SIZE);
    assert(charsRead == 14);
    assert(strncmp(line, "hello, world!", charsRead) == 0);

    charsRead = readLine(filePtr, line, LINE_SIZE);
    assert(charsRead == 32);
    assert(strncmp(line, "this is a file used for testing", charsRead) == 0);

    charsRead = readLine(filePtr, line, LINE_SIZE);
    assert(charsRead == 25);
    assert(strncmp(line, "the cs101 helper library", charsRead) == 0);

    // empty line
    charsRead = readLine(filePtr, line, LINE_SIZE);
    assert(charsRead == 1);

    charsRead = readLine(filePtr, line, LINE_SIZE);
    assert(charsRead == 5);

    // end of file
    charsRead = readLine(filePtr, line, LINE_SIZE);
    assert(charsRead == 0);

    fclose(filePtr);
}

void testReadUntilDelim(void) {
    char line[LINE_SIZE];
    int charsRead;
    FILE *filePtr = fopen("testFile.txt", "r");

    charsRead = readUntilDelim(filePtr, ',', line, LINE_SIZE);
    assert(charsRead == 6);
    assert(strncmp(line, "hello", charsRead) == 0);

    charsRead = readUntilDelim(filePtr, '!', line, LINE_SIZE);
    assert(charsRead == 7);
    assert(strncmp(line, " world", charsRead) == 0);

    charsRead = readUntilDelim(filePtr, '\n', line, LINE_SIZE);
    assert(charsRead == 1);
    assert(strncmp(line, "", charsRead) == 0);

    fclose(filePtr);
}

void testStripping(void) {

    char testString1[LINE_SIZE] = "   abc   x ";
    char testString2[LINE_SIZE] = " \t\na\n\t b c\nd \n\n\t ";
    char outString[LINE_SIZE];
    int outLength;


    outLength = stripBeginningWhitespace(testString1, LINE_SIZE, outString);
    assert(outLength == 1 + strlen("abc   x "));
    assert(strncmp(outString, "abc   x ", outLength) == 0);

    outLength = stripBeginningWhitespace(testString2, LINE_SIZE, outString);
    assert(outLength == 1 + strlen("a\n\t b c\nd \n\n\t "));
    assert(strncmp(outString, "a\n\t b c\nd \n\n\t ", outLength) == 0);

    outLength = stripTrailingWhitespace(testString1, LINE_SIZE, outString);
    assert(outLength == 1 + strlen("   abc   x"));
    assert(strncmp(outString, "   abc   x", outLength) == 0);

    outLength = stripTrailingWhitespace(testString2, LINE_SIZE, outString);
    assert(outLength == 1 + strlen(" \t\na\n\t b c\nd"));
    assert(strncmp(outString, " \t\na\n\t b c\nd", outLength) == 0);

    outLength = stripWhitespace(testString1, LINE_SIZE, outString);
    assert(outLength == 1 + strlen("abc   x"));
    assert(strncmp(outString, "abc   x", outLength) == 0);

    outLength = stripWhitespace(testString2, LINE_SIZE, outString);
    assert(outLength == 1 + strlen("a\n\t b c\nd"));
    assert(strncmp(outString, "a\n\t b c\nd", outLength) == 0);
}


void testConversions(void) {
    bool isConverted;
    char intAsString1[LINE_SIZE] = "42";
    char intAsString2[LINE_SIZE] = " 42 ";
    char doubleAsString[LINE_SIZE] = "3.14159";

    assert(intFromString(intAsString1, LINE_SIZE, 10, &isConverted) == 42);
    assert(isConverted);

    assert(intFromString(intAsString2, LINE_SIZE, 10, &isConverted) == 42);
    assert(isConverted);

    assert(intFromString("hello", 5, 10, &isConverted) == 0);
    assert(!isConverted);

    assert(doubleFromString(doubleAsString, LINE_SIZE, &isConverted) == 3.14159);
    assert(isConverted);

    assert(doubleFromString("hello", 5, &isConverted) == 0);
    assert(!isConverted);
}

int main(int argc, char *argv[]) {
    testReadLine();
    testReadUntilDelim();
    testStripping();
    testConversions();

    printf("All tests passed!\n");

    return 0;
}