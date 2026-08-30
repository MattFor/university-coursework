import matplotlib.pyplot as plt
import numpy as np
import math  # Można użyć math.log2 lub numpy.log2

# Lista rozmiarów tablic (N) podana przez użytkownika
n_values = np.array([10, 50, 100, 300, 750, 1000, 3000, 4500, 6000, 7000, 8000, 9000, 10000, 15000, 20000])


# Definicje funkcji złożoności (używamy log2)
# Funkcje zwracają wartość dla tablicy rozmiarów n_values
def linear(n):
	# Klasa O(n)
	return n


def n_log_n(n):
	# Klasa O(n log n)
	# numpy.log2 automatycznie radzi sobie z tablicami
	# Dodajemy małą wartość do n, aby uniknąć log2(0) jeśli 0 byłoby w n_values, choć tu nie jest
	return n * np.log2(n + 1e-9)  # +1e-9 dla bezpieczeństwa, choć n_values startuje od 10


def n_log_sq_n(n):
	# Klasa O(n log^2 n)
	log_n = np.log2(n + 1e-9)
	return n * log_n * log_n


def quadratic(n):
	# Klasa O(n^2)
	return n * n


# Skalowanie funkcji
# Wybieramy stałe przeskalowania, aby krzywe były widoczne na jednym wykresie
# Te stałe są empiryczne i służą tylko celom wizualizacji porównawczej
scale_linear = 1.0  # O(n) rośnie najwolniej, potrzebuje większej skali względnej
scale_n_log_n = 0.1  # O(n log n)
scale_n_log_sq_n = 0.01  # O(n log^2 n)
scale_quadratic = 0.0001  # O(n^2) rośnie najszybciej, potrzebuje najmniejszej skali względnej

# Obliczanie wartości funkcji złożoności dla podanych rozmiarów tablic, ze skalowaniem
y_linear = scale_linear * linear(n_values)
y_n_log_n = scale_n_log_n * n_log_n(n_values)
y_n_log_sq_n = scale_n_log_sq_n * n_log_sq_n(n_values)
y_quadratic = scale_quadratic * quadratic(n_values)

# Tworzenie wykresu
plt.figure(figsize=(12, 8))  # Rozmiar wykresu

# Rysowanie linii dla każdej złożoności
plt.plot(n_values, y_linear, label=f'O(n) (skalowane o {scale_linear})', marker='o')
plt.plot(n_values, y_n_log_n, label=f'O(n log n) (skalowane o {scale_n_log_n})', marker='o')
plt.plot(n_values, y_n_log_sq_n, label=f'O(n log² n) (skalowane o {scale_n_log_sq_n})', marker='o')
plt.plot(n_values, y_quadratic, label=f'O(n²) (skalowane o {scale_quadratic})', marker='o')

# Dodanie etykiet i tytułu
plt.xlabel("Rozmiar tablicy (n)")
plt.ylabel("Skalowana wartość funkcji złożoności")
plt.title("Porównanie teoretycznej złożoności obliczeniowej (skalowane)")
plt.legend()  # Wyświetlenie legendy
plt.grid(True, linestyle='--', alpha=0.6)  # Dodanie siatki

# Ustawienie skali osi X, aby lepiej pokazać rozkład danych
plt.xscale('linear')  # Domyślnie jest liniowa, ale można jawnie ustawić
# plt.yscale('linear') # Domyślnie jest liniowa, ale można jawnie ustawić

# plt.yscale('log')
# plt.ylabel("Skalowana wartość funkcji złożoności (skala logarytmiczna)")
# plt.title("Porównanie teoretycznej złożoności obliczeniowej (skala logarytmiczna Y)")


# Wyświetlenie wykresu
plt.show()
