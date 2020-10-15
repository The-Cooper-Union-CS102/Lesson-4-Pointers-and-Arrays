# Pointers and Arrays

This section discusses pointers and arrays, which are constructs for dealing
with more complexly structured data.

You can think of pointers as being a small piece of data that says where
another piece of data is.  As an analogy, consider a person's address like
41 Cooper Sq.  This address it enough for you to find the location and
anything inside.

Let's consider a neighborhood block of addressed and people:

```
[a0 a1 a2 a3 a4 a5 a6 a7]
[p0 p1 p2 p3 p4 p5 p6 p7]
```

Given an address, it's obvious how to find the person, though that
is not particularly useful.  The utility comes when several people
share an address.

```
[a0       a1    a2    a3    a4             a6         ]
[p0 p1 p2 p3 p4 p5 p6 p7 p8 p9 p10 p11 p12 p13 p14 p15]
```

Now with just on address, you can find multiple people, and there is no
limit to how many people you might find.  This is much more flexible than
storing only a single piece of data in a single variable.

## Pointers

In C, you can get the address of a variable with the reference operator
`&` and get the value of a reference with the dereference operator `*`

For example here is some code that initializes a variable, then initiaizes
a pointer to the address of said variable, and prints both.

```c
// snippets/basicPointer.c
#include <stdio.h>

int main() {
    int value = 1; // Read as value equals one
    int *pointer = &value; // Read as pointer equals to address of value
    printf("value: %d\n", value);
    printf("address: %p\n", pointer);
}
```


```
value: 1
address: 0x7ffee709f77c
```


Note that when we initialize the pointer to our integer, we use

```
int *pointer
```

This means that `*pointer` is an `int`

Also note that actual value of our pointer is some large integer that has
nothing to do with the actual value that is points to.  This value represents
the value's location in "memory".  With that, you may be asking what is
the actual point of pointers?  The rest of this section goes through some
examples of use cases.

## Pointers and Function Arguments

The first new thing you can do with pointers is modify variables within
functions.

```c
// snippets/noPointer.c
#include <stdio.h>

void addOne(int a) {
    a += 1;
}

int main() {
    int a = 1;
    addOne(a);
    printf("%d\n", a);
}
```


```
1
```


You can see from the above example, if you pass a variable into a function
and modify it there, it is not modified in its original scope.  This is
because the variable is copied when being passed to the function.  If we
want to modify the variable, we can instead pass a pointer as in the following
example.

```c
// snippets/withPointer.c
#include <stdio.h>

void addOne(int *a) {
    *a += 1;
}

int main() {
    int a = 1;
    int *pointerToA = &a;
    addOne(pointerToA);
    printf("%d\n", a);
}
```


```
2
```


This can be especially useful if we want to pass multiple pieces of
information from a function.  For example, remember our previous example
of finding a pythagorean triple.  Before we could not return our answer
because it consisted of three values.

```c
// snippets/pointerTriple.c
#include <stdio.h>

int find_triple(int *aPtr, int *bPtr, int *cPtr, int max) {
    int a, b, c;
    *aPtr = 0;
    *bPtr = 0;
    *cPtr = 0;
    for (a = 1; a <= max; a++) {
        for (b = 1; b <= max; b++) {
            for (c = 1; c <= max; c++) {
                if (a*a + b*b == c*c) {
                    *aPtr = a;
                    *bPtr = b;
                    *cPtr = c;
                    return 1;
                }
            }
        }
    }
    return 0;
}

int main() {
    int a, b, c;
    int triple_exists = find_triple(&a, &b, &c, 13);
    printf("Triple exists? %d\n", triple_exists);
    printf("Triple: (%d %d %d)\n", a, b, c);
}
```


```
Triple exists? 1
Triple: (3 4 5)
```


See how in the above example, we pass the address of the variable we
wish to set with a function.

## Pointers and Arrays

Consider what code you would write if someone asked you to keep track of
a large number of similar objects.  For example, how would you track the
grades in a class of 15 people?  From what we have seen so far, there is
really no good way of doing this.  You could write a loop from 0 to 14,
but we have not yet seen any way of tracking the data outside of the loop.
That is where arrays come in.

An array can be declared and accessed with the special syntax demonstrated
below.

```c
// snippets/basicArray.c
#include <stdio.h>

int main() {
    // Declare array `a`
    int a[15];
    int n;
    // Set the n'th element of `a` to n
    for (n = 0; n < 15; n++) {
        a[n] = n;
    }
    // Print all elements of `a`
    for (n = 0; n < 15; n++) {
        printf("%d\n", a[n]);
    }
}
```


```
0
1
2
3
4
5
6
7
8
9
10
11
12
13
14
```


Now, while that's great, you may be asking what this has to do with pointers?
Well, it turns out this is essentially "syntactic sugar", and pointers are
really what we are using deep down.  This is demonstrated by the following
example:

```c
// snippets/pointerArray.c
#include <stdio.h>

int main() {
    // Declare array `a`
    int a[15];
    int *b = a; // This is legal because `a` is really a pointer
    int n;
    // Set the n'th element of `b` to n
    for (n = 0; n < 15; n++) {
        b[n] = n;
    }
    // Print all elements of `a`
    for (n = 0; n < 15; n++) {
        printf("%d\n", a[n]);
    }
}
```


```
0
1
2
3
4
5
6
7
8
9
10
11
12
13
14
```


