#ifndef ITERATOR_H
#define ITERATOR_H

#include <QWidget>
#include "iterable.h"

class Iterator: public Iterable
{
public:
    Iterator(QVector <int> inputCities);
    void apply();
    void solve();

protected:
    QVector <int> cities;
};

Iterator::Iterator(QVector <int> inputCities)
{
    cities = inputCities;
}

#endif // ITERATOR_H
