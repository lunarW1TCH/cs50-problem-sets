#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

const int KEY_LENGTH = 26;
char key_standardized[KEY_LENGTH + 1];

// not capitalized letters ASCII codes: 97-122
// capitalized letters ASCII codes: 65-90
const int CAP_BEG = 65;
const int CAP_END = 90;
const int LOWER_BEG = 97;
const int LOWER_END = 122;

void string_to_upper(string key)
{
  char temp[KEY_LENGTH];

  for (int i = 0; i < KEY_LENGTH; i++)
  {
    temp[i] = toupper(key[i]);
  }

  memcpy(key_standardized, temp, KEY_LENGTH);
  key_standardized[KEY_LENGTH] = '\0';
}

bool is_letter(char c)
{
  if (((c >= LOWER_BEG && c <= LOWER_END) || (c >= CAP_BEG && c <= CAP_END)))
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool is_capitalized(char letter)
{
  if (letter >= LOWER_BEG)
  {
    return false;
  }
  else
  {
    return true;
  }
}

void cipher_string(string text)
{
  int text_length = strlen(text);

  // creating an array of ciphered chars
  char temp[text_length];

  for (int i = 0; i < text_length; i++)
  {

    int dec = text[i];

    // check if letter and whether it's capitalized
    bool capitalized;

    if (is_letter(dec))
    {
      capitalized = is_capitalized(dec);
    }
    else
    {
      // not a letter
      temp[i] = dec;
      continue;
    }

    // convert ascii to key's index
    int key_index;

    char ciphered;
    if (capitalized)
    {
      key_index = dec - CAP_BEG;

      ciphered = key_standardized[key_index];
      temp[i] = ciphered;
    }
    else
    {
      key_index = dec - LOWER_BEG;

      // preserving lowercase
      ciphered = tolower(key_standardized[key_index]);

      temp[i] = ciphered;
    }
  }

  // printing cipher
  char output[text_length + 1];
  memcpy(output, temp, text_length);
  output[text_length] = '\0';
  printf("%s\n", output);
}

int substitute(string key)
{
  string_to_upper(key);

  // user input
  printf("plaintext: ");
  string input = get_string("");

  printf("ciphertext: ");
  cipher_string(input);

  return 0;
}

int main(int argc, string argv[])
{

  // input validation

  if (argc != 2)
  {
    printf("Missing command-line argument\n");
    return 1;
  }

  string key = argv[1];

  if (strlen(key) != KEY_LENGTH)
  {
    printf("The key is invalid\n");
    return 1;
  }

  // ciphering

  if (!substitute(key))
  {
    return 0;
  }

  printf("hello, %s\n", argv[1]);
  return 0;
}
