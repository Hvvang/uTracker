#ifndef DAILYPLANMODEL_H
#define DAILYPLANMODEL_H

#include <QAbstractListModel>

struct dailyTask {
    int id;
    QString title = "Untitled";
    bool status = false;
};

class DailyPlanModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit DailyPlanModel(QObject *parent = nullptr);
    enum {
        DescriptionRole = Qt::UserRole,
        StatusRole,
        IdRole,
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

   void push_back(const dailyTask &task);
   void update(const int &taskId, const QString &desc, const bool &status);
   void remove(const int &taskId);

private:
    QList<dailyTask> m_data;
};

#endif // DAILYPLANMODEL_H
