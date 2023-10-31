#include "Case.h"

Case::Case()
{
    valeur = 0;
    merge = false;
}

int Case::GetValue()
{
    return valeur;
}


void Case::ChangeValue(int i) {
    valeur = i;
}