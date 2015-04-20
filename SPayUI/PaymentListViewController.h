//
//  PaymentListViewController.h
//  SPayUI
//
//  Created by RInz on 15/4/16.
//  Copyright (c) 2015年 BeeCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <BeeCloud/BeeCloud.h>
#import <BCAliPay/BCAliPay.h>
#import <BCWXPay/BCWXPay.h>
#import <BCUnionPay/BCUnionPay.h>

@interface PaymentListViewController : UIViewController<UITableViewDataSource, UITableViewDelegate>

@property (weak, nonatomic) IBOutlet UISegmentedControl *paySegment;
@property (weak, nonatomic) IBOutlet UITableView *listTableView;
@property (strong,nonatomic) NSMutableArray *payList;

@end
