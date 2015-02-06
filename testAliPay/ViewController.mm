//
//  ViewController.m
//  testAliPay
//
//  Created by JSen on 14/9/29.
//  Copyright (c) 2014年 wifitong. All rights reserved.
//

#import "ViewController.h"
#import "CommonUtil.h"
#import <BeeCloud/BeeCloud.h>

@interface ViewController ()

- (IBAction)WXPayAction:(UIButton *)sender;

@end

@implementation ViewController
@synthesize seg,payType;


#pragma mark - 微信支付


- (IBAction)WXPayAction:(UIButton *)sender {
   
    switch([seg selectedSegmentIndex]) {
            case 0:
            [self wxPayAction];
            break;
        case 1:
            [self aliPayment];
            break;
        case 2:
            [self unionPayment];
            break;
        default:
            break;
            
    }
    
}

- (void)viewDidLoad {
    [super viewDidLoad];
    self.edgesForExtendedLayout = UIRectEdgeNone;
    self.extendedLayoutIncludesOpaqueBars = YES;
    [self segValueChange:seg];
    _tableView.delegate = self;
    _tableView.dataSource = self;
    self.title = @"支付集成";
}

- (IBAction)segValueChange:(id)sender {
    UISegmentedControl *tseg = (UISegmentedControl *)sender;
    NSUInteger index = tseg.selectedSegmentIndex;
    if (index == 0) {
        [payType setTitle:@"微信支付" forState:UIControlStateNormal];
    } else {
        [payType setTitle:@"支付宝支付" forState:UIControlStateNormal];
    }
}

#pragma mark -
#pragma mark - 支付宝支付

- (void)UPPayPluginResult:(NSString *)result {
    NSLog(@"result = %@", result);
}
- (NSString *)generateTradeNO
{
    const int N = 15;
    
    NSString *sourceString = @"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    NSMutableString *result = [[NSMutableString alloc] init] ;
    srand(time(0));
    for (int i = 0; i < N; i++)
    {
        unsigned index = rand() % [sourceString length];
        NSString *s = [sourceString substringWithRange:NSMakeRange(index, 1)];
        [result appendString:s];
    }
    return result;
}

- (IBAction)onQueryOrder:(id)sender {
    _dataList = nil;
    _dataList = [NSMutableArray arrayWithArray:[self queryOrder:seg.selectedSegmentIndex]];
    [_tableView reloadData];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return _dataList.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *cellIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:cellIdentifier];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:cellIdentifier];
    }
    
    NSString * trade_status_key = (seg.selectedSegmentIndex==0)?@"trade_state":@"trade_status";
    cell.textLabel.text = [NSString stringWithFormat:@"%@支付金额:%@ 交易状态:%@", [[_dataList objectAtIndex:indexPath.row] objectForKey:@"trace_id"], [[_dataList objectAtIndex:indexPath.row] objectForKey:@"total_fee"], [[_dataList objectAtIndex:indexPath.row] objectForKey:trade_status_key]];
    
    [cell.textLabel setFont:[UIFont systemFontOfSize:13]];
    //total_fee out_trade_no
    cell.detailTextLabel.text = [NSString stringWithFormat:@"订单号:%@", [[_dataList objectAtIndex:indexPath.row] objectForKey:@"out_trade_no"]];
    return cell;

}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    if (seg.selectedSegmentIndex == 1) {
        if ([[_dataList[indexPath.row] objectForKey:@"trade_status"] isEqualToString:@"TRADE_SUCCESS"]) {
            [self refundForAli:[_dataList[indexPath.row] objectForKey:@"out_trade_no"]];
        }
    } else {
        if ([[_dataList[indexPath.row] objectForKey:@"trade_state"] integerValue] == 0) {
        [self wxRefundAction:[_dataList[indexPath.row] objectForKey:@"out_trade_no"]];
        }
    }
    
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
}

- (void)refundForAli:(NSString *)out_trade_no {
    NSDate *date = [NSDate date];
    NSDateFormatter * formatter = [[NSDateFormatter alloc] init];
    [formatter setDateFormat:@"yyyyMMddHHmmss"];
    NSString *dateString = [formatter stringFromDate:date];
    [BCPay reqAliRefund:out_trade_no refundNo:dateString refundFee:@"0.01" refundReason:@"不好喝" refundBlock:^(BOOL success, NSString *strMsg, NSError *error) {
        NSLog(@"AliRefund strMsg = %@", strMsg);
    }];
}

- (void)aliPayment {
    
    NSString *outTradeNo = [self generateTradeNO];
    [BCPay reqAliPayment:kTraceID outTradeNo:outTradeNo subject:@"薯片" body:@"品客薯片" totalFee:@"0.01" scheme:kAppScheme payBlock:^(BOOL success, NSString *strMsg, NSError *error) {
        NSLog(@"AliPay strMsg = %@", strMsg);
    }];
    
}

- (void)wxPayAction {
    [BCPay reqWXPayment:@"自制白开水" totalFee:@"1" outTradeNo:[self generateTradeNO] traceID:kTraceID payBlock:^(BOOL success, NSString *strMsg, NSError *error) {
        NSLog(@"%s strMsg = %@", __func__, strMsg);
    }];
}

- (void)wxRefundAction:(NSString *)outTradeNo {
    
    NSString *outRefundNo = [[BCUtil generateRandomUUID] stringByReplacingOccurrencesOfString:@"-" withString:@""];
    NSLog(@"refund no = %@", outRefundNo);
    [BCPay reqWXRefund:outTradeNo outRefundNo:outRefundNo refundReason:@"不好喝" refundFee:@"1" payBlock:^(BOOL success, NSString *errMsg, NSError *error) {
        NSLog(@"%s,%s,%d,%@", __FILE__, __func__, __LINE__, errMsg);
    }];
}
/*
 *随机生成15位订单号,外部商户根据自己情况生成订单号
 */
+ (NSString *)generateTradeNO
{
    const int N = 15;
    
    NSString *sourceString = @"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    NSMutableString *result = [[NSMutableString alloc] init];
    srand(time(0));
    for (int i = 0; i < N; i++)
    {
        unsigned index = rand() % [sourceString length];
        NSString *s = [sourceString substringWithRange:NSMakeRange(index, 1)];
        [result appendString:s];
    }
    return result;
}
- (NSArray *)queryOrder:(NSUInteger)index {
    NSArray *array = nil;
    if (index == 0) {
        array = [BCPay queryOrderByTraceID:kTraceID channel:BCWeChatPay action:BCPayActionPayment];
    } else {
        array = [BCPay queryOrderByTraceID:kTraceID channel:BCAliPay action:BCPayActionPayment];
    }
    return array;
}


#pragma mark - unionPay

- (void)unionPayment {
    [BCPay reqUnionPayment:@"BeeCloud" body:@"自制白开水" outTradeNo:[self generateTradeNO] totalFee:@"1" viewController:self payblock:^(BOOL success, NSString *strMsg, NSError *error) {
        NSLog(@"unionPay %s %@", __func__, strMsg);
    }];
}

@end
