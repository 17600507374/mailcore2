//
//  MCOAbstractMessagePart.h
//  mailcore2
//
//  Created by DINH Viêt Hoà on 3/10/13.
//  Copyright (c) 2013 MailCore. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <mailcore/MCOAbstractPart.h>

@class MCOMessageHeader;

@interface MCOAbstractMessagePart : MCOAbstractPart

@property (nonatomic, retain) MCOMessageHeader * header;
@property (nonatomic, retain) MCOAbstractPart * mainPart;

@end
