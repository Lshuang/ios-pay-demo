//
//  CustomInfo.h
//  SPayUI
//
//  Created by RInz on 15/3/27.
//  Copyright (c) 2015年 BeeCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CustomInfo : NSObject

@property (strong, nonatomic) NSString *body;
@property (strong, nonatomic) NSString *subject;
@property (strong, nonatomic) NSString *traceID;
@property (strong, nonatomic) NSString *outTradeNo;
@property (strong, nonatomic) NSDictionary *optional;
@property (strong, nonatomic) NSString* aliScheme;

@end
