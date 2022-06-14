#pragma once
#include "Item.h"

class Star :
    public Item
{
public:
    Star(Map& map, int position_x, int position_y);
};

