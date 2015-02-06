//
//  ViewController.m
//  testAliPay
//
//  Created by JSen on 14/9/29.
//  Copyright (c) 2014年 wifitong. All rights reserved.
//

#import "ViewController.h"
#import "JSenPayEngine.h"


@interface ViewController ()

- (IBAction)payAction:(UIButton *)sender;
- (IBAction)WXPayAction:(UIButton *)sender;

@end

@implementation ViewController
@synthesize seg,payType;


#pragma mark - 微信支付


- (IBAction)WXPayAction:(UIButton *)sender {
   
    switch([seg selectedSegmentIndex]) {
            case 0:
        [[JSenPayEngine sharePayEngine] wxPayAction];
            break;
        case 1:
            [self testAliPay];
            break;
        case 2:
            [self testUnionPay];
        default:
            break;
            
    }
    
}

- (void)viewDidLoad {
    [super viewDidLoad];
    _result = @selector(paymentResult:);
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

- (void)testAliPay {
   
    NSString *orderId = [self generateTradeNO];
    NSDictionary *dict = @{
                           kOrderID:orderId,
                           kTotalAmount:@"0.01",
                           kProductDescription:@"3D打印VS无人机，谁在未来更赚钱？",
                           kProductName:@"自制白开水",
                           kNotifyURL:@"http://www.xxx.com"
                           };
    
    [JSenPayEngine paymentWithInfo:dict result:^(int statusCode, NSString *statusMessage, NSString *resultString, NSError *error, NSData *data) {
        NSLog(@"statusCode=%d \n statusMessage=%@ \n resultString=%@ \n err=%@ \n data=%@",statusCode,statusMessage,resultString,error,data);
    }];
}

- (void)testUnionPay {
    [JSenPayEngine unionPayment:self];
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
    _dataList = [NSMutableArray arrayWithArray:[JSenPayEngine queryOrder:seg.selectedSegmentIndex]];
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
            [JSenPayEngine refundForAli:[_dataList[indexPath.row] objectForKey:@"out_trade_no"]];
        }
    } else {
        if ([[_dataList[indexPath.row] objectForKey:@"trade_state"] integerValue] == 0) {
        [[JSenPayEngine sharePayEngine] wxRefundAction:[_dataList[indexPath.row] objectForKey:@"out_trade_no"]];
        }
    }
    
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
}
@end
