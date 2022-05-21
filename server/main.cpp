//#include "server.h"
//#include "database.h"

#include <Core.h>
#include "Application.h"
#include "CryptoSSL.h"
#include "Server.h"

void Init()
{
    // Initialize required systems
    Crypto::Initialize(ApplicationContext::ConfigLocation, SSLFile);
    Server::Initialize(CommandPrompt::GetValue("-port").toInt());

}

void Deinit()
{

}

int main(int argc, char *argv[]) {
    Application App(argc, argv);

    App.Context().OnApplicationStart = &Init;
    App.Context().OnApplicationExit = &Deinit;

    return App.Run();
}
