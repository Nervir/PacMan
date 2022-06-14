#pragma once
#include "Item.h"

class NPCEater :
    public Item
{
public:
    NPCEater(Map& map, int position_x, int position_y);
};