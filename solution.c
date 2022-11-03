#include <stdio.h>
#include <stdlib.h>

//-------------------------------- VARIABLE GLOBALE EXPRESSION --------------------------------//

// char expression[]="((A+B)*(C-(D/E)))";
// char expression[] = "(((A+B)*C)-(((D-(F/G))*(H+(K*L)))/((M-N)*O)))";
char expression[1000];

//-------------------------------- STRUCTURE DE DONNEES DU PROGRAMME --------------------------------//

typedef struct Operateur
{
    char value;
    int index;
} Operateur;

typedef struct Noeud
{
    Operateur operateur;
    int precedence;
    int nom;

} Noeud;

//-------------------------------- FONCTION QUI COMPTE CARACTERES D'UNE STRING  --------------------------------//

int count_of(char *string)
{
    int compteur = 0;

    for (int i = 0; string[i]; i++)
        compteur++;

    return compteur;
}

//-------------------------------- FONCTION QUI VERIFIE SI UN CARACTERE EST UN OPERATEUR --------------------------------//

int is_operator(char letter)
{

    if (letter == '+' || letter == '*' || letter == '/' || letter == '-')
        return 1;

    return 0;
}

//-------------------------------- FONCTION QUI TROUVE L'OPERATEUR PRINCIPALE --------------------------------//

Operateur chercher_ops(char string[])
{

    Operateur operator_principal;
    int first_time = 1;
    int temp = 0;
    int count_nb_parenthese = 0;
    int nb_letters = count_of(string);
    int minimum = 10000000000;

    for (int i = 0; i < nb_letters; i++)
    {
        if (string[i] == '(')
        {
            temp = count_nb_parenthese;
            count_nb_parenthese++;
        }
        else if (string[i] == ')')
        {
            temp = count_nb_parenthese;
            count_nb_parenthese--;
        }
        else if (is_operator(string[i]) == 1 && count_nb_parenthese < temp)
        {
            if (minimum > count_nb_parenthese)
            {
                operator_principal.value = string[i];
                operator_principal.index = i;
                minimum = count_nb_parenthese;
            }
        }

        if (first_time == 1 && is_operator(string[i]))
        {
            if (minimum > count_nb_parenthese)
            {
                operator_principal.value = string[i];
                operator_principal.index = i;
                minimum = count_nb_parenthese;
                first_time = 0;
            }
        }
    }

    return operator_principal;
}

//-------------------------------- FONCTION QUI LIT UNE EXPRESSION --------------------------------//

void lire_expression()
{
    printf("Entrez une expression valide : \n");
    scanf("%s", expression);
}

//-------------------------------- FONCTION QUI CHERCHE L'EXPRESSION A GAUCHE --------------------------------//

char *find_left(int index, char string[])
{
    int nb_letters = count_of(string);
    int left_nb_letters = index - 1;
    int j = 0;

    char *left_expression = (char *)malloc(sizeof(char) * left_nb_letters);
    // char left_expression[1000];

    for (int i = index - 1; i > 0; i--)
    {
        left_expression[j] = string[i];
        j++;
    }

    int temp_nb_letter = count_of(left_expression);
    int count;
    char temp;

    for (int i = 0; i < (int)temp_nb_letter / 2; i++)
    {
        temp = left_expression[i];
        left_expression[i] = left_expression[temp_nb_letter - i - 1];
        left_expression[temp_nb_letter - i - 1] = temp;
    }

    return left_expression;
}

//-------------------------------- FONCTION QUI CHERCHE L'EXPRESSION A DROITE --------------------------------//

char *find_right(int index, char string[])
{
    int nb_letters = count_of(string);
    int j = 0;

    int right_nb_letters = (nb_letters - index + 3);
    char *right_expression = (char *)malloc(sizeof(char) * right_nb_letters);

    for (int i = index + 1; i < nb_letters - 1; i++)
    {
        right_expression[j] = string[i];
        j++;
    }

    return right_expression;
}

//-------------------------------- FONCTIONS QUI GENERENT LA TACHE AVEC EXPRESSION --------------------------------//

void generer_noeud(Noeud noeud, int pere)
{
    // Noeud current_noeud
    // generer_precedences();
    // generer_tache();
}

void generer_precedences(Noeud noeud, int pere)
{
}

int genrer_tache(char expression[], Noeud noeud, int operateur_central, int parent)
{
}

//-------------------------------- FONCTION QUI GENERE L'ARBRE --------------------------------//

void genere(char expression[], Noeud noeud, int pere)
{
    Operateur op = chercher_ops(expression);
    printf("Operateur %c , Index : %d \n", op.value, op.index);

    char *left_string = find_left(op.index, expression);
    char *right_string = find_right(op.index, expression);

    printf("left : %s \n", left_string);
    printf("right : %s \n", right_string);

    // int j = generer_tache(expression, noeud, op.index, pere);
    // generer_precedences(noeud, pere);
}

//-------------------------------- FONCTION PRINCIPALE--------------------------------//

int main()
{
    Noeud tache_0;
    lire_expression(tache_0);
    genere(expression, tache_0, 0);

    return 0;
}