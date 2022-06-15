// # Write a program that takes a string and displays it, replacing each of its
// # letters by the letter 13 spaces ahead in alphabetical order.
// # 'z' becomes 'm' and 'Z' becomes 'M'. Case remains unaffected.
// # The output will be followed by a newline.
// # If the number of arguments is not 1, the program displays a newline.
// # Example:
// # $>./rot_13 "abc"
// # nop
// # $>./rot_13 "My horse is Amazing." | cat -e
// # Zl ubefr vf Nznmvat.$
// # $>./rot_13 "AkjhZ zLKIJz , 23y " | cat -e
// # NxwuM mYXVWm , 23l $
// # $>./rot_13 | cat -e
// # $
// # $>
// # $>./rot_13 "" | cat -e
// # $

#include <unistd.h>
int main (int argc, char **argv)
{
    char s1[26] = "abcdefghijklmnopqrstuvwxyz";
    char s2[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    int i = 0;
    int j = 0;
    if (argc == 2)
    {
        while (argv[1][i])
        {
            if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
            {
                j = argv[1][i] - 'a' + 13;
                 write(1, &(s1[j]), 1);
            }
            else if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
            {
                 j = argv[1][i] - 'A' + 13;
                 write(1, &(s2[j]), 1);
            }
            else
                write(1, &argv[1][i], 1);
            i++;
        }
    }
    write(1, "\n", 1);
    return (0);
}