#ifndef __MAILCORE_MCOPERATION_H_

#define __MAILCORE_MCOPERATION_H_

#include <pthread.h>
#include <mailcore/MCObject.h>

#ifdef __cplusplus

namespace mailcore {

	class OperationCallback;

	class Operation : public Object {
	public:
		Operation();
		virtual ~Operation();
		
		virtual void setCallback(OperationCallback * callback);
		virtual OperationCallback * callback();
		
		virtual void cancel();
		virtual bool isCancelled();
		
		virtual void main();
        
	private:
		OperationCallback * mCallback;
		bool mCancelled;
		pthread_mutex_t mLock;
		
	};
	
}

#endif

#endif
