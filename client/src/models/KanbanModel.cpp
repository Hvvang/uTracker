#include "KanbanModel.h"

#include <qdebug.h>

KanbanModel::KanbanModel(QObject *parent)
    : QAbstractListModel(parent)
{
    Kanban k1;
    k1.index = m_model.size();
    k1.title = "ToDo";
    k1.model = new TaskPanelModel(this);
    Kanban k2;
    k2.index = m_model.size();
    k2.title = "In Progress";
    k2.model = new TaskPanelModel(this);
    Kanban k3;
    k3.index = m_model.size();
    k3.title = "Done";
    k3.model = new TaskPanelModel(this);

    m_model.append(k1);
    m_model.append(k2);
    m_model.append(k3);

}

int KanbanModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_model.size();
}

QVariant KanbanModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    switch(role) {
        case TitleRole: return m_model[index.row()].title;
        case PanelModelRole: return QVariant::fromValue(m_model[index.row()].model);
    }
    // FIXME: Implement me!
    return QVariant();
}

bool KanbanModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags KanbanModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

bool KanbanModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
}

bool KanbanModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);

    // FIXME: Implement me!
    endRemoveRows();
}

QHash<int, QByteArray> KanbanModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "panelTitle";
    roles[PanelModelRole] = "panelModel";
    roles[DragHeight] = "dragHeight";
    return roles;
}

void KanbanModel::test(int index) {
    m_model.at(index).model->reset();

}

void KanbanModel::setHeight(int height) {
    m_height = height;
}

int KanbanModel::getHeight() {
    return m_height;
}

void KanbanModel::removeBlank(int panelIndex) {
    if (panelIndex < m_model.size()) {
        m_model.at(panelIndex).model->removeBlank();
    }
}

void KanbanModel::swap(int sourcePanelIndex, int taskIndex, int targetPanelIndex, int targetTaskIndex) {

    auto sourceTask = m_model.at(sourcePanelIndex).model->getTask(taskIndex);
    m_model.at(targetPanelIndex).model->setTask(targetTaskIndex, sourceTask);

}