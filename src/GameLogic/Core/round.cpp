#include "round.h"

Round::Round()
{
}

void Round::Start()
{
    _isFinished = false;
}

bool Round::IsFinished() const
{
    return _isFinished;
}
