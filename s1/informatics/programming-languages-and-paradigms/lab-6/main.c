#include <stdio.h>
#include <string.h>

#define MAX_LINES 256
#define MAX_LINE_LEN 256


void zad11(char data[MAX_LINES][MAX_LINE_LEN], int line_count)
{
	int s_count = 0; // Liczba małych liter
	int b_count = 0; // Liczba dużych liter
	int o_count = 0; // Liczba innych znaków

	for (int i = 0; i < line_count; i++)
	{
		int j = 0;
		char c;
		while ((c = data[i][j++]) != '\0')
		{
			if (c >= 'a' && c <= 'z')
			{
				s_count++;
			}
			else if (c >= 'A' && c <= 'Z')
			{
				b_count++;
			}
			else if (c != '\n')
			{
				o_count++;
			}
		}

		printf("Line Number: %d | small char cnt: %d | big char cnt: %d | other char cnt: %d\n", i + 1, s_count, b_count, o_count);
	}

	printf("Total number of small characters: %d\nTotal number of big characters: %d\nTotal number of other characters: %d\n", s_count, b_count, o_count);
}

void zad15(char data[MAX_LINES][MAX_LINE_LEN], int line_count)
{
	int a, b;
	printf("\n\nInput 2 indices of the rows to swap.\n");
	scanf("%d %d", &a, &b);

	if (a < 1 || a > line_count || b < 1 || b > line_count)
	{
		printf("Invalid input\n");
		return;
	}

	char temp[MAX_LINE_LEN];
	strcpy(temp, data[a - 1]);
	strcpy(data[a - 1], data[b - 1]);
	strcpy(data[b - 1], temp);

	printf("\nData after swapping lines %d and %d:\n", a, b);
	for (int j = 0; j < line_count; j++)
	{
		printf("%d. %s", j + 1, data[j]);
	}
}

void zad16(char data[MAX_LINES][MAX_LINE_LEN], int line_count, const char *prefix)
{
	printf("\nLines starting with \"%s\":\n", prefix);
	for (int i = 0; i < line_count; i++)
	{
		if (strncmp(data[i], prefix, strlen(prefix)) == 0)
		{
			printf("%d. %s", i + 1, data[i]);
		}
	}
}

void zad17(char data[MAX_LINES][MAX_LINE_LEN], int *line_count, int n, const char *new_line)
{
	if (n < 1 || n > *line_count || *line_count >= MAX_LINES)
	{
		printf("Invalid line number or array is full\n");
		return;
	}

	// Przesuwanie linii w dół, aby zrobić miejsce dla nowej linii
	for (int i = *line_count; i > n; i--)
	{
		strcpy(data[i], data[i - 1]);
	}

	strcpy(data[n], new_line);
	(*line_count)++;

	printf("\nData after inserting a new line after line %d:\n", n);
	for (int j = 0; j < *line_count; j++)
	{
		printf("%d. %s", j + 1, data[j]);
	}
}

void zad18(char data[MAX_LINES][MAX_LINE_LEN], int line_number, int word_position)
{
	if (line_number < 1 || line_number > MAX_LINES)
	{
		printf("Invalid line number\n");
		return;
	}

	char *token;
	char line_copy[MAX_LINE_LEN];
	strcpy(line_copy, data[line_number - 1]);

	int current_position = 1;
	token = strtok(line_copy, ":");
	while (token != nullptr)
	{
		if (current_position == word_position)
		{
			printf("Word at position %d in line %d: %s\n", word_position, line_number, token);
			return;
		}

		token = strtok(nullptr, ":");
		current_position++;
	}

	printf("No word found at position %d in line %d\n", word_position, line_number);
}

