//
//  Goods.h
//  SPayUI
//
//  Created by RInz on 15/3/24.
//  Copyright (c) 2015年 BeeCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Goods : NSObject

@property (strong, nonatomic) NSString* goodImage;
@property (strong, nonatomic) NSMutableAttributedString* goodDescription;
@property (strong, nonatomic) NSString* goodPrice;
@property int count;
@property double price;

@end
