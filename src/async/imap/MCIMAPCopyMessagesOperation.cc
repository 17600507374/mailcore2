//
//  MCIMAPCopyMessagesOperation.cc
//  mailcore2
//
//  Created by DINH Viêt Hoà on 1/12/13.
//  Copyright (c) 2013 MailCore. All rights reserved.
//

#include "MCIMAPCopyMessagesOperation.h"

#include "MCIMAPSession.h"
#include "MCIMAPAsyncSession.h"

using namespace mailcore;

IMAPCopyMessagesOperation::IMAPCopyMessagesOperation()
{
    mUids = NULL;
    mDestFolder = NULL;
    mDestUids = NULL;
}

IMAPCopyMessagesOperation::~IMAPCopyMessagesOperation()
{
    MC_SAFE_RELEASE(mDestUids);
    MC_SAFE_RELEASE(mUids);
    MC_SAFE_RELEASE(mDestFolder);
}

void IMAPCopyMessagesOperation::setUids(Array * uids)
{
    MC_SAFE_REPLACE_RETAIN(Array, mUids, uids);
}

Array * IMAPCopyMessagesOperation::uids()
{
    return mUids;
}

Array * IMAPCopyMessagesOperation::destUids()
{
    return mDestUids;
}

void IMAPCopyMessagesOperation::setDestFolder(String * destFolder)
{
    MC_SAFE_REPLACE_COPY(String, mDestFolder, destFolder);
}

String * IMAPCopyMessagesOperation::destFolder()
{
    return mDestFolder;
}

void IMAPCopyMessagesOperation::main()
{
    ErrorCode error;
    session()->session()->copyMessages(folder(), mUids, mDestFolder, &mDestUids, &error);
    MC_SAFE_RETAIN(mDestUids);
    setError(error);
}
