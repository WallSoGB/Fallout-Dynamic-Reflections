#include "GridCellArray.hpp"

GridCell* GridCellArray::GetCell(SInt32 aX, SInt32 aY) {
    UInt32 uiGridSize = iDimension;
    if (aX < iDimension && aY < iDimension)
        return &pGridCells[aX + aY * uiGridSize];
    return nullptr;
}
