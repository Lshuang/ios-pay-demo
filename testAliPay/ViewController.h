//
//  ViewController.h
//  testAliPay
//
//  Created by JSen on 14/9/29.
//  Copyright (c) 2014年 wifitong. All rights reserved.
//

#import <UIKit/UIKit.h>
//#import "AlixLibService.h"

@interface Product : NSObject
{
    float _price;
    NSString *_subject;
    NSString *_body;
    NSString *_orderId;
}

@property (nonatomic, assign) float price;
@property (nonatomic, copy) NSString *subject;
@property (nonatomic, copy) NSString  *body;
@property (nonatomic, copy) NSString  *orderId;

@end

@interface ViewController : UIViewController<UITableViewDataSource, UITableViewDelegate>
{
    NSMutableArray *_products;
    SEL _result;
}

@property (nonatomic, assign) SEL result;
- (void)paymentResult:(NSString *)result;
@property (strong, nonatomic) IBOutlet UISegmentedControl *seg;
@property (strong, nonatomic) IBOutlet UITableView *tableView;
- (IBAction)onQueryOrder:(id)sender;
@property (strong, nonatomic) IBOutlet UIButton *payType;

@property (nonatomic, strong) NSMutableArray *dataList;

@end

