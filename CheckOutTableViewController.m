//
//  CheckOutTableViewController.m
//  SPayUI
//
//  Created by RInz on 15/3/27.
//  Copyright (c) 2015年 BeeCloud. All rights reserved.
//

#import "CheckOutTableViewController.h"
#import "SuccessViewController.h"

@interface CheckOutTableViewController ()

@end

@implementation CheckOutTableViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.tableView.backgroundColor = [UIColor colorWithRed:0.97 green:0.97 blue:0.97 alpha:1];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return 4;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    switch (indexPath.row) {
        case 0:
            [self aliPay];
            break;
        case 1:
            [self wxPay];
            break;
        case 2:
            [self unionPay];
            break;
        case 3:
            [self mmmPay];
            break;
        default:
            break;
    }
}

- (void)wxPay {
    int cost = round(self.totalCost *100.0);
    [BCWXPay reqWXPayV3:self.customInfo.subject totalFee:[NSString stringWithFormat:@"%d",cost] outTradeNo:self.customInfo.outTradeNo traceID:self.customInfo.traceID optional:self.customInfo.optional payBlock:^(BOOL success, NSString *strMsg, NSError *error) {
        if (success) {
            NSString * storyboardName = @"CheckOutProcess";
            NSString * viewControllerID = @"SuccessViewController";
            UIStoryboard * storyboard = [UIStoryboard storyboardWithName:storyboardName bundle:nil];
            SuccessViewController *successViewController = [storyboard instantiateViewControllerWithIdentifier:viewControllerID];
//            [self.navigationController presentViewController:successViewController animated:YES completion:nil];
            [self.navigationController pushViewController:successViewController animated:YES];
        } else {
            NSLog(strMsg);
            // 表明支付过程中出现错误，strMsg为错误原因
        }
        if (error) NSLog(@"%s,%s,%d,%@", __FILE__, __func__, __LINE__, error);
    }];
}

- (void)aliPay {
    [BCAliPay reqAliPayment:self.customInfo.traceID outTradeNo:self.customInfo.outTradeNo subject:self.customInfo.subject body:self.customInfo.body totalFee:[NSString stringWithFormat:@"%.2f",self.totalCost] scheme:self.customInfo.aliScheme optional:self.customInfo.optional payBlock:^(BOOL success, NSString *strMsg, NSError *error) {
        if (success) {
            NSString * storyboardName = @"CheckOutProcess";
            NSString * viewControllerID = @"SuccessViewController";
            UIStoryboard * storyboard = [UIStoryboard storyboardWithName:storyboardName bundle:nil];
            SuccessViewController *successViewController = [storyboard instantiateViewControllerWithIdentifier:viewControllerID];
//            [self.navigationController presentViewController:successViewController animated:YES completion:nil];
            [self.navigationController pushViewController:successViewController animated:YES];
        } else {
            // 表明支付过程中出现错误，strMsg为错误原因
        }
    }];
}

- (void)unionPay {
    int cost = round(self.totalCost *100.0);
    [BCUnionPay reqUnionPayment:self.customInfo.traceID body:self.customInfo.body outTradeNo:self.customInfo.outTradeNo totalFee:[NSString stringWithFormat:@"%d",cost] viewController:self optional:self.customInfo.optional payblock:^(BOOL success, NSString *strMsg, NSError *error) {
        if (success) {
            NSString * storyboardName = @"CheckOutProcess";
            NSString * viewControllerID = @"SuccessViewController";
            UIStoryboard * storyboard = [UIStoryboard storyboardWithName:storyboardName bundle:nil];
            SuccessViewController *successViewController = [storyboard instantiateViewControllerWithIdentifier:viewControllerID];
            [self.navigationController pushViewController:successViewController animated:YES];
        }else{
          
        }
    }];
}

- (void)mmmPay {
    [BCMMMPay reqMMMPay:@"183338" billNo:self.customInfo.outTradeNo amount:[NSString stringWithFormat:@"%.2f",self.totalCost] paymentType:@"" products:@"AppleNike" viewController:self payblock:^(BOOL success, NSString *strMsg, NSError *error) {
        if (success) {
            NSString * storyboardName = @"CheckOutProcess";
            NSString * viewControllerID = @"SuccessViewController";
            UIStoryboard * storyboard = [UIStoryboard storyboardWithName:storyboardName bundle:nil];
            SuccessViewController *successViewController = [storyboard instantiateViewControllerWithIdentifier:viewControllerID];
            [self.navigationController pushViewController:successViewController animated:YES];
        }else{
            NSLog(@"MMMPay Faild:%@",error.description);
        }
    }];
}




@end
