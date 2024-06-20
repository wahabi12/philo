void union_str(char *str1, char *str2)
{
    char seen[256] = {0};
    int i = 0;

    while (*str1)
    {
        if (!has_char(seen, *str1))
        {
            seen[i] = *str1;
            write(1, str1, 1);
            i++;
        }
        str1++;
    }
    while (*str2)
    {
        if (!has_char(seen, *str2))
        {
            seen[i] = *str2;
            write(1, str2, 1);
            i++;
        }
        str2++;
    }
}