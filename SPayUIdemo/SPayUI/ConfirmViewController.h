//
//  CheckOutProcessTableViewController.h
//  SPayUI
//
//  Created by RInz on 15/3/25.
//  Copyright (c) 2015年 BeeCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ConfirmTableViewCell.h"
#import "OptionalTableViewCell.h"
#import "CheckOutTableViewController.h"
#import "Goods.h"
#import "Optional.h"
#import "CustomInfo.h"

@interface ConfirmViewController : UIViewController<UITableViewDataSource, UITableViewDelegate, UIActionSheetDelegate>

@property (weak, nonatomic) IBOutlet UITableView *tableView;

@property (strong, nonatomic) NSMutableArray* checkoutData;
@property (strong, nonatomic) CustomInfo* customInfo;
@property double totalCost;

@end
