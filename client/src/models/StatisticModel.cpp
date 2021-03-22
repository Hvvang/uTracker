#include "StatisticModel.h"

StatisticModel::StatisticModel(QObject *parent)
    : QAbstractListModel(parent) {
    Statistic s1;
    Statistic s2;
    Statistic s3;
    s1.chartTitle = "Workflows` statistic";
    s2.chartTitle = "Kanbans` statistic";
    s3.chartTitle = "Daily plans` statistic";
    s1.m_model = new QStandardItemModel(3, 4);
    QStringList labels;
    labels << "" << "In Progress" << "Over late" << "Done";

    for (int column = 0; column < s1.m_model->columnCount(); column++) {
        QStandardItem *item1 = new QStandardItem(QString::number(column));
        QStandardItem *item2 = new QStandardItem(QString(labels[column]));
        QStandardItem *item3 = new QStandardItem(QString::number(column*column));

        s1.m_model->setItem(0, column, item1);
        s1.m_model->setItem(1, column, item2);
        s1.m_model->setItem(2, column, item3);
    }

    s2.m_model = new QStandardItemModel(3, 4);
    for (int column = 0; column < s2.m_model->columnCount(); column++) {
        QStandardItem *item1 = new QStandardItem(QString::number(column));
        QStandardItem *item2 = new QStandardItem(QString(labels[column]));
        QStandardItem *item3 = new QStandardItem(QString::number(column*column + column));

        s2.m_model->setItem(0, column, item1);
        s2.m_model->setItem(1, column, item2);
        s2.m_model->setItem(2, column, item3);
    }

    s3.m_model = new QStandardItemModel(3, 4);
    for (int column = 0; column < s3.m_model->columnCount(); column++) {
        QStandardItem *item1 = new QStandardItem(QString::number(column));
        QStandardItem *item2 = new QStandardItem(QString(labels[column]));
        QStandardItem *item3 = new QStandardItem(QString::number(column*column - column));

        s3.m_model->setItem(0, column, item1);
        s3.m_model->setItem(1, column, item2);
        s3.m_model->setItem(2, column, item3);
    }

    m_data.push_back(s1);
    m_data.push_back(s2);
    m_data.push_back(s3);
}

int StatisticModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;
    return m_data.size();
}

QVariant StatisticModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    switch (role) {
        case ChartTitleRole:
            return m_data.at(index.row()).chartTitle;
        case ChartDataRole:
            return QVariant::fromValue<QStandardItemModel *>(m_data.at(index.row()).m_model);
        case ChartEntityCountRole:
            return m_data.at(index.row()).m_model->rowCount();
    }
    return QVariant();
}

bool StatisticModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags StatisticModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

bool StatisticModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    endInsertRows();
}

bool StatisticModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    endRemoveRows();
}

QHash<int, QByteArray> StatisticModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[ChartTitleRole] = "chartTitle";
    roles[ChartDataRole] = "chartSeries";
    roles[ChartEntityCountRole] = "entityChartCount";
    return roles;
}