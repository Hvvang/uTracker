#include "DailyPlanModel.h"
#include <qdebug.h>

DailyPlanModel::DailyPlanModel(QObject *parent)
        : QAbstractListModel(parent) { }

int DailyPlanModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;
    return m_data.size();
}

QVariant DailyPlanModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    switch(role) {
        case IdRole:
            return m_data[index.row()].id;
        case DescriptionRole:
            return m_data[index.row()].title;
        case StatusRole:
            return m_data[index.row()].status;
    }
    return QVariant();
}

bool DailyPlanModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags DailyPlanModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

bool DailyPlanModel::insertRows(int row, int count, const QModelIndex &parent) {
    beginInsertRows(parent, row, row + count - 1);

    endInsertRows();
//    return true;
}

bool DailyPlanModel::removeRows(int row, int count, const QModelIndex &parent) {
    beginRemoveRows(parent, row, row + count - 1);
    m_data.erase(m_data.begin() + row);
    endRemoveRows();
//    return true;
}

QHash<int, QByteArray> DailyPlanModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdRole] = "dailyTaskId";
    roles[DescriptionRole] = "dailyTaskDescription";
    roles[StatusRole] = "dailyTaskStatus";
    return roles;
}

void DailyPlanModel::push_back(const DailyTask &task) {
    beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.push_back(task);
    endInsertRows();
}

void DailyPlanModel::update(const int &taskId, const QString &desc, const bool &status)
{
    for (int i = 0; i < m_data.size(); ++i) {
        auto &task = m_data[i];
        if (task.id == taskId) {
            task.title = desc;
            task.status = status;
            emit dataChanged(index(i), index(i));
            break;
        }
    }
}

void DailyPlanModel::remove(const int &taskId)
{
    for (int i = 0; i < m_data.size(); ++i) {
        auto &task = m_data[i];
        if (task.id == taskId) {
            removeRows(i, 1);
            break;
        }
    }
}

void DailyPlanModel::reset() {
    if (m_data.size()) {
        beginResetModel();
        m_data.clear();
        endResetModel();
    }

}
