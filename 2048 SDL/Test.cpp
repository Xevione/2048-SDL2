#include "Test.h"

#include "Grid.h"

Test::Test() {
}

void Test::Test1() 
{
    testGrid->grid[0].ChangeValue(2);
    testGrid->grid[1].ChangeValue(2);
    testGrid->grid[2].ChangeValue(4);
    testGrid->grid[3].ChangeValue(4);
    // on initialise la grille de test pour avoir ce placement
    /*
    * {2,2,4,4
    *  0,0,0,0
    *  0,0,0,0
    *  0,0,0,0}
    */

    referenceGrid->grid[2].ChangeValue(8);
    referenceGrid->grid[3].ChangeValue(4);

    // lorsqu'on fait un mouvement vers la droite nous sommes sensé obtenir:
    /*
    * {0,0,8,4
    *  0,0,0,0
    *  0,0,0,0
    *  0,0,0,0}
    */

    testGrid->TilePlayRight();

    if (testGrid == referenceGrid) {
        cout << "Test 1 passé" << endl;
    }
    else 
    {
        cout << "Test 1 échoué" << endl;
    }

}