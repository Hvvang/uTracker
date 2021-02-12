#ifndef COLABORANTSMODEL_H
#define COLABORANTSMODEL_H

#include <QAbstractListModel>

struct Colaborant {
    quint64 id;
    QString name;
    QString surname;
    QChar icon;
    bool status;
};

class ColaborantsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum {
        IconRole = Qt::UserRole,
        NameRole,
        SurnameRole,
        StatusRole,
    };
    explicit ColaborantsModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

     QHash<int, QByteArray> roleNames() const override;

     Q_INVOKABLE int hidden();

private:
    QList<Colaborant> m_data;

};

#endif // COLABORANTSMODEL_H
