//
// Created by Artem Shemidko on 15.05.2022.
//

#ifndef SERVER_TASK_H
#define SERVER_TASK_H

template<class ContextT>
class BaseTask {
public:
    BaseTask(const ContextT &InContext)
        : Context(&InContext) {}

    virtual ~BaseTask() = 0;

    virtual void DoWork() = 0;
    virtual void DoTask() = 0;

private:
    const ContextT *Context;
};


#endif //SERVER_TASK_H
