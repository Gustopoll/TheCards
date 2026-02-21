#include "game.h"

#include "src/Drawing/Entities/drawingentity.h"

#include <memory>
#include <QDebug>

Game::Game()
{
    std::shared_ptr<QImage> a = std::make_shared<QImage>();
    qDebug() << a->load("Data/Cards/A-0A.png");

    std::vector<std::shared_ptr<QImage>> vec;

    for (const auto item : {'A', 'B', 'H', 'L'})
    {
        auto& a = vec.emplace_back(std::make_shared<QImage>());
        a->load(std::format("Data/Cards/{}-0A.png", item).c_str());

        auto& b = vec.emplace_back(std::make_shared<QImage>());
        b->load(std::format("Data/Cards/{}-07.png", item).c_str());

        auto& c = vec.emplace_back(std::make_shared<QImage>());
        c->load(std::format("Data/Cards/{}-08.png", item).c_str());

        auto& d = vec.emplace_back(std::make_shared<QImage>());
        d->load(std::format("Data/Cards/{}-09.png", item).c_str());

        auto& e = vec.emplace_back(std::make_shared<QImage>());
        e->load(std::format("Data/Cards/{}-10.png", item).c_str());

        auto& f = vec.emplace_back(std::make_shared<QImage>());
        f->load(std::format("Data/Cards/{}-J1.png", item).c_str());

        auto& g = vec.emplace_back(std::make_shared<QImage>());
        g->load(std::format("Data/Cards/{}-J2.png", item).c_str());

        auto& h = vec.emplace_back(std::make_shared<QImage>());
        h->load(std::format("Data/Cards/{}-KI.png", item).c_str());
    }

}
