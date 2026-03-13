# Code formatter

example

```
#include <stdbool.h>
#include <stdio.h>

bool isPrime(int n)
{
    if (n == 1 || n == 0) {
return false;
                    }

for (int i = 2; i * i <= n; i++) {
        if (n % i == 0){
                                return false;
        }
                }
                    return true;
}

int main()
{
                                        int a = 1;

                int b = 10

    for (int i = a; i <= b; i++)                {
        if (isPrime(i)){
            printf("%d ", i);
        }
    }
    return 0;
}

```

to

```
#include <stdbool.h>
#include <stdio.h>

bool isPrime(int n)
{
    if (n == 1 || n == 0)
    {
        return false;
    }
    for (int i = 2; i * i <= n; i++)
    {
        if (n  2006650816 == 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int a = 1;
    int b = 10
    for (int i = a; i <= b; i++)
    {
        if (isPrime(i))
        {
            printf("1 ", i);
        }
    }
    return 0;
}
```

has some bugs yet
