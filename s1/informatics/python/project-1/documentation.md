**Opis Programu: Wizualizator Algorytmów Sortowania z Analizą Wydajności - przez REDACTED**

**1. Wstęp i Cel Projektu**

Projekt "Wizualizator Algorytmów Sortowania" to interaktywne narzędzie napisane w C++, którego głównym celem jest graficzne przedstawienie działania popularnych algorytmów sortowania. Program umożliwia użytkownikowi nie tylko obserwację krok po kroku, w jaki sposób dane są porządkowane, ale także dogłębną analizę ich wydajności w różnych scenariuszach.

**2. Funkcjonalność i Interakcja**

Aplikacja oferuje szereg funkcji, które zwiększają jej wartość edukacyjną i analityczną:

* **Wizualizacja na żywo:** Główna część programu to dynamiczne przedstawienie tablicy danych jako zestawu słupków o różnej wysokości, odpowiadającej wartości elementu. Zmiany w tablicy podczas sortowania są wizualizowane w czasie rzeczywistym.
* **Obsługa Wielu Algorytmów:** Program implementuje i pozwala na wybór spośród wielu znanych algorytmów sortowania, takich jak Sortowanie Bąbelkowe, Wstawianie, Wybieranie, Quicksort, Shellsort, Heapsort, Radix Sort (LSD Bucket), Cocktail Sort, Gnome Sort, Timsort, a nawet Bogosort oraz eksperymentalny Spreadsort. Użytkownik może łatwo przełączać się między algorytmami.
* **Statystyki w czasie rzeczywistym:** Wykorzystując bibliotekę ImGui, program wyświetla nakładkę z kluczowymi statystykami pracy algorytmu w trakcie sortowania, takimi jak liczba porównań elementów oraz liczba dostępów do tablicy. Te metryki są kluczowe dla zrozumienia teoretycznej złożoności algorytmów w praktyce.
* **Tryby Krokowe i Automatyczne:** Użytkownik ma kontrolę nad tempem wizualizacji. Możliwe jest sortowanie w trybie automatycznym z konfigurowalnym opóźnieniem między krokami, jak również manualne przechodzenie przez kolejne etapy sortowania co pozwala na dokładne śledzenie logiki algorytmu.
* **Konfiguracja Danych:** Przed rozpoczęciem wizualizacji, użytkownik może skonfigurować liczbę elementów do posortowania.
* **Integracja Dźwięku:** Jest możliwość usłyszenia sortowanych danych za pomocą customowego DLL-a który używia funkcji z biblioteki `windows.h` w celu produkowania różnych beeps i boops.

**3. Moduł Analizy Wydajności**

Jednym z kluczowych wyróżników projektu jest zaawansowany moduł analizy wydajności. Zamiast jedynie wizualizować sortowanie dla jednej, losowej tablicy, moduł ten pozwala na:

* **Testowanie Wielu Scenariuszy:** Algorytmy mogą być testowane na tablicach danych o różnej charakterystyce początkowej: tablice losowe (mieszane), zawierające tylko wartości dodatnie, tylko ujemne, tablice już posortowane oraz tablice posortowane odwrotnie. Testowanie na tych skrajnych przypadkach pozwala zaobserwować, jak struktura danych wpływa na czas wykonania poszczególnych algorytmów (np. algorytmy wrażliwe na częściowe posortowanie).
* **Testowanie Różnych Rozmiarów Danych:** Moduł umożliwia automatyczne uruchamianie testów dla predefiniowanego zestawu rozmiarów tablic (od małych, np. 10 elementów, do bardzo dużych, np. 20000 elementów).
* **Pomiar Czasu Wykonania:** Dla każdego algorytmu, typu danych i rozmiaru tablicy, program mierzy czas potrzebny na ukończenie sortowania.
* **Generowanie Raportów:** Wyniki pomiarów są zapisywane do pliku w formacie CSV, co ułatwia dalszą analizę i przetwarzanie danych.
* **Automatyczne Generowanie Wykresów:** Program posiada możliwość odczytania i przetworzenia wygenerowanych danych CSV za pomocą skryptu w pythonie, który automatycznie wczytuje wygenerowany raport CSV i tworzy czytelne wykresy porównujące czasy wykonania algorytmów w różnych scenariuszach.

**4. Aspekty Techniczne i Użyte Technologie**

Projekt został zrealizowany w C++26 i korzysta z systemu budowania CMake. Zastosowano następujące kluczowe biblioteki zewnętrzne:

* **GLFW:** Lekka biblioteka do tworzenia okien, kontekstów OpenGL i zarządzania wejściem.
* **OpenGL:** Standardowa biblioteka graficzna wykorzystana do rysowania słupków reprezentujących elementy tablicy oraz innych elementów wizualizacji.
* **ImGui:** Biblioteka do tworzenia interfejsów użytkownika, wykorzystana do wyświetlania dynamicznych statystyk podczas sortowania.
* **SDL3:** Teoretycznie znajduje się i jest poprawnie podpięta do programu, ale zdecydowałem że dźwiękiem zajmować będzie się custom SOUNDLIB.DLL.
* **Niestandardowe Biblioteki DLL:** Projekt korzysta z dwóch własnych bibliotek/DLL (SOUNDLIB i GET\_RANDLIB).

Implementacja algorytmów sortowania została przeprowadzona krok po kroku, co pozwoliło na wizualizację każdego etapu pracy algorytmu. Zarządzanie stanem wizualizacji i logiką przejścia między trybami (IDLE, SORTING, SETTINGS, COMPLETED, RANDOMIZING).

**5. Dlaczego Projekt Zasługuje na Ocenę 5?**

Projekt wykracza poza standardowe wymagania wizualizacji algorytmów sortowania i stanowi kompleksowe narzędzie analityczno-edukacyjne. Uzasadnienie dla oceny 5 obejmuje:

* **Złożoność i Zakres:** Implementacja kilkunastu różnorodnych algorytmów sortowania, w tym zarówno prostszych (O(n²)) jak i bardziej złożonych (O(n log n), O(nk)).
* **Wykorzystanie Wielu Bibliotek Zewnętrznych:** Umiejętne zintegrowanie i wykorzystanie kilku popularnych bibliotek graficznych i multimedialnych (GLFW, OpenGL, ImGui, SDL3) świadczy o tym że umiem czytać dokumentacje.
* **Moduł Analizy Wydajności:** Implementacja dedykowanego modułu do systematycznego testowania wydajności algorytmów w różnych warunkach (rozmiar danych, stopień posortowania) jest znaczącym rozszerzeniem standardowej funkcjonalności i dodaje projektowi głębi analitycznej. Automatyczne generowanie wykresów dodatkowo podnosi wartość tej części.
* **Statystyki w czasie Rzeczywistym:** Dynamiczne wyświetlanie kluczowych metryk wydajności (porównania, dostępy do tablicy) w trakcie wizualizacji dostarcza użytkownikowi natychmiastowej informacji zwrotnej o pracy algorytmu.
* **Kontrola i Interakcja:** Możliwość pełnej kontroli nad procesem sortowania (tryb krokowy/automatyczny, konfiguracja opóźnienia) oraz intuicyjny interfejs (ImGui) sprawiają, że program jest efektywnym narzędziem edukacyjne.
* **Dodatkowe Elementy:** Podjęcie próby integracji dźwięku i wykorzystanie własnych bibliotek DLL pokazuje moją niesamowitą ambicję dostania 5 i zaliczenia tego semestru bo nie zdaje z analizy i czas mi się kończy by się jej w końcu nauczyć.
