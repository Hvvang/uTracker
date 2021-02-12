#include "ColaborantsModel.h"

#include "qdebug.h"

ColaborantsModel::ColaborantsModel(QObject *parent)
    : QAbstractListModel(parent)
{
    Colaborant c1;
    c1.icon = 'A';
    m_data.push_back(c1);
    Colaborant c2;
    c2.icon = 'A' + m_data.size();
    m_data.push_back(c2);
    Colaborant c3;
    c3.icon = 'A' + m_data.size();
    m_data.push_back(c3);
    Colaborant c4;
    c4.icon = 'A' + m_data.size();
    m_data.push_back(c4);
    Colaborant c5;
    c5.icon = 'A' + m_data.size();
    m_data.push_back(c5);

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
        case IconRole: qDebug() << "m_data[index.row()].icon is " << m_data[index.row()].icon; return m_data[index.row()].icon;
        case NameRole: return m_data[index.row()].name;
        case SurnameRole: return m_data[index.row()].surname;
        case StatusRole: return m_data[index.row()].status;
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
    // FIXME: Implement me!
    endInsertRows();
}

bool ColaborantsModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
}


QHash<int, QByteArray> ColaborantsModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IconRole] = "colaborantIcon";
    roles[NameRole] = "colaborantName";
    roles[SurnameRole] = "colaborantSurname";
    roles[StatusRole] = "colaborantStatus";
    return roles;
}

int ColaborantsModel::hidden() {
    return m_data.size() - 4;
}
