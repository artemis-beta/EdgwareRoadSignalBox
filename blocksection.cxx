#include "blocksection.hxx"

void EWRB::BlockSection::update()
{
    _block_signal->setBlockOccupied(isOccupied());
    _block_signal->setOn(isOccupied());
}
