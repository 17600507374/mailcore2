//
//  MCOIMAPFetchMessagesOperation.m
//  mailcore2
//
//  Created by DINH Viêt Hoà on 3/25/13.
//  Copyright (c) 2013 MailCore. All rights reserved.
//

#import "MCOIMAPFetchMessagesOperation.h"

#include "MCAsyncIMAP.h"

#import "MCOOperation+Private.h"
#import "MCOUtils.h"

typedef void (^completionType)(NSError *error, NSArray * messages, MCOIndexSet * vanishedMessages);

@implementation MCOIMAPFetchMessagesOperation {
    completionType _completionBlock;
}

#define nativeType mailcore::IMAPFetchMessagesOperation

+ (void) load
{
    MCORegisterClass(self, &typeid(nativeType));
}

+ (NSObject *) mco_objectWithMCObject:(mailcore::Object *)object
{
    nativeType * op = (nativeType *) object;
    return [[[self alloc] initWithMCOperation:op] autorelease];
}

- (void) dealloc
{
    [_completionBlock release];
    [super dealloc];
}

- (void)start:(void (^)(NSError *error, NSArray * messages, MCOIndexSet * vanishedMessages))completionBlock {
    _completionBlock = [completionBlock copy];
    [self start];
}

- (void)operationCompleted {
    nativeType *op = MCO_NATIVE_INSTANCE;
    if (op->error() == mailcore::ErrorNone) {
        _completionBlock(nil, MCO_TO_OBJC(op->messages()), MCO_TO_OBJC(op->vanishedMessages()));
    } else {
        _completionBlock([NSError mco_errorWithErrorCode:op->error()], nil, nil);
    }
}

- (void) itemProgress:(unsigned int)current maximum:(unsigned int)maximum
{
    _progress(current);
}

@end
