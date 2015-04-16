//
//  ShoppingCartTableViewController.h
//  SPayUI
//
//  Created by RInz on 15/3/24.
//  Copyright (c) 2015年 BeeCloud. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ShoppingCartTableViewController : UIViewController<UITableViewDataSource, UITableViewDelegate>

@property (weak, nonatomic) IBOutlet UITableView *tableView;
@property (strong, nonatomic) NSMutableArray *tableData;

@end
