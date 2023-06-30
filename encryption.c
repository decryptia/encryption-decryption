#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Color codes
#define COLOR_RESET "\x1b[0m"
#define COLOR_CYAN "\x1b[36m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_RED "\x1b[31m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_WHITE "\x1b[37m"
#define COLOR_BOLDBLACK "\x1b[1m\x1b[30m"
#define COLOR_BOLDRED "\x1b[1m\x1b[31m"
#define COLOR_BOLDGREEN "\x1b[1m\x1b[32m"

long int gcd(long int a, long int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

long int mod_inverse(long int a, long int m)
{
    long int m0 = m;
    long int y = 0, x = 1;

    if (m == 1)
        return 0;

    while (a > 1)
    {
        long int q = a / m;
        long int t = m;

        m = a % m, a = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0)
        x += m0;

    return x;
}

long int mod_exp(long int base, long int exponent, long int modulus)
{
    long int result = 1;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        base = (base * base) % modulus;
        exponent = exponent / 2;
    }
    return result;
}

int is_prime(long int number)
{
    if (number <= 1)
        return 0;

    for (long int i = 2; i <= sqrt(number); i++)
    {
        if (number % i == 0)
            return 0;
    }
    return 1;
}

void rsa_encrypt_decrypt()
{
    long int p, q, n, phi, e, d;
    char plaintext[100];
    long int ciphertext[100], decryptedtext[100];
    char continueFlag = 'y';

    // General Information
    system("cls"); // using the `cls` command to clear screen. In linux instead of `cls` we have to use `clear`.
    printf(COLOR_CYAN "Welcome to the Practicing RSA Encryption and Decryption.\n" COLOR_RESET);
    printf(COLOR_YELLOW "Please Remember!!! Do enter the prime number greater than or equal to 17 for proper working. And both the primes should be different.\n" COLOR_RESET);

    while (continueFlag == 'y')
    {
        printf("Enter first prime number (p):\t");
        if (scanf("%ld", &p) != 1 || !is_prime(p))
        {
            printf("Invalid input! Please enter a prime number.\n");
            continue;
        }

        printf("Enter second prime number (q):\t");
        if (scanf("%ld", &q) != 1 || !is_prime(q))
        {
            printf("Invalid input! Please enter a prime number.\n");
            continue;
        }

        if (q == p)
        {
            printf(COLOR_RED "Both the prime numbers are same. Please do enter different.\n" COLOR_RESET);
            continue;
        }

        n = p * q;
        phi = (p - 1) * (q - 1);
        printf("\nProduct of two primes(n): %ld\n\n", n);

        // Calculate the encryption key (e)
        for (e = 2; e < phi; e++)
        {
            if (gcd(e, phi) == 1)
                break;
        }

        // Calculate the decryption key (d)
        d = mod_inverse(e, phi);

        printf("Public Key: (%ld, %ld)\n", e, n);
        printf("Private Key: (%ld, %ld)\n", d, n);

        printf("\nEnter the plaintext message: ");
        scanf(" %[^\n]", plaintext); // Here I'm using a different datatype as in the plaintext there could be whitespace and to include it as an input I have done it.

        if (strlen(plaintext) >= n)
        {
            printf(COLOR_BOLDRED "Invalid input! Plaintext should be less than n.\n" COLOR_RESET);
            continue;
        }

        // Encryption
        for (int i = 0; i < strlen(plaintext); i++)
        {
            ciphertext[i] = mod_exp(plaintext[i], e, n);
        }

        printf("\nCiphertext: ");
        for (int i = 0; i < strlen(plaintext); i++)
        {
            printf("%ld ", ciphertext[i]);
        }
        printf("\n");

        // Decryption
        char decryptFlag = 'n';
        printf(COLOR_MAGENTA "\nDo you want to decrypt the ciphertext? [y/n]: " COLOR_RESET);
        scanf(" %c", &decryptFlag);

        if (decryptFlag == 'y')
        {
            long int privateKey;
            printf("Enter the private key: ");
            if (scanf("%ld", &privateKey) != 1)
            {
                printf("Invalid input! Please enter a valid private key.\n");
                continue;
            }

            for (int i = 0; i < strlen(plaintext); i++)
            {
                decryptedtext[i] = mod_exp(ciphertext[i], privateKey, n);
            }

            printf("\nDecrypted Text: ");
            for (int i = 0; i < strlen(plaintext); i++)
            {
                printf("%c", (char)decryptedtext[i]);
            }
            printf("\n");
        }

        printf("\nDo you want to re-run the program? [y/(Any characters)]: "); // here if we provide 'y' then only it re-runs.
        scanf(" %c", &continueFlag);
        printf("\n----------------------------------------------\n");
    }

    printf("\nGood Bye!\n\n");
}

int main()
{
    rsa_encrypt_decrypt();
    return 0;
}