Note that while we set the elements of `b`, the elements of `a` are still
changed when we print them.  That is because both `a` and `b` are references
to the same underlying object.  However, that is not where the pointer fun
stops.  We actually do not need these brackets `[]` for indexing:

```c
// snippets/pointerIndexing.c
#include <stdio.h>

int main() {
    // Declare array `a`
    int a[15];
    int n;
    // Set the n'th element of `b` to n
    for (n = 0; n < 15; n++) {
        *(a+n) = n;
    }
    // Print all elements of `a`
    for (n = 0; n < 15; n++) {
        printf("%d\n", *(a+n));
    }
}
```


```
0
1
2
3
4
5
6
7
8
9
10
11
12
13
14
```


So what's going on here?  Well, `int a[15];` is really saying to carve
out a block of contiguous memory, and put the address of the first one
into the variable `a`.  That means that the expression `(*a)` will be
the value of the first piece of memory we carved out, `(*a+1)` will be
the value of the next piece, and so on.  The one difference between
`a` and a regular pointer is that `a` cannot be changed.  So for example,
`a++` is not valid.

You may then ask, what if we go beyond our predefined length?  That behavior
is undefined, so anything could happen.  Usually your program will crash but in
usually worse case it can continue incorrectly.  This goes the same for
any pointer which does not reference an explicitly defined address, such
as a pointer not initialized to any value.

In C, a string (or piece of text) is represented by an array of characters.
You can initialize and print it as in the following example:

```c
// snippets/basicString.c
#include <stdio.h>

int main() {
    char name[] = "Cory Nezin";
    char *greeting = "Hello";
    printf("%s, name is %s\n", greeting, name);
}
```


```
Hello, name is Cory Nezin
```


There is one hidden piece of machinery here specific to strings, however.
Each string should be "null terminated".  This means each string actually
has another hidden character at the end which is equal to zero.  This is
shown in the following example where we use this to find the length of a
string.

```c
// snippets/nullTerm.c
#include <stdio.h>

int len(char *s) {
    int n = 0;
    while (*s != '\0') {
        n++;
        s++;
    }
    return n;
}

int main() {
    char *s = "12345";
    printf("Length of '%s': %d\n", s, len(s));
}
```


```
Length of '12345': 5
```


### Problem

Let's look at a problem of analyzing grades.  We will print the array,
find its average, median, sort it, and create a histogram of the grades.

```c
int main() {
    double grades[10] = {100, 75, 63, 89, 100, 78, 90, 55, 88, 99};
    printArray(grades, 10);
    printf("Average: %.2f\n", averageArray(grades, 10));
    printf("Sorted Grades: ");
    sortArray(grades, 10);
    printArray(grades, 10);
    printf("Median: %.2f\n", medianArray(grades, 10));
    double histogram[5];
    gradeHistogram(grades, histogram, 10);
    printArray(histogram, 5);
}
```

## Address Arithmetic and Variable Sized Arrays

Note that so far, all of the arrays we have shown you have a fixed size length.
Here we will show a simple example of how we can simulate variable sized
character arrays by carving them out from a large fixed size array.  This
example is taken from "The C Programming Lanugage" by Kerninghan and Ritchie.

**Note** that you should usually not do this in practice, as C provides
better ways of creating variable sized arrays that we'll discuss later.

Our general strategy here will be to create a large fixed size array.  We will
have one function to reserve a given amount of characters from the array,
checking if there is enough space.  This is called allocation.  We will have a
second function free up that space when it is no longer used.  This is called
freeing.  We will reserve space by returning a pointer to the big array and
moving the next pointer to the right as we take up more space.  We will free
space by simply moving the pointer to the left.

You can think of this strategy as simply writing down characters on a page,
then erasing them to make more space.  But note that this strategy will not
allow us to erase characters in any order, we can only erase from right
to left.

We begin by declaring our allocation buffer `allocbuf` as well as the pointer
to the next free space, `allocp`.

```c
#define ALLOCSIZE 10000 // size of available space

static char allocbuf[ALLOCSIZE]; // storage for allocation
static char *allocp = allocbuf; // next free position
```

Note that we are using a macro and the `static` keyword which should be
familiar from the last section.  As a reminder though, the macro `#define`
simply replaces all cases of `ALLOCSIZE` in the text with `10000`.  The
`static` keyword on a global variable means that other files including this
one will not be able to access these variables directly.

First let's look at the allocation function.

```c
char *alloc(int n) // return pointer to n characters
{
    int spaceUsed = allocp - allocbuf;
    int spaceLeft = ALLOCSIZE - spaceUsed;
    if (spaceLeft >= n) {
        // It fits
        allocp += n;
        return allocp - n; // old p
   } else {
        // Not enough room
        return 0;
   }
}
```

The function declaration is similar to what we've seen before.
`char *alloc(int n)` means `alloc` is a function that taken an integer `n`
and returns a pointer to a `char`.  This pointer is a position in our big
array representing free space for the caller to use.

We need to check if there is enough space so first we calculate the space
we are using by subtracting the beginning of the big array, `allocbuf` from
the current pointer position `allocp`.  Then we calculate the space remaining
as the total space minus the used space.  This calculation is illustrated
below.

```
                                             ALLOCSIZE
        spaceUsed - x         spaceLeft - o  v
xxxxxxxxxxxxxxxxxxxxxxxxxxxxoooooooooooooooooo
^                           ^
allocbuf                    allocp
```

