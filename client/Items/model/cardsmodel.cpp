#include "cardsmodel.h"

CardsModel::CardsModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

QVariant CardsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

bool CardsModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (value != headerData(section, orientation, role)) {
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}

int CardsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_cards.size();
}

QVariant CardsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == TitleRole)
//        return m_cards[index.row()].getTitle();
    if (role == IdRole)
//        return m_cards[index.row()].getId();
        return 0;
    return QVariant();
}

bool CardsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        if (role == TitleRole)
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags CardsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

bool CardsModel::insertRows(int row, int count, const QModelIndex &parent)
{
    // request to insert Cards
    beginInsertRows(parent, row, row + count - 1);
//    Card newCard{this};
    int newCard;
    m_cards.insert(row, count, newCard);
    endInsertRows();
    return /*response is true*/count < rowCount() || row < rowCount();
}

bool CardsModel::removeRows(int row, int count, const QModelIndex &parent)
{
    // request to remove Cards
    beginRemoveRows(parent, row, row + count - 1);
    m_cards.remove(row, count);
    endRemoveRows();
    return /*response is true*/count < rowCount() || row < rowCount();
}

QHash<int, QByteArray> CardsModel::roleNames() const
{
    QHash<int, QByteArray> roleName;
    roleName[TitleRole] = "text";
    roleName[IdRole] = "idCard";
    return  roleName;
}
