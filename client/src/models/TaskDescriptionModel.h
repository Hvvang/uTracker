#ifndef TASKDESCRIPTIONMODEL_H
#define TASKDESCRIPTIONMODEL_H

#include <QAbstractListModel>
#include <QJsonObject>



struct Description {
    int type; // 0: string; 1: date; 2: checkboxes, 3: tags
    QString property;
    QString str;
    QString date;
    QStringList tags;
    QStringList checkboxesText;
    QStringList checkboxesValue;
};

class TaskDescriptionModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit TaskDescriptionModel(const QJsonObject &json, QObject *parent = nullptr);

    enum {
        PropertyRole = Qt::UserRole,
        TypeRole,
        StrRole,
        DateRole,
        CheckBoxRole,
        CheckBoxStatus,
        CheckBoxesCountRole,
        TagsRole,
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    QHash<int, QByteArray> roleNames() const override;

private:
    QVector<Description> m_data;

};

#endif // TASKDESCRIPTIONMODEL_H