Note in the case where we have not yet allocated anything, `allocp` is
equal to `allocbuf` meaning `spaceUsed` is zero and `spaceLeft` is
`ALLOCSIZE` which makes sense.  We then perform a check to see if the space
remaining is more than what is requested.  If so we move the pointer
over so the next caller will get free space, and return a poiner to the
old position.  Otherwise, we return 0 (which is never a valid pointer)
signalling to the caller that the request failed.

Note the property of pointer arithmetic that this implies: the difference
between pointers (namely `allocp` and `allocbuf`) always represents the
number of objects between them (plus 1).  This is true regardless of the
type pointed to by each pointer, so long as they are the same.  That means
if our buffer was a buffer of integers, floats, or anything else this code
would still be valid.

Now let's look at the `free` function.

```c
void afree(char *p) // free storage pointed to by p
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE) {
        // p within bounds of big array allocbuf
        allocp = p;
    }
}
```

This function is a bit simpler, let's explain step by step how it works.
First, the expression `p >= allocbuf` asks whether the position we are
trying to free from is at the start, or after the start of the big array.
The expression `p < allocbuf + ALLOCSIZE` asks whether the pointer is
before or at the end.  Note that as in the first function, the end of the
array is calculated as the start plus the size.  All in all, the expression
`p >= allocbuf && p < allocbuf + ALLOCSIZE` asks whether the pointer is within
the bouneds of the array.  Then, if it is, we assign the current pointer to
the given location `p`.  Note that this doesn't actually do any erasing,
it only means that future callers of `alloc` will be able to write over
whatever is there.

As a sidebar, this is actually a common feature of many storage systems.  This
is why why you "delete" something on your computer, it may not actually delete
it but simply mark its position as free.  This could allow you to recover files
you accidentally deleted, or for hackers to recover files you thought were
deleted.  This is also why you may get garbage values in an uninitalized
variable rather than all zeros.

Now, let's see our functions in action.

### Problem

Let's write a function to join each character in a string by a separator.
# Pointers to Pointers and Arrays

Just as we can have pointers to characters, integers, and doubles, we can
also have pointers to pointers, or pointers to arrays.  This can be useful
for representing higher dimensional structures like a grid of numbers or
a list of strings.

First we will illustrate with a very simple example of a single integer.

```c
// snippets/multiPointer.c
#include <stdio.h>

int main() {
    int x = 1;
    int *px = &x;
    int **ppx = &px;
    int ***pppx = &ppx;
    printf("x: %d\n", ***pppx);
}
```


```
x: 1
```


See how we first initialize a single pointer as before `*px = &x` but then
we go on to initialize a pointer to that pointer by adding another `*` to the
initialization, and using the reference operator `&` on the ponter itself.
We then repeat this pattern one more time to make a pointer to a pointer
to a pointer, `pppx`.  To get the original value, we must dereference with
the defererence operator `*` three times as done in the `printf` statement.
You could also dereference fewer times if you want one of the references
instead.

We can use this same technique to create an array of strings as shown below.

```c
// snippets/stringArray.c
#include <stdio.h>

int main() {
    char *names[] = {"Cory", "Ross", "Gordon"};
    int n;
    for (n = 0; n < 3; n++) {
        printf("name %d: %s\n", n, names[n]);
    }
}
```


```
name 0: Cory
name 1: Ross
name 2: Gordon
```


Note that by leaving the `[]` empty, the size of the array is automatically
determined by its initialization.  We could have put a value there.  In
particular, we could have put the value `3` as shown below since that
is the size of the array.

```c
// snippets/stringArrayFixed.c
#include <stdio.h>

int main() {
    char *names[3] = {"Cory", "Ross", "Gordon"};
    int n;
    for (n = 0; n < 3; n++) {
        printf("name %d: %s\n", n, names[n]);
    }
}
```


```
name 0: Cory
name 1: Ross
name 2: Gordon
```


More importantly though, we could have also put a larger value which leaves
room for more strings in the future, as the code below demonstrates

```c
// snippets/StringArrayMoreRoom.c
#include <stdio.h>

int main() {
    char *names[4] = {"Cory", "Ross", "Gordon"};
    names[3] = "Deborah";
    int n;
    for (n = 0; n < 4; n++) {
        printf("name %d: %s\n", n, names[n]);
    }
}
```


```
name 0: Cory
name 1: Ross
name 2: Gordon
name 3: Deborah
```


We also didn't need to initialize the array with any names at all, it's just
fine to initialize it as empty and then add strings later as in this example.

```c
// snippets/StringArrayEmpty.c
#include <stdio.h>

int main() {
    char *names[4];
    names[0] = "Cory";
    names[1] = "Ross";
    names[2] = "Gordon";
    names[3] = "Deborah";
    int n;
    for (n = 0; n < 4; n++) {
        printf("name %d: %s\n", n, names[n]);
    }
}
```


```
name 0: Cory
name 1: Ross
name 2: Gordon
name 3: Deborah
```


Note that while very similar, a pointer to string arrays is different than
a pointer to pointers of chars.  For one, the previous methods of
initialization are not legal with a simple pointer to pointers.

```c
// snippets/stringArrayBad.c
#include <stdio.h>

int main() {
    char **names = {"Cory", "Ross", "Gordon"};
    int n;
    for (n = 0; n < 3; n++) {
        printf("name %d: %s\n", n, names[n]);
    }
}
```

