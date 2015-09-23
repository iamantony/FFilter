#include "medaggregoperator.h"

#include <QDebug>

int MedAggregOperator::Calc(const QList<double>& t_list)
{
    if ( t_list.isEmpty() )
    {
        qDebug() << __FUNCTION__ << "Error - list is empty";
        return 0;
    }

    QList<double> values = t_list;
    qSort(values);

    int meanInd = values.size() / 2;
    int moduloInd = values.size() % 2;
    double summ = 0.0;
    if ( 0 == moduloInd )
    {
        // there are an even number of values
        summ += values.at(meanInd - 1);
        summ += values.at(meanInd);
        summ /= 2;
    }
    else
    {
        // there are an odd number of values
        summ = values.at(meanInd);
    }

    return ResultToInt(summ);
}
