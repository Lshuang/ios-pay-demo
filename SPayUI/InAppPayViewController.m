//
//  InAppPayViewController.m
//  SPayUI
//
//  Created by RInz on 15/4/17.
//  Copyright (c) 2015年 BeeCloud. All rights reserved.
//

#import "InAppPayViewController.h"

@implementation InAppPayViewController

@synthesize starCount;

- (void)viewDidLoad {
    [[BCIAPay sharedInstance]initProducts:@[@"spayui_starstar"] withBlock:nil];
    self.starCount = 0;
}

- (IBAction)InAppPay:(id)sender {
    [[BCIAPay sharedInstance]purchase:[BCIAPay sharedInstance].products[0] traceID:@"BeeCloudSPay" withBlock:^(NSString *productId, NSInteger state, NSError *error) {
        if (state ==0) {
            self.starNumberLabel.text = @"我有1颗星星";
        }
        else {
            NSLog([NSString stringWithFormat:@"state: %d, error:%@",state, error.description]);
        }
    }];
}

- (IBAction)InAppRestore:(id)sender {
    [[BCIAPay sharedInstance]restore:@[@"spayui_starstar"] traceID:@"BeeCloudSPay" withBlock:^(NSString *productId, NSInteger state, NSError *error) {
        if (state == 2) {
            self.starNumberLabel.text = @"我有1颗星星";
        }else {
         NSLog([NSString stringWithFormat:@"state: %d, error:%@",state, error.description]);
     }
    }];
}


@end