```
gcc snippets/stringArrayBad.c
```

```
snippets/stringArrayBad.c:4:21: warning: incompatible pointer types initializing 'char **' with an expression of type 'char [5]' [-Wincompatible-pointer-types]
    char **names = {"Cory", "Ross", "Gordon"};
                    ^~~~~~
snippets/stringArrayBad.c:4:29: warning: excess elements in scalar initializer
    char **names = {"Cory", "Ross", "Gordon"};
                            ^~~~~~
2 warnings generated.

```



In addition, if you initialize a pointer to chars with a string literal
like in the below example, attempting to modify it is illegal and will
result in an error.

```c
// snippets/stringArrayVsPointer1.c
#include <stdio.h>

int main() {
    char arrayString[] = "now is the time";
    char *pointerString = "now is the time";
    // Fine
    arrayString[0] = 'N';
    printf("%s\n", arrayString);
    // Wrong
    pointerString[0] = 'N';
    printf("%s\n", pointerString);
}
```

```
gcc snippets/stringArrayVsPointer1.c
```



However this is only because it is pointing to the string literal which is
read-only.  If you instead switch the string pointer to point to the start of
the string array, as done below, it is fine.

```c
// snippets/stringArrayVsPointer2.c
#include <stdio.h>

int main() {
    char arrayString[] = "now is the time";
    char *pointerString = "now is the time";
    // Fine
    arrayString[0] = 'N';
    printf("%s\n", arrayString);
    // Fine
    pointerString = arrayString;
    pointerString[1] = 'O';
    printf("%s\n", pointerString);
}
```


```
Now is the time
NOw is the time
```


One final difference is that a string pointer can be incremented while the
array cannot, as shown in the following example.

```c
// snippets/stringArrayVsPointer3.c
#include <stdio.h>

int main() {
    char arrayString[] = "now is the time";
    char *pointerString = "now is the time";
    // Fine
    ++pointerString;
    printf("%s\n", pointerString);
    // Wrong
    ++arrayString;
    printf("%s\n", arrayString);
}
```

```
gcc snippets/stringArrayVsPointer3.c
```

```
snippets/stringArrayVsPointer3.c:10:5: error: cannot increment value of type 'char [16]'
    ++arrayString;
    ^ ~~~~~~~~~~~
1 error generated.

```



You should note that whenver you pass an array into a function, it will never
truly receive the array, but a pointer which points to the start of the array.
This applies to all types of arrays, not just character arrays.

### Problem

How can we sort an array of names?

## Command Line Arguments

Now we have enough of a basis to start talking about command line arguments,
because these are mostly handled with string pointers.  It turns out that
in fact, our main function can take arguments, usually denoted by `argc`
and `argv`.  The `argc` argument is the "argument count" meaning the number
of arguments passed by the user.  The `argv` argument is the "argument
vector" meaning an array of actual arguments themselves.  The `argc`
parameter is a simple integer, and the `argv` parameter is a pointer to
character arrays.

Let's take a look at a simple example which simply repeat the inputs,
separated onto different lines.

```c
// snippets/basicIo.c
#include <stdio.h>

int main(int argc, char *argv[]) {
    int n;
    for (n = 0; n < argc; n++) {
        printf("%s", argv[n]);
        if (n < (argc - 1)) {
            printf("\n");
        }
    }
    printf("\n");
}
```


```
./a.out
```


This code is instructive but it isn't very useful.  Let's take a look at
a program that actually takes the inputs and does something useful, a
rudimentary calculator that adds all the inputs.

```c
// snippets/bigSum.c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int n;
    int sum = 0;
    for (n = 1; n < argc; n++) {
        sum += atoi(argv[n]);
    }
    printf("Sum: %d\n", sum);
}
```


```
Sum: 0
```


You can see the code is mostly similar to our basic example of printing
the inputs.  The major difference is that instead of printing the input,
we convert it to an integer by using the built in `atoi` (ascii to integer)
function which comes from the standard library, `stdlib`.  We add it to
our running sum, `sum` and print it at the end.

### Problem

How can sort our inputs and print them back sorted?

## Multidimensional arrays

Multidimensional arrays are useful for storing information which naturally
takes the shape of higher dimensions, such as images or videos.  Below
we demonstrate the usage of a two dimensional array to generate and store
a synthetic image, which we then print.

```c
// snippets/multidimArray.c
/*
Prints rule 110:
111 110 101 100 011 010 001 000
 0   1   1   0   1   1   1   0
*/

#include <stdio.h>
#define M 80
#define N 80

int main() {
    int rule[] = {0, 1, 1, 1, 0, 1, 1, 0};
    int a[M][N] = {0};
    a[0][N-1] = 1;
    int m, n;
    int index;
    for (m = 1; m < M; m++) {
        for (n = 1; n < N-1; n++) {
            index = a[m-1][n-1]*4 + a[m-1][n]*2 + a[m-1][n+1];
            a[m][n] = rule[index];
        }
    }
    for (m = 0; m < M; m++) {
        for (n = 0; n < N-1; n++) {
            printf(a[m][n] ? "x" : " ");
        }
        printf("\n");
    }
}
```


