#include "WorkflowsModel.h"

WorkflowsModel::WorkflowsModel(QObject *parent)
    : QAbstractListModel(parent) {
    Workflow w1;
    w1.icon = "A";
    w1.title = "What is Lorem Ipsum?\n"
            "Lorem Ipsum is simply dummy text of the printing and typesetting industry.";
    w1.progress = 34;
    w1.colaborants = new ColaborantsModel(this);
    m_data.push_back(w1);
}

int WorkflowsModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;
    return m_data.size();
}

QVariant WorkflowsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    switch(role) {
        case IconRole: return m_data[index.row()].icon;
        case TitleRole: return m_data[index.row()].title;
        case ProgressRole: return m_data[index.row()].progress;
        case ColaborantsRole: return QVariant::fromValue(m_data[index.row()].colaborants);
    }
    return QVariant();
}

bool WorkflowsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags WorkflowsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

bool WorkflowsModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
}

bool WorkflowsModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
}

QHash<int, QByteArray> WorkflowsModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IconRole] = "flowIcon";
    roles[TitleRole] = "flowTitle";
    roles[ProgressRole] = "flowProgress";
    roles[ColaborantsRole] = "flowColaborants";
    return roles;
}

