#include <time.h>
#include <stdio.h>

#define ADD(a, b) a + b;

int main(void)
{
   int rok_urodzenia = 0;
   time_t czas_teraz = time(NULL);
   struct tm *czas_info = localtime(&czas_teraz);
   int obecny_rok = czas_info->tm_year + 1900;

   printf("Wpisz rok urodzenia:\n");
   scanf("%d", &rok_urodzenia);

   printf("Masz %d lat.\n", obecny_rok - rok_urodzenia);

   return 0;
}
