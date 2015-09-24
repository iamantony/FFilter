#ifndef CBLISTMODEL_H
#define CBLISTMODEL_H

#include <QAbstractListModel>
#include <QModelIndex>
#include <QVariant>
#include <QList>
#include <QPair>
#include <QString>

// Template model for QComboBox-es that show variants of
// AggregOperator::Type or AggregOperator::Func.
template<typename T>
class CBListModel : public QAbstractListModel
{
    // == METHODS ==
public:
    explicit CBListModel(QObject* t_parent = 0) :
        QAbstractListModel(t_parent) {}
    virtual ~CBListModel() {}

    // Init function. Call it after object creation
    void init()
    {
        qDebug() << __FUNCTION__ << "No implementation";
    }

    virtual QVariant data(const QModelIndex& t_index,
                          int t_role = Qt::DisplayRole ) const
    {
        if (t_index.isValid() &&
            t_role == Qt::DisplayRole &&
            false == m_data.isEmpty())
        {
            return m_data.at(t_index.row()).second;
        }

        return QVariant();
    }

    virtual int	rowCount(const QModelIndex& t_parent = QModelIndex()) const
    {
        Q_UNUSED(t_parent);
        return m_data.size();
    }

    // Return corresponding type for specified string
    // @input:
    // - t_str - string that have corresponding type in this model
    // @output:
    // - T - corresponding type. If we can't find corresponding type for
    // specified string, then function will return default-constructed type.
    T getType(const QString& t_str) const
    {
        for (int i = 0; i < m_data.size(); ++i)
        {
            if (m_data.at(i).second == t_str)
            {
                return m_data.at(i).first;
            }
        }

        return T();
    }

    // Get index of specified type
    // @input:
    // - t_key - specified type
    // @output:
    // - int - index of the type. If model don't have such type, function will
    // return 0.
    int getIndex(const T& t_key) const
    {
        for (int i = 0; i < m_data.size(); ++i)
        {
            if (m_data.at(i).first == t_key)
            {
                return i;
            }
        }

        return 0;
    }

    // == DATA ==
private:
    QList< QPair<T, QString> > m_data;
};

#endif // CBLISTMODEL_H
