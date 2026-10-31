#ifndef ASSETS_H
#define ASSETS_H

#include <array>

namespace Assets
{

namespace Buttons
{
    constexpr auto kGroup = "Buttons";
    constexpr std::array kPaths =
    {
        "Data/Buttons/button_end_turn.png",
        "Data/Buttons/no_cards.png",
        "Data/Buttons/back_card.png",
    };

    //! Indices into kPaths for named access.
    constexpr std::size_t kEndTurn  = 0;
    constexpr std::size_t kNoCards  = 1;
    constexpr std::size_t kBackCard = 2;
}

namespace Backgrounds
{
    constexpr auto kGroup = "Backgrounds";
    constexpr std::array kPaths =
    {
        "Data/Backgrounds/enemy_background.jpg",
    };

    constexpr std::size_t kEnemyBackground = 0;
}

namespace Cards
{
    constexpr auto kGroup = "Cards";
    constexpr std::array kPaths =
    {
        // Acorns (A)
        "Data/Cards/A-0A.png",
        "Data/Cards/A-07.png",
        "Data/Cards/A-08.png",
        "Data/Cards/A-09.png",
        "Data/Cards/A-10.png",
        "Data/Cards/A-J1.png",
        "Data/Cards/A-J2.png",
        "Data/Cards/A-KI.png",
        // Bells (B)
        "Data/Cards/B-0A.png",
        "Data/Cards/B-07.png",
        "Data/Cards/B-08.png",
        "Data/Cards/B-09.png",
        "Data/Cards/B-10.png",
        "Data/Cards/B-J1.png",
        "Data/Cards/B-J2.png",
        "Data/Cards/B-KI.png",
        // Hearts (H)
        "Data/Cards/H-0A.png",
        "Data/Cards/H-07.png",
        "Data/Cards/H-08.png",
        "Data/Cards/H-09.png",
        "Data/Cards/H-10.png",
        "Data/Cards/H-J1.png",
        "Data/Cards/H-J2.png",
        "Data/Cards/H-KI.png",
        // Leaves (L)
        "Data/Cards/L-0A.png",
        "Data/Cards/L-07.png",
        "Data/Cards/L-08.png",
        "Data/Cards/L-09.png",
        "Data/Cards/L-10.png",
        "Data/Cards/L-J1.png",
        "Data/Cards/L-J2.png",
        "Data/Cards/L-KI.png",
    };
}

} // namespace Assets

#endif // ASSETS_H
