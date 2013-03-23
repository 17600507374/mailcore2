//
//  MCOAddress.m
//  mailcore2
//
//  Created by DINH Viêt Hoà on 3/10/13.
//  Copyright (c) 2013 MailCore. All rights reserved.
//

#import "MCOAddress.h"
#import "MCOAddress+Private.h"

#include <typeinfo>

#include "MCAddress.h"
#include "NSString+MCO.h"
#include "NSObject+MCO.h"

@implementation MCOAddress {
    mailcore::Address * _nativeAddress;
}

+ (void) initialize
{
    MCORegisterClass(self, &typeid(mailcore::Address));
}

+ (NSObject *) mco_objectWithMCObject:(mailcore::Object *)object
{
    mailcore::Address * address = (mailcore::Address *) object;
    return [[[self alloc] initWithMCAddress:address] autorelease];
}

+ (MCOAddress *) addressWithDisplayName:(NSString *)displayName
                                mailbox:(NSString *)mailbox
{
    MCOAddress * result = [[[MCOAddress alloc] init] autorelease];
    MC_SAFE_RELEASE(result->_nativeAddress);
    result->_nativeAddress = mailcore::Address::addressWithDisplayName([displayName mco_mcString], [mailbox mco_mcString]);
    result->_nativeAddress->retain();
    return result;
}

+ (MCOAddress *) addressWithMailbox:(NSString *)mailbox
{
    MCOAddress * result = [[[MCOAddress alloc] init] autorelease];
    MC_SAFE_RELEASE(result->_nativeAddress);
    result->_nativeAddress = mailcore::Address::addressWithMailbox([mailbox mco_mcString]);
    result->_nativeAddress->retain();
    return result;
}

+ (MCOAddress *) addressWithRFC822String:(NSString *)RFC822String
{
    MCOAddress * result = [[[MCOAddress alloc] init] autorelease];
    MC_SAFE_RELEASE(result->_nativeAddress);
    result->_nativeAddress = mailcore::Address::addressWithRFC822String([RFC822String mco_mcString]);
    result->_nativeAddress->retain();
    return result;
}

+ (MCOAddress *) addressWithNonEncodedRFC822String:(NSString *)nonEncodedRFC822String
{
    MCOAddress * result = [[[MCOAddress alloc] init] autorelease];
    MC_SAFE_RELEASE(result->_nativeAddress);
    result->_nativeAddress = mailcore::Address::addressWithNonEncodedRFC822String([nonEncodedRFC822String mco_mcString]);
    result->_nativeAddress->retain();
    return result;
}

- (id) init
{
    self = [super init];
    
    _nativeAddress = new mailcore::Address();
    
    return self;
}

- (id) initWithMCAddress:(mailcore::Address *)address
{
    self = [super init];
    
    _nativeAddress = address;
    _nativeAddress->retain();
    
    return self;
}

+ (MCOAddress *) addressWithMCAddress:(mailcore::Address *)address
{
    if (address == NULL)
        return nil;
    
    return [[[self alloc] initWithMCAddress:address] autorelease];
}

- (void) dealloc
{
    MC_SAFE_RELEASE(_nativeAddress);
    [super dealloc];
}

- (id) copyWithZone:(NSZone *)zone
{
    mailcore::Address * address = (mailcore::Address *) _nativeAddress->copy();
    MCOAddress * result = [[MCOAddress alloc] initWithMCAddress:address];
    MC_SAFE_RELEASE(address);
    return result;
}

- (NSString *) description
{
    return [NSString mco_stringWithMCObject:_nativeAddress];
}

- (NSString *) displayName
{
    return [NSString mco_stringWithMCString:_nativeAddress->displayName()];
}

- (void) setDisplayName:(NSString *)displayName
{
    _nativeAddress->setDisplayName([displayName mco_mcString]);
}

- (NSString *) mailbox
{
    return [NSString mco_stringWithMCString:_nativeAddress->mailbox()];
}

- (void) setMailbox:(NSString *)mailbox
{
    _nativeAddress->setMailbox([mailbox mco_mcString]);
}

- (NSString *) RFC822String
{
    return [NSString mco_stringWithMCString:_nativeAddress->RFC822String()];
}

- (NSString *) nonEncodedRFC822String
{
    return [NSString mco_stringWithMCString:_nativeAddress->nonEncodedRFC822String()];
}

- (mailcore::Object *) mco_mcObject
{
    return _nativeAddress;
}

@end
