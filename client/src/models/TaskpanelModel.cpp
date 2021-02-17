#include "TaskpanelModel.h"

#include <qdebug.h>
#include <Client.h>

TaskPanelModel::TaskPanelModel(QObject *parent)
    : QAbstractListModel(parent) {
    Task t1;
    t1.title = QString("task %1").arg(m_model.size());
    t1.tags.append({"common", "feature", "high priority", "important"});
    m_model.append(t1);
    Task t2;
    t2.title = QString("task %1").arg(m_model.size());
    t2.tags.append({"common", "high priority", "important"});
    m_model.append(t2);
    Task t3;
    t3.title = QString("task %1").arg(m_model.size());
    t3.tags.append("important");
    m_model.append(t3);
    Task t4;
    t4.title = QString("task %1").arg(m_model.size());
    t4.tags.append("important");
    m_model.append(t4);

}

int TaskPanelModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;
    return m_model.size();
}

QVariant TaskPanelModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    switch(role) {
        case TitleRole: return m_model[index.row()].title;
        case TagsRole: return m_model[index.row()].tags;
//        case TagsRole: return QVariant::fromValue(m_model[index.row()].tags);
        case ColabsRole: return QVariant::fromValue(m_model[index.row()].workers);
        case BlankRole: return m_model[index.row()].blank;
//        case IconRole: return m_model[index.row()].m_colaborants;
//        case PanelModelRole: return m_model[index.row()].model;
    }
    // FIXME: Implement me!
    return QVariant();
}

bool TaskPanelModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags TaskPanelModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

bool TaskPanelModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
    return true;
}

bool TaskPanelModel::removeRows(int row, int count, const QModelIndex &parent) {
    beginRemoveRows(parent, row, row + count - 1);
    m_model.removeAt(row);
    endRemoveRows();
    return true;
}

QHash<int, QByteArray> TaskPanelModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "taskTitle";
    roles[TagsRole] = "tagsModel";
    roles[ColabsRole] = "WorkersModel";
    roles[IconRole] = "headerIcon";
    roles[BlankRole] = "isBlank";
    return roles;
}

void TaskPanelModel::move(int from, int to, int n) {
    if (from != to && from < m_model.size() && to < m_model.size()) {
        bool status = (from > to)
                ? beginMoveRows(QModelIndex(), from, from, QModelIndex(), to)
                : beginMoveRows(QModelIndex(), to, to, QModelIndex(), from);
        if (status) {
            m_model.swapItemsAt(from, to);

            endMoveRows();
        }
    }
}

void TaskPanelModel::test(int index) {
    if (blank_index == -1) {
        Task blankTask;
        blankTask.blank = true;
        beginInsertRows(QModelIndex(), index, index);
        m_model.insert(index, blankTask);
        blank_index = index;
        endInsertRows();
    }
    else if (index != blank_index && blank_index != -1) {
        move(blank_index, index, 1);
        blank_index = index;
    }
}

void TaskPanelModel::removeBlank() {
    for (int index = 0; index < m_model.size() && blank_index != -1; ++index) {
        if (m_model.at(index).blank) {
            beginRemoveRows(QModelIndex(), index, index);
            m_model.removeAt(index);
            blank_index = -1;
            endRemoveRows();
        }
    }
}

Task TaskPanelModel::getTask(int index) {
    qDebug() << "blank while get " << blank_index;
    beginRemoveRows(QModelIndex(), index, index);
    Task task = m_model.takeAt(index);
    endRemoveRows();
    return task;
}

void TaskPanelModel::setTask(int index, Task &task) {
    qDebug() << "blank while set up" << blank_index;
    removeBlank();
    insert(index, task);
}

void TaskPanelModel::reset() {
    beginRemoveRows(QModelIndex(), 0, m_model.size());
    endRemoveRows();

    beginInsertRows(QModelIndex(), 0, m_model.size());
    endInsertRows();
}

void TaskPanelModel::insert(const int &index, const Task &task) {
    beginInsertRows(QModelIndex(), index, index);
    m_model.insert(index, task);
    m_client->getTaskWorkers(task.id);
    endInsertRows();
}

Task &TaskPanelModel::at(const int &id) {
    foreach(auto &task, m_model) {
        if (task.id == id) {
            return const_cast<Task &>(task);
        }
    }
}


