#include "Case.h"

Case::Case()
{
    this->valeur = 0;
    this->merge = false;
}

int Case::GetValue()
{
    return this->valeur;
}


void Case::ChangeValue(int i) {
    this->valeur = i;
}