#include "DailyPlanModel.h"

DailyPlanModel::DailyPlanModel(QObject *parent)
    : QAbstractListModel(parent)
{}


int DailyPlanModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;
    return m_data.size();
}

QVariant DailyPlanModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    switch(role) {
        case DescriptionRole: return m_data[index.row()].title;
        case StatusRole: return m_data[index.row()].status;
        case IdRole: return m_data[index.row()].id;
    }
    return QVariant();
}

QHash<int, QByteArray> DailyPlanModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[DescriptionRole] = "taskDescription";
    roles[StatusRole] = "taskStatus";
    roles[IdRole] = "taskId";
    return roles;
}

void DailyPlanModel::push_back(const dailyTask &task)
{
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
            beginRemoveRows(QModelIndex(), i, i);
            m_data.removeAt(i);
            endRemoveRows();
            break;
        }
    }
}


