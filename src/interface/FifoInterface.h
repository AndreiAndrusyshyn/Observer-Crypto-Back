#ifndef OCB_FIFOINTERFACE_H
#define OCB_FIFOINTERFACE_H

#include "../../include/includes.h"

class FifoInterface
{
public:
    static const constexpr char *kFIFODir = "fifo/";
protected:
    FifoInterface() : mFIFODescriptor(0) {};

    virtual const char *FIFOName() const = 0;

    virtual const char *FIFONameAnswer() const = 0;

    const string FIFOFilePath() const
    {
        return string(kFIFODir) + string(FIFOName());
    }

    const string FIFOFilePathAnswer() const
    {
        return string(kFIFODir) + string(FIFONameAnswer());
    }

    const bool ifFIFOExists() const
    {
        return fs::exists(fs::path(FIFOFilePath()));
    }

    const bool ifFIFOAnswerExists() const
    {
        return fs::exists(fs::path(FIFOFilePathAnswer()));
    }

    void createFIFO(unsigned int permissonMask)
    {
        if (!ifFIFOExists())
        {
            fs::create_directories(kFIFODir);

            if (mkfifo(FIFOFilePath().c_str(), permissonMask) != 0)
            {
                std::cout << "WRONG_1";// todo:  -> add ExceptionInterface
            }
        }
    }

    void createFIFOAnswer(unsigned int permissonMask)
    {
        if (!ifFIFOAnswerExists())
        {

            if (mkfifo(FIFOFilePathAnswer().c_str(), permissonMask) != 0)
            {
                std::cout << "WRONG_1";// todo:  -> add ExceptionInterface
            }
        }
    }

protected:
    int mFIFODescriptor;
};


#endif //OCB_FIFOINTERFACE_H
