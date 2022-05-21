//#include "server.h"
//#include "database.h"

#include "Application.h"
#include "CryptoSSL.h"
#include "Server.h"

void Init()
{
    // Initialize required systems
    Crypto::Initialize(ApplicationContext::ConfigLocation, SSLFile);
    Server::Initialize();

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