```
                                                                               
                                                                              x
                                                                             xx
                                                                            xxx
                                                                           xx x
                                                                          xxxxx
                                                                         xx   x
                                                                        xxx  xx
                                                                       xx x xxx
                                                                      xxxxxxx x
                                                                     xx     xxx
                                                                    xxx    xx x
                                                                   xx x   xxxxx
                                                                  xxxxx  xx   x
                                                                 xx   x xxx  xx
                                                                xxx  xxxx x xxx
                                                               xx x xx  xxxxx x
                                                              xxxxxxxx xx   xxx
                                                             xx      xxxx  xx x
                                                            xxx     xx  x xxxxx
                                                           xx x    xxx xxxx   x
                                                          xxxxx   xx xxx  x  xx
                                                         xx   x  xxxxx x xx xxx
                                                        xxx  xx xx   xxxxxxxx x
                                                       xx x xxxxxx  xx      xxx
                                                      xxxxxxx    x xxx     xx x
                                                     xx     x   xxxx x    xxxxx
                                                    xxx    xx  xx  xxx   xx   x
                                                   xx x   xxx xxx xx x  xxx  xx
                                                  xxxxx  xx xxx xxxxxx xx x xxx
                                                 xx   x xxxxx xxx    xxxxxxxx x
                                                xxx  xxxx   xxx x   xx      xxx
                                               xx x xx  x  xx xxx  xxx     xx x
                                              xxxxxxxx xx xxxxx x xx x    xxxxx
                                             xx      xxxxxx   xxxxxxxx   xx   x
                                            xxx     xx    x  xx      x  xxx  xx
                                           xx x    xxx   xx xxx     xx xx x xxx
                                          xxxxx   xx x  xxxxx x    xxxxxxxxxx x
                                         xx   x  xxxxx xx   xxx   xx        xxx
                                        xxx  xx xx   xxxx  xx x  xxx       xx x
                                       xx x xxxxxx  xx  x xxxxx xx x      xxxxx
                                      xxxxxxx    x xxx xxxx   xxxxxx     xx   x
                                     xx     x   xxxx xxx  x  xx    x    xxx  xx
                                    xxx    xx  xx  xxx x xx xxx   xx   xx x xxx
                                   xx x   xxx xxx xx xxxxxxxx x  xxx  xxxxxxx x
                                  xxxxx  xx xxx xxxxxx      xxx xx x xx     xxx
                                 xx   x xxxxx xxx    x     xx xxxxxxxxx    xx x
                                xxx  xxxx   xxx x   xx    xxxxx       x   xxxxx
                               xx x xx  x  xx xxx  xxx   xx   x      xx  xx   x
                              xxxxxxxx xx xxxxx x xx x  xxx  xx     xxx xxx  xx
                             xx      xxxxxx   xxxxxxxx xx x xxx    xx xxx x xxx
                            xxx     xx    x  xx      xxxxxxxx x   xxxxx xxxxx x
                           xx x    xxx   xx xxx     xx      xxx  xx   xxx   xxx
                          xxxxx   xx x  xxxxx x    xxx     xx x xxx  xx x  xx x
                         xx   x  xxxxx xx   xxx   xx x    xxxxxxx x xxxxx xxxxx
                        xxx  xx xx   xxxx  xx x  xxxxx   xx     xxxxx   xxx   x
                       xx x xxxxxx  xx  x xxxxx xx   x  xxx    xx   x  xx x  xx
                      xxxxxxx    x xxx xxxx   xxxx  xx xx x   xxx  xx xxxxx xxx
                     xx     x   xxxx xxx  x  xx  x xxxxxxxx  xx x xxxxx   xxx x
                    xxx    xx  xx  xxx x xx xxx xxxx      x xxxxxxx   x  xx xxx
                   xx x   xxx xxx xx xxxxxxxx xxx  x     xxxx     x  xx xxxxx x
                  xxxxx  xx xxx xxxxxx      xxx x xx    xx  x    xx xxxxx   xxx
                 xx   x xxxxx xxx    x     xx xxxxxx   xxx xx   xxxxx   x  xx x
                xxx  xxxx   xxx x   xx    xxxxx    x  xx xxxx  xx   x  xx xxxxx
               xx x xx  x  xx xxx  xxx   xx   x   xx xxxxx  x xxx  xx xxxxx   x
              xxxxxxxx xx xxxxx x xx x  xxx  xx  xxxxx   x xxxx x xxxxx   x  xx
             xx      xxxxxx   xxxxxxxx xx x xxx xx   x  xxxx  xxxxx   x  xx xxx
            xxx     xx    x  xx      xxxxxxxx xxxx  xx xx  x xx   x  xx xxxxx x
           xx x    xxx   xx xxx     xx      xxx  x xxxxxx xxxxx  xx xxxxx   xxx
          xxxxx   xx x  xxxxx x    xxx     xx x xxxx    xxx   x xxxxx   x  xx x
         xx   x  xxxxx xx   xxx   xx x    xxxxxxx  x   xx x  xxxx   x  xx xxxxx
        xxx  xx xx   xxxx  xx x  xxxxx   xx     x xx  xxxxx xx  x  xx xxxxx   x
       xx x xxxxxx  xx  x xxxxx xx   x  xxx    xxxxx xx   xxxx xx xxxxx   x  xx
      xxxxxxx    x xxx xxxx   xxxx  xx xx x   xx   xxxx  xx  xxxxxx   x  xx xxx
     xx     x   xxxx xxx  x  xx  x xxxxxxxx  xxx  xx  x xxx xx    x  xx xxxxx x
    xxx    xx  xx  xxx x xx xxx xxxx      x xx x xxx xxxx xxxx   xx xxxxx   xxx
   xx x   xxx xxx xx xxxxxxxx xxx  x     xxxxxxxxx xxx  xxx  x  xxxxx   x  xx x
  xxxxx  xx xxx xxxxxx      xxx x xx    xx       xxx x xx x xx xx   x  xx xxxxx
 xx   x xxxxx xxx    x     xx xxxxxx   xxx      xx xxxxxxxxxxxxxx  xx xxxxx   x
 xx  xxxx   xxx x   xx    xxxxx    x  xx x     xxxxx            x xxxxx   x  xx
```


