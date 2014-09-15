/*  Class Name  : GEntity
    Definition  : Entity collisions.
    Author      : Aleqh
*/

#include "GEntity.h"

std::vector<GEntityCollide> GEntityCollide::EntityColList;

GEntityCollide::GEntityCollide()
{
    this->EntityA = NULL;
    this->EntityB = NULL;
}
