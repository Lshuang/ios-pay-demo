//
//  CheckOutTableViewController.h
//  SPayUI
//
//  Created by RInz on 15/3/27.
//  Copyright (c) 2015年 BeeCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <BeeCloud/BeeCloud.h>
#import <BCAliPay/BCAliPay.h>
#import <BCWXPay/BCWXPay.h>
#import <BCUnionPay/BCUnionPay.h>
#import <BCMMMPay/BCMMMPay.h>
#import "CustomInfo.h"
#import <BCMMMPay/BCMMMPayViewController.h>

@interface CheckOutTableViewController : UITableViewController

@property (weak, nonatomic) IBOutlet UIBarButtonItem *totalCostLabel;
@property (strong, nonatomic) IBOutlet UITableView *tableView;
@property (strong, nonatomic) CustomInfo* customInfo;
@property double totalCost;
@property (strong, nonatomic) NSArray* goodsInfo;


@end
