//
//  MCIMAPCheckAccountOperation.h
//  mailcore2
//
//  Created by DINH Viêt Hoà on 1/12/13.
//  Copyright (c) 2013 MailCore. All rights reserved.
//

#ifndef __mailcore2__MCIMAPCheckAccountOperation__
#define __mailcore2__MCIMAPCheckAccountOperation__

#include <mailcore/MCIMAPOperation.h>

namespace mailcore {
    
    class IMAPCheckAccountOperation : public IMAPOperation {
    private:
        
    public:
        virtual void main();
    };
}

#endif /* defined(__mailcore2__MCIMAPCheckAccountOperation__) */
