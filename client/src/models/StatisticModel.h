#ifndef STATISTICMODEL_H
#define STATISTICMODEL_H

#include <QAbstractListModel>
#include <QStandardItemModel>

struct Statistic {
    QString chartTitle;
    QStandardItemModel *m_model;
};

class StatisticModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit StatisticModel(QObject *parent = nullptr);

    enum {
        ChartTitleRole = Qt::UserRole,
        ChartDataRole,
        ChartEntityCountRole,
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    QHash<int, QByteArray> roleNames() const override;

private:
    QList<Statistic> m_data;
};

#endif // STATISTICMODEL_H
