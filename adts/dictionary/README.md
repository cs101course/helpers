# Dictionary Abstract Data Type

Implemented in two different ways:
- An array of key/value pairs (in `arrayDictionary.c`) - slow
- A Hash Table (in `hashTableDictionary.c`) - much faster

A Dictionary has the ability to store and retrieve data (in this case an integer) using a string _key_.

For example:

```

    Dictionary potionsTestScores;
    int harryScore;

    potionsTestScores = Dictionary_create(MAX_DICT_SIZE);
    Dictionary_set(potionsTestScores, "Harry Potter", 58);
    Dictionary_set(potionsTestScores, "Hermione Granger", 99);
    Dictionary_set(potionsTestScores, "Ron Weasley", 51);
    Dictionary_set(potionsTestScores, "Cho Chang", 87);
    Dictionary_set(potionsTestScores, "Luna Lovegood", 82);

    harryScore = Dictionary_get(potionsTestScores, "Harry Potter");
    printf("Harry Potter's test score is: %d\n", harryScore);

    Dictionary_destroy(potionsTestScores);
```

This is equivalent to using a `{"key": value}` dictionary in Python, e.g.

```
potionsTestScores = {
    "Harry Potter": 58,
    "Hermione Granger": 99,
    "Ron Weasley": 51,
    "Cho Chang": 87,
    "Luna Lovegood": 82
}

harry_score = potionsTestScores["Harry Potter"]
print(f"Harry Potter's test score is: {harry_score}")
```
