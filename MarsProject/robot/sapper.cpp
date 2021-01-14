#include "sapper.h"

namespace mars
{
    Sapper::Sapper()
    {

    }

    Point Sapper::getNearestBombCoords(const Point &) const
    {
        return m_repeater->getNearestBombCoords(m_localCoords);
    }

    Point Sapper::getLocalCoords() const
    {
        return m_localCoords;
    }

    void Sapper::setLocalCoords(const Point &coords)
    {
        m_localCoords = coords;
    }

    void Sapper::bindRepeater(Repeater *repeater)
    {
        m_repeater = repeater;
    }

    void Sapper::move(const Point &moveCoords)
    {
        m_localCoords = moveCoords;
    }

    void Sapper::defuse()
    {
        m_repeater->setBombDefused(true);                                                                               // говорим передатчику, что бомба была разминирована
        m_repeater->eraseBombCoords(m_localCoords);                                                                     // удаляем бомбу из вектора бомб
        m_repeater->addDefusedBombCoords(m_localCoords);
    }

    Repeater * Sapper::getRepeater()
    {
        return m_repeater;
    }

    bool Sapper::allBombsDefused() const
    {
        return m_repeater->allBombsDefused();
    }

    void Sapper::eraseBombCoords(const Point &coords)
    {
        m_repeater->eraseBombCoords(coords);
    }
}
