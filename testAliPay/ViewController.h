//
//  ViewController.h
//  testAliPay
//
//  Created by JSen on 14/9/29.
//  Copyright (c) 2014年 wifitong. All rights reserved.
//

#import <UIKit/UIKit.h>

#define kTraceID @"BeeCloud"
#define kAppScheme @"payTestDemo"

@interface ViewController : UIViewController<UITableViewDataSource, UITableViewDelegate>
{
}

@property (strong, nonatomic) IBOutlet UISegmentedControl *seg;
@property (strong, nonatomic) IBOutlet UITableView *tableView;
- (IBAction)onQueryOrder:(id)sender;
@property (strong, nonatomic) IBOutlet UIButton *payType;
@property (nonatomic, strong) NSMutableArray *dataList;

@end

