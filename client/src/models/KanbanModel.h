#ifndef KANBANMODEL_H
#define KANBANMODEL_H

#include <QAbstractListModel>
#include <QList>

#include "TaskpanelModel.h"

struct Kanban {
    int index;
    int id;
    QString title;
    TaskPanelModel *model = new TaskPanelModel;
};

class KanbanModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit KanbanModel(const int &workflowId, QObject *parent = nullptr);

    int getWorkflow() const;
    void setWorkflow(int workflowId);
    void reset();
    void insertPanel(const Kanban &kanban);

    Kanban &at(int panelId);

    enum {
        TitleRole = Qt::UserRole,
        IDRole,
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

    Q_INVOKABLE int flowId();
    Q_INVOKABLE void setHeight(int height);
    Q_INVOKABLE int getHeight();
    Q_INVOKABLE void removeBlank(int panelIndex);
    Q_INVOKABLE void swap(int sourcePanelIndex, int sourceTaskIndex, int targetPanelIndex, int targetTaskIndex);

    void rename(const int &panelIndex, const QString &title);

    [[nodiscard]] bool contains(const int &panelId) const;
    void moveTask(const int &taskId, const int &fromPanel, const int &fromIndex, const int &toPanel, const int &toIndex);

private:
    QList<Kanban> m_model;
    int m_workflowId;
    int m_height;
};
Q_DECLARE_METATYPE(QModelIndex)
#endif // KANBANMODEL_H