char litery[] = {'a',165,'b','c',134,'d','e',169,'f','g','h','i','j','k','l',136, 'm','n',228,'o',162,'p','q','r','s',152,'t','u','v','w','x','y','z',190,171,'A',164,'B','C',143,'D','E',168,'F','G','H','I','J','K','L',157,'M','N',227,'O',224,'P','Q','R','S',151,'T','U','V','W','X','Y','Z',189,141,' ','.',',','?',':','-','0','1','2','3','4','5','6','7','8','9','!','\0' };
char *mors[] = { ".-",".-.-","-...","-.-.","-.-..","-..",".","..-..","..-.","--.","....","..",".---","-.-",".-..",".-..-","--","-.","--.--","---","---.",".--.","--.-",".-.","...","...-...","-","..-","...-",".--","-..-","-.--","--..","--..-","--",".-",".-.-","-...","-.-.","-.-..","-..",".","..-..","..-.","--.","....","..",".---","-.-",".-..",".-..-","--","-.","--.--","---","---.",".--.","--.-",".-.", "...","...-...","-","..-","...-",".--","-..-","-.--","--..","--..-","--"," ",".-.-.-","--..--","..--..","---...","-....-","-----",".----","..---","...--","....-",".....","-....","--...","---..","----.","!",0 };

void encode_morse(const char *text)
{
	while (*text) {
		char ch = *text;
		int found = 0;

		// Szukaj odpowiednika znaku w tablicy litery
		for (int i = 0; litery[i] != '\0'; i++)
		{
			if (litery[i] == ch)
			{
				printf("%s/", mors[i]);
				found = 1;
				break;
			}
		}

		if (!found)
		{
			printf("? ");  // Nieznany znak
		}

		text++;
	}

	printf("\n");
}

void decode_morse(const char *morseCode)
{
	char buffer[16];
	int index = 0;

	while (*morseCode)
	{
		if (*morseCode == '/' || *morseCode == '\0')
		{
			buffer[index] = '\0';
			index = 0;

			int found = 0;
			for (int i = 0; mors[i] != nullptr; i++)
			{
				if (strcmp(buffer, mors[i]) == 0)
				{
					printf("%c", litery[i]);
					found = 1;
					break;
				}
			}

			if (!found)
			{
				printf("?");
			}

			if (*morseCode == '\0')
			{
				break;
			}
		}
		else
		{
			buffer[index++] = *morseCode;
		}

		morseCode++;
	}

	printf("\n");
}

void zad19()
{
	int choice;
	char text[MAX_LINE_LEN];

	printf("Choose an option:\n1. Encode text to Morse code\n2. Decode Morse code to text\nChoice: ");
	scanf("%d", &choice);
	getchar();  // Usunięcie \n po scanf

	if (choice == 1)
	{
		printf("Enter text to encode: ");
		fgets(text, MAX_LINE_LEN, stdin);
		text[strcspn(text, "\n")] = '\0';  // Usunięcie \n
		printf("Encoded Morse Code: ");
		encode_morse(text);
	}
	else if (choice == 2)
	{
		printf("Enter Morse code to decode ( separate with / ): ");
		fgets(text, MAX_LINE_LEN, stdin);
		text[strcspn(text, "\n")] = '\0';
		printf("Decoded Text: ");
		decode_morse(text);
	}
	else
	{
		printf("Invalid choice\n");
	}
}


int main()
{
    // zad11();

	// Wczytanie pliku
	int i = 0;
	char data[MAX_LINES][MAX_LINE_LEN];

	FILE *file = fopen("../data.txt", "r");
	if (!file)
	{
		printf("ERROR - File could not be opened\n");
		return 1;
	}

	while (fgets(data[i], MAX_LINE_LEN, file) != nullptr && i < MAX_LINES)
	{
		// Dodać na końcu newline, bo mnie denerwuje to
		const size_t len = strlen(data[i]);
		if (len > 0 && data[i][len - 1] != '\n')
		{
			if (len < MAX_LINE_LEN - 1)
			{
				data[i][len] = '\n';
				data[i][len + 1] = '\0';
			}
		}

		i++;
	}

	fclose(file);

	zad11(data, i);
	zad15(data, i);
	zad16(data, i, "Hello");
	zad17(data, &i, 2, "New Line after line 2\n");
	zad18(data, 3, 2);
	zad19();
}
