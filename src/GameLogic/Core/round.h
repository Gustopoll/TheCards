#ifndef ROUND_H
#define ROUND_H

#include "turn.h"

#include <memory>
#include <optional>
#include <vector>

class Round
{
public:
    Round();
    ~Round() = default;

    void Start();
    bool IsFinished() const;

private:
    std::optional<Turn> _currentTurn;
    bool _isFinished = false;
};

#endif // ROUND_H
