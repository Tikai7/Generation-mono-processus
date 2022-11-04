#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//-------------------------------- VARIABLE GLOBALE EXPRESSION --------------------------------//

// char expression[] = "((A+B)*(C-(D/E)))";
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
    int precedence;
    int nom;

    char operateur;
    char *expression_gauche;
    char *expression_droite;

    int e_gauche;
    int e_droite;

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

//-------------------------------- FONCTION QUI VERIFIE SI C'EST UNE EXPRESSION --------------------------------//

int is_expression(char *string)
{
    int nb_letters = count_of(string);
    int boolean = -1;

    for (int i = 0; i < nb_letters; i++)
    {
        if (string[i] == '(')
            boolean += 1;

        if (string[i] == ')')
            boolean++;
    }
    if (boolean > 0)
        boolean = 1;
    else
        boolean = 0;

    return boolean;
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
    int left_nb_letters = index;
    int j = 0;

    char *left_expression = (char *)malloc(sizeof(char) * left_nb_letters);
    // char left_expression[1000];

    for (int i = index - 1; i > 0; i--)
    {
        left_expression[j] = string[i];
        j++;
    }

    left_expression[left_nb_letters - 1] = '\0';

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

    int right_nb_letters = (nb_letters - index - 1);
    char *right_expression = (char *)malloc(sizeof(char) * right_nb_letters);

    for (int i = index + 1; i < nb_letters - 1; i++)
    {
        right_expression[j] = string[i];
        j++;
    }

    right_expression[right_nb_letters - 1] = '\0';

    return right_expression;
}

//-------------------------------- FONCTIONS QUI GENERENT LA TACHE AVEC EXPRESSION --------------------------------//

void genrer_noeud(Noeud noeud)
{
    printf("Tache M%d = ", noeud.nom);

    if (noeud.e_gauche > -1)
        printf("M%d %c ", noeud.e_gauche, noeud.operateur);
    else
        printf("%s %c ", noeud.expression_gauche, noeud.operateur);

    if (noeud.e_droite > -1)
        printf("M%d \n", noeud.e_droite);
    else
        printf("%s \n", noeud.expression_droite);
}

Noeud generer_precedence(Noeud noeud, int pere)
{
    noeud.precedence = pere;
    noeud.nom = pere + 1;
    return noeud;
}

Noeud generer_graphe(char expression[], Noeud noeud, Operateur operateur_central, int parent)
{
    noeud.expression_droite = find_right(operateur_central.index, expression);
    noeud.expression_gauche = find_left(operateur_central.index, expression);
    noeud.operateur = operateur_central.value;

    noeud = generer_precedence(noeud, parent);
    // genrer_noeud(noeud);

    return noeud;
}
//-------------------------------- FONCTION QUI GENERE UNE TACHE --------------------------------//

void genere_tache()
{
}

//-------------------------------- FONCTION QUI GENERE L'ARBRE --------------------------------//

Noeud genere(char expression[], Noeud noeud, int pere)
{
    Operateur op = chercher_ops(expression);

    Noeud current_node = generer_graphe(expression, noeud, op, pere);

    Noeud son_node_right;
    Noeud son_node_left;

    current_node.e_gauche = -1;
    current_node.e_droite = -1;

    int value = 0;

    if (is_expression(current_node.expression_gauche))
    {
        value = 1;
        son_node_left = genere(current_node.expression_gauche, current_node, current_node.nom);
        current_node.e_gauche = son_node_left.nom;
    }

    if (is_expression(current_node.expression_droite))
    {
        son_node_right = genere(current_node.expression_droite, current_node, current_node.nom + value);
        current_node.e_droite = son_node_right.nom;
    }

    genrer_noeud(current_node);

    return current_node;
}

//-------------------------------- FONCTION PRINCIPALE--------------------------------//

int main()
{
    //((A+B)*(C-(D/E)))
    Noeud tache_0;
    tache_0.precedence = 0;
    tache_0.nom = 1;

    lire_expression();
    genere(expression, tache_0, 0);

    return 0;
}