Note that our basic strategy for producing this image is to look at the
previous row, apply some calculation, and use the result as our new value
of in the current row we are looking at.

Note something important here, we had to use macros to define the height
and width of our array because C would not allow us to create it from
variables.  This represents one of the key restrictions of multidimensional
arrays in C, and that is why it is more common to see regular pointers
to arrays.

## Void Pointers

It is possible to create a pointer which points to some location in memory,
but is not directly associated with any variable type.  Such an object is
called a void pointer.  Below is an example showing the creation of a void
pointer pointing to an integer.

```c
// snippets/voidPointer.c
#include <stdio.h> 

int main() {
    int x = (67 << 0) + //  C
            (79 << 8) + //  O
            (82 << 16) + // R
            (89 << 24); //  Y
    void *ptr = &x;
    printf("%lu\n", sizeof(int));
    printf("%lu\n", sizeof(char));
    printf("%d\n", *(int *)ptr);
    printf("%c", *((char *)ptr+0));
    printf("%c", *((char *)ptr+1));
    printf("%c", *((char *)ptr+2));
    printf("%c\n", *((char *)ptr+3));
} 
```


```
4
1
1498566467
CORY
```


Note that while it was originally created to point to an integer, we can
interpret it in multiple ways.  In particular, we interpret it both as
pointing to an integer and point to a character by casting as each type
of pointer.  This can be useful when we want to write code, or functions
that apply to multiple types of data.

## Pointers to Functions

While functions in C are not technically variables, it turns out it is still
possible to have function pointers.  This conept of treating functions as
data hints at the idea of something called "functional programming".  However,
C is a not a "functional programming" language meaning it does not support
it well, so we will not discuss it any more here.

One particularly useful case for function pointers is to pass them to other
functions.  We demonstrate this with an "integral" function which can
approximate the integral of a function passed to it over a given interval.

```c
// snippets/integral.c
#include <stdio.h> 
#include <math.h> 

double integral(double (*f)(double), double start, double end) {
    double eps = 1e-6;
    double result = 0;
    double x;
    for (x = start; x < end; x += eps) {
        result += f(x) * eps;
    }
    return result;
}

double inverse(double x) {
    return 1 / x;
}

int main() {
    double result = integral(&inverse, 1, 2);
    printf("Integral of 1/x from 1 to 2: %f\n", result);
    printf("ln(2): %f\n", log(2));
} 
```


```
Integral of 1/x from 1 to 2: 0.693148
ln(2): 0.693147
```


Note that there is a bit of freedom as to how you pass function pointers
into another function.  We can remove the dereference operator, `&`, and
change `(*f)` to just `f` and the program would behave exactly the same.
We only put them here to be explicit about the fact that we are passing a
function pointer.

Now let's take a look and see if we can enhance our old sorting code with
this feature.

```c
// snippets/sortCompare.c
#include <stdio.h>

int stringCompare(char *a, char *b) {
    while (*a == *b) {
        if (*a == '\0') {
            return 0;
        }
        a++;
        b++;
    }
    return *a - *b;
}

void sort(void *a[], int size, int (*compare) (void *, void *)) {
    int n, m;
    void *temp;
    for (n = 0; n < size; n++) {
        for (m = n; m >= 1; m--) {
            if (compare(a[m], a[m-1]) < 0) {
                temp = a[m-1];
                a[m-1] = a[m];
                a[m] = temp;
            }
        }
    }
}

int main() {
    char *names[] = {"Cory", "Zoe", "Ross", "Gordon", "Deborah"};
    sort((void *) names, 5, (int (*)(void *, void *))(stringCompare));
    int n;
    for (n = 0; n < 5; n++) {
        printf("name %d: %s\n", n, names[n]);
    }
}
```


```
name 0: Cory
name 1: Deborah
name 2: Gordon
name 3: Ross
name 4: Zoe
```


There are a few things going on here.  First, the `sort` function has been
modified to work with `void` pointers rather than being hard coded as
`char` pointers.  This makes it compatible with a wider range of data
types.  Second, the `sort` function has been augmented to take in a function
pointer as a parameter.  Note that the expression
`int (*compare) (void *, void *))` says that the parameter is a pointer to
a function that accepts two void pointers.  You should notice at this point
however, that our comparison function doesn't actually take void pointers.
The way we get around this is by *casting* the function pointer with:
`(int (*)(void *, void *))(stringCompare)`.  This means that our function
will actually receive `void` pointers, but remember since we have `char`
in the declaration of the function, those parameters will be automatically
cast when the function receives them.

The above is fairly complex, but it can get even worse!

## Complicated Declarations

Overly complex declarations rarely come up in practice, however it is a good
idea to be able to interpret them in case you come across them in the wild.

