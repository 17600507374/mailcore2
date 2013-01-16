#include "MCOperationQueue.h"

#include "MCOperation.h"
#include "MCOperationCallback.h"
#include "MCMainThread.h"
#include "MCUtils.h"
#include "MCArray.h"
#include "MCLog.h"
#include "MCAutoreleasePool.h"
#include <libetpan/libetpan.h>

using namespace mailcore;

OperationQueue::OperationQueue()
{
	mOperations = new Array();
	mStarted = false;
    //sem_init(&mOperationSem, 0, 0);
    //sem_init(&mStartSem, 0, 0);
    //sem_init(&mStopSem, 0, 0);
    pthread_mutex_init(&mLock, NULL);
    mWaiting = false;
    //sem_init(&mWaitingFinishedSem, 0, 0);
    mOperationSem = mailsem_new();
    mStartSem = mailsem_new();
    mStopSem = mailsem_new();
    mWaitingFinishedSem = mailsem_new();
}

OperationQueue::~OperationQueue()
{
    MC_SAFE_RELEASE(mOperations);
    //sem_destroy(&mOperationSem);
    //sem_destroy(&mStartSem);
    //sem_destroy(&mStopSem);
    pthread_mutex_destroy(&mLock);
    //sem_destroy(&mWaitingFinishedSem);
    mailsem_free(mOperationSem);
    mailsem_free(mStartSem);
    mailsem_free(mStopSem);
    mailsem_free(mWaitingFinishedSem);
}

void OperationQueue::addOperation(Operation * op)
{
    pthread_mutex_lock(&mLock);
    mOperations->addObject(op);
    pthread_mutex_unlock(&mLock);
    //sem_post(&mOperationSem);
    mailsem_up(mOperationSem);
    startThread();
}

void OperationQueue::runOperationsOnThread(OperationQueue * queue)
{
    queue->runOperations();
}

void OperationQueue::runOperations()
{
    MCLog("start thread");
    //sem_post(&mStartSem);
    mailsem_up(mStartSem);
    
    while (true) {
        Operation * op = NULL;
        bool needsCheckRunning = false;

        AutoreleasePool * pool = new AutoreleasePool();
        
        //int value = 0;
        //int r;
        
        //r = sem_getvalue(&mOperationSem, &value);
        //MCLog("x before sem %i %i", value, r);
        //sem_wait(&mOperationSem);
        mailsem_down(mOperationSem);
        //sem_getvalue(&mOperationSem, &value);
        //MCLog("x after sem %i", value);
        
        pthread_mutex_lock(&mLock);
        if (mOperations->count() > 0) {
            op = (Operation *) mOperations->objectAtIndex(0);
        }
        pthread_mutex_unlock(&mLock);

        if (op == NULL) {
            //sem_post(&mStopSem);
            mailsem_up(mStopSem);
            pool->release();
            break;
        }

        op->main();
        
        if (op->callback() != NULL) {
            performMethodOnMainThread((Object::Method) &OperationQueue::callbackOnMainThread, op, true);
        }
        
        pthread_mutex_lock(&mLock);
        mOperations->removeObjectAtIndex(0);
        if (mOperations->count() == 0) {
            if (mWaiting) {
                //sem_post(&mWaitingFinishedSem);
                mailsem_up(mWaitingFinishedSem);
            }
            needsCheckRunning = true;
        }
        pthread_mutex_unlock(&mLock);
        
        if (needsCheckRunning) {
            retain(); // (1)
            performMethodOnMainThread((Object::Method) &OperationQueue::checkRunningOnMainThread, this);
        }
        
        pool->release();
    }
    MCLog("cleanup thread");
}

void OperationQueue::callbackOnMainThread(Operation * op)
{
    if (op->callback() != NULL) {
        op->callback()->operationFinished(op);
    }
}

void OperationQueue::checkRunningOnMainThread(void * context)
{
    performMethodAfterDelay((Object::Method) &OperationQueue::checkRunningAfterDelay, NULL, 1);
}

void OperationQueue::checkRunningAfterDelay(void * context)
{
    bool quitting = false;
    
    pthread_mutex_lock(&mLock);
    if (mOperations->count() == 0) {
        //sem_post(&mOperationSem);
        mailsem_up(mOperationSem);
        quitting = true;
    }
    pthread_mutex_unlock(&mLock);
    
    // Number of operations can't be changed because it runs on main thread.
    // And addOperation() should also be called from main thread.
    
    if (quitting) {
        //sem_wait(&mStopSem);
        mailsem_down(mStopSem);
        mStarted = false;
    }
    
    release(); // (1)
}

void OperationQueue::startThread()
{
    if (mStarted)
        return;
    
    mStarted = true;
    pthread_create(&mThreadID, NULL, (void * (*)(void *)) OperationQueue::runOperationsOnThread, this);
    //sem_wait(&mStartSem);
    mailsem_down(mStartSem);
}

#if 0
void OperationQueue::waitUntilAllOperationsAreFinished()
{
    bool waiting = false;
    
    pthread_mutex_lock(&mLock);
    if (mOperations->count() > 0) {
        mWaiting = true;
        waiting = true;
    }
    pthread_mutex_unlock(&mLock);
    
    if (waiting) {
        sem_wait(&mWaitingFinishedSem);
    }
    mWaiting = false;
}
#endif
