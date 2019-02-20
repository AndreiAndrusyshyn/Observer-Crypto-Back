#include "InitInterface.h"

int InitInterface::run()
{
    initFileNameInterface();
    mFileNameInterface->beginAcceptFileNames();
    mIOService.run();
}

int InitInterface::initFileNameInterface()
{
    mFileNameInterface = make_unique<FileNameInterface>(mIOService);
}

InitInterface::~InitInterface(){};