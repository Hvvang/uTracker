#ifndef CHECKBOXPROPERTYMODEL_H
#define CHECKBOXPROPERTYMODEL_H

#include <QAbstractListModel>
#include <QJsonObject>

struct Checkbox {
    bool done = false;
    QString description = "";
};

class CheckboxPropertyModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit CheckboxPropertyModel(QObject *parent = nullptr);

    enum {
        IsDoneRole = Qt::UserRole,
        DescriptionRole,
    };

    static QVariant QVariantFromJson(const QJsonArray &json);
    QJsonArray toJsonArray();

    // Basic functionality:
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

    QHash<int, QByteArray> roleNames() const;
    QVector<Checkbox> &model();

    Q_INVOKABLE void addItem();
    Q_INVOKABLE void removeItem(const int &index);

private:
    QVector<Checkbox> m_data;

};

#endif // CHECKBOXPROPERTYMODEL_H
