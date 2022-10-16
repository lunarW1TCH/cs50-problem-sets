#include <math.h>
#include <cs50.h>
#include <stdio.h>

int checksum(long number, int num_digits)
{
  // creating inverted array of digits
  int digits[num_digits];
  long temp = number;

  for (int i = 0; i < num_digits; i++)
  {
    int dig = temp % 10;
    digits[i] = dig;
    temp = temp / 10;
  }

  // multiplying every other digit by 2 and summing the others
  int sum_multiplied = 0;
  int sum_others = 0;
  for (int i = 0; i < num_digits; i += 2)
  {
    // multiplying and summing even digits
    if (digits[i + 1] * 2 < 10)
    {
      sum_multiplied += digits[i + 1] * 2;
    }
    else
    {
      // separating digits of the product

      // adding 1 for every number >= 10
      sum_multiplied += 1;

      // adding modulo
      sum_multiplied += (digits[i + 1] * 2) % 10;
    }

    // summing the rest of digits
    sum_others += digits[i];
  }

  printf("%i\n", sum_multiplied);
  printf("%i\n", sum_others);

  // checking validity
  int sum = sum_multiplied + sum_others;
  printf("%i\n", sum);

  if (sum % 10 == 0)
  {
    return 1;
  }

  printf("INVALID\n");
  return 0;
}

int check_first_digits(long number, int num_digits)
{
  // extracting digits
  int first_digit = floor(number / pow(10, num_digits - 1));
  int first_two_digits = floor(number / pow(10, num_digits - 2));

  // visa 13 and 16 digits - starts with 4
  if (num_digits == 13 || num_digits == 16)
  {
    if (first_digit == 4)
    {
      printf("VISA\n");
      return 1;
    }
  }

  // american express 15 digits - starts with 34 or 37
  if (num_digits == 15)
  {
    if (first_two_digits == 34 || first_two_digits == 37)
    {
      printf("AMEX\n");
      return 1;
    }
  }

  // mastercard 16 digits - starts with 51, 52, 53, 54, 55
  if (num_digits == 16)
  {
    int mastercard_digits[] = {51, 52, 53, 54, 55};

    for (int i = 0; i < sizeof(mastercard_digits); i++)
    {
      if (first_two_digits == mastercard_digits[i])
      {
        printf("MASTERCARD\n");
        return 1;
      }
    }
  }

  // invalid
  printf("INVALID\n");
  return 0;
}

void check_validity(long number)
{
  if (number <= 0)
  {
    printf("INVALID\n");
    return;
  }

  // checks the number of digits in a positive number other than 0
  int num_digits = floor(log10(number)) + 1;
  printf("%i\n", num_digits);

  // checks if length == 13, 15 or 16
  if (!(num_digits == 13 || num_digits == 15 || num_digits == 16))
  {
    printf("INVALID\n");
    return;
  }

  // checks sum
  if (!checksum(number, num_digits))
  {
    return;
  }

  // checks the card manufacturer
  if (!check_first_digits(number, num_digits))
  {
    return;
  }
}

int main(void)
{
  long number = get_long("Enter card number: \n");
  check_validity(number);
}