#ifndef OCB_INITINTERFACE_H
#define OCB_INITINTERFACE_H

#include "../../../src/interface/FileNameInterface/FileNameInterface.cpp"

class InitInterface
{
public:
    int run();
    int initFileNameInterface();
    ~InitInterface();
protected:
    as::io_service mIOService;
    unique_ptr<FileNameInterface> mFileNameInterface;

};


#endif //OCB_INITINTERFACE_H
