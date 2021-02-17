#include "WorkflowsModel.h"

#include "qdebug.h"
#include "Client.h"

WorkflowsModel::WorkflowsModel(QObject *parent)
    : QAbstractListModel(parent) {
//    Workflow w1;
//    w1.deadline = "A";
//    w1.title = "What is Lorem Ipsum?\n"
//            "Lorem Ipsum is simply dummy text of the printing and typesetting industry.";
//    w1.progress = 34;
//    w1.colaborants = new ColaborantsModel(this);
//    m_data.push_back(w1);
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
        case IdRole: return m_data[index.row()].id;
        case DeadlineRole: return m_data[index.row()].deadline;
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

bool WorkflowsModel::insertRows(int row, int count, const QModelIndex &parent) {


    beginInsertRows(parent, row, row + count - 1);

    endInsertRows();
    return true;
}

bool WorkflowsModel::removeRows(int row, int count, const QModelIndex &parent) {
    beginRemoveRows(parent, row, row + count - 1);
    delete m_data.at(row).colaborants;
    m_data.removeAt(row);
    qDebug() << "removing";
    endRemoveRows();
//    return true;
}

QHash<int, QByteArray> WorkflowsModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdRole] = "flowId";
    roles[DeadlineRole] = "flowDeadline";
    roles[TitleRole] = "flowTitle";
    roles[ProgressRole] = "flowProgress";
    roles[ColaborantsRole] = "flowColaborants";
    return roles;
}

void WorkflowsModel::add(const Workflow &flow) {
    beginInsertRows(QModelIndex(), 0, 0);
    m_data.prepend(flow);
    m_client->getWorkflowColaborants(flow.id);
    endInsertRows();
}

void WorkflowsModel::archive(int id) {
    for (int index = 0; index < rowCount(); ++index) {
        if (m_data[index].id == id) {
            removeRows(index, 1);
        }
    }
}

void WorkflowsModel::addColaborant(quint64 index, const Colaborant &contact) {
    foreach (auto &flow, m_data) {
        if (flow.id == index) {
            flow.colaborants->add(contact);
            break;
        }
    }
}

void WorkflowsModel::updateWorkflow(const Workflow &workflow) {
    for (int index = 0; index < rowCount(); ++index) {
        if (m_data[index].id == workflow.id) {
            m_data[index].title = workflow.title;
            m_data[index].progress = workflow.progress;
            m_data[index].deadline = workflow.deadline;

            emit dataChanged(this->index(index, 0), this->index(index, 0));
            break;
        }
    }

}
