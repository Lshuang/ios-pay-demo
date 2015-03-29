//
//  ViewController.h
//  BeeCloudDemo
//
//  Created by RInz on 15/2/5.
//  Copyright (c) 2015年 RInz. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <BeeCloud/BeeCloud.h>
#import <BCAliPay/BCAliPay.h>
#import <BCWXPay/BCWXPay.h>
#import <BCUnionPay/BCUnionPay.h>

static NSString * const kBody = @"自制白开水";
static NSString * const kSubject = @"BeeCloud自制白开水";
static NSString * const kTraceID = @"BeeCloudSPay";
static NSString * const kRefundReason = @"不好喝";


@interface ViewController : UIViewController<UITableViewDataSource,UITableViewDelegate,UIAlertViewDelegate>

@property (weak, nonatomic) IBOutlet UISegmentedControl *paySegment;
@property (weak, nonatomic) IBOutlet UIButton *payButton;
@property (weak, nonatomic) IBOutlet UIButton *listButton;
@property (weak, nonatomic) IBOutlet UITableView *listTableView;
@property (strong,nonatomic) NSMutableArray *payList;
@property (weak, nonatomic) IBOutlet UILabel *listName;


@end

