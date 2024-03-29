#include "TaskpanelModel.h"

#include <qdebug.h>
#include <Client.h>

TaskPanelModel::TaskPanelModel(QObject *parent)
    : QAbstractListModel(parent) {
}

int TaskPanelModel::rowCount(const QModelIndex &parent) const
{
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
        case ColabsRole: return QVariant::fromValue(m_model[index.row()].workers);
        case BlankRole: return m_model[index.row()].blank;
        case IconRole: return "";
        case IdRole: return m_model[index.row()].id;
        case WorkStatusRole: return m_model[index.row()].mine;
        case DoneRole: return m_model[index.row()].isDone;
    }
    return QVariant();
}

bool TaskPanelModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
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
    m_model.erase(m_model.begin() + row);
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
    roles[IdRole] = "taskId";
    roles[WorkStatusRole] = "workStatus";
    roles[DoneRole] = "doneStatus";
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

void TaskPanelModel::addBlank(int index) {
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
            m_model.erase(m_model.begin() + index);
            blank_index = -1;
            endRemoveRows();
        }
    }
}

Task TaskPanelModel::getTask(int index) {
    beginRemoveRows(QModelIndex(), index, index);
    Task task = m_model.takeAt(index);
    endRemoveRows();
    return task;
}

void TaskPanelModel::setTask(int index, Task &task) {
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
    endInsertRows();
}

Task &TaskPanelModel::at(const int &id) {
    foreach(auto &task, m_model) {
        if (task.id == id) {
            return const_cast<Task &>(task);
        }
    }
}

bool TaskPanelModel::contains(const int &taskId) const {
    foreach(auto &task, m_model) {
        if (task.id == taskId) {
            return true;
        }
    }
    return false;
}

void TaskPanelModel::rename(const int &taskId, const QString &title) {
    auto &task = at(taskId);
    task.title = title;
    emit dataChanged(index(task.index, 0), index(task.index, 0));
}

void TaskPanelModel::update(const int &taskId, const QString &title, const QStringList &tags) {
    auto &task = at(taskId);
    task.title = title;
    task.tags = tags;
    emit dataChanged(index(task.index, 0), index(task.index, 0));
}

void TaskPanelModel::incrementTaskIndex(const int &from) {
    for (int i = from; i < m_model.size(); ++i) {
        m_model[i].index++;
    }
}

void TaskPanelModel::decrementTaskIndex(const int &from) {
    for (int i = from; i < m_model.size(); ++i) {
        m_model[i].index--;
    }
}

void TaskPanelModel::remove(const int &taskId) {
        for (int index = 0; index < m_model.size(); ++index) {
            if (m_model.at(index).id == taskId) {
                removeRows(index, 1);
                return;
            }
        }
}

void TaskPanelModel::setStatus(const int &taskId, const bool &status) {
    for (int i = 0; i < m_model.size(); ++i) {
        auto &task = m_model[i];
        if (task.id == taskId) {
            task.mine = status;
            const auto &profile = m_client->profile();
            if (status) {
                Colaborant c;
                c.id = profile.id;
                c.surname = profile.surname;
                c.name = profile.name;
                c.icon = profile.name.front();
                task.workers->add(c);
            } else {
                task.workers->remove(profile.id);
            }
            emit dataChanged(index(i), index(i));
            return;
        }
    }
}

void TaskPanelModel::setDoneStatus(const int &taskId, const bool &status) {
    for (int i = 0; i < m_model.size(); ++i) {
        auto &task = m_model[i];
        if (task.id == taskId) {
            task.isDone = status;
            emit dataChanged(index(i), index(i));
            return;
        }
    }
}

void TaskPanelModel::updateView(const int &taskId) {
    for (int i = 0; i < m_model.size(); ++i) {
        auto &task = m_model[i];
        if (task.id == taskId) {
            emit dataChanged(index(i), index(i));
        }
    }
}







