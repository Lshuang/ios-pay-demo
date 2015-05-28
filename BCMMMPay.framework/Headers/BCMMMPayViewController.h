//
//  BCMMMPayViewController.h
//  BCMMMPay
//
//  Created by 钱志浩 on 15/5/25.
//  Copyright (c) 2015年 BeeCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <BeeCloud/BeeCloud.h>

@interface BCMMMPayViewController : UIViewController<UIWebViewDelegate>

@property(nonatomic, strong) BCPayBlock block;
@property(nonatomic, strong) NSString * URLString;

@end