This ]Medium article](https://medium.com/@bartobri/untangling-complex-c-declarations-9b6a0cf88c96)
is a great resource for understanding them.  I will summarize it here.

When looking at a declaration, follow this order of precedence:

0. Variable name
1. Grouping parentheses
2. Paranthses (containing nothing or types) or brackets (containing nothing or
a number)
3. Prefixed asterisk `*`
4. Type

For example, to interpret `char *a[];`, first look at the variable name, `a`,
Then brackets (containing nothing), then, the prefixed asertisk, then the
type.  Combining these in order we have: "a is an array of pointers to char"
If we instead wanted a pointer to an array of char, we could use grouping
parentheses: `char (*a)[];`

Going through the most complex example in the source:

```
char* (*(*foo[5])(char*))[];
```

0. `foo`: foo is
1. `foo[5]`: foo is an array of 5
2. `(*foo[5])`: foo is an array of 5 pointers to
3. `(*foo[5])()`: foo is an array of 5 pointers to functions taking
4. `(*foo[5])(char*)`: foo is an array of 5 pointers to functions taking character pointers
5. `(*(*foo[5])(char*))`: foo is an array of 5 pointers to functions taking character pointers returning a pointer to 
6. `(*(*foo[5])(char*))[]`: foo is an array of 5 pointers to functions taking character pointers returning a pointer to an array
7. `char* (*(*foo[5])(char*))[]`: foo is an array of 5 pointers to functions taking character pointers returning a pointer to an array of character pointers
# Advanced Input and Output

Now that we know almost all there is to know about pointers, we can begin
a proper discussion of input and output.  We have already seen a couple
of simple examples such as taking input from the command line and printing
output to the command line, but now we will talk about reading and writing
from files and reading from the command line interactively.

## Getting Characters

The simplest form of interactive input is getting characters from the user.
In C, this can be done with the `getchar` function which is from `stdio.h`.
Below is a simple example which gets the first character the user enters
and prints it back to them when they hit enter.

```c
// snippets/getchar.c
#include <stdio.h>

int main() {
    int c;
    c = getchar();
    printf("%c\n", c);
}
```

```
gcc snippets/getchar.c
```



Note that even if the user types multiple characters before hitting enter,
only the first will be displayed.  If we wanted to instead echo everything
the user entered, we could use a loop as in the below example.

```c
// snippets/getcharLoop.c
#include <stdio.h>

int main() {
    int c;
    while ((c = getchar()) != EOF) {
        printf("%c", c);
    }
    printf("--Done reading!--\n");
}
```

```
gcc snippets/getcharLoop.c
```



Note two things that may seem weird here.  First, we gave `c` the type `int`
and second, the condition of the while loop is that `c` is not `EOF`.  These
oddities are related.  We typically need some way to exit this input loop and
continue with the rest of the program.  You should know that `ctrl-c` can be
used to exit from a program when you are stuck in a loop, however we do
not want to exit the program itself but just this input loop.  To do this,
we can send a special value called `EOF` (End of file) by using `ctrl-d`.
This value is typically `-1` hence the possible need for `c` to be an `int`.
This value is also automatically fed if we were to use a file input rather
than the users keyboard by doing something like `./a.out < getcharLoop.c`

### Problem

How can we modify the above program to remove all whitespace from the input?

## Getting Fromatted Input

So far we have the tools to read the user input character by character, but
eventually we may want to store the user input into different kinds of
variables.  That is where `scanf`, the sibling of `printf` comes in.  It
performs very similarly to printf with the same placeholder syntax, except
that it is passed pointers (which it uses to modify the underlying values)
rather than actual values.

For example, the below program gets two numbers and an operation and prints
the result.

```c
// snippets/calc.c
#include <stdio.h>

int main() {
    int x, y, result;
    char op;
    scanf("%d %d %c", &x, &y, &op);
    if (op == '+') {
        result = x + y;
    } else if (op == '-') {
        result = x - y;
    } else if (op == '*') {
        result = x * y;
    } else if (op == '/') {
        result = x / y;
    }
    printf("%d\n", result);
}
```

```
gcc snippets/calc.c
```



One can also use `scanf` in a loop to continuously process user input.  This
is demonstrated in the program below which asks the user to enter numbers
that are added up and displayed at the end.

```c
// snippets/scanfLoop.c
#include <stdio.h>

int main() {
    double x;
    double sum = 0;
    while ((scanf("%lf", &x) == 1)) {
        printf("added: %lf\n", x);
        sum += x;
    }
    printf("Sum: %f\n", sum);
}
```

```
gcc snippets/scanfLoop.c
```



Note two things about this code: First, we use the output of `scanf`.  The
output represents the number of parameters successfully formatted.  If it is 1,
the user entered a proper number that can be interpreted as a double.
Otherwise, they may have entered some garbage.  Second, there is not a very
elegant way to tell the program to stop summing numbers.  We have to use
our old trick of sending the `EOF` value with `ctrl-d`.  You might think
it would be nice to stop when the user enters a blank input (i.e. hits
enter with no number) but `scanf` simply ignores whitespace and will continue
waiting for the number input.

## Getting Strings

Just as we can get single characters from the user, we can also get entire
lines at a time by using `gets`.  The following example demonstrates the use
of `gets` to get lines until the user enters an empty line.  The result
of `gets` is then consumed by `sscanf` which is the same as `scanf` except
that it reads from a string rather than directly from user input.

```c
// snippets/gets.c
#include <stdio.h>
#include <string.h>

#define BUFSIZE 10

int main() {
    double x, sum;
    sum = 0;
    char line[BUFSIZE];
    while (gets(line) > 0) {
        if (line[0] == '\0') {
            break;
        } else if (sscanf(line, "%lf", &x) == 1) {
            sum += x;
        }
    }
    printf("Sum: %f\n", sum);
}
```

```
gcc snippets/gets.c
```



Note however, that this program may show you the output
`warning: this program uses gets(), which is unsafe.` and for good reason.
If a user enters a string longer than what can be stored by `line` the
behavior is undefined.  This means the program is buggy, but more importantly
it may be insecure and vulnerable to exploit.  We will now discuss an
alternative which does not have this vulnerability.

## Getting from Files

Getting data from files might seem like it should be different than reading
from input, but it's actually fundamentally the same.  This is because user
input (actually called standard input) is really a file.  First we will
reproduce the last example, but by using a file reading function, `fgets`
to read the user input.

```c
// snippets/fgets.c
#include <stdio.h>
#include <string.h>

#define BUFSIZE 10

int main() {
    double x, sum;
    sum = 0;
    char line[BUFSIZE];
    while (fgets(line, BUFSIZE, stdin) > 0) {
        if (line[0] == '\n') {
            break;
        } else if (sscanf(line, "%lf", &x) == 1) {
            sum += x;
        }
    }
    printf("Sum: %f\n", sum);
}
```

```
gcc snippets/fgets.c
```



There are three important differences in this code.  First, we use `fgets`
instead of `gets`, providing the maximum amount of characters we can accept.
This prevents the earlier issue of taking more input than we can handle.
Second, we check the first character of the input for being a newline rather
than a null because `fgets` includes newlines.  Third (and probably most
strange looking) is we provide the `fgets` function an argument called
`stdin` (meaning standard input).  This tells it to read from user input.

This code is much safer, however it does still have the issue that inputs
that are too long will be truncated.  For instance, entering just
`1234.56789` will result in a sum of `1234.5678` because with the null
character at the end, that is all that will fit.

To fix this, we can explicitly check that the input is within the acceptable
bounds by checking if the end of the string is a newline.  If it is not,
the input has been truncated and we should abort.

```c
// snippets/fgetsBetter.c
#include <stdio.h>
#include <string.h>

#define BUFSIZE 10

int main() {
    double x, sum;
    sum = 0;
    char line[BUFSIZE];
    while (fgets(line, BUFSIZE, stdin) > 0) {
        int len = strlen(line);
        if (line[len-1] != '\n') {
            printf("ERROR: input too long. Aborting.\n");
            return -1;
        }
        if (line[0] == '\n') {
            break;
        } else if (sscanf(line, "%lf", &x) == 1) {
            sum += x;
        }
    }
    printf("Sum: %f\n", sum);
}
```

```
gcc snippets/fgetsBetter.c
```



Now, instead of reading directly from `stdin` we could also read from a
regular file.  Let's take a look at how we can open a file and then read
it with `fgets`.

```c
// snippets/fileRead.c
#include <stdio.h>
#include <string.h>

#define BUFSIZE 10

int main() {
    char line[BUFSIZE];
    FILE *filePointer = fopen("snippets/test.txt", "r");
    while (fgets(line, BUFSIZE, filePointer) > 0) {
        int len = strlen(line);
        printf("%s", line);
        if (line[len-1] != '\n') {
            printf("ERROR: line too long. Aborting.\n");
            return -1;
        }
    }
}
```


```
hello
please
read
me
```


Note that this code is a bit buggy because we do not handle the case
where we fail to open the file.  This can happen if the path we gave it
does not exist, or if we do not have permission to read it.  If `fopen`
fails to open the file, it will return a null pointer, which we handle
in this next version.

```c
// snippets/fileReadBetter.c
#include <stdio.h>
#include <string.h>

#define BUFSIZE 10

int main() {
    char line[BUFSIZE];
    FILE *filePointer = fopen("snippets/notexist.txt", "r");
    if (filePointer == NULL) {
        printf("ERROR: file could not be found.\n");
        return -1;
    }
    while (fgets(line, BUFSIZE, filePointer) > 0) {
        int len = strlen(line);
        printf("%s", line);
        if (line[len-1] != '\n') {
            printf("ERROR: line too long. Aborting.\n");
            return -1;
        }
    }
}
```


```
ERROR: file could not be found.
```


This code is better but there is still one more thing we should do whenever
we open a file: close it when we are done.  You should always close the file
you have opened because some computers have limits on how many files can
be opened by a single program.

```c
// snippets/fileReadBest.c
#include <stdio.h>
#include <string.h>

#define BUFSIZE 10

int main() {
    char line[BUFSIZE];
    FILE *filePointer = fopen("snippets/test.txt", "r");
    if (filePointer == NULL) {
        printf("ERROR: file could not be found.\n");
        return -1;
    }
    while (fgets(line, BUFSIZE, filePointer) > 0) {
        int len = strlen(line);
        printf("%s", line);
        if (line[len-1] != '\n') {
            printf("ERROR: line too long. Aborting.\n");
            return -1;
        }
    }
    fclose(filePointer);
}
```


```
hello
please
read
me
```

