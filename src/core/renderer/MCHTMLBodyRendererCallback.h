//
//  MCHTMLBodyRendererCallback.h
//  mailcore2
//
//  Created by Paul Young on 02/07/2013.
//  Copyright (c) 2013 MailCore. All rights reserved.
//

#ifndef __MAILCORE_MCHTMLBODYRENDERERCALLBACK_H_

#define __MAILCORE_MCHTMLBODYRENDERERCALLBACK_H_

#include <MailCore/MCHTMLRendererCallback.h>

#ifdef __cplusplus

namespace mailcore {
        
    class HTMLBodyRendererTemplateCallback : public HTMLRendererTemplateCallback {
        virtual String * templateForMainHeader(MessageHeader * header);
    };
    
}

#endif

#endif
