#ifndef KANBANMODEL_H
#define KANBANMODEL_H

#include <QAbstractListModel>
#include <QList>

#include "taskpanelmodel.h"

struct Kanban {
    int index;
    QString title;
    TaskPanelModel *model;
};

class KanbanModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit KanbanModel(QObject *parent = nullptr);

    enum {
        TitleRole = Qt::UserRole,
        PanelModelRole,
        DragHeight,
    };

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

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void test(int index);
    Q_INVOKABLE void setHeight(int height);
    Q_INVOKABLE int getHeight();
    Q_INVOKABLE void removeBlank(int panelIndex);
    Q_INVOKABLE void swap(int sourcePanelIndex, int sourceTaskIndex, int targetPanelIndex, int targetTaskIndex);


private:
    QList<Kanban> m_model;
    int m_height;
};
Q_DECLARE_METATYPE(QModelIndex)
#endif // KANBANMODEL_H
