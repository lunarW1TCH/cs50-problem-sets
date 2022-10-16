#include <cs50.h>
#include <stdio.h>

void pyramid_left(int height, int index)
{
  for (int j = 0; j < height - index - 1; j++)
  {
    printf(" ");
  }
  for (int k = 1 + index; k > 0; k--)
  {
    printf("#");
  }
}

void pyramid_right(int height, int index)
{

  for (int k = 1 + index; k > 0; k--)
  {
    printf("#");
  }
  for (int j = 0; j < height - index - 1; j++)
  {
    printf(" ");
  }
}

void pyramid(int height)
{
  for (int i = 0; i < height; i++)
  {
    pyramid_left(height, i);

    // break in the pyramid
    printf("  ");

    pyramid_right(height, i);

    printf("\n");
  }
}

int main(void)
{
  int height = 0;
  // checks if height is an integer bigger than 0
  while (height <= 0)
  {
    height = get_int("Input height of the pyramid: \n");
  }

  pyramid(height);
}