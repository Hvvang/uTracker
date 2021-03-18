#include "ColaborantsModel.h"

#include "qdebug.h"

ColaborantsModel::ColaborantsModel(QObject *parent)
    : QAbstractListModel(parent) {

}

int ColaborantsModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;
    return qMin<int>(m_data.size(), 4);
}

QVariant ColaborantsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    switch(role) {
        case IconRole: return m_data[index.row()].icon;
        case NameRole: return m_data[index.row()].name;
        case SurnameRole: return m_data[index.row()].surname;
    }
    return QVariant();
}

bool ColaborantsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags ColaborantsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

bool ColaborantsModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    endInsertRows();
    return true;
}

bool ColaborantsModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    m_data.removeAt(row);
    endRemoveRows();
    return true;
}


QHash<int, QByteArray> ColaborantsModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IconRole] = "colaborantIcon";
    roles[NameRole] = "colaborantName";
    roles[SurnameRole] = "colaborantSurname";
    return roles;
}

void ColaborantsModel::add(const Colaborant &contact) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data.push_back(contact);
    endInsertRows();
}

void ColaborantsModel::remove(const int &colabId) {
    for (int i = 0; i < m_data.size(); ++i) {
        if (m_data.at(i).id == colabId) {
            removeRows(i, 1);
            return;
        }
    }
}

