//
//  BCMMMPay.h
//  BCMMMPay
//
//  Created by 钱志浩 on 15/5/22.
//  Copyright (c) 2015年 BeeCloud. All rights reserved.
//1

#import <UIKit/UIKit.h>
#import <BeeCloud/BeeCloud.h>

//! Project version number for BCMMMPay.
FOUNDATION_EXPORT double BCMMMPayVersionNumber;

//! Project version string for BCMMMPay.
FOUNDATION_EXPORT const unsigned char BCMMMPayVersionString[];


@interface BCMMMPay : NSObject

+ (void)reqMMMPay:(NSString *)merNo
           billNo:(NSString *)billNo
           amount:(NSString *)amount
      paymentType:(NSString *)paymentType
         products:(NSString *)products
   viewController:(UIViewController *)viewController
         payblock:(BCPayBlock)block ;

@end
