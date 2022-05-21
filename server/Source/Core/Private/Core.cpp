//
// Created by Artem Shemidko on 21.05.2022.
//

#include "Core.h"
#include "Application.h"

QString CommandPrompt::GetValue(const QString &Arg) {

    QString ArgValue;
    QStringList CommandArgs = Application::arguments();
    CommandArgs.removeFirst(); // remove application

    if (!CommandArgs.isEmpty())
    {
        QStringList PortFilter(CommandArgs.filter(Arg, Qt::CaseInsensitive));
        if (!PortFilter.isEmpty())
        {
            foreach(const QString &Argument, PortFilter) {
                QStringList ArgValuePair = Argument.split('=');

                if (ArgValuePair[0].endsWith(Arg, Qt::CaseInsensitive))
                {
                    ArgValue = ArgValuePair[1];
                }
            }
        }
    }
    return ArgValue;
}
