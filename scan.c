#include <stdio.h>

int main() {
    char string[100]; // Defina um tamanho adequado para a sua string
    char character;
    int ascii_value;

    // Lê a entrada como "Entrada A"
    scanf("%s %c", string, &character);

    // Calcula o valor ASCII do caractere
    ascii_value = character;

    // Exibe a string e o caractere com seus respectivos valores
    printf("String: %s\n", string);
    printf("Caractere: %c\n", character);
    printf("Valor ASCII do caractere: %d\n", ascii_value);

    return 0;
}